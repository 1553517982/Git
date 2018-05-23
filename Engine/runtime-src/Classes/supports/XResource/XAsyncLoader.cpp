#include "XResource/XAsyncLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "download/XDownloaderUnit.h"
#include "download/XDownloader.h"

static unsigned int s_global_ID = 0;


	
XAsyncLoader::XAsyncLoader() : 
	m_nID(0),
	m_bLoopingEvents(false),
	m_bRegistered(false),
	m_priority(0),
	m_cancelCallback(nullptr)
{
	++s_global_ID;
	m_nID = s_global_ID;
}

XAsyncLoader::~XAsyncLoader()
{
	for (XAsyncLoaderCallbackMap::iterator iter = m_loadCallbacks.begin();
		iter != m_loadCallbacks.end();
		iter++)
	{
		(*iter)->reset();
		(*iter)->release();
	}
}

void XAsyncLoader::init(const std::string& filename, const std::string& customID, const std::string& key, unsigned char p)
{
	CCASSERT(m_loadCallbacks.size() == 0, "XAsyncLoader::init");
	m_strFilename = filename;
	m_customID = customID;
	m_loaderKey = key;
	m_priority = p;
}

void XAsyncLoader::cancel()
{
	removeReference();
	//清空重置回调列表
	for (XAsyncLoaderCallbackMap::iterator iter = m_loadCallbacks.begin();
		iter != m_loadCallbacks.end();
		iter++)
	{
		(*iter)->reset();
		(*iter)->release();
	}

	m_loadCallbacks.clear();

	// 执行清空回调
	if (m_cancelCallback)
	{
		m_cancelCallback();
		m_cancelCallback = nullptr;
	}
	cleanup();
}

void XAsyncLoader::addCallback(XAsyncLoaderCallback* callback)
{
	CCAssert(m_bLoopingEvents == false, "XAsyncLoader::addCallback");
	if (m_bLoopingEvents == false)
	{
		if (m_loadCallbacks.find(callback) == m_loadCallbacks.end())
		{
			XAsyncLoaderPtr ptr = shared_from_this();
			callback->setOwner(ptr);
			callback->retain();
			m_loadCallbacks.insert(callback);
		}
		else
		{
			XLOGERROR("XAsyncLoader::addCallback dupilcated");
		}
	}	
}

void XAsyncLoader::removeCallback(XAsyncLoaderCallback* callback)
{
	CCAssert(m_bLoopingEvents == false, "XAsyncLoader::removeCallback");
	for (XAsyncLoaderCallbackMap::iterator iter = m_loadCallbacks.begin();
		iter != m_loadCallbacks.end();
		iter++)
	{
		XAsyncLoaderCallback* ptr = *iter;
		if (ptr == callback)
		{
			ptr->release();
			m_loadCallbacks.erase(iter);
			break;
		}
	}

	//没人关注了就删除自己
	if (m_loadCallbacks.empty())
	{
		onNobodyCares();
	}
}

void XAsyncLoader::onAsyncLoad(const XAsyncLoaderRet* ret)
{
	//加载结束
	removeReference();

	//无需取消了
	m_cancelCallback = nullptr;

	//删除回调列表
	std::list<XAsyncLoaderCallback*> callbacks;
	for (XAsyncLoaderCallbackMap::iterator iter = m_loadCallbacks.begin();
		iter != m_loadCallbacks.end();
		iter++)
	{
		XAsyncLoaderCallback* ptr = *iter;
		callbacks.push_back(ptr);
	}
	m_loadCallbacks.clear();

	// 清理垃圾
	cleanup();

	//回调到目标
	for (auto it = callbacks.begin(); it != callbacks.end(); it++)
	{
		auto ptr = *it;
		ptr->onAsyncLoad(ret);
		ptr->release();
	}
}

void XAsyncLoader::clearCallback()
{
	//清空重置回调列表
	for (XAsyncLoaderCallbackMap::iterator iter = m_loadCallbacks.begin();
		iter != m_loadCallbacks.end();
		iter++)
	{
		(*iter)->reset();
		(*iter)->release();
	}

	m_loadCallbacks.clear();
	m_cancelCallback = nullptr;
}


void XAsyncLoader::onNobodyCares()
{
	removeReference();
	if (m_cancelCallback)
	{
		m_cancelCallback();
		m_cancelCallback = nullptr;
	}
	cleanup();
}

void XAsyncLoader::removeReference()
{
	if (m_bRegistered)
	{
		m_bRegistered = false;
		XAsyncLoaderManager::sharedManager()->removeLoader(m_loaderKey);
	}
}