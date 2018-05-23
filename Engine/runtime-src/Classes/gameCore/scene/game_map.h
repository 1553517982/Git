#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <stdlib.h>
#include "supports/utils/stream/stream.h"

/*************************************************************
*		地图数据读取后将不保存用于显示的图片编号等数据，而仅仅
*	保存用于进行逻辑处理的点阵数据——使用一个字节表示一个坐标。
*	当坐标数据的值为1的时候，表示该坐标可以移动，否则表示该
*	坐标不可移动。
*
************************************************************/

//当前地图版本号
const unsigned int MapFileVersion_Current = 0x0102;
//不可移动标记
const unsigned int MAPFLAG_MOVEABLE = 0x8000;
//遮挡标记
const unsigned int MAPFLAG_SHIELD = 0x4000;

/*
 * 地图文件头结构
 */
#define NEW_VER
typedef struct tagMapFileHeader
{
#ifdef NEW_VER
	unsigned int	version_;		//文件版本0x0101
	int		width_;			//地图宽度
	int		height_;		//地图高度
	int		bg_img_;	//地图背景图片编号
	unsigned int	data_size_;		//地图坐标数据段字节长度
	unsigned char	reseve_[32];
#else
	unsigned int	indent_;		//文件头标识，固定为0x004D584A
	unsigned int	version_;		//文件版本，固定为0x000A0B0F
	int		width_;			//地图宽度
	int		height_;		//地图高度
	int		bg_img_;	//地图背景图片编号
	unsigned int	data_size_;		//地图坐标数据段字节长度
	unsigned char	reseve_[40];
#endif
} MAPFILE_HEADER;

// 地图网格的结构
typedef struct tagMapGrid
{
	unsigned short	bg_img_;		// 背景图片编号
	unsigned short	ft_img_;		// 前景图片编号
	unsigned short	flag_;			// 地图坐标标志位		包括障碍和遮挡
	unsigned char	obj_root_;		// 素材分类索引			地图包命名
	unsigned char	reseve_;		// 图片类型				jpg or png

	unsigned short	effect_id_;		// 地图的特效id
	unsigned short  width_;			// 特效的宽度
	unsigned short  height_;		// 特效的高度
} MAPGrid;


class GameMapInfo
{
protected:
	unsigned int	width_;						// 地图宽度 (tile count)
	unsigned int	height_;					// 地图高度 (tile count)
	unsigned int	width_in_pixel_;			// 地图宽度 (pixel)
	unsigned int	height_in_pixel_;			// 地图高度 (pixel)
	int*			moveable_index_;			// 每坐标对应的可移动索引，主要是用于省内存的优化，暂时没使用到
	int				moveable_count_;			// 移动坐标数量
	MAPGrid*		map_grid_;					// 格子信息
	
public:
	GameMapInfo();
	virtual ~GameMapInfo();

	/* 从流中加载地图数据 */
	bool LoadFromStream(stream::BaseStream& stream);
	/* 从文件中加载地图数据 */
	bool LoadFromFile(const char* fn);
	/* 从字节加载地图数据(主要是因为cocos2d接口直接把文件的字节都读取了) */
	bool LoadFromChar(unsigned char* buffer, const unsigned long size);

	/* 生成一张全部可以移动的地图 */
	void initDefault(unsigned int w, unsigned int h);
	/* 公有释放函数 */
	void release();

	/* 获取地图宽度 (tile count) */
	inline int getWidth()
	{
		return width_;
	}
	/* 获取地图高度 (tile count) */
	inline int getHeight()
	{
		return height_;
	}
	/* 获取地图宽度 (pixel) */
	inline int getWidthInPixel()
	{
		return width_in_pixel_;
	}
	/* 获取地图宽度 (pixel) */
	inline int getHeightInPixel()
	{
		return height_in_pixel_;
	}
	/* 获取可移动坐标数量 */
	inline int getMoveableCount()
	{
		return moveable_count_;
	}

	/* 获取地图中所有单元数目 */
	inline int getUnitCount() const
	{
		return width_ * height_;
	}

	inline int getPosIndex(unsigned int x, unsigned int y)
	{
		if (x >= width_ || y >= height_)
			return -1;

		return y * width_ + x;
	}

	/* 判断地图中x, y坐标位置是否可以移动，返回true表示坐标可以移动 */
	inline bool canMove(unsigned int x, unsigned int y)
	{
		if (!moveable_index_ || x >= width_ || x < 0 || y >= height_ || y < 0)
			return false;

		return moveable_index_[y * width_ + x] != -1;
	}

	/* 判断地图中x, y坐标位置是否为遮挡 */
	inline bool isShield(unsigned int x, unsigned int y)
	{
		if (x >= width_ || x < 0 || y >= height_ || y < 0)
			return false;

		return (getGridInfo(x, y)->flag_ & MAPFLAG_SHIELD) != 0;
	}

	int getMapPosValue(unsigned int x, unsigned int y)
	{
		if (x >= width_ || y >= height_)
			return -1;

		return moveable_index_[y * width_ + x] != -1 ? 0 : -1;
	}

	MAPGrid* getGridInfo(unsigned int x, unsigned int y)
	{
		if (x >= width_ || y >= height_)
			return NULL;

		return &map_grid_[y * width_ + x];
	}
};


#endif


