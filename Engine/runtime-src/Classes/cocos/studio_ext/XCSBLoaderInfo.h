#ifndef __XCSBLoaderInfo__
#define __XCSBLoaderInfo__


#include "cocos2d.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "cocostudio/CSParseBinary_generated.h"

USING_NS_CC;

class XCSBLoaderInfo : public Ref
{
protected:
	XCSBLoaderInfo();
public:
	virtual ~XCSBLoaderInfo();
	static XCSBLoaderInfo* create();
	//std::set<std::string>& getPlists() { return m_plistsSet; };
	void setData(const std::string& _buildID, unsigned char* pkFB);
	const flatbuffers::CSParseBinary* getData();
	const char* getFileName() const { return m_strFileName.c_str(); }
	void setFileName(const std::string& val) { m_strFileName = val; }
protected:
	unsigned char*							m_pkFileBuffer;
	const flatbuffers::CSParseBinary*		m_pkCSBContent;
	//std::set<std::string>					m_plistsSet;
	std::string								m_strFileName;

};

#endif /* defined(__cocos2d_libs__CSLoader__) */
