#include "SystemHelpers.h"
#include "cocos2d.h"
#include "base/ccUtils.h"
#include "XCommon.h"
#include "cocos/2d/Animation/XAnimationCache.h"

#include "XResource/XAsyncLoaderCallbacks.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XWebLoader.h"
#include "XResource/XResourceUtils.h"
#include "CCLuaEngine.h"
#include "ScriptCallbackHelpers.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

#include "cocostudio/ActionTimeline/CCActionTimelineCache.h"
#include "ResourceHelpers.h"
//#include "supports/utils/unzip/XUnzipUtils.h"
#include "helpers/XLambda.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"

typedef unsigned int tAsyncHandle;

static tAsyncHandle s_async_load_handler = 0;
Map<tAsyncHandle, XAsyncLoaderCallback*> s_callbackMap;
static XAsyncLoadOption s_XAsyncLoadOption;
static Scheduler* s_scheduler = nullptr;
static XLambda* s_onAsyncLoadFinished = NULL;


static void _eraseCallbackMap(unsigned int handle)
{
	if (handle)
	{
		s_callbackMap.erase(handle);
	}
}

static void _pushCallbackMap(int h, XAsyncLoaderCallback* pkCallback)
{
	s_callbackMap.insert(h, pkCallback);
	return;
}

class asyncLoadTracker
{
	asyncLoadTracker()
	{

	}
public:
	asyncLoadTracker(tAsyncHandle handle, XAsyncLoaderCallback* pkCallback, XAsyncLoaderFunction inputFunction)
	{
		m_handle = handle;
		m_onLoadCallback = inputFunction;
		_pushCallbackMap(m_handle, pkCallback);
	}

	~asyncLoadTracker()
	{
		_eraseCallbackMap(m_handle);
	}

	void onAsyncLoad(const XAsyncLoaderRet* ret)
	{
		if (m_onLoadCallback)
			m_onLoadCallback(ret);
	}

	static XAsyncLoaderFunction wrap(tAsyncHandle handle, XAsyncLoaderCallback* pkCallback, const XAsyncLoaderFunction& inputFunction)
	{
		auto tracker = std::shared_ptr<asyncLoadTracker>(new asyncLoadTracker(handle, pkCallback, inputFunction));
		handle = tracker->m_handle;
		XAsyncLoaderFunction wrap_func = [tracker](const XAsyncLoaderRet* ret)
		{
			tracker->onAsyncLoad(ret);
		};
		return wrap_func;
	}
protected:
	tAsyncHandle			m_handle;
	XAsyncLoaderFunction	m_onLoadCallback;
};


static const std::string& getStringFromOption(ValueMap& options, const char* key, const char* defaultValue)
{
	static std::string value = "";
	auto it = options.find(key);
	if (it == options.end())
	{
		value = defaultValue;
	}
	else
	{
		value = it->second.asString();
	}

	return value;
}

static bool getBooleanFromOption(ValueMap& options, const char* key, bool defaultValue)
{
	auto it = options.find(key);
	if (it == options.end())
	{
		return defaultValue;
	}
	else
	{
		return it->second.asBool();
	}
}

static int getIntFromOption(ValueMap& options, const char* key, int defaultValue)
{
	auto it = options.find(key);
	if (it == options.end())
	{
		return defaultValue;
	}
	else
	{
		return it->second.asInt();
	}
}

