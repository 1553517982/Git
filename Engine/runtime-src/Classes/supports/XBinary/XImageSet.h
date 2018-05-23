#pragma once
#ifndef XImageSet_H
#define XImageSet_H
#include <map>
#include <vector>
#include <string>
#include "XBinaryCommon.h"

//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
//copy�����ļ�
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End

typedef struct _XImageUnit
{	
	_XImageUnit() : x(0),y(0),width(0),height(0),textureName(0),
		rotation(0),offsetX(0),offsetY(0),sourceSizeX(0),sourceSizeY(0)
	{
		memset(imageName,0,sizeof(imageName));
	}

	bool SetImageName(const char* szName)
	{
		if(strlen(szName) >= XBINARY_FILENAME_MAX_SIZE)
			return false;
		strncpy(imageName,szName,XBINARY_FILENAME_MAX_SIZE - 1);
		return true;
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
		if(!SetImageName(szName))
			return false;

		x = _x;
		y = _y;
		width = _width;
		height = _height;
		textureName = NULL;
		rotation = _rot;
		offsetX = _offsetX;
		offsetY = _offsetY;
		sourceSizeX = _sourceSizeX;
		sourceSizeY = _sourceSizeY;
		return true;
	}

	const char* ImageName() const { return &imageName[0]; }
	const char* TextureName() const { return textureName; }

	unsigned short	x;										// ��������x			2
	unsigned short	y;										// ��������y			2
	unsigned short	width;									// С��ͼ���			2
	unsigned short	height;									// С��ͼ�߶�			2
	char*			textureName;							// ��������ָ��		

	char			imageName[XBINARY_FILENAME_MAX_SIZE];	// С��ͼ����			72
	bool			rotation;								// �Ƿ���ת

	short			offsetX;								// ƫ����X
	short			offsetY;								// ƫ����Y

	unsigned short  sourceSizeX;							// ԭ���Ĵ�СX
	unsigned short  sourceSizeY;							// ԭ���Ĵ�СY
	// size 81				
}XImageUnit;

typedef std::map<std::string,XImageUnit*>					XImageUnitMap;
typedef XImageUnitMap::iterator								XImageUnitMapIter;
typedef std::vector<XImageUnit*>							XImageUnitList;

class XImageSet
{
public:
	XImageSet();
	virtual ~XImageSet();
	//��ȡ����Ȼ�����ݷ��ص�һ�������б�
	bool Read(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap = NULL );

	//����
	bool Save(const char* pFileName);

	bool Load(const char* pFileName, XImageUnitMap* pkMap = NULL );

	bool Initialize(const char* szImageSetName, unsigned int unCount );

	bool Set(XImageUnit* pkData, unsigned int i);

	XImageUnit* Get(unsigned int i)
	{
		if(m_pImageUnits && i < m_unImageUnitCount)
			return &m_pImageUnits[i];
		return NULL;
	}

	unsigned int ImageUnitCount() const { return m_unImageUnitCount; }

	const char* TextureName() const { return &m_szTextureName[0]; }

	bool SetTextureName(const char* szName)
	{
		if(strlen(szName) >= XBINARY_FILENAME_MAX_SIZE)
			return false;
		strncpy(m_szTextureName,szName,XBINARY_FILENAME_MAX_SIZE - 1);
		return true;
	}

	unsigned short GetVersion()
	{
		return m_kFileHeader.unFileVersion;
	}

//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
#if defined(XIMAGEUNIT_SLOW__READ)
	//��ȡ����Ȼ�����ݷ��ص�һ�������б�
	bool ReadSlow(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap);
	bool CreateFromBufferSlow(void* pkBuffer, int uBufferSize);
#endif
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End
	
	static int nameToIndex(const char* szName);

protected:
	XBinaryHeader											m_kFileHeader;										//�ļ�ͷ
	char													m_szTextureName[XBINARY_FILENAME_MAX_SIZE];			//����������
	XImageUnit*												m_pImageUnits;										//С����
	unsigned int											m_unImageUnitCount;									//С�������

};

typedef std::map<std::string,XImageSet*>					XImageSetMap;
typedef XImageSetMap::iterator								XImageSetMapIter;

#endif