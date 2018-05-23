//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
//copy整个文件
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End

#include "XBinaryCommon.h"
#include "XFrameSet.h"
#include <algorithm>
#include "XCommon.h"

const unsigned int MagicNumber = 0xfff2;
const unsigned int FileVersion = 3;

bool compareFrameName(XImageUnit* pFirst, XImageUnit* pSecond)
{
	if(strcmp(pFirst->imageName,pSecond->imageName) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

XImageUnitList* XFrameList :: Data()
{ 
	//通过打包工具进行文件排序
#if 0
	if(m_bNeedSort) 
	{
		std::sort(m_kData.begin(),m_kData.end(),compareFrameName);
		m_bNeedSort = false;
	}
#endif
	return &m_kData; 
}

XFrameSet::XFrameSet(void)
{
	memset(m_szTextureName,0,sizeof(m_szTextureName));
}


XFrameSet::~XFrameSet(void)
{
}

bool XFrameSet::Read(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap, XFrameListMap* pkListMap)
{
	//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
#if defined(XIMAGEUNIT_SLOW__READ)
	return ReadSlow(pkBuffer,uBufferSize,pkMap,pkListMap);
#endif
	//MOD_FOR_64BIT by Shan Lu 2015-01-10 End

	if(m_pImageUnits)
		return false;

	unsigned char* pkReader = (unsigned char*)pkBuffer;
	unsigned int nOffset = 0;
	unsigned int uReadMagic = 0;
	unsigned int nByteToRead = sizeof(m_kFileHeader);

	//读取头
	memcpy(&m_kFileHeader,pkBuffer,nByteToRead);
	strncpy(m_szTextureName,m_kFileHeader.szReserze,XBINARY_FILENAME_MAX_SIZE - 1);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	if(m_kFileHeader.unFileType != X_FILE_IMAGESET)
		return false;

	XAssert(m_kFileHeader.unFileVersion == FileVersion,"wrong file ver");
	if(m_kFileHeader.unFileVersion != FileVersion)
		return false;

	//有多少个ImageUnit
	m_unImageUnitCount = m_kFileHeader.unItemCount;
	m_pImageUnits = new XImageUnit[m_unImageUnitCount];
	nByteToRead = m_unImageUnitCount * sizeof(XImageUnit);
	memcpy(m_pImageUnits,pkReader, nByteToRead);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	//检查魔法数字
	nByteToRead = sizeof(MagicNumber);
	memcpy(&uReadMagic,pkReader,nByteToRead);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	XAssert(uReadMagic == MagicNumber,"magic number error");
	XAssert(nOffset == uBufferSize,"size error");
	std::string File = "";
	XFrameList* pkFrameList = NULL;
	//填充数据
	for(unsigned int i=0;i<m_unImageUnitCount;i++)
	{
		XImageUnit* pkData = &m_pImageUnits[i];
		pkData->textureName = m_szTextureName;
		if(pkMap)
		{
#ifdef _DEBUG
			XImageUnitMap::iterator iter = pkMap->find(pkData->imageName);
			if(iter != pkMap->end())
			{
				cocos2d::log("loading %s %s already in %s ",pkData->textureName,pkData->imageName,iter->second->textureName);
			}
#endif // _DEBUG
			XAssert(pkMap->find(pkData->imageName) == pkMap->end(),"load error");
			pkMap->insert(std::make_pair(pkData->imageName,pkData));
		}
		if(pkListMap)
		{
			File = std::string(pkData->imageName);
			size_t pos = File.find_last_of("/");
			if( pos == std::string::npos)
			{
				XAssert(false,"find no path");
				return false;
			}
			File = File.substr(0,pos);
			XFrameListMap::iterator iter = pkListMap->find(File);
			if(iter == pkListMap->end())
			{
				pkFrameList = new XFrameList();
				pkListMap->insert(std::make_pair(File,pkFrameList));
			}
			else
			{
				pkFrameList = iter->second;
			}
			pkFrameList->push_back(pkData);
		}
	}
	return true;
}


//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
#if defined(XIMAGEUNIT_SLOW__READ)
#define _READ_BUFFER(dst, buffer, size, offset)	\
	memcpy(dst,buffer, size);					\
	buffer += size;								\
	offset += size;								

//读取数据然后将数据返回到一个查找列表
bool XFrameSet::ReadSlow(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap, XFrameListMap* pkListMap)
{
	if(m_pImageUnits)
		return false;

	if(!CreateFromBufferSlow(pkBuffer,uBufferSize))
		return false;

	std::string File = "";
	XFrameList* pkFrameList = NULL;
	//填充数据
	for(unsigned int i=0;i<m_unImageUnitCount;i++)
	{
		XImageUnit* pkData = &m_pImageUnits[i];
		pkData->textureName = m_szTextureName;
		if(pkMap)
		{
#ifdef _DEBUG
			XImageUnitMap::iterator iter = pkMap->find(pkData->imageName);
			if(iter != pkMap->end())
			{
				cocos2d::log("loading %s %s already in %s ", pkData->textureName, pkData->imageName, iter->second->textureName);
			}
#endif // _DEBUG
			XAssert(pkMap->find(pkData->imageName) == pkMap->end(),"already loaded");
			pkMap->insert(std::make_pair(pkData->imageName,pkData));
		}
		if(pkListMap)
		{
			File = std::string(pkData->imageName);
			size_t pos = File.find_last_of("/");
			if( pos == std::string::npos)
			{
				XAssert(false,"find not /");
				return false;
			}
			File = File.substr(0,pos);
			XFrameListMap::iterator iter = pkListMap->find(File);
			if(iter == pkListMap->end())
			{
				pkFrameList = new XFrameList();
				pkListMap->insert(std::make_pair(File,pkFrameList));
			}
			else
			{
				pkFrameList = iter->second;
			}
			pkFrameList->push_back(pkData);
		}
	}
	return true;
}
#endif
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End