#ifndef __cocos2d_libs__XCSLoader__
#define __cocos2d_libs__XCSLoader__

#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocos2d.h"
#include "base/ObjectFactory.h"
//--------------------------------
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "XCSBLoaderInfo.h"
#include "XCSLoaderRet.h"
//--------------------------------
USING_NS_CC;

class XRefHolder : public Ref
{
public:
	XRefHolder()	{};
	virtual ~XRefHolder() override  {};
	static XRefHolder* create();
	cocos2d::Vector<Ref*>*	getRefs()	{ return &m_refs; }
	void addRef(Ref* r)					{ m_refs.pushBack(r); }
private:
	cocos2d::Vector<Ref*>				  m_refs;
};

class XCSLoader : public CSLoader
{
public:
	enum LOADINGTYPE
	{
		LOAD_NULL,
		LOAD_NODE,
		LOAD_TIMELINE,
		LOAD_ANIMATED_NODE
	};

	static XCSLoader* getInstance();
    static void destroyInstance();
    
	XCSLoader();
	virtual ~XCSLoader();

	void removeUnusedInfo();

	XCSBLoaderInfo* loadCSBInfo(const std::string& filename, bool bCache);

	

	Node* nodeWithCSBInfo(XCSBLoaderInfo* pkInfo, const ccNodeLoadCallback &callback);

	cocostudio::timeline::ActionTimeline* timeLineWithCSBInfo(XCSBLoaderInfo* pkInfo);

	XCSLoadRet* loadCSB(const std::string& filename, bool bWithTimeline, bool bCache, const ccNodeLoadCallback &callback);


protected:
	void loadPlistFromCSBInfo(XCSBLoaderInfo* szFilename, XRefHolder* holder);
	void _loadDependency(const char* szFilename, XRefHolder* holder);

	static unsigned char					m_uLoadingType;
	Map<std::string, XCSBLoaderInfo*>		m_csbFiles;
};

#endif /* defined(__cocos2d_libs__CSLoader__) */
