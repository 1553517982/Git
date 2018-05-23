#include <zlib.h>
#include <stdlib.h>
#include "utils/stream/stream.h"
#include "utils/stream/zstream.h"
#include "game_map.h"
#include "CCFileUtils.h"
#include "XGameScene.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "XCommon.h"

using namespace stream;
using namespace zstream;
using namespace cocos2d;

static alloc_func zalloc = (alloc_func)0;
static free_func zfree = (free_func)0;

void _check_deflate_error(int err, const char* msg)
{
	if (err != Z_OK){
		XLOGERROR("%s error: %d\n", msg, err);
	}
}


/* ===========================================================================
* 测试deflate()：使用大缓冲区和动态改变的压缩级别
*/
uLong do_deflate(Byte * compr, uLong comprLen, Byte * uncompr, uLong uncomprLen)
{
	z_stream c_stream; /* 压缩流 */
	int err;

	/* 这三个字段要在defalteInit之前初始化 */
	c_stream.zalloc = zalloc;
	c_stream.zfree = zfree;
	c_stream.opaque = (voidpf)0;

	/* 初始化压缩流的状态，使用最快速度压缩 */
	err = deflateInit(&c_stream, Z_BEST_COMPRESSION);
	_check_deflate_error(err, "deflateInit");

	c_stream.next_out = compr;
	c_stream.avail_out = (uInt)comprLen;

	/* 这里，uncompr几乎都为0，因此可以很好地被压缩 */
	c_stream.next_in = uncompr;
	c_stream.avail_in = (uInt)uncomprLen;
	err = deflate(&c_stream, Z_NO_FLUSH); /* 压缩输入数据 */
	_check_deflate_error(err, "deflate");
	if (c_stream.avail_in != 0) {
		fprintf(stderr, "deflate not greedy\n");
		exit(1);
	}
	/* 流刷新，产生全部压缩输出 */
	err = deflate(&c_stream, Z_FINISH);
	if (err != Z_STREAM_END) {
		fprintf(stderr, "deflate should report Z_STREAM_END\n");
		exit(1);
	}
	uLong outSize = c_stream.total_out;
	err = deflateEnd(&c_stream);  /* 释放流的资源 */
	_check_deflate_error(err, "deflateEnd");
	return outSize;
}


GameMapInfo::GameMapInfo()
	:width_(0)
	,height_(0)
	,width_in_pixel_(0)
	,height_in_pixel_(0)
	,moveable_index_(NULL)
	,moveable_count_(0)
	,map_grid_(NULL)
{
}

GameMapInfo::~GameMapInfo()
{
	release();
}


bool GameMapInfo::LoadFromStream(BaseStream& stream)
{
	/*
	MAPFILE_HEADER hdr;
	MAPGrid* map_grid, *grid_ptr;

	//��ȡ������ļ�ͷ
	if (stream.read(&hdr, sizeof(hdr)) != sizeof(hdr))
		return false;

	if (hdr.version_ != MapFileVersion_Current)
		return false;

	//int mytest = sizeof(MAPGrid);
	//��ѹ�������������ݶζ�ȡ���ڴ���
	MemoryStream ms;
	ms.copyFrom(stream, hdr.data_size_);
	ms.setPosition(0);

	//���ڴ����д�����ѹ�����Ա��ѹ��������
	ZDecompressionStream deStream(ms);

	size_t grid_count = sizeof(MAPGrid) * hdr.width_ * hdr.height_;

	grid_ptr = map_grid = (MAPGrid*)malloc(grid_count);

	if (grid_count != (const size_t)deStream.read(map_grid, (const int)grid_count))
		return false;

	//���ɳ���Ҷȵ�ͼ
	int max = hdr.width_ * hdr.height_;

	moveable_ount_ = 0;
	int* index_ptr = moveable_index_ = (int*)realloc(moveable_index_, max * sizeof(*index_ptr));
	memset(index_ptr, -1, max * sizeof(*index_ptr));		// �����memset����ֵ��������

	for (int i = 0; i < max; ++i)
	{
		if ((grid_ptr->flag_ & MAPFLAG_MOVEABLE) != 0)
		{
			(*index_ptr) = moveable_ount_;
			moveable_ount_++;
		}

		index_ptr++;
		grid_ptr++;
	}

	//�����ͼ����Լ��߶�����
	width_ = hdr.width_;
	height_ = hdr.height_;

	free(map_grid);
	*/
	return true;
}

