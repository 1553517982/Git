#ifndef _BRESENHAMLINE_H_
#define _BRESENHAMLINE_H_

#include "gameCore/common/vector.h"
using namespace container;

class GameMapInfo;

namespace bresenhamline
{

/**
 *	Bresenham直线算法
 *	用于在网格的世界中计算直线经过的格子，同时也用于判断两点间是否无障碍可直接通过
 *	@author WynnLam
 */
class BresenhamLine
{
public:
	/**
	 *	判断指定的两个点是否可以通过
	 *	@param ox 起始格子x坐标
	 *	@param oy 起始格子y坐标
	 *	@param tx 目标格子x坐标
	 *	@param ty 目标格子y坐标
	 *	@param mapInfo 地图数据指针，用于获取格子是否可以移动
	 *	@return 检测结果数组，第一个元素表示是否可以通过，0-不可以，1-可以；第二表示通过格子的数量；第三和第四个表示最后一个通过的格子坐标
	 */
	static int *isAbleToThrough(float ox, float oy, float tx, float ty, GameMapInfo *mapInfo);
	
	/**
	 *	计算指定两点间直线经过的格子
	 *	@param coords 经过格子的坐标列表，将会被修改为[x0, y0, x1, y1, ...]
	 *	@param ox 起始格子x坐标
	 *	@param oy 起始格子y坐标
	 *	@param tx 目标格子x坐标
	 *	@param ty 目标格子y坐标
	 */
	static void tileLine(container::Vector<int> *coords, float ox, float oy, float tx, float ty);
	
	/**
	 * 获取指定直线上的点
	 * @param ox 起始点x坐标
	 * @param oy 起始点y坐标
	 * @param tx 目标点x坐标
	 * @param ty 目标点y坐标
	 * @param ds 起始点和目标点构成的直线延伸的距离
	 * @param pt 延伸ds后的点，一个长度为2的int数组
	 */		
	static void getPointOnLine(float ox, float oy, float tx, float ty, float ds, int *pt);
	
	/**
	 *	缩短路径
	 *	注意：该方法会直接修改path参数，不会创建新的path
	 *	@param ox 寻路起点x
	 *	@param oy 寻路起点y
	 *	@param path 路径
	 *	@param distance 缩短距离
	 */
	static void shortenPath(int ox, int oy, container::Vector<int> *path, int distance);
private:
	// 直线经过的格子是否都可以通过的检测结果，是一个长度为4的整型列表
	// 第1个表示是否可以通过，0-不可以，1-可以；
	// 第2个表示通过的格子数量;
	// 第3个和第4个表示可以通过的最后一个格子的坐标
	static int throughCheckResult[4];
};

}
#endif