static int loadWWWNative(ValueMap& options, XLambda* okFunction, XLambda* errorFunction, XLambda* progressFunction, unsigned int handler)
{

	std::string filename = getStringFromOption(options, "file", "");
	if (filename.empty())
		return 0;
	
	unsigned char priority = getIntFromOption(options, "priority", 1);
	//XAssert(priority != BACKGROUND_PRELOAD_TASK, "loadWWW not allow using ucPriority = BACKGROUND_PRELOAD_TASK, use download Instead");
	XDownloaderCallbackObject* pkCallback = XDownloaderCallbackObject::create(filename);
	XDownloader::Options download_options = XDownloader::Options(filename,
		getStringFromOption(options, "url", ""),
		pkCallback,
		priority,
		getIntFromOption(options, "retry", 1),
		getBooleanFromOption(options, "replace", false));


	download_options.strMD5 = getStringFromOption(options, "md5", "");
	download_options.bResumeSupport = getBooleanFromOption(options, "resume", false);
	download_options.uRemotefileSize = getIntFromOption(options, "fileSize", 0);

	std::string strCustomID = getStringFromOption(options, "customID", filename.c_str());

	if (progressFunction)
	{
		XLambdaHolderPtr progressHandle = XLambdaHolder::create(progressFunction);

		XDownloaderCallbackObject::ProgressCallback onProgress = [progressHandle, filename, strCustomID](double code1, double code2,
			const std::string& url, const std::string& customID,
			unsigned int localFileSize)
		{
			auto _lambda = progressHandle->getLambda();
			_lambda->begin();
			_lambda->pushFloat(code1);
			_lambda->pushFloat(code2);
			_lambda->pushInt(localFileSize);
			//_lambda->pushString(strCustomID.c_str());
			//_lambda->pushString(filename.c_str());
			_lambda->invoke();
			//CCDLOG("onProgressCallback %d %f %f %s %s", code0, code1, code2, url.c_str(), customID.c_str());

		};
		pkCallback->setProgressCallback(onProgress);
	}

	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();

	//TODO
	XLambdaHolderPtr okHandle = XLambdaHolder::create(okFunction);

	XLambdaHolderPtr errorHandle = XLambdaHolder::create(errorFunction);

	//s_callbackMap.insert(handler, callback);

	auto load_callback = [okHandle, errorHandle](const XAsyncLoaderRet* ret)
	{
		if (ret->ret() == XAsyncLoaderCode::eOK)
		{
			auto _lambda = okHandle->getLambda();
			_lambda->begin();
			_lambda->pushString(ret->customID().c_str());
			//_lambda->pushString(filename.c_str());
			_lambda->invoke();
		}
		else
		{
			auto _lambda = errorHandle->getLambda();
			_lambda->begin();
			_lambda->pushString(ret->customID().c_str());
			_lambda->pushString(ret->getMessage().c_str());
			_lambda->invoke();
		}
	};
	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
	callback->init(wrap_callback);
	int retCode = XAsyncLoaderManager::sharedManager()->loadWWW(download_options, strCustomID, callback);
	if (retCode == XAsyncLoaderManager::eReady)
	{
		return handler;
	}
	return 0;
}

