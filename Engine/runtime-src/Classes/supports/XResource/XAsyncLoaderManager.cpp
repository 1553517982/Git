#include "XCommon.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XTextureAsyncLoader.h"
#include "XResource/XFrameAsyncLoader.h"
#include "XResource/XWebLoader.h"
#include "XResource/XCSBAsyncLoader.h"
#include "XResource/XUnzipLoader.h"
#include "XResource/XGroupAsyncLoader.h"
#include "XResource/XResourceUtils.h"
USING_NS_CC;

void removeXAsyncLoader(XAsyncLoaderPtrMap& map, const std::string& id)
{
	XAsyncLoaderPtrMap::iterator iter = map.find(id);
	if (iter != map.end())
	{
		map.erase(iter);
	}
}

static XAsyncLoaderManager*	gSharedManager = NULL;


XAsyncLoaderManager* XAsyncLoaderManager::sharedManager()
{
	if (gSharedManager)
		return gSharedManager;
	gSharedManager = new XAsyncLoaderManager();
	return gSharedManager;
}

void XAsyncLoaderManager::purgeSharedManager()
{
	CC_SAFE_DELETE(gSharedManager);
}

XAsyncLoaderManager::XAsyncLoaderManager()
{
	_textureCache = Director::getInstance()->getTextureCache();
	_fileUtils = FileUtils::getInstance();
	m_bNeedCollect = false;
}

XAsyncLoaderManager::~XAsyncLoaderManager()
{
	cancelAll();
}

int XAsyncLoaderManager::loadTexture(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback)
{
	TextureCache* pkTextureCache = Director::getInstance()->getTextureCache();
	Texture2D *pTexture = pkTextureCache->getTextureForKey(filename);
	if (pTexture)
	{
		XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eOK, pTexture, customID);
		callback->onAsyncLoad(&ret);
		return eLoaded;
	}

	XAsyncLoaderPtr ptr = nullptr;
	XAsyncLoaderPtrMap& _loaders = m_Loaders;
	std::string key = XL_TEXTURE_TAG + filename;
	XAsyncLoaderPtrMap::iterator iter = _loaders.find(key);

	//如果已经有加载中的loader
	if (iter != _loaders.end())
	{
		ptr = iter->second;
		ptr->addCallback(callback);
	}

	if (ptr == nullptr)
	{
		// create
		ptr = XTextureAsyncLoader::create();
//		CCLOG(" set texture callback !! 111 %s", key.c_str());
		_loaders.insert(std::make_pair(key, ptr));
		ptr->setRegistered(true);
		ptr->init(filename, customID, key, priority);
		ptr->addCallback(callback);
		ptr->start(nullptr);
	}

	return eReady;
}

int XAsyncLoaderManager::loadAnimation(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback)
{
	XAsyncLoaderPtr ptr;
	XAsyncLoaderPtrMap& _loaders = m_Loaders;
	std::string key = XL_ANIMATION_TAG + filename;
	XAsyncLoaderPtrMap::iterator iter = _loaders.find(key);

	//如果已经有加载中的loader
	if (iter != _loaders.end())
	{
		ptr = iter->second;
		ptr->addCallback(callback);
	}

	if (ptr == nullptr)
	{
		// create
		ptr = XFrameAsyncLoader::create();
		_loaders.insert(std::make_pair(key, ptr));
		ptr->setRegistered(true);
		ptr->init(filename, customID, key, priority);
		ptr->addCallback(callback);
		ptr->start(nullptr);
	}
	
	return eReady;
}

