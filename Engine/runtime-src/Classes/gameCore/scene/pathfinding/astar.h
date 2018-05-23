#ifndef _ASTART_H_
#define _ASTART_H_

#include "gameCore/common//vector.h"
#include "game_map.h"

using namespace container;
/**
 *	A*Ѱ·�Ľڵ�
 */
class ASNode
{
public:
	//////////////////////////////
	// �ڵ���״̬����
	//////////////////////////////
	static const int NODE_STATE_ORIGINAL	= 0;// ԭʼ״̬, δ����
	static const int NODE_STATE_OPEN		= 1;// �����
	static const int NODE_STATE_CLOSE		= 2;// �Ѽ��

public:
	unsigned short	x;			// �ڵ�x����
	unsigned short	y;			// �ڵ�y����
	unsigned short	f;			// ȫ������,��g + h����
	unsigned short	g;			// ����㵽��ǰ�ڵ�Ĵ���
	unsigned short	h;			// �ӵ�ǰ�ڵ㵽�յ�Ĺ��ƴ���
	bool			walkable;	// �ڵ��Ƿ���ƶ�
	unsigned char	state;		// �ڵ���״̬,ֵΪ�ڵ�״̬����
	int				markTag;	// �ڵ��ʼ����ǣ������Ż�Ѱ·Ч�ʣ���ʡѭ����ʼ�����нڵ�Ŀ���
	short			prevX;		// ��һ���ڵ��x����
	short			prevY;		// ��һ���ڵ��y����
	ASNode*			prevNode;	// ��һ���ڵ�
	ASNode*			nextNode;	// ��һ���ڵ�
};

/**
 *	A*Ѱ·�㷨
 */
class AStar
{
public:
	//////////////////////////////////////////////////////////////////////////
	// Ѱ·������
	//////////////////////////////////////////////////////////////////////////
	static const int PATHFINDING_ERROR_NONE			 = 0;// ����
	static const int PATHFINDING_ERROR_START_POINT	 = 1;// ��ʼ�㳬����Χ
	static const int PATHFINDING_ERROR_TARGET_POINT	 = 2;// Ŀ��㳬����Χ
	static const int PATHFINDING_ERROR_NOT_FOUND	 = 3;// �в���Ѱ·��

private:
	//////////////////////////////////////////////////////////////////////////
	// Ѱ·�㷨��صĳ���
	//////////////////////////////////////////////////////////////////////////
	static const int DIAGONAL_COST	= 14;	// �Խ����ƶ�����
	static const int VERTICAL_COST	= 10;	// ��ֱ���ƶ�����
	static const int MOVE_COST[2];	// �ƶ����۱�,��ǰ�����ƶ����۴�ŵ��б���
	static const int AROUND_X[8];	// ���ڰ�˳ʱ�뷽����ټ�����Χ�ڵ�x�����ƫ����
	static const int AROUND_Y[8];	// ���ڰ�˳ʱ�뷽����ټ�����Χ�ڵ�y�����ƫ����

public:
	AStar(GameMapInfo *grid = NULL);
	~AStar();

public:
	/**
	 *	��ʼ������
	 *	@param grid ��ͼ��������Ϣ
	 */
	void initGrid(GameMapInfo *grid);
	
	/**
	 *	Ѱ·
	 *	@param path ·���ڵ��б���ʽΪ[x0, y0, x1, y1, ...]
	 *	@param sx ��ʼx����
	 *	@param sy ��ʼy����
	 *	@param tx Ŀ��x����
	 *	@param ty Ŀ��y����
	 *	@return �����룬��PATHFINDING_ERROR_��ͷ����ĳ���
	 */
	int findPath(container::Vector<int> *path, int sx, int sy, int tx, int ty);

private:
	ASNode*		_lastOpenNode;		// �������Ľڵ�
	ASNode*		_nodes;				// �ڵ��б�,�������㹫ʽ:y * _numCols + x
	int			_numCols;			// ����,����ͼ���
	int			_numRows;			// ����,����ͼ�߶�
	int			_markTag;			// �ڵ��ʼ�����

private:
	/**
	 *	���ýڵ�����
	 *	@param x
	 *	@param y
	 */
	void reset(int x, int y);

	/**
	 *	�ѽڵ���ӵ��ѿ����б�
	 *	@param node
	 */
	void closeNode(ASNode *node);

	/**
	 *	�ѽڵ���ӵ��������б�
	 *	@param node
	 */
	void openNode(ASNode *node);

	/**
	 *	������ӽڵ㵽�������б�
	 *	@param node
	 */
	void reopenNode(ASNode *node);
};

#endif