bool GameMapInfo::LoadFromChar(unsigned char* buffer, const unsigned long size)
{
	MAPFILE_HEADER hdr;
	MAPGrid* grid_ptr;

	MemoryStream ms;
	ms.copyFromChar((char*)buffer, size);
	ms.setPosition(0);

	if (ms.read(&hdr, sizeof(hdr)) != sizeof(hdr))
		return false;

	if (hdr.version_ != MapFileVersion_Current)
		return false;

	MemoryStream ms1;
	ms1.copyFrom(ms, hdr.data_size_);
	ms1.setPosition(0);

	ZDecompressionStream deStream(ms1);

	size_t grid_count = sizeof(MAPGrid) * hdr.width_ * hdr.height_;

	//Shan Lu Begin 2013/09/14
	if (map_grid_)
		free(map_grid_);
	map_grid_ = NULL;
	//Shan Lu End 2013/09/14

	grid_ptr = map_grid_ = (MAPGrid*)malloc(grid_count);

	if (grid_count != (const size_t)deStream.read(map_grid_, (const int)grid_count))
		return false;

	int max = hdr.width_ * hdr.height_;

	moveable_count_ = 0;
	int* index_ptr = moveable_index_ = (int*)realloc(moveable_index_, max * sizeof(*index_ptr));
	memset(index_ptr, -1, max * sizeof(*index_ptr));

	for (int i = 0; i < max; ++i)
	{
		if ((grid_ptr->flag_ & MAPFLAG_MOVEABLE) != 0)
		{
			(*index_ptr) = moveable_count_;
			moveable_count_++;
		}

		index_ptr++;
		grid_ptr++;
	}
	
	width_			= hdr.width_;
	height_			= hdr.height_;
	width_in_pixel_	= width_  * XGameScene::s_logicTileWidth; // LOGIC_TILE_WIDTH;
	height_in_pixel_= height_ * XGameScene::s_logicTileHeight;// LOGIC_TILE_HEIGHT;
	return true;
}

bool GameMapInfo::LoadFromFile(const char* fn)
{
	//std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fn);
	//Data data = FileUtils::getInstance()->getDataFromFile(fullPath);
	release();
	char * pBuffer;
	unsigned int nSize;
	if (!cocos2d::CNewLoader::Inst().SyncLoadFile(fn, &pBuffer, &nSize))
	{
		if (map_grid_)
			free(map_grid_);
		map_grid_ = NULL;
		if (moveable_index_)
			free(moveable_index_);
		moveable_index_ = NULL;
		return false;
	}
	
	return LoadFromChar( (unsigned char*)pBuffer, nSize );
}

void GameMapInfo::initDefault(unsigned int w, unsigned int h)
{
	int max = w * h;

	moveable_count_ = 0;
	int* index_ptr = moveable_index_ = (int*)realloc(moveable_index_, max * sizeof(*index_ptr));

	for (int i = 0; i < max; ++i)
	{
		(*index_ptr) = moveable_count_;
		moveable_count_++;
		index_ptr++;
	}

	width_ = w;
	height_ = h;
}

void GameMapInfo::release()
{
	if (moveable_index_)
	{
		free(moveable_index_);
		moveable_index_ = 0;
	}

	if (map_grid_)
	{
		free(map_grid_);
		map_grid_ = 0;
	}
}
