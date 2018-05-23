#include <math.h>
#include "cocos2d.h"
#include "BresenhamLine.h"
#include "game_map.h"

//#include "../include/game_map.h"
namespace bresenhamline
{

int BresenhamLine::throughCheckResult[4] = {0};

int *BresenhamLine::isAbleToThrough(float ox, float oy, float tx, float ty, GameMapInfo *mapInfo)
{
	int x1, y1, x2, y2;
	int xstep, ystep, dx, x, y, lastY, i;
	float ny, k, b;

	throughCheckResult[0] = 0;
	throughCheckResult[1] = 0;

	//����б�ʺ�ֱ�ߵĽؾೣ��
	k = (ty - oy) / (tx - ox);
	b = ty - k * tx;

	//����ֱ�ߵ����귽������
	xstep = tx > ox ? 1 : -1;
	ystep = ty > oy ? 1 : -1;

	//�������յ�����ȡ����������x����ľ��Ծ���
	x1 = (int)(ox), y1 = (int)(oy), x2 = (int)(tx), y2 = (int)(ty);
	dx = x2 - x1, dx = (dx ^ (dx >> 31)) - (dx >> 31);

	//��¼��ʼ����
	x = x1, lastY = y1;
	throughCheckResult[2] = x, throughCheckResult[3] = lastY;
	//trace(throughCheckResult[2], throughCheckResult[3]);

	//������㵽�յ��x������������������㾭���ĸ���
	for (i = 0; i < dx; i++)
	{
		x += xstep;
		//�������ע�⣬x����ͬ�ķ�����y�ཻ�ĵ㲻ͬ
		ny = k * (xstep > 0 ? x : x + 1) + b;
		//����yȡ�����õ��������ӵ�y����
		y = (int)(ny);
		//���㵱ǰ��������һ������֮�侭���ĸ���
		while (lastY != y)
		{
			lastY += ystep;
			if (!mapInfo->canMove(x - xstep, lastY)) return throughCheckResult;
			throughCheckResult[2] = x - xstep, throughCheckResult[3] = lastY;
			//trace(throughCheckResult[2], throughCheckResult[3]);
		}
		//Ѻ�뵱ǰ����ó��ĸ���
		if (!mapInfo->canMove(x, y)) return throughCheckResult;
		throughCheckResult[2] = x, throughCheckResult[3] = y;
		//trace(throughCheckResult[2], throughCheckResult[3]);
	}

	//�������һ�ཻ�����յ�֮��ĸ���
	while (lastY != y2)
	{
		lastY += ystep;
		if (!mapInfo->canMove(x, lastY)) return throughCheckResult;
		throughCheckResult[2] = x, throughCheckResult[3] = lastY;
		//trace(throughCheckResult[2], throughCheckResult[3]);
	}

	throughCheckResult[0] = 1;
	return throughCheckResult;
}

void BresenhamLine::tileLine(Vector<int> *coords, float ox, float oy, float tx, float ty)
{
	int x1, y1, x2, y2;
	int xstep, ystep, dx, x, y, lastY, i;
	float ny, k, b;

	//����б�ʺ�ֱ�ߵĽؾೣ��
	k = (ty - oy) / (tx - ox);
	b = ty - k * tx;

	//����ֱ�ߵ����귽������
	xstep = tx > ox ? 1 : -1;
	ystep = ty > oy ? 1 : -1;

	//�������յ�����ȡ����������x����ľ��Ծ���
	x1 = (int)(ox), y1 = (int)(oy), x2 = (int)(tx), y2 = (int)(ty);
	dx = x2 - x1, dx = (dx ^ (dx >> 31)) - (dx >> 31);

	//Ѻ����ʼ����
	coords->add(x1);
	coords->add(y1);
	x = x1, lastY = y1;

	//������㵽�յ��x������������������㾭���ĸ���
	for (i = 0; i < dx; i++)
	{
		x += xstep;
		//�������ע�⣬x����ͬ�ķ�����y�ཻ�ĵ㲻ͬ
		ny = k * (xstep > 0 ? x : x + 1) + b;
		//����yȡ�����õ��������ӵ�y����
		y = (int)(ny);
		//���㵱ǰ��������һ������֮�侭���ĸ���
		while (lastY != y)
		{
			lastY += ystep;
			coords->add(x - xstep), coords->add(lastY);
		}
		//Ѻ�뵱ǰ����ó��ĸ���
		coords->add(x), coords->add(y);
	}

	//�������һ�ཻ�����յ�֮��ĸ���
	while ( lastY != y2)
	{
		lastY += ystep;
		coords->add(x), coords->add(lastY);
	}
}

void BresenhamLine::getPointOnLine(float ox, float oy, float tx, float ty, float ds, int *pt)
{
	float os, ts, dx, dy;

	dx = tx - ox, dy = ty - oy;
	os = sqrt(dx * dx + dy * dy);
	ts = os + ds;

	*pt			 = (int)(ox + dx * ts / os + 0.5);
	*(pt + 1)	 = (int)(oy + dy * ts / os + 0.5);
}

void BresenhamLine::shortenPath(int ox, int oy, Vector<int> *path, int distance)
{
	int sx, sy, tx, ty;
	int dx, dy, length;
	int pt[2], *lastp;

	sx = ox;
	sy = oy;
	length = path->count();
	lastp = *path + length - 1;
	tx = *(lastp - 1);
	ty = *lastp;

	// ��ȡ���·�ε��������
	if (length >= 4)
	{
		sx = *(lastp - 3);
		sy = *(lastp - 2);
	}

	// �������·�����ڵ�������
	dx = tx - sx, dy = ty - sy;

	// ������·�γ��ȴ���Ҫ���̵ĳ��ȣ������̾��룬�������ڵ�
	if (dx * dx + dy * dy > distance * distance)
	{
		BresenhamLine::getPointOnLine((float)(sx), (float)(sy), (float)(tx), (float)(ty), (float)(-distance), pt);
		*(lastp - 1) = *pt;
		*lastp = *(pt + 1);
	}
	// ������·�β��������̾��룬����ȥ���ڵ�
	else
	{
		path->remove(length - 3, 2);
	}
}
}