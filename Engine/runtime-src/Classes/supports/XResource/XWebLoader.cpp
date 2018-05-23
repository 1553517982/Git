#include "XCommon.h"
#include "XResource/XWebLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"


XWebLoader::XWebLoader()
{
}

XWebLoader::~XWebLoader()
{
	//CC_SAFE_DELETE(m_pkOptions);
}

XAsyncLoaderPtr XWebLoader::create()
{
	XWebLoader* pkLoader = new (std::nothrow) XWebLoader();
	return XAsyncLoaderPtr(pkLoader);
}

bool XWebLoader::tryDownload(XDownloader::Options& option)
{
	
	CCASSERT(m_cancelCallback == nullptr, "");

	std::string strFilename = option.strFilename;
	CCLOG("XAsyncLoader:XWebLoader start %s", strFilename.c_str());
	XAsyncLoaderPtr ptr = shared_from_this();
	FileUtils* _fileUtils = FileUtils::getInstance();

	// 先不管，一进来先创建目录，以防找不到文件夹
	//if (strFilename.find(".\\") == 0)
	//{
	//	strFilename = strFilename.substr(2);
	//}
	//int index = strFilename.find("\\");
	//if (index != -1)
	//{
	//	std::string prefix = strFilename.substr(0, index);
	//	strFilename = prefix + strFilename.substr(index + 1);
	//}
	//int pos = strFilename.rfind("/");
	//std::string dir = strFilename.substr(0, pos);
	//if (!_fileUtils->isDirectoryExist(dir))
	//{
	//	bool ret = FileUtils::getInstance()->createDirectory(dir);
	//	XLOG("createDirectory %s %d", dir.c_str(), ret);
	//}

	m_cancelCallback = [=]
	{
		XDownloader::getInstance()->cancelDownload(strFilename);
	};

	std::weak_ptr<XAsyncLoader> weak_p = ptr;

	//看看是否已经创建了！
	XDownloaderCallbackObject* pkCallback = option.getCallbackObject();
	if (pkCallback == nullptr)
	{
		pkCallback = XDownloaderCallbackObject::create(strFilename);
		option.setCallbackObject(pkCallback);
	}
#ifdef X_DEBUG
	if (pkCallback->getErrorCallback() != nullptr)
	{
		XLOGERROR("getErrorCallback should be null");
	}
	if (pkCallback->getSuccessCallback() != nullptr)
	{
		XLOGERROR("getSuccessCallback should be null");
	}
#endif // X_DEBUG

	XDownloaderCallbackObject::ErrorCallback onError = [weak_p, strFilename](unsigned int code0, unsigned int code1, unsigned int code2, const std::string custom_id)
	{
		if (!weak_p.expired())
		{
			CCLOG("XAsyncLoader:loadWWW error %s %d %d %d", strFilename.c_str(), code0, code1, code2);
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XWebLoader* pkLoader = ((XWebLoader*)loader.get());
			//XAsyncLoaderErrorData* data = XAsyncLoaderErrorData::create(code0, code1, code2);
			
			XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eDownloadError, nullptr, custom_id);
			char buf[256] = { 0 };
			snprintf(buf, 255, "%d-%d-%d", code0,code1,code2);
			ret.setMessage(buf);
			pkLoader->onDownload(&ret);
		}
		else
		{
			XLOGINFO("XAsyncLoader:loadWWW expired %s", strFilename.c_str());
		}
	};
	pkCallback->setErrorCallback(onError);


	XDownloaderCallbackObject::SuccessCallback onSuccess = [weak_p, strFilename](const std::string & filename, const std::string & url, const std::string & custom_id)
	{
		if (!weak_p.expired())
		{
			CCLOG("XAsyncLoader:loadWWW ok %s", strFilename.c_str());
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XWebLoader* pkLoader = ((XWebLoader*)loader.get());
			XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eOK, nullptr, custom_id);
			pkLoader->onDownload(&ret);
		}
		else
		{
			XLOGINFO("XWebLoader:tryDownload expired %s", strFilename.c_str());
		}
	};
	pkCallback->setSuccessCallback(onSuccess);

	m_progressCallback = pkCallback->getProgressCallback();
	if (m_progressCallback)
	{
		XDownloaderCallbackObject::ProgressCallback onProgress = [weak_p, strFilename](double code1, double code2,
			const std::string& url, const std::string& customID,
			unsigned int localFileSize)
		{
			if (!weak_p.expired())
			{
//				XLOG("XAsyncLoader:loadWWW progress %s", strFilename.c_str());
				std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
				XWebLoader* pkLoader = ((XWebLoader*)loader.get());
				pkLoader->onProgress(code1, code2, url, customID, localFileSize);
			}
			else
			{
				XLOGINFO("XWebLoader:loadWWW progress expired %s", strFilename.c_str());
			}
		};
		pkCallback->setProgressCallback(onProgress);
	}
	if (XDownloader::getInstance()->downloadFile(option) == false)
	{
		XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eDownloadError, nullptr, m_customID);
		ret.setMessage("0-0-0");
		onAsyncLoad(&ret);
		return false;
	}
	return true;
}

void XWebLoader::onDownload(const XAsyncLoaderRet* ret)
{
	onAsyncLoad(ret);
}

void XWebLoader::onProgress(double code1, double code2,
							const std::string& url, const std::string& customID,
							unsigned int localFileSize)
{
	if (m_progressCallback)
	{
		m_progressCallback(code1, code2, url, customID, localFileSize);
	}
}

void XWebLoader::_start(XDownloader::Options& option)
{
	//CC_SAFE_DELETE(m_pkOptions);
	//m_pkOptions = option.clone();
	if (tryDownload(option))
	{
		return;
	}
	XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eOK, nullptr, m_customID);
	onAsyncLoad(&ret);
}

void XWebLoader::start(void* param)
{
	if (!param)
		XLOGERROR("param == null");
	XDownloader::Options* option = (XDownloader::Options*) param;
	_start(*option);
}
