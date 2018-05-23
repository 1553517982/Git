#include "XCommon.h"
#include "XResource/XUnzipLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"
#include "supports/utils/unzip/XUnzipUtils.h"

XUnzipLoader::XUnzipLoader() : m_pkDownloadCallback(nullptr)
{
}

XUnzipLoader::~XUnzipLoader()
{
	if (m_pkDownloadCallback)
	{
		m_pkDownloadCallback->cancel();
		m_pkDownloadCallback->release();
	}
}

XAsyncLoaderPtr XUnzipLoader::create()
{
	XUnzipLoader* pkLoader = new (std::nothrow) XUnzipLoader();
	return XAsyncLoaderPtr(pkLoader);
}




void XUnzipLoader::load(const std::string& filename, const std::string& customID)
{
	CCASSERT(m_cancelCallback == nullptr, "");
	XAsyncLoaderPtr ptr = shared_from_this();
	m_cancelCallback = [=]
	{
		XLOG("XUnzipLoader canceled %s", filename.c_str());
		XUnzipUtils::sharedUtils()->cancelDecompressAsync(filename);
	};

	std::weak_ptr<XAsyncLoader> weak_p = ptr;


	auto finishCallback = [=](int code)
	{
		if (!weak_p.expired())
		{
			XLOG("XUnzipLoader result %s", filename.c_str());
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XAsyncLoaderErrorData* data = nullptr;
			if (code == XUnzipUtils::DecompressErrorCode::OK)
			{
				code = XAsyncLoaderCode::eOK;
			}
			else
			{
				//code = code;
				//data = XAsyncLoaderErrorData::create(XAsyncLoaderCode::eUnzipError, 0, 0);
			}
			XAsyncLoaderRet ret = XAsyncLoaderRet(code, nullptr, customID);
			loader->onAsyncLoad(&ret);
		}
		else
		{
			XLOGINFO("XUnzipLoader expired %s", filename.c_str());
		}
	};
	XUnzipUtils::sharedUtils()->decompressAsync(filename, 0xffff, finishCallback, nullptr);
}

void XUnzipLoader::cancelDownload()
{
	if (m_pkDownloadCallback)
	{
		m_pkDownloadCallback->cancel();
		CC_SAFE_RELEASE_NULL(m_pkDownloadCallback);
	}
}

bool XUnzipLoader::tryDownload(const std::string& filename, const std::string& customID)
{
	CCASSERT(m_cancelCallback == nullptr, "");
	XAsyncLoaderPtr ptr = shared_from_this();
	FileUtils* _fileUtils = FileUtils::getInstance();
	if (_fileUtils->isFileExist(filename))
	{
		return false;
	}

	cancelDownload();

	m_pkDownloadCallback = XAsyncLoaderCallback::create();
	m_pkDownloadCallback->retain();

	//调用cancel时执行
	m_cancelCallback = [this]
	{
		this->cancelDownload();
	};
	std::weak_ptr<XAsyncLoader> weak_p = ptr;
	auto _downloadCallback = [=](const XAsyncLoaderRet* ret)
	{
		if (!weak_p.expired())
		{
			XLOG("XAsyncLoader:loadWWW error %s %d", filename.c_str(), ret->ret());
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XUnzipLoader* pkLoader = dynamic_cast<XUnzipLoader*>(loader.get());
			if (pkLoader)
				pkLoader->onDownload(ret);
			else
			{
				XLOGERROR("cast failed");
			}
		}
		else
		{
			XLOGINFO("XUnzipLoader:tryDownload expired %s", filename.c_str());
		}
	};
	m_pkDownloadCallback->init(_downloadCallback);
	//使用WWWLoader创建XDownloaderCallbackObject
	XDownloader::Options option = XDownloader::Options(filename, "", nullptr, m_priority, 2, false);
	XAsyncLoaderManager::sharedManager()->loadWWW(option, customID, m_pkDownloadCallback);
	return true;
}

void XUnzipLoader::onDownload(const XAsyncLoaderRet* retCode)
{
	if (retCode->ret() == XAsyncLoaderCode::eOK)
	{
		m_cancelCallback = nullptr;
		load(m_strFilename, m_customID);
	}
	else
	{
		onAsyncLoad(retCode);
	}
}

void XUnzipLoader::start(void* param)
{
	if (tryDownload(m_strFilename, m_customID))
	{
		return;
	}
	load(m_strFilename, m_customID);
}
