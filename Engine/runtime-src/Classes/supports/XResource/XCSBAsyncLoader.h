#pragma once
#include "XResource/XAsyncLoader.h"
#include "cocos/studio_ext/XCSBLoaderInfo.h"
#include "cocos/studio_ext/XActionTimelineCache.h"

USING_NS_CC;

class XAsyncLoaderManager;
class XCSBAsyncLoader : public XAsyncLoader
{
protected:
	XCSBAsyncLoader();
public:
	virtual ~XCSBAsyncLoader();

	static XAsyncLoaderPtr create();

	virtual void start(void *) override;

	virtual void cancel();

	virtual void cleanup() override;

protected:
	void onTextureAsyncLoad(const XAsyncLoaderRet* ret);
	
	void cancelSubCallbacks();

	void load(const std::string& filename, const std::string& customID);

	virtual void onAsyncLoad(const XAsyncLoaderRet* ret);

	Map<std::string, XAsyncLoaderCallback*>			m_subCallbacks;
	std::set<std::string>							m_subCallbackCustomIDS;
};

