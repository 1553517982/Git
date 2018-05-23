#include <math.h>
#include <string.h>
#include "cocos2d.h"
#include "XCommon.h"
#include "gameCore/scene/pathfinding/astar.h"


//////////////////////
static unsigned long g_ulAstarNum = 0;
//////////////////////


const int AStar::MOVE_COST[2] = {AStar::VERTICAL_COST, AStar::DIAGONAL_COST};
const int AStar::AROUND_X[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int AStar::AROUND_Y[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

AStar::AStar(GameMapInfo *grid)
{
	if (grid != NULL)
	{
		initGrid(grid);
	}
	_nodes		= NULL;
}

void AStar::initGrid(GameMapInfo *grid)
{
	int x, y, index;
	ASNode node;

	_numCols = grid->getWidth();
	_numRows = grid->getHeight();

	if (_nodes)
	{
		delete[] _nodes;
	}
	//XLOG("-----------------------------------------------------------------");
	//XLOG("run Astar initGrid");
	//XLOG("_numCols * _numRows",_numCols * _numRows);
	g_ulAstarNum = _numCols * _numRows;

	_nodes = new ASNode[_numCols * _numRows];

	index = 0;
	for (y = 0; y < _numRows; y++)
	{
		for (x = 0; x < _numCols; x++)
		{
			node.x = (unsigned short)x;
			node.y = (unsigned short)y;
			node.walkable = grid->canMove(x, y);
			_nodes[index++] = node;
		}
	}
	//XLOG("end run Astar initGrid");
	//XLOG("-----------------------------------------------------------------");
}

AStar::~AStar()
{
	//XLOG("-----------------------------------------------------------------");
	//XLOG(" run ~AStar()");
	if (_nodes)
	{
		delete[] _nodes;
	}
	//XLOG("-----------------------------------------------------------------");
}

int AStar::findPath(Vector<int> *path, int sx, int sy, int tx, int ty)
{
	int cx, cy, x, y, i;
	ASNode *cnode, *node;
	bool isFound = false;

	// ���Ѱ·����ʼ��Ŀ���
	if (sx < 0 || sx >= _numCols || sy < 0 || sy >= _numRows)
		return PATHFINDING_ERROR_START_POINT;
	if (tx < 0 || tx >= _numCols || ty < 0 || ty >= _numRows)
		return PATHFINDING_ERROR_TARGET_POINT;
	if (sx == tx && sy == ty)
		return PATHFINDING_ERROR_NONE;
	if (!_nodes[ty * _numCols + tx].walkable)
	{
		if(g_ulAstarNum - 1 < ty * _numCols + tx)
				XLOG(" Astar error g_ulAstarNum < y * _numCols + x!!!!!!!!!!! @@@@ info: g_ulAstarNum = %d, ty * _numCols + tx = %d ",g_ulAstarNum, ty * _numCols + tx);
		return PATHFINDING_ERROR_NONE;
	}
	//Shan Lu Add Begin 23/4/2013 21:15 
	//@brief: 
	if (!_nodes[sy * _numCols + sx].walkable)
		return PATHFINDING_ERROR_NONE;
	//Shan Lu Add End

	reset(sx, sy);

	// �����ڵ�����Ϊ��ǰ�ڵ�,����ӵ��������б�
	cx = sx, cy = sy;
	cnode = &_nodes[cy * _numCols + cx];
	if(g_ulAstarNum - 1 < cy * _numCols + cx)
			XLOG(" Astar error g_ulAstarNum <cy * _numCols + cx!!!!!!!!!!! @@@@ info: g_ulAstarNum = %d, cy * _numCols + cx = %d ",g_ulAstarNum, cy * _numCols + cx);

	cnode->g = 0;
	cnode->h = (unsigned short)(abs(tx - sx) + abs(ty - sy) * 10);
	cnode->prevX = -1;
	cnode->prevY = -1;
	cnode->x = (unsigned short)cx;
	cnode->y = (unsigned short)cy;
	cnode->markTag = _markTag;

	// Ѱ·��ѭ��
	while (true)
	{
		// ��ǰ�ڵ����յ㣬�����ҵ�·��
		if (cx == tx && cy == ty)
		{
			isFound = true;
			break;
		}

		if (cnode->state != ASNode::NODE_STATE_CLOSE)
		{
			closeNode(cnode);
		}

		// ����ÿһ���ڽڵ�
		for (i = 0; i < 8; i++)
		{
			x = cx + AROUND_X[i];
			y = cy + AROUND_Y[i];

			if (x < 0 || x >= _numCols || y < 0 || y >= _numRows)
				continue;
			node = &_nodes[y * _numCols + x];
			if(g_ulAstarNum - 1 < y * _numCols + x)
				XLOG(" Astar error g_ulAstarNum < y * _numCols + x!!!!!!!!!! @@@@ info: g_ulAstarNum = %d, y*_numCols+x = %d",g_ulAstarNum,y*_numCols+x);
			if (!node->walkable)
				continue;

			if (node->markTag != _markTag || node->state == ASNode::NODE_STATE_ORIGINAL)
			{
				node->markTag = _markTag;
				node->prevX = (short)cx;
				node->prevY = (short)cy;
				node->g = (unsigned short)(cnode->g + MOVE_COST[i & 1]);
				node->h = (unsigned short)(abs(tx - x) + abs(ty - y) * 10);
				openNode(node);
			}
			else if (node->state == ASNode::NODE_STATE_OPEN)
			{
				if (node->g > cnode->g + MOVE_COST[i & 1])
				{
					node->prevX = (short)cx;
					node->prevY = (short)cy;
					node->g = (unsigned short)(cnode->g + MOVE_COST[i & 1]);
					reopenNode(node);
				}
			}
		}

		cnode = _lastOpenNode;
		if (cnode == NULL) break;

		cx = cnode->x;
		cy = cnode->y;
	}

	if (isFound)
	{
		while (true)
		{
			path->add(cnode->x);
			path->add(cnode->y);
			cnode = &_nodes[cnode->prevY * _numCols + cnode->prevX];
			if (cnode->prevX <= 0 || cnode->markTag != _markTag)
				break;
		}
	}
	else
	{
		return PATHFINDING_ERROR_NOT_FOUND;
	}

	return PATHFINDING_ERROR_NONE;
}

void AStar::reset(int x, int y)
{
	//XLOG("----------------------------------------------------");
	//XLOG(" run AStar reset ");
	ASNode &node = _nodes[y * _numCols + x];
	//if(g_ulAstarNum  != y * _numCols + x)
	//	XLOG(" g_ulAstarNum != y * _numCols + x @@@ info: g_ulAstarNum = %d, y*_numCols+x = %d",g_ulAstarNum,y*_numCols+x);
	node.f = 0;
	node.g = 0;
	node.h = 0;
	node.prevX = 0;
	node.prevY = 0;
	node.state = ASNode::NODE_STATE_ORIGINAL;
	node.prevNode = NULL;
	node.nextNode = NULL;

	_lastOpenNode = NULL;
	_markTag += 1;

}

void AStar::closeNode(ASNode *node)
{
	if (node->state == ASNode::NODE_STATE_OPEN)
	{
		if (node->prevNode != NULL)
			node->prevNode->nextNode = node->nextNode;
		if (node->nextNode != NULL)
			node->nextNode->prevNode = node->prevNode;
		if (node == _lastOpenNode)
			_lastOpenNode = node->prevNode;
	}

	node->state = ASNode::NODE_STATE_CLOSE;
}

void AStar::openNode(ASNode *node)
{
	unsigned short f = node->g + node->h;
	ASNode *lastNode = _lastOpenNode;

	node->state = ASNode::NODE_STATE_OPEN;
	node->f = f;

	if (lastNode == NULL)
	{
		_lastOpenNode = node;
		node->prevNode = NULL;
		node->nextNode = NULL;
	} 
	else
	{
		while (lastNode->f < f)
		{
			if (lastNode->prevNode == NULL)
			{
				lastNode->prevNode = node;
				node->prevNode = NULL;
				node->nextNode = lastNode;
				return;
			}
			lastNode = lastNode->prevNode;
		}

		node->prevNode = lastNode;
		if (lastNode->nextNode != NULL)
		{
			node->nextNode = lastNode->nextNode;
			lastNode->nextNode->prevNode = node;
			lastNode->nextNode = node;
		} 
		else
		{
			node->nextNode = NULL;
			lastNode->nextNode = node;
			_lastOpenNode = node;
		}
	}
}

void AStar::reopenNode(ASNode *node)
{
	unsigned short f = node->g + node->h;
	ASNode *nextNode = node->nextNode;

	node->f = f;
	if (nextNode != NULL && nextNode->f > f)
	{
		do 
		{
			nextNode = nextNode->nextNode;
		} while (nextNode != NULL && nextNode->f > f);

		if (node->prevNode != NULL)
			node->prevNode->nextNode = node->nextNode;
		if (node->nextNode != NULL)
			node->nextNode->prevNode = node->prevNode;

		if (nextNode != NULL)
		{
			node->nextNode = nextNode;
			if (nextNode->prevNode != NULL)
			{
				node->prevNode = nextNode->prevNode;
				nextNode->prevNode->nextNode = node;
			}
			else node->prevNode = NULL;
			nextNode->prevNode = node;
		} 
		else
		{
			node->prevNode = _lastOpenNode;
			node->nextNode = NULL;
			_lastOpenNode->nextNode = node;
			_lastOpenNode = node;
		}
	}
}
