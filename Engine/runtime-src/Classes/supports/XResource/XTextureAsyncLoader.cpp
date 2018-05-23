#include "XCommon.h"
#include "XResource/XTextureAsyncLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"
#include "download/XDownloader.h"


XTextureAsyncLoader::XTextureAsyncLoader() : m_pkDownloadCallback(nullptr), m_pkLoadedTexture(nullptr)
{
}

XTextureAsyncLoader::~XTextureAsyncLoader() 
{
	if (m_pkDownloadCallback)
	{
		m_pkDownloadCallback->cancel();
		m_pkDownloadCallback->release();
	}
	CC_SAFE_RELEASE_NULL(m_pkLoadedTexture);
}

XAsyncLoaderPtr XTextureAsyncLoader::create()
{
	XTextureAsyncLoader* pkLoader = new (std::nothrow) XTextureAsyncLoader();
	return XAsyncLoaderPtr(pkLoader);
}

void XTextureAsyncLoader::load(const std::string& filename, const std::string& customID)
{
	CCASSERT(m_cancelCallback == nullptr, "");
	XAsyncLoaderPtr ptr = shared_from_this();
	m_cancelCallback = [=]
	{
//		XLOG("loadTexture canceled %s", filename.c_str());
		XResourceUtils::unbindImageAsync(filename);
	};

	std::weak_ptr<XAsyncLoader> weak_p = ptr;

	auto loadTextureCallback = [=](Texture2D* pkTexture)
	{
		if (!weak_p.expired())
		{
//			XLOG("loadTexture result %s", filename.c_str());
			XAssert(m_pkLoadedTexture == nullptr, "m_pkLoadedTexture should be nullptr");
			if (pkTexture)
			{
				m_pkLoadedTexture = pkTexture;
				pkTexture->retain();
			}
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XAsyncLoaderRet ret = XAsyncLoaderRet(pkTexture != nullptr ? XAsyncLoaderCode::eOK : XAsyncLoaderCode::eFileLoadError,
				pkTexture, customID);
			loader->onAsyncLoad(&ret);
		}
		else
		{
			XLOGINFO("XTextureAsyncLoader expired %s", filename.c_str());
		}
	};
	XResourceUtils::loadImageAsync(filename, loadTextureCallback);
}

void XTextureAsyncLoader::cancelDownload()
{
	if (m_pkDownloadCallback)
	{
		m_pkDownloadCallback->cancel();
		CC_SAFE_RELEASE_NULL(m_pkDownloadCallback);
	}
}

bool XTextureAsyncLoader::tryDownload(const std::string& filename, const std::string& customID)
{
//	XLOG("XAsyncLoader:loadWWW start %s", filename.c_str());
	CCASSERT(m_cancelCallback == nullptr, "");
	// added by aXing on 2017-6-2
	// 尝试下载贴图的判断，加上版本好的判断
	// 这个修改需要配合一个地方:
	// 1, 在跨场景的时候，去保存一下
	std::string newVersion = Director::getInstance()->getTextureCache()->getFileVersion(filename);
	std::string curVersion = CNewLoader::Inst().loadKey(filename.c_str());
	if (curVersion == newVersion && FileUtils::getInstance()->isFileExist(filename))
//	if (FileUtils::getInstance()->isFileExist(filename))
	{
		return false;
	}

	XAsyncLoaderPtr ptr = shared_from_this();
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
//			XLOG("XAsyncLoader:loadWWW error %s %d", filename.c_str(), ret->ret());
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XTextureAsyncLoader* pkLoader = dynamic_cast<XTextureAsyncLoader*>(loader.get());
			if (pkLoader)
				pkLoader->onDownload(ret);
			else
			{
				XLOGERROR("cast failed");
			}
		}
		else
		{
			XLOGINFO("XTextureAsyncLoader:tryDownload expired %s", filename.c_str());
		}
		// 如果下载成功，则记录一下版本号
		if (ret->ret()== XAsyncLoaderCode::eOK)
		{
			CNewLoader::Inst().saveKey(filename.c_str(), newVersion.c_str());
		}
	};
	m_pkDownloadCallback->init(_downloadCallback);
	//使用WWWLoader创建XDownloaderCallbackObject
	std::string urlPath = UserDefault::getInstance()->getStringForKey("resource_download", ""); 
	std::string version = Director::getInstance()->getTextureCache()->getFileVersion(filename);
	if (!urlPath.empty() && !version.empty())
	{
		std::string url = urlPath + version + "/" + filename;
		XDownloader::Options option = XDownloader::Options(filename, url, nullptr, m_priority, 2, true);
		XAsyncLoaderManager::sharedManager()->loadWWW(option, customID, m_pkDownloadCallback);
	}
	else{
		XLOGERROR("texture AsyncLoader :: resource_download is null!!! %s or version is null!! :: %s", urlPath.c_str(), filename.c_str());
	}
	return true;
}

void XTextureAsyncLoader::onDownload(const XAsyncLoaderRet* retCode)
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

void XTextureAsyncLoader::start(void* param)
{
	// added by aXing on 2017-4-21
	// 为了调试闪退问题，添加一个接口，尝试用lua可以关闭边玩边下载功能
	bool isShutTextureAsync = UserDefault::getInstance()->getBoolForKey("isShutTextureAsync", false);
	if (!isShutTextureAsync && tryDownload(m_strFilename, m_customID))
	{
		return;
	}
	load(m_strFilename, m_customID);
}

void XTextureAsyncLoader::cleanup()
{
	CC_SAFE_RELEASE_NULL(m_pkLoadedTexture);
	XAsyncLoader::cleanup();
}