//bool downloadNative(ValueMap& options, XLambda* okFunction, XLambda* errorFunction, XLambda* progressFunction, unsigned int handler)
//{
//	std::string filename = getStringFromOption(options, "file", "");
//	if (filename.empty())
//		return false;
//	unsigned char priority = getIntFromOption(options, "priority", 1);
//	//XAssert(priority != BACKGROUND_PRELOAD_TASK, "loadWWW not allow using ucPriority = BACKGROUND_PRELOAD_TASK, use download Instead");
//	XDownloaderCallbackObject* pkCallback = XDownloaderCallbackObject::create(filename);
//	XDownloader::Options download_options = XDownloader::Options(filename,
//		getStringFromOption(options, "url", ""),
//		pkCallback,
//		priority,
//		getIntFromOption(options, "retry", 1));
//
//
//	download_options.strMD5 = getStringFromOption(options, "md5", "");
//	download_options.bResumeSupport = getBooleanFromOption(options, "resume", false);
//	download_options.uRemotefileSize = getIntFromOption(options, "fileSize", 0);
//
//	std::string strCustomID = getStringFromOption(options, "customID", filename.c_str());
//
//	if (progressFunction)
//	{
//		XLambdaHolderPtr progressHandle = XLambdaHolder::create(progressFunction);
//
//		XDownloaderCallbackObject::ProgressCallback onProgress = [progressHandle, filename, strCustomID](double code1, double code2,
//			const std::string& url, const std::string& customID,
//			unsigned int localFileSize)
//		{
//			auto _lambda = progressHandle->getLambda();
//			_lambda->begin();
//			_lambda->pushFloat(code1);
//			_lambda->pushFloat(code2);
//			_lambda->pushInt(localFileSize);
//			//_lambda->pushString(strCustomID.c_str());
//			//_lambda->pushString(filename.c_str());
//			_lambda->invoke();
//			//CCDLOG("onProgressCallback %d %f %f %s %s", code0, code1, code2, url.c_str(), customID.c_str());
//
//		};
//		pkCallback->setProgressCallback(onProgress);
//	}
//
//	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();
//
//	//TODO
//	XLambdaHolderPtr okHandle = XLambdaHolder::create(okFunction);
//
//	XLambdaHolderPtr errorHandle = XLambdaHolder::create(errorFunction);
//
//	//s_callbackMap.insert(handler, callback);
//
//	auto load_callback = [okHandle, errorHandle](const XAsyncLoaderRet* ret)
//	{
//		if (ret->ret() == XAsyncLoaderCode::eOK)
//		{
//			auto _lambda = okHandle->getLambda();
//			_lambda->begin();
//			_lambda->pushString(ret->customID().c_str());
//			//_lambda->pushString(filename.c_str());
//			_lambda->invoke();
//		}
//		else
//		{
//			auto _lambda = errorHandle->getLambda();
//			_lambda->begin();
//			_lambda->pushString(ret->customID().c_str());
//			_lambda->pushString(ret->getMessage().c_str());
//			_lambda->invoke();
//		}
//	};
//	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
//	callback->init(wrap_callback);
//	return XDownloader::getInstance()->downloadFile(download_options);
////	int retCode = XAsyncLoaderManager::sharedManager()->loadWWW(download_options, strCustomID, callback);
//	//if (retCode == XAsyncLoaderManager::eReady)
//	//{
//	//	return handler;
//	//}
//	//return false;
//}

/*------------------------------------------------------*/

void ResourceHelpers::init()
{
	s_scheduler = Director::getInstance()->getScheduler();
}

void ResourceHelpers::fini()
{
	//if (s_asyncFinishNotifier)
	//	LuaEngine::getInstance()->removeScriptHandler(s_asyncFinishNotifier);
	CC_SAFE_RELEASE_NULL(s_onAsyncLoadFinished);

	//if (!s_callbackMap.empty())
	//{
	//	XLOGERROR("s_callbackMap.size() %d", s_callbackMap.size());
	//}

	s_XAsyncLoadOption.m_callback = nullptr;
	cancelAllAsyncLoadScript();
}

bool ResourceHelpers::loadDependency(const char* szFilename)
{
	if (szFilename == nullptr)
	{
		XLOGERROR("load Dependency null");
		return false;
	}

	return CNewLoader::Inst().LoadResource(szFilename);
}

bool ResourceHelpers::LoadResourceTab(const char* szFilename)
{
	if (szFilename == nullptr)
	{
		XLOGERROR("load resource.tab null");
		return false;
	}

	return CNewLoader::Inst().LoadResrouceTab(szFilename);
}

bool ResourceHelpers::loadAnimationTab(const char* szFilename)
{
	if (szFilename == nullptr)
	{
		XLOGERROR("load animation.tab null");
		return false;
	}

	return CNewLoader::Inst().LoadAnimationTab(szFilename);
}

bool ResourceHelpers::loadMD5Tab(const char* szFilename)
{
	if (szFilename == nullptr)
	{
		XLOGERROR("load extend.m null");
		return false;
	}
	return CNewLoader::Inst().LoadMD5Tab(szFilename);
}

bool ResourceHelpers::loadConfigPack(const char * szConfigPack)
{
	if (!szConfigPack)
		return false;
	return CNewLoader::Inst().SyncLoadConfigPack(szConfigPack);
}

void ResourceHelpers::purgeCache()
{
	cocostudio::timeline::ActionTimelineCache::getInstance()->purge();
	XAnimationCache::getInstance()->removeUnusedAnimations();
	Director::getInstance()->purgeCachedData();
}

