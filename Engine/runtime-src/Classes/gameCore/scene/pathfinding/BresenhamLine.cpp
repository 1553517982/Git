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

	//计算斜率和直线的截距常量
	k = (ty - oy) / (tx - ox);
	b = ty - k * tx;

	//计算直线的坐标方向增量
	xstep = tx > ox ? 1 : -1;
	ystep = ty > oy ? 1 : -1;

	//对起点和终点坐标取整，并计算x方向的绝对距离
	x1 = (int)(ox), y1 = (int)(oy), x2 = (int)(tx), y2 = (int)(ty);
	dx = x2 - x1, dx = (dx ^ (dx >> 31)) - (dx >> 31);

	//记录起始格子
	x = x1, lastY = y1;
	throughCheckResult[2] = x, throughCheckResult[3] = lastY;
	//trace(throughCheckResult[2], throughCheckResult[3]);

	//沿着起点到终点的x方向递增（减），计算经过的格子
	for (i = 0; i < dx; i++)
	{
		x += xstep;
		//这里必须注意，x往不同的方向与y相交的点不同
		ny = k * (xstep > 0 ? x : x + 1) + b;
		//交点y取整，得到经过格子的y坐标
		y = (int)(ny);
		//计算当前交点与上一个交点之间经过的格子
		while (lastY != y)
		{
			lastY += ystep;
			if (!mapInfo->canMove(x - xstep, lastY)) return throughCheckResult;
			throughCheckResult[2] = x - xstep, throughCheckResult[3] = lastY;
			//trace(throughCheckResult[2], throughCheckResult[3]);
		}
		//押入当前计算得出的格子
		if (!mapInfo->canMove(x, y)) return throughCheckResult;
		throughCheckResult[2] = x, throughCheckResult[3] = y;
		//trace(throughCheckResult[2], throughCheckResult[3]);
	}

	//计算最后一相交点与终点之间的格子
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

	//计算斜率和直线的截距常量
	k = (ty - oy) / (tx - ox);
	b = ty - k * tx;

	//计算直线的坐标方向增量
	xstep = tx > ox ? 1 : -1;
	ystep = ty > oy ? 1 : -1;

	//对起点和终点坐标取整，并计算x方向的绝对距离
	x1 = (int)(ox), y1 = (int)(oy), x2 = (int)(tx), y2 = (int)(ty);
	dx = x2 - x1, dx = (dx ^ (dx >> 31)) - (dx >> 31);

	//押入起始格子
	coords->add(x1);
	coords->add(y1);
	x = x1, lastY = y1;

	//沿着起点到终点的x方向递增（减），计算经过的格子
	for (i = 0; i < dx; i++)
	{
		x += xstep;
		//这里必须注意，x往不同的方向与y相交的点不同
		ny = k * (xstep > 0 ? x : x + 1) + b;
		//交点y取整，得到经过格子的y坐标
		y = (int)(ny);
		//计算当前交点与上一个交点之间经过的格子
		while (lastY != y)
		{
			lastY += ystep;
			coords->add(x - xstep), coords->add(lastY);
		}
		//押入当前计算得出的格子
		coords->add(x), coords->add(y);
	}

	//计算最后一相交点与终点之间的格子
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

	// 获取最后路段的起点坐标
	if (length >= 4)
	{
		sx = *(lastp - 3);
		sy = *(lastp - 2);
	}

	// 计算最后路段两节点的坐标差
	dx = tx - sx, dy = ty - sy;

	// 如果最后路段长度大于要缩短的长度，则缩短距离，调整最后节点
	if (dx * dx + dy * dy > distance * distance)
	{
		BresenhamLine::getPointOnLine((float)(sx), (float)(sy), (float)(tx), (float)(ty), (float)(-distance), pt);
		*(lastp - 1) = *pt;
		*lastp = *(pt + 1);
	}
	// 如果最后路段不超过缩短距离，则舍去最后节点
	else
	{
		path->remove(length - 3, 2);
	}
}
}