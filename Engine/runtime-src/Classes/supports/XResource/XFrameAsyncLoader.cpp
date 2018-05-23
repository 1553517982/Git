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
	// ��ʱ�ò���֡�첽���غ�����
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

	//// �����ؼ�֡����ָ�룬����Ѿ����ڴ棬�򷵻� true ��ʾ�Ѿ�׼������
	//// ���������ָ��û��׼���ã��������������б�׼������
	//std::set<std::string> readyToLoad;
	//for (XImageUnitList::iterator iter = pkFrameList->begin();
	//	iter != pkFrameList->end();
	//	iter++)
	//{
	//	//��ȡ֡��Ϣ
	//	XImageUnit* info = *iter;
	//	Texture2D *pTexture = pkTextureCache->getTextureForKey(info->textureName);
	//	if (!pTexture)
	//	{
	//		//�ŵ�Ԥ���б�
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

	//// ���ݼ����б���������
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
		//�ҵ�ʣ�µ�û���������ȡ����
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
	// �ص��ɹ�remove ID
	std::set<std::string>::iterator iter = m_subCallbackCustomIDS.find(retCode->customID());
	if (iter != m_subCallbackCustomIDS.end())
	{
		m_subCallbackCustomIDS.erase(iter);
	}
	// ����ɹ�����ʾ�ɹ�
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
		//���ʧ����ʾʧ��
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