#pragma once
#include "XResource/XAsyncLoader.h"

USING_NS_CC;

class XAsyncLoaderManager;
class XTextureAsyncLoader : public XAsyncLoader
{
protected:
	XTextureAsyncLoader();
public:
	virtual ~XTextureAsyncLoader();

	static XAsyncLoaderPtr create();

	virtual void start(void* param) override;

protected:
	bool tryDownload(const std::string& filename, const std::string& customID);

	void onDownload(const XAsyncLoaderRet* ret);

	void load(const std::string& filename, const std::string& customID);

	void cancelDownload();

	virtual void cleanup() override;

	XAsyncLoaderCallback*	m_pkDownloadCallback;
	Texture2D*				m_pkLoadedTexture;
};