unsigned int ResourceHelpers::loadAnimationAsync(XAsyncLoadOption* option, unsigned int handler)
{
	if (option == nullptr)
	{
		XLOGERROR("loadTextureAsync null");
		return 0;
	}
	auto& filename = option->m_filename;
	auto& customID = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;

	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();

	//s_callbackMap.insert(handler, callback);
	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
	callback->init(wrap_callback);
	int retCode = XAsyncLoaderManager::sharedManager()->loadAnimation(filename, customID, priority, callback);
	if (retCode == XAsyncLoaderManager::eReady)
	{
		return handler;
	}
	return 0;
}

unsigned int ResourceHelpers::loadTextureAsync(XAsyncLoadOption* option, unsigned int handler)
{
	if (option == nullptr)
	{
		XLOGERROR("loadTextureAsync null");
		return 0;
	}
	auto& filename = option->m_filename;
	auto& customID = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;

	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();

	//s_callbackMap.insert(handler, callback);
	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
	callback->init(wrap_callback);
	auto retCode = XAsyncLoaderManager::sharedManager()->loadTexture(filename, customID, priority, callback);
	if (retCode == XAsyncLoaderManager::eReady)
	{
		return handler;
	}
	return 0;
}

int ResourceHelpers::loadWWW(ValueMap& pkMap, XLambda* okFunction, XLambda* errorFunction, XLambda* progressFunction, unsigned int handle)
{
	return loadWWWNative(pkMap, okFunction, errorFunction, progressFunction, handle);
}

//bool ResourceHelpers::download(ValueMap& pkMap, XLambda* okFunction, XLambda* errorFunction, XLambda* progressFunction, unsigned int handle)
//{
//	return downloadNative(pkMap, okFunction, errorFunction, progressFunction, handle);
//}

void ResourceHelpers::cancelLoadAsync(unsigned int handle)
{
	auto callback = s_callbackMap.at(handle);
	if (callback)
	{
		callback->cancel();
		s_callbackMap.erase(handle);
	}
}

XAsyncLoadOption* ResourceHelpers::getAsyncLoadOption(const char* filename,
	const char* customID,
	unsigned char priority,
	XLambda* handle)
{
	if (filename == nullptr || customID == nullptr)
	{
		XLOGERROR("getAsyncLoadOption == null");
		return NULL;
	}
	XLambdaHolderPtr handePtr = XLambdaHolder::create(handle);
	std::string skinname = filename;
	auto func = [handePtr, skinname](const XAsyncLoaderRet* ret)
	{
		auto _lambda = handePtr->getLambda();
		_lambda->begin();
		_lambda->pushInt(ret->ret());
		_lambda->pushString(ret->customID().c_str());
		_lambda->pushString(skinname.c_str());
		_lambda->pushString(ret->getMessage().c_str());
		_lambda->invoke();
	};
	s_XAsyncLoadOption.init(filename, customID, priority, func);
	return &s_XAsyncLoadOption;
}

unsigned int ResourceHelpers::loadCSBTextureAsync(XAsyncLoadOption* option, unsigned int handler)
{
	if (option == nullptr)
	{
		XLOGERROR("loadCSBTextureAsync null");
		return 0;
	}
	auto& filename = option->m_filename;
	auto& customID = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;
	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();

	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
	//s_callbackMap.insert(handler, callback);
	callback->init(wrap_callback);

	auto retCode = XAsyncLoaderManager::sharedManager()->loadCSBDependency(filename, customID, priority, callback);
	if (retCode == XAsyncLoaderManager::eReady)
	{
		return handler;
	}
	return 0;
}

//XCSLoadRet* ResourceHelpers::loadCSB(const char* filename, bool bWithTimeline, bool bCache)
//{
//	return XResourceUtils::loadCSB(filename, bWithTimeline, bCache, nullptr);
//}

XCSLoadRet* ResourceHelpers::loadCSB(const char* filename, bool bWithTimeline, bool bCache, XLambda* luaFunction)
{
	XLambdaHolderPtr _lambdaHolderPtr = XLambdaHolder::create(luaFunction);

	auto callback = [_lambdaHolderPtr](cocos2d::Ref* ref){
		if (nullptr == ref)
			return;
		auto _lambda = _lambdaHolderPtr->getLambda();
		_lambda->begin();
		_lambda->pushObject(ref, "cc.Ref");
		_lambda->invoke();
	};
	return XResourceUtils::loadCSB(filename, bWithTimeline, bCache, callback);
}

