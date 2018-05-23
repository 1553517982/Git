#ifndef _BRESENHAMLINE_H_
#define _BRESENHAMLINE_H_

#include "gameCore/common/vector.h"
using namespace container;

class GameMapInfo;

namespace bresenhamline
{

/**
 *	Bresenhamֱ���㷨
 *	����������������м���ֱ�߾����ĸ��ӣ�ͬʱҲ�����ж�������Ƿ����ϰ���ֱ��ͨ��
 *	@author WynnLam
 */
class BresenhamLine
{
public:
	/**
	 *	�ж�ָ�����������Ƿ����ͨ��
	 *	@param ox ��ʼ����x����
	 *	@param oy ��ʼ����y����
	 *	@param tx Ŀ�����x����
	 *	@param ty Ŀ�����y����
	 *	@param mapInfo ��ͼ����ָ�룬���ڻ�ȡ�����Ƿ�����ƶ�
	 *	@return ��������飬��һ��Ԫ�ر�ʾ�Ƿ����ͨ����0-�����ԣ�1-���ԣ��ڶ���ʾͨ�����ӵ������������͵��ĸ���ʾ���һ��ͨ���ĸ�������
	 */
	static int *isAbleToThrough(float ox, float oy, float tx, float ty, GameMapInfo *mapInfo);
	
	/**
	 *	����ָ�������ֱ�߾����ĸ���
	 *	@param coords �������ӵ������б����ᱻ�޸�Ϊ[x0, y0, x1, y1, ...]
	 *	@param ox ��ʼ����x����
	 *	@param oy ��ʼ����y����
	 *	@param tx Ŀ�����x����
	 *	@param ty Ŀ�����y����
	 */
	static void tileLine(container::Vector<int> *coords, float ox, float oy, float tx, float ty);
	
	/**
	 * ��ȡָ��ֱ���ϵĵ�
	 * @param ox ��ʼ��x����
	 * @param oy ��ʼ��y����
	 * @param tx Ŀ���x����
	 * @param ty Ŀ���y����
	 * @param ds ��ʼ���Ŀ��㹹�ɵ�ֱ������ľ���
	 * @param pt ����ds��ĵ㣬һ������Ϊ2��int����
	 */		
	static void getPointOnLine(float ox, float oy, float tx, float ty, float ds, int *pt);
	
	/**
	 *	����·��
	 *	ע�⣺�÷�����ֱ���޸�path���������ᴴ���µ�path
	 *	@param ox Ѱ·���x
	 *	@param oy Ѱ·���y
	 *	@param path ·��
	 *	@param distance ���̾���
	 */
	static void shortenPath(int ox, int oy, container::Vector<int> *path, int distance);
private:
	// ֱ�߾����ĸ����Ƿ񶼿���ͨ���ļ��������һ������Ϊ4�������б�
	// ��1����ʾ�Ƿ����ͨ����0-�����ԣ�1-���ԣ�
	// ��2����ʾͨ���ĸ�������;
	// ��3���͵�4����ʾ����ͨ�������һ�����ӵ�����
	static int throughCheckResult[4];
};

}
#endif