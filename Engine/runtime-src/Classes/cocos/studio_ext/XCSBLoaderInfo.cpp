#include "XCSBLoaderInfo.h"
#include "XCommon.h"
XCSBLoaderInfo::XCSBLoaderInfo() : m_pkFileBuffer(NULL), m_pkCSBContent(NULL)
{

}

XCSBLoaderInfo::~XCSBLoaderInfo()
{
	CC_SAFE_FREE(m_pkFileBuffer);
}

XCSBLoaderInfo* XCSBLoaderInfo::create()
{
	XCSBLoaderInfo* pkObject = new XCSBLoaderInfo();
	pkObject->autorelease();
	return pkObject;
}

void XCSBLoaderInfo::setData(const std::string& _csBuildID, unsigned char* pkFB)
{
	CC_SAFE_FREE(m_pkFileBuffer);
	m_pkFileBuffer = pkFB;
	m_pkCSBContent = flatbuffers::GetCSParseBinary(pkFB);
}

const flatbuffers::CSParseBinary* XCSBLoaderInfo::getData()
{
	return m_pkCSBContent;
}