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

	unsigned short	x;										// 纹理坐标x			2
	unsigned short	y;										// 纹理坐标y			2
	unsigned short	width;									// 小贴图宽度			2
	unsigned short	height;									// 小贴图高度			2
	short			offsetX;								// 偏移量X
	short			offsetY;								// 偏移量Y
	unsigned short  sourceSizeX;							// 原来的大小X
	unsigned short  sourceSizeY;							// 原来的大小Y
	bool			rotation;								// 是否旋转

	char			textureName[XBINARY_FILENAME_MAX_SIZE];	// 纹理名字指针
	char 			imageName[XBINARY_FILENAME_MAX_SIZE];	// 小贴图名字			72
	
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
	//读取数据然后将数据返回到一个查找列表
	bool Read(void* pkBuffer, unsigned int uBufferSize );
	
	XImageUnitList * GetImageUnitList();

protected:
	std::string	m_textureName;
	XImageUnitList	 m_pImageUnits;
};

NS_CC_END
#endif