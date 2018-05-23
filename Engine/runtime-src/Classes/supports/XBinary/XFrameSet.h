#pragma once
#ifndef XFrameSet_H
#define XFrameSet_H
#include "XImageSet.h"
//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
//copy整个文件
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End
class XFrameList
{
public:
	XFrameList() : m_bNeedSort(false)
	{

	}
	~XFrameList()
	{

	}

	void push_back(XImageUnit* pkData)
	{
		m_kData.push_back(pkData);
		m_bNeedSort = true;
	}

	XImageUnitList* Data();

private:
	bool							m_bNeedSort;
	XImageUnitList					m_kData;
	unsigned int					m_uMaxKey;

};

typedef std::map<std::string,XFrameList*>						XFrameListMap;
typedef XFrameListMap::iterator									XFrameListMapIter;

class XFrameSet : public XImageSet
{
public:
	XFrameSet();
	~XFrameSet();
	bool Read(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap = NULL, XFrameListMap* pkListMap = NULL );

	//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
#if defined(XIMAGEUNIT_SLOW__READ)
	//读取数据然后将数据返回到一个查找列表
	bool ReadSlow(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap, XFrameListMap* pkListMap);
#endif
	//MOD_FOR_64BIT by Shan Lu 2015-01-10 End
};
#endif