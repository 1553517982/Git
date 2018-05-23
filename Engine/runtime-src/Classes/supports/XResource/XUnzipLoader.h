#pragma once
#include "XResource/XAsyncLoader.h"

USING_NS_CC;

class XAsyncLoaderManager;

class XUnzipLoader : public XAsyncLoader
{
protected:
	XUnzipLoader();
public:
	virtual ~XUnzipLoader();

	static XAsyncLoaderPtr create();

	virtual void start(void* param) override;

protected:
	bool tryDownload(const std::string& filename, const std::string& customID);

	void onDownload(const XAsyncLoaderRet* ret);

	void load(const std::string& filename, const std::string& customID);

	void cancelDownload();

	XAsyncLoaderCallback* m_pkDownloadCallback;
};

