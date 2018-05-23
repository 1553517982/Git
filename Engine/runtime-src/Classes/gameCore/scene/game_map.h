#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <stdlib.h>
#include "supports/utils/stream/stream.h"

/*************************************************************
*		��ͼ���ݶ�ȡ�󽫲�����������ʾ��ͼƬ��ŵ����ݣ�������
*	�������ڽ����߼�����ĵ������ݡ���ʹ��һ���ֽڱ�ʾһ�����ꡣ
*	���������ݵ�ֵΪ1��ʱ�򣬱�ʾ����������ƶ��������ʾ��
*	���겻���ƶ���
*
************************************************************/

//��ǰ��ͼ�汾��
const unsigned int MapFileVersion_Current = 0x0102;
//�����ƶ����
const unsigned int MAPFLAG_MOVEABLE = 0x8000;
//�ڵ����
const unsigned int MAPFLAG_SHIELD = 0x4000;

/*
 * ��ͼ�ļ�ͷ�ṹ
 */
#define NEW_VER
typedef struct tagMapFileHeader
{
#ifdef NEW_VER
	unsigned int	version_;		//�ļ��汾0x0101
	int		width_;			//��ͼ���
	int		height_;		//��ͼ�߶�
	int		bg_img_;	//��ͼ����ͼƬ���
	unsigned int	data_size_;		//��ͼ�������ݶ��ֽڳ���
	unsigned char	reseve_[32];
#else
	unsigned int	indent_;		//�ļ�ͷ��ʶ���̶�Ϊ0x004D584A
	unsigned int	version_;		//�ļ��汾���̶�Ϊ0x000A0B0F
	int		width_;			//��ͼ���
	int		height_;		//��ͼ�߶�
	int		bg_img_;	//��ͼ����ͼƬ���
	unsigned int	data_size_;		//��ͼ�������ݶ��ֽڳ���
	unsigned char	reseve_[40];
#endif
} MAPFILE_HEADER;

// ��ͼ����Ľṹ
typedef struct tagMapGrid
{
	unsigned short	bg_img_;		// ����ͼƬ���
	unsigned short	ft_img_;		// ǰ��ͼƬ���
	unsigned short	flag_;			// ��ͼ�����־λ		�����ϰ����ڵ�
	unsigned char	obj_root_;		// �زķ�������			��ͼ������
	unsigned char	reseve_;		// ͼƬ����				jpg or png

	unsigned short	effect_id_;		// ��ͼ����Чid
	unsigned short  width_;			// ��Ч�Ŀ��
	unsigned short  height_;		// ��Ч�ĸ߶�
} MAPGrid;


class GameMapInfo
{
protected:
	unsigned int	width_;						// ��ͼ��� (tile count)
	unsigned int	height_;					// ��ͼ�߶� (tile count)
	unsigned int	width_in_pixel_;			// ��ͼ��� (pixel)
	unsigned int	height_in_pixel_;			// ��ͼ�߶� (pixel)
	int*			moveable_index_;			// ÿ�����Ӧ�Ŀ��ƶ���������Ҫ������ʡ�ڴ���Ż�����ʱûʹ�õ�
	int				moveable_count_;			// �ƶ���������
	MAPGrid*		map_grid_;					// ������Ϣ
	
public:
	GameMapInfo();
	virtual ~GameMapInfo();

	/* �����м��ص�ͼ���� */
	bool LoadFromStream(stream::BaseStream& stream);
	/* ���ļ��м��ص�ͼ���� */
	bool LoadFromFile(const char* fn);
	/* ���ֽڼ��ص�ͼ����(��Ҫ����Ϊcocos2d�ӿ�ֱ�Ӱ��ļ����ֽڶ���ȡ��) */
	bool LoadFromChar(unsigned char* buffer, const unsigned long size);

	/* ����һ��ȫ�������ƶ��ĵ�ͼ */
	void initDefault(unsigned int w, unsigned int h);
	/* �����ͷź��� */
	void release();

	/* ��ȡ��ͼ��� (tile count) */
	inline int getWidth()
	{
		return width_;
	}
	/* ��ȡ��ͼ�߶� (tile count) */
	inline int getHeight()
	{
		return height_;
	}
	/* ��ȡ��ͼ��� (pixel) */
	inline int getWidthInPixel()
	{
		return width_in_pixel_;
	}
	/* ��ȡ��ͼ��� (pixel) */
	inline int getHeightInPixel()
	{
		return height_in_pixel_;
	}
	/* ��ȡ���ƶ��������� */
	inline int getMoveableCount()
	{
		return moveable_count_;
	}

	/* ��ȡ��ͼ�����е�Ԫ��Ŀ */
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

	/* �жϵ�ͼ��x, y����λ���Ƿ�����ƶ�������true��ʾ��������ƶ� */
	inline bool canMove(unsigned int x, unsigned int y)
	{
		if (!moveable_index_ || x >= width_ || x < 0 || y >= height_ || y < 0)
			return false;

		return moveable_index_[y * width_ + x] != -1;
	}

	/* �жϵ�ͼ��x, y����λ���Ƿ�Ϊ�ڵ� */
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


