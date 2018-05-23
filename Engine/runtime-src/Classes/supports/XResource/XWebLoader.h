#pragma once
#include "XResource/XAsyncLoader.h"
#include "download/XDownloader.h"
USING_NS_CC;

class XAsyncLoaderManager;


class XWebLoader : public XAsyncLoader
{
protected:
	XWebLoader();
public:

	virtual ~XWebLoader();

	static XAsyncLoaderPtr create();

	virtual void start(void* param) override;

protected:
	void _start(XDownloader::Options& option);
	bool tryDownload(XDownloader::Options& option);
	void onDownload(const XAsyncLoaderRet* ret);
	void onProgress(double code1, double code2,
					const std::string& url, const std::string& customID,
					unsigned int localFileSize);
	XDownloaderCallbackObject::ProgressCallback m_progressCallback;
	//XDownloader::Options* m_pkOptions;
};

