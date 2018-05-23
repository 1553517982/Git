#pragma once
#include "XResource/XAsyncLoader.h"

USING_NS_CC;

class XAsyncLoaderManager;
class XFrameAsyncLoader : public XAsyncLoader
{
protected:
	XFrameAsyncLoader();
public:
	virtual ~XFrameAsyncLoader();

	static XAsyncLoaderPtr create();

	virtual void cancel();

	virtual void start(void *) override;

	virtual void cleanup() override;

protected:
	void onTextureAsyncLoad(const XAsyncLoaderRet* ret);

	void cancelSubCallbacks();

	void load(const std::string& filename, const std::string& customID);

	virtual void onAsyncLoad(const XAsyncLoaderRet* ret);

	Map<std::string, XAsyncLoaderCallback*>			m_subCallbacks;
	std::set<std::string>							m_subCallbackCustomIDS;
};

