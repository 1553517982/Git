#include "XCommon.h"
#include "XResource/XCSBAsyncLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"
#include "cocos/studio_ext/XCSLoader.h"

XCSBAsyncLoader::XCSBAsyncLoader()
{
}

XCSBAsyncLoader::~XCSBAsyncLoader()
{
#ifdef _DEBUG
	for (auto iter = m_subCallbacks.begin();
		iter != m_subCallbacks.begin();
		iter++)
	{

		if (iter->second->getReferenceCount() > 1)
		{
			XLOGERROR("~XCSBAsyncLoader with subCallback %d", iter->second->getReferenceCount());
		}
	}
#endif // _DEBUG
}

XAsyncLoaderPtr XCSBAsyncLoader::create()
{
	XCSBAsyncLoader* pkLoader = new (std::nothrow) XCSBAsyncLoader();
	return XAsyncLoaderPtr(pkLoader);
}

void XCSBAsyncLoader::start(void* param)
{
	load(m_strFilename, m_customID);
}

void XCSBAsyncLoader::load(const std::string& filename, const std::string& customID)
{
	XLOGERROR("XCSBAsyncLoader::loading >>>>>>>>>>>>>>>>>>>>>>>>>> %s", filename.c_str());
	CCASSERT(m_subCallbackCustomIDS.empty(), "");
	m_subCallbackCustomIDS.clear();

	//XCSBLoaderInfo* pkInfo = XCSLoader::getInstance()->loadCSBInfo(filename,true);
	//if (pkInfo == NULL)
	//{
	//	XLOGERROR("XCSBAsyncLoader::load %s failed", filename.c_str());
	//	m_cancelCallback = nullptr;
	//	cancel();
	//	return;
	//}
	TextureCache* pkTextureCache = Director::getInstance()->getTextureCache();

	XResourceDataBase* pkDataBase = XResourceUtils::getResourceDataBase();
	// 遍历关键帧纹理指针，如果已经在内存，则返回 true 表示已经准备好了
	// 如果有纹理指针没有准备好，则加入纹理加载列表，准备加载
	std::set<std::string> readyToLoad;
	auto* pkNameList = pkDataBase->getResourceGroup(filename);
	if (!pkNameList)
	{
		XLOGERROR("XCSBAsyncLoader::load %s failed [pkNameList == null]", filename.c_str());
		m_cancelCallback = nullptr;
		cancel();
		return;
	}

	auto res = pkNameList->getResource();
	for (auto t_iter = res->begin();
		t_iter != res->end();
		t_iter++)
	{
		auto data = (*t_iter);
		if (data->m_nType == XResouceDataTypes::eResTypeImage)
		{
			const std::string& textureName = data->m_strFilename;
			Texture2D *pTexture = pkTextureCache->getTextureForKey(textureName);
			if (!pTexture)
			{
				//放到预备列表
				readyToLoad.insert(textureName);
				m_subCallbackCustomIDS.insert(textureName);
			}
		}
	}

	if (readyToLoad.empty())
	{
		XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eOK, nullptr, customID);
		onAsyncLoad(&ret);
		return;
	}

	CCAssert(m_subCallbacks.empty(), "XCSBAsyncLoader::load old callback remains");

	XAsyncLoaderPtr ptr = shared_from_this();
	std::string key = m_loaderKey;

	std::weak_ptr<XAsyncLoader> weak_p = ptr;
	auto textureCallback = [=](const XAsyncLoaderRet* ret)
	{
		if (!weak_p.expired())
		{
			std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
			XCSBAsyncLoader* pkLoader = (XCSBAsyncLoader*)loader.get();
			pkLoader->onTextureAsyncLoad(ret);
		}
		else
		{
			XLOGINFO("XCSBAsyncLoader expired %s", filename.c_str());
		}
	};

	// 根据加载列表，请求下载
	for (std::set<std::string>::iterator iter = readyToLoad.begin();
		iter != readyToLoad.end();
		iter++)
	{
		const std::string& textureName = (*iter);
		XAsyncLoaderCallback* pkCallback = XAsyncLoaderCallback::create();
		pkCallback->init(textureCallback);
		m_subCallbacks.insert(textureName, pkCallback);
		XAsyncLoaderManager::sharedManager()->loadTexture(textureName, textureName, m_priority, pkCallback);
	}	
}

void XCSBAsyncLoader::cancel()
{
	XAsyncLoader::cancel();
}

void XCSBAsyncLoader::cancelSubCallbacks()
{
	if (!m_subCallbacks.empty())
	{
		//找到剩下的没处理的请求，取消掉
		for (std::set<std::string>::iterator iter = m_subCallbackCustomIDS.begin();
			iter != m_subCallbackCustomIDS.end();
			iter++)
		{
			auto iter2 = m_subCallbacks.find(*iter);
			if (iter2 != m_subCallbacks.end())
			{
				iter2->second->cancel();
			}
		}
		m_subCallbacks.clear();
	}

	if (!m_subCallbackCustomIDS.empty())
	{
		m_subCallbackCustomIDS.clear();
	}
}

void XCSBAsyncLoader::onTextureAsyncLoad(const XAsyncLoaderRet* retCode)
{
	// 回调成功remove ID
	std::set<std::string>::iterator iter = m_subCallbackCustomIDS.find(retCode->customID());
	if (iter != m_subCallbackCustomIDS.end())
	{
		m_subCallbackCustomIDS.erase(iter);
	}
	// 如果成功，提示成功
	XAsyncLoaderCode result = (XAsyncLoaderCode)retCode->ret();
	
	if (result == XAsyncLoaderCode::eOK)
	{
		if (m_subCallbackCustomIDS.empty())
		{
			XAsyncLoaderRet realRet = XAsyncLoaderRet(result, nullptr, m_customID);
			onAsyncLoad(&realRet);
		}
	}
	else
	{
		//如果失败提示失败
		XAsyncLoaderRet realRet = XAsyncLoaderRet(result, nullptr, m_customID);
		onAsyncLoad(&realRet);
	}
}

void XCSBAsyncLoader::onAsyncLoad(const XAsyncLoaderRet* ret)
{
	XAsyncLoader::onAsyncLoad(ret);
}

void XCSBAsyncLoader::cleanup()
{
	cancelSubCallbacks();
}