void ResourceHelpers::purgeCSBCache()
{
//	XCSLoader::getInstance()->removeUnusedInfo();
}

void ResourceHelpers::cancelAllAsyncLoadScript()
{
	//erase in loop will crash
	auto& cm = s_callbackMap;
	std::vector<XAsyncLoaderCallback*> removeList;
	for (auto it = cm.begin(); it != cm.end(); it++)
	{
		removeList.push_back(it->second);
	}

	for (auto it = removeList.begin(); it != removeList.end(); it++)
	{
		(*it)->cancel();
	}
	//cm.clear();
}

void ResourceHelpers::cancelAllAsyncLoad()
{
	cancelAllAsyncLoadScript();
	XAsyncLoaderManager::sharedManager()->cancelAll();
}

int ResourceHelpers::decompressAsync(const char* filename, unsigned int progressThreshold, XLambda* finish, XLambda* progress)
{
	if (filename == NULL)
		return 1;

	XLambdaHolderPtr finishPtr = XLambdaHolder::create(finish);
	XLambdaHolderPtr progressPtr = XLambdaHolder::create(progress);
	std::string strFilename = filename;
	auto finishCallback = [strFilename, finishPtr](int code)
	{
		auto _lambda = finishPtr->getLambda();
		_lambda->begin();
		_lambda->pushString(strFilename.c_str());
		_lambda->pushInt(code);
		_lambda->invoke();
	};

	auto progressCallback = [strFilename, progressPtr](double code1, double code2)
	{
		auto _lambda = progressPtr->getLambda();
		_lambda->begin();
		_lambda->pushString(strFilename.c_str());
		_lambda->pushInt(code1);
		_lambda->pushInt(code2);
		_lambda->invoke();
	};
	//XUnzipUtils::sharedUtils()->decompressAsync(filename, progressThreshold, finishCallback, progressCallback);
	return 0;
}

void ResourceHelpers::listenAsyncFinish(XLambda* finish)
{
	CC_SAFE_RELEASE_NULL(s_onAsyncLoadFinished);
	s_onAsyncLoadFinished = finish;
	CC_SAFE_RETAIN(s_onAsyncLoadFinished);
}

unsigned int ResourceHelpers::unzipLoaderAsync(XAsyncLoadOption* option, unsigned int handler)
{
	if (option == nullptr)
	{
		XLOGERROR("unzipAsync null");
		return 0;
	}
	auto& filename = option->m_filename;
	auto& customID = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;
	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();
	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
	//s_callbackMap.insert(handler, callback);
	callback->init(wrap_callback);
	auto retCode = XAsyncLoaderManager::sharedManager()->unzip(filename, customID, priority, callback);
	if (retCode == XAsyncLoaderManager::eReady)
	{
		return handler;
	}
	return 0;
}

void ResourceHelpers::cancelDecompressAsync(const char* filename)
{
	//XUnzipUtils::sharedUtils()->cancelDecompressAsync(filename);
}

unsigned int ResourceHelpers::loadGroupAsync(XAsyncLoadOption* option, unsigned int handler)
{
	if (option == nullptr)
	{
		XLOGERROR("loadGroupAsync null");
		return 0;
	}
	auto& filename = option->m_filename;
	auto& customID = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;
	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();

	auto wrap_callback = asyncLoadTracker::wrap(handler, callback, load_callback);
	//s_callbackMap.insert(handler, callback);
	callback->init(wrap_callback);

	auto retCode = XAsyncLoaderManager::sharedManager()->loadGroup(filename, customID, priority, callback);
	if (retCode == XAsyncLoaderManager::eReady)
	{
		return handler;
	}
	return 0;
}

bool ResourceHelpers::loadResourceConfig(const char* szFilename)
{
	return XResourceUtils::getResourceDataBase()->loadConfig(szFilename);
}