int XAsyncLoaderManager::loadWWW(XDownloader::Options& options, const std::string& customID, XAsyncLoaderCallback* callback)
{
	if (!options.bReplace && _fileUtils->isFileExist(options.strFilename))
	{
		XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eOK, nullptr, customID);
		callback->onAsyncLoad(&ret);
		return eLoaded;
	}

	XAsyncLoaderPtr ptr;
	XAsyncLoaderPtrMap& _loaders = m_Loaders;
	std::string key = XL_DOWNLOAD_TAG + options.strFilename;
	XAsyncLoaderPtrMap::iterator iter = _loaders.find(key);

	//如果已经有加载中的loader
	if (iter != _loaders.end())
	{
		ptr = iter->second;
#ifdef X_DEBUG
			if (options.getCallbackObject() && options.getCallbackObject()->getProgressCallback())
			{
				//只有第一个请求的监听能生效
				XLOGERROR("download file = %s url = %s has started progress func can not be set", options.strFilename.c_str(), options.strURL.c_str());
			}
#endif // X_DEBUG
		ptr->addCallback(callback);
	}
	if (ptr == nullptr)
	{
		// create
		ptr = XWebLoader::create();
		_loaders.insert(std::make_pair(key, ptr));
		ptr->setRegistered(true);
		ptr->init("", customID, key, 0);
		ptr->addCallback(callback);
		ptr->start(&options);
	}

	return eReady;
}


int XAsyncLoaderManager::loadCSBDependency(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback)
{
	return loadGroup(filename, customID, priority, callback);
	//XAsyncLoaderPtr ptr;
	//XAsyncLoaderPtrMap& _loaders = m_Loaders;
	//std::string key = XL_CSB_TAG + filename;
	//XAsyncLoaderPtrMap::iterator iter = _loaders.find(key);

	////如果已经有加载中的loader
	//if (iter != _loaders.end())
	//{
	//	ptr = iter->second;
	//	ptr->addCallback(callback);
	//}
	//if (ptr == nullptr)
	//{
	//	// create
	//	ptr = XCSBAsyncLoader::create();
	//	_loaders.insert(std::make_pair(key, ptr));
	//	ptr->setRegistered(true);
	//	ptr->init(filename, customID, key, priority);
	//	ptr->addCallback(callback);
	//	ptr->start(nullptr);
	//}


	//return eReady;
}

void XAsyncLoaderManager::cancelAll()
{
	std::list<XAsyncLoaderPtr> cancelList;

	for (XAsyncLoaderPtrMap::iterator iter = m_Loaders.begin();
		iter != m_Loaders.end();
		iter++)
	{
		cancelList.push_back(iter->second);
	}

	for (auto iter = cancelList.begin();
			  iter != cancelList.end();
			  iter++)
	{
		XAsyncLoaderPtr pkLoader = *iter;
		pkLoader->setRegistered(false);
		pkLoader->setCancelCallback(nullptr);
		pkLoader->cancel();
	}
	m_Loaders.clear();
}


int XAsyncLoaderManager::unzip(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback)
{
	XAsyncLoaderPtr ptr;
	XAsyncLoaderPtrMap& _loaders = m_Loaders;
	std::string key = XL_UNZIP_TAG + filename;
	XAsyncLoaderPtrMap::iterator iter = _loaders.find(key);

	//如果已经有加载中的loader
	if (iter != _loaders.end())
	{
		ptr = iter->second;
		ptr->addCallback(callback);
	}
	if (ptr == nullptr)
	{
		// create
		ptr = XUnzipLoader::create();
		_loaders.insert(std::make_pair(key, ptr));
		ptr->setRegistered(true);
		ptr->init(filename, customID, key, priority);
		ptr->addCallback(callback);
		ptr->start(nullptr);
	}
	return eReady;
}

int XAsyncLoaderManager::loadGroup(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback)
{
	XAsyncLoaderPtr ptr;
	XAsyncLoaderPtrMap& _loaders = m_Loaders;
	std::string key = XL_GROUP_TAG + filename;
	XAsyncLoaderPtrMap::iterator iter = _loaders.find(key);

	//如果已经有加载中的loader
	if (iter != _loaders.end())
	{
		ptr = iter->second;
		ptr->addCallback(callback);
	}
	if (ptr == nullptr)
	{
		// create
		ptr = XGroupAsyncLoader::create();
		_loaders.insert(std::make_pair(key, ptr));
		ptr->setRegistered(true);
		ptr->init(filename, customID, key, priority);
		ptr->addCallback(callback);
		ptr->start(nullptr);
	}

	return eReady;
}

void XAsyncLoaderManager::removeLoader(const std::string& filename)
{
	auto iter = m_Loaders.find(filename);
	if (iter != m_Loaders.end())
	{
		XAsyncLoaderPtr loader = iter->second;
		m_Loaders.erase(iter);
		return;
	}
	return;
}