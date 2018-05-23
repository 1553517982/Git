#ifndef _ASTART_H_
#define _ASTART_H_

#include "gameCore/common//vector.h"
#include "game_map.h"

using namespace container;
/**
 *	A*寻路的节点
 */
class ASNode
{
public:
	//////////////////////////////
	// 节点检测状态常量
	//////////////////////////////
	static const int NODE_STATE_ORIGINAL	= 0;// 原始状态, 未处理
	static const int NODE_STATE_OPEN		= 1;// 待检测
	static const int NODE_STATE_CLOSE		= 2;// 已检测

public:
	unsigned short	x;			// 节点x坐标
	unsigned short	y;			// 节点y坐标
	unsigned short	f;			// 全部代价,由g + h决定
	unsigned short	g;			// 从起点到当前节点的代价
	unsigned short	h;			// 从当前节点到终点的估计代价
	bool			walkable;	// 节点是否可移动
	unsigned char	state;		// 节点检测状态,值为节点状态常量
	int				markTag;	// 节点初始化标记，用于优化寻路效率，节省循环初始化所有节点的开销
	short			prevX;		// 上一个节点的x坐标
	short			prevY;		// 上一个节点的y坐标
	ASNode*			prevNode;	// 上一个节点
	ASNode*			nextNode;	// 下一个节点
};

/**
 *	A*寻路算法
 */
class AStar
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 寻路错误常量
	//////////////////////////////////////////////////////////////////////////
	static const int PATHFINDING_ERROR_NONE			 = 0;// 正常
	static const int PATHFINDING_ERROR_START_POINT	 = 1;// 起始点超出范围
	static const int PATHFINDING_ERROR_TARGET_POINT	 = 2;// 目标点超出范围
	static const int PATHFINDING_ERROR_NOT_FOUND	 = 3;// 招不到寻路点

private:
	//////////////////////////////////////////////////////////////////////////
	// 寻路算法相关的常量
	//////////////////////////////////////////////////////////////////////////
	static const int DIAGONAL_COST	= 14;	// 对角线移动代价
	static const int VERTICAL_COST	= 10;	// 垂直线移动代价
	static const int MOVE_COST[2];	// 移动代价表,把前两个移动代价存放到列表中
	static const int AROUND_X[8];	// 用于按顺时针方向快速计算周围节点x坐标的偏移量
	static const int AROUND_Y[8];	// 用于按顺时针方向快速计算周围节点y坐标的偏移量

public:
	AStar(GameMapInfo *grid = NULL);
	~AStar();

public:
	/**
	 *	初始化网格
	 *	@param grid 地图的网格信息
	 */
	void initGrid(GameMapInfo *grid);
	
	/**
	 *	寻路
	 *	@param path 路径节点列表，格式为[x0, y0, x1, y1, ...]
	 *	@param sx 起始x坐标
	 *	@param sy 起始y坐标
	 *	@param tx 目标x坐标
	 *	@param ty 目标y坐标
	 *	@return 错误码，以PATHFINDING_ERROR_开头定义的常量
	 */
	int findPath(container::Vector<int> *path, int sx, int sy, int tx, int ty);

private:
	ASNode*		_lastOpenNode;		// 最后待检查的节点
	ASNode*		_nodes;				// 节点列表,索引计算公式:y * _numCols + x
	int			_numCols;			// 列数,即地图宽度
	int			_numRows;			// 行数,即地图高度
	int			_markTag;			// 节点初始化标记

private:
	/**
	 *	重置节点数据
	 *	@param x
	 *	@param y
	 */
	void reset(int x, int y);

	/**
	 *	把节点添加到已考察列表
	 *	@param node
	 */
	void closeNode(ASNode *node);

	/**
	 *	把节点添加到待考察列表
	 *	@param node
	 */
	void openNode(ASNode *node);

	/**
	 *	重新添加节点到待考察列表
	 *	@param node
	 */
	void reopenNode(ASNode *node);
};

#endif