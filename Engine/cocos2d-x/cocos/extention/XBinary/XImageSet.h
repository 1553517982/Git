#pragma once
#ifndef XImageSet_H
#define XImageSet_H
#include <map>
#include <vector>
#include <string>
#include "XBinaryCommon.h"
NS_CC_BEGIN
typedef struct _XImageUnit
{	
	_XImageUnit() : x(0),y(0),width(0),height(0),
		rotation(0),offsetX(0),offsetY(0),sourceSizeX(0),sourceSizeY(0)
	{
	}

	bool Set( unsigned short _x, 
		unsigned short _y,
		unsigned short _width,
		unsigned short _height,
		const char* szName,
		bool  _rot = false,
		short _offsetX = 0,
		short _offsetY = 0,
		unsigned short _sourceSizeX = 0,
		unsigned short _sourceSizeY = 0)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		rotation = _rot;
		offsetX = _offsetX;
		offsetY = _offsetY;
		sourceSizeX = _sourceSizeX;
		sourceSizeY = _sourceSizeY;
		memset(textureName, 0, sizeof(textureName));
		strncpy(imageName, szName, XBINARY_FILENAME_MAX_SIZE - 1);
		return true;
	}

	const char* ImageName() const { return &imageName[0]; }
	const char* TextureName() const { return textureName; }

	unsigned short	x;										// ��������x			2
	unsigned short	y;										// ��������y			2
	unsigned short	width;									// С��ͼ���			2
	unsigned short	height;									// С��ͼ�߶�			2
	short			offsetX;								// ƫ����X
	short			offsetY;								// ƫ����Y
	unsigned short  sourceSizeX;							// ԭ���Ĵ�СX
	unsigned short  sourceSizeY;							// ԭ���Ĵ�СY
	bool			rotation;								// �Ƿ���ת

	char			textureName[XBINARY_FILENAME_MAX_SIZE];	// ��������ָ��
	char 			imageName[XBINARY_FILENAME_MAX_SIZE];	// С��ͼ����			72
	
	// size 81				
}XImageUnit;

typedef std::map<std::string,XImageUnit*>					XImageUnitMap;
typedef XImageUnitMap::iterator								XImageUnitMapIter;


typedef std::vector<XImageUnit> XImageUnitList;
class XImageSet
{
public:
	XImageSet();
	virtual ~XImageSet();
	//��ȡ����Ȼ�����ݷ��ص�һ�������б�
	bool Read(void* pkBuffer, unsigned int uBufferSize );
	
	XImageUnitList * GetImageUnitList();

protected:
	std::string	m_textureName;
	XImageUnitList	 m_pImageUnits;
};

NS_CC_END
#endif