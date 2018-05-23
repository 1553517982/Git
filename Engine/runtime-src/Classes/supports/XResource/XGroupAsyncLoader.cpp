#include "XCommon.h"
#include "XResource/XGroupAsyncLoader.h"
#include "XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"
#include "cocos/studio_ext/XCSLoader.h"

XGroupAsyncLoader::XGroupAsyncLoader()
{
}

XGroupAsyncLoader::~XGroupAsyncLoader()
{
#ifdef _DEBUG
	for (auto iter = m_subCallbacks.begin();
		iter != m_subCallbacks.begin();
		iter++)
	{

		if (iter->second->getReferenceCount() > 1)
		{
			XLOGERROR("~XGroupAsyncLoader with subCallback %d", iter->second->getReferenceCount());
		}
	}
#endif // _DEBUG
}

XAsyncLoaderPtr XGroupAsyncLoader::create()
{
	XGroupAsyncLoader* pkLoader = new (std::nothrow) XGroupAsyncLoader();
	return XAsyncLoaderPtr(pkLoader);
}

void XGroupAsyncLoader::start(void* param)
{
	load(m_strFilename, m_customID);
}

void XGroupAsyncLoader::load(const std::string& groupFilename, const std::string& customID)
{
	//获取组别
	CCASSERT(m_subCallbackCustomIDS.empty(), "");
	m_subCallbackCustomIDS.clear();
	if (groupFilename.empty())
	{
		XLOGERROR("XGroupAsyncLoader::load failed [groupFilename == empty]");
		m_cancelCallback = nullptr;
		cancel();
		return;
	}
	//检查依赖
	XResourceDataBase* pkDataBase = XResourceUtils::getResourceDataBase();
	auto* pkNameList = pkDataBase->getResourceGroup(groupFilename);
	if (!pkNameList)
	{
		XLOGERROR("XGroupAsyncLoader::load %s failed [pkNameList == null]", groupFilename.c_str());
		m_cancelCallback = nullptr;
		cancel();
		return;
	}
	TextureCache* pkTextureCache = Director::getInstance()->getTextureCache();
	std::set<XResouceData*> needToLoad;
	// 遍历关键帧纹理指针，如果已经在内存，则返回 true 表示已经准备好了
	// 如果有纹理指针没有准备好，则加入纹理加载列表，准备加载
	//提早filter
	auto res = pkNameList->getResource();
	for (auto t_iter = res->begin();
		t_iter != res->end();
		t_iter++)
	{
		auto data = (*t_iter);
		switch (data->m_nType)
		{
			//检查纹理是否已经存在
			case XResouceDataTypes::eResTypeImage:
			{
				const std::string& textureName = data->m_strFilename;
				Texture2D *pTexture = pkTextureCache->getTextureForKey(textureName);
				if (!pTexture)
				{
					//放到预备列表
					needToLoad.insert(data);
					m_subCallbackCustomIDS.insert(data->m_strFilename);
				}
			}
			break;
			//检查知否Zip文件
			//case XResouceDataTypes::eResTypeZip:
			//{
			//	//放到预备列表
			//	readyToLoad.insert(data);
			//	m_subCallbackCustomIDS.insert(data->m_strFilename);
			//}
			//其他文件检查是否已经下载过了
			default:
			{
				if (!FileUtils::getInstance()->isFileExist(data->m_strFilename))
				{
					needToLoad.insert(data);
					m_subCallbackCustomIDS.insert(data->m_strFilename);
				}
			}
		}
	}

	if (needToLoad.empty())
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
			XGroupAsyncLoader* pkLoader = (XGroupAsyncLoader*)loader.get();
			pkLoader->onFileLoaded(ret);
		}
		else
		{
			XLOGINFO("XCSBAsyncLoader expired %s", groupFilename.c_str());
		}
	};

	// 根据加载列表，请求下载
	for (auto iter = needToLoad.begin();
			iter != needToLoad.end();
			  iter++)
	{
		auto data = (*iter);
		const std::string& subFilename = data->m_strFilename;
		switch (data->m_nType)
		{
			//如果是图片走图片加载流程
			case XResouceDataTypes::eResTypeImage:
			{
				XAsyncLoaderCallback* pkCallback = XAsyncLoaderCallback::create();
				pkCallback->init(textureCallback);
				m_subCallbacks.insert(subFilename, pkCallback);
				XAsyncLoaderManager::sharedManager()->loadTexture(subFilename, subFilename, m_priority, pkCallback);
			}
				break;

			//case eResTypeZip:
			//{
			//	XAsyncLoaderCallback* pkCallback = XAsyncLoaderCallback::create();
			//	pkCallback->init(textureCallback);
			//	m_subCallbacks.insert(subFilename, pkCallback);
			//	XAsyncLoaderManager::sharedManager()->unzip(subFilename, subFilename, m_priority, pkCallback);
			//}
			//	break;
			//否则尝试下载
			default:
			{
				XAsyncLoaderCallback* pkCallback = XAsyncLoaderCallback::create();
				pkCallback->init(textureCallback);
				m_subCallbacks.insert(subFilename, pkCallback);
				XDownloader::Options option = XDownloader::Options(subFilename, "", nullptr, m_priority, 2, false);
				XAsyncLoaderManager::sharedManager()->loadWWW(option, subFilename, pkCallback);
			}
				break;
		}
		
	}
}

void XGroupAsyncLoader::cancel()
{
	XAsyncLoader::cancel();
}

void XGroupAsyncLoader::cancelSubCallbacks()
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

void XGroupAsyncLoader::onFileLoaded(const XAsyncLoaderRet* retCode)
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

void XGroupAsyncLoader::onAsyncLoad(const XAsyncLoaderRet* ret)
{
	XAsyncLoader::onAsyncLoad(ret);
}

void XGroupAsyncLoader::cleanup()
{
	cancelSubCallbacks();
}