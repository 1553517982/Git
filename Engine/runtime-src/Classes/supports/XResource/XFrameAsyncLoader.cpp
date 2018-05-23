#include "XCommon.h"
#include "XResource/XFrameAsyncLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"

XFrameAsyncLoader::XFrameAsyncLoader()
{

}

XFrameAsyncLoader::~XFrameAsyncLoader()
{
#ifdef _DEBUG
	for (auto iter = m_subCallbacks.begin();
		iter != m_subCallbacks.begin();
		iter++)
	{
		if (iter->second->getReferenceCount() > 1)
		{
			XLOGERROR("!XFrameAsyncLoader with subCallback %d", iter->second->getReferenceCount());
		}
	}
#endif // _DEBUG
}

XAsyncLoaderPtr XFrameAsyncLoader::create()
{
	XFrameAsyncLoader* pkLoader = new (std::nothrow) XFrameAsyncLoader();
	return XAsyncLoaderPtr(pkLoader);
}

void XFrameAsyncLoader::load(const std::string& filename, const std::string& customID)
{
	// removed by aXing on 2017-4-15
	// 暂时用不到帧异步加载函数了
	return;
	//CCASSERT(m_subCallbackCustomIDS.empty(), "");
	//m_subCallbackCustomIDS.clear();

	//XImageUnitList* pkFrameList = XResourceUtils::getFrameList(filename.c_str());
	//if (pkFrameList == NULL)
	//{
	//	XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eNotFound, nullptr, customID);
	//	onAsyncLoad(&ret);
	//	return;
	//}


	//TextureCache* pkTextureCache = Director::getInstance()->getTextureCache();

	//// 遍历关键帧纹理指针，如果已经在内存，则返回 true 表示已经准备好了
	//// 如果有纹理指针没有准备好，则加入纹理加载列表，准备加载
	//std::set<std::string> readyToLoad;
	//for (XImageUnitList::iterator iter = pkFrameList->begin();
	//	iter != pkFrameList->end();
	//	iter++)
	//{
	//	//获取帧信息
	//	XImageUnit* info = *iter;
	//	Texture2D *pTexture = pkTextureCache->getTextureForKey(info->textureName);
	//	if (!pTexture)
	//	{
	//		//放到预备列表
	//		readyToLoad.insert(info->textureName);
	//		m_subCallbackCustomIDS.insert(info->textureName);
	//	}
	//}

	//if (readyToLoad.empty())
	//{
	//	XAsyncLoaderRet ret = XAsyncLoaderRet(XAsyncLoaderCode::eOK, nullptr, customID);
	//	onAsyncLoad(&ret);
	//	return;
	//}

	//CCAssert(m_subCallbacks.empty(), "XFrameAsyncLoader::load old callback remains");

	//XAsyncLoaderPtr ptr = shared_from_this();
	//std::string key = m_loaderKey;

	//std::weak_ptr<XAsyncLoader> weak_p = ptr;
	//auto textureCallback = [=](const XAsyncLoaderRet* ret)
	//{
	//	if (!weak_p.expired())
	//	{
	//		std::shared_ptr<XAsyncLoader> loader = weak_p.lock();
	//		XFrameAsyncLoader* pkLoader = (XFrameAsyncLoader*)loader.get();
	//		pkLoader->onTextureAsyncLoad(ret);
	//	}
	//	else
	//	{
	//		XLOGINFO("XTextureAsyncLoader expired %s", filename.c_str());
	//	}
	//};

	//// 根据加载列表，请求下载
	//for (std::set<std::string>::iterator iter = readyToLoad.begin();
	//	iter != readyToLoad.end();
	//	iter++)
	//{
	//	const std::string& textureName = (*iter);
	//	XAsyncLoaderCallback* pkCallback = XAsyncLoaderCallback::create();
	//	pkCallback->init(textureCallback);
	//	m_subCallbacks.insert(textureName, pkCallback);
	//	XAsyncLoaderManager::sharedManager()->loadTexture(textureName, textureName, m_priority, pkCallback);
	//}	
}

void XFrameAsyncLoader::cancel()
{
	XAsyncLoader::cancel();
}

void XFrameAsyncLoader::cancelSubCallbacks()
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
		m_subCallbackCustomIDS.clear();
	}
	else
	{
		XAssert(m_subCallbackCustomIDS.empty(),"m_subCallbackCustomIDS should be empty");
	}
}

void XFrameAsyncLoader::onTextureAsyncLoad(const XAsyncLoaderRet* retCode)
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

void XFrameAsyncLoader::onAsyncLoad(const XAsyncLoaderRet* ret)
{
	XAsyncLoader::onAsyncLoad(ret);
}


void XFrameAsyncLoader::start(void* param)
{
	load(m_strFilename, m_customID);
}

void XFrameAsyncLoader::cleanup()
{
	cancelSubCallbacks();
}