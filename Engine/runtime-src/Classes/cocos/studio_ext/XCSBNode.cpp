#include "XCSBNode.h"
#include "cocos/studio_ext/XCSLoader.h"
#include "XCommon.h"
#include "supports/XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"
#include "CCLuaEngine.h"

XCSBNode::XCSBNode() 
	: m_pkCallback(NULL)
	, m_pkTimeline(NULL)
	, m_pkNode(NULL)
	, m_asyncOption(NULL)
	, m_asyncNodeCallback(nullptr)
{

}

XCSBNode::~XCSBNode()
{
	if (m_pkCallback)
	{
		m_pkCallback->cancel();
		m_pkCallback->release();
	}
	CC_SAFE_RELEASE(m_pkTimeline);
}

XCSBNode* XCSBNode::create()
{
	XCSBNode* pkNode = new XCSBNode();
	pkNode->autorelease();
	return pkNode;
}

bool XCSBNode::load(const std::string& filename, bool bTimeline)
{
	XCSLoader* pkLoader = XCSLoader::getInstance();
	XCSLoadRet* info = nullptr;
	if (m_asyncNodeCallback == nullptr)
		info = pkLoader->loadCSB(filename, bTimeline, true, nullptr);
	else
		info = pkLoader->loadCSB(filename, bTimeline, true, m_asyncNodeCallback);
//	auto info = pkLoader->loadCSB(filename, bTimeline, true, nullptr);
	if (!info)
	{
		XAssert(info, filename.c_str());
		return false;
	}
	auto node = info->getNode();
	if (!node)
	{
		return false;
	}
	if (m_pkNode)
		m_pkNode->removeAllChildrenWithCleanup(true);
	m_pkNode = node;
	addChild(m_pkNode, 0, 0);
	CC_SAFE_RELEASE_NULL(m_pkTimeline);
	if (bTimeline)
	{
		cocostudio::timeline::ActionTimeline* timeline = info->getTimeline();
		m_pkTimeline = timeline;
		CC_SAFE_RETAIN(m_pkTimeline);
	}
	return true;
}

void XCSBNode::loadAsync(XAsyncLoadOption* option, bool bTimeline)
{
	if (!option)
	{
		XLOGERROR("loadAnimationAsync option == null");
		return;
	}

	if (option == m_asyncOption)
	{
		CCLOG("XCSBNode have already load this option:: %s", option->m_filename.c_str());
		return;
	}

	m_asyncOption		= option;
	auto& skinName		= option->m_filename;
	auto& customId		= option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority		= option->m_priority;

	if (m_pkCallback == nullptr)
	{
		m_pkCallback = XAsyncLoaderCallback::create();
		m_pkCallback->retain();

	}
	m_pkCallback->init(CC_CALLBACK_1(XCSBNode::onTextureAsyncLoad, this));
//	m_pkCallback->init(load_callback);
	XAsyncLoaderManager::sharedManager()->loadGroup(skinName, customId, priority, m_pkCallback);
}

void XCSBNode::onTextureAsyncLoad(const XAsyncLoaderRet* retCode)
{
	XAsyncLoaderCode result = (XAsyncLoaderCode)retCode->ret();
	if (result == XAsyncLoaderCode::eOK)
	{
		if (this->load(m_asyncOption->m_filename, false))
		{
			// 如果加载完成，则回调
			m_asyncOption->m_callback(retCode);
		}
	}
	else
	{
		XLOGERROR("XCSBNode %s load Texture Failed", m_asyncOption->m_filename.c_str());
	}
}

bool XCSBNode::play(const std::string& name, bool loop)
{
	if (!m_pkTimeline || !m_pkNode)
		return false;

	if (m_pkTimeline->getTarget() == nullptr)
	{
		m_pkNode->runAction(m_pkTimeline);
	}
	m_pkTimeline->play(name, loop);
	m_currentAnimationName = name;
	return true;
}

bool XCSBNode::gotoFrameAndPlay(int start_index, int end_index, bool loop)
{
	if (!m_pkTimeline || !m_pkNode)
		return false;

	if (m_pkTimeline->getTarget() == nullptr)
	{
		m_pkNode->runAction(m_pkTimeline);
	}
	m_pkTimeline->gotoFrameAndPlay(start_index,end_index, loop);
	return true;
}

bool XCSBNode::gotoFrameAndPlay(int start_index, bool loop)
{
	if (!m_pkTimeline || !m_pkNode)
		return false;

	if (m_pkTimeline->getTarget() == nullptr)
	{
		m_pkNode->runAction(m_pkTimeline);
	}

	m_pkTimeline->gotoFrameAndPlay(start_index, loop);
	return true;
}

void XCSBNode::cancelLoadAsync()
{
	if (m_pkCallback)
	{
		m_pkCallback->cancel();
		m_pkCallback->release();
		m_pkCallback = nullptr;
	}
}

Node* XCSBNode::getNode()
{
	return m_pkNode;
}

cocostudio::timeline::ActionTimeline* XCSBNode::getTimeLine()
{
	return m_pkTimeline;
}

void XCSBNode::setSpriteFrameByIndex(int index, Sprite* parent)
{
	if (!m_pkTimeline || !m_pkNode)
		return ;
	char buffer[33] = { 0 };
#if _MSC_VER
	int ret = sprintf_s(buffer, sizeof(buffer), "%d", index);
#else
	int ret = snprintf(buffer, sizeof(buffer), "%d", index);
#endif
	XAssert(ret >= 1,"setSpriteFrameByIndex sprintf failed");
	if (m_currentAnimationName.compare(buffer) != 0)
	{
		play(buffer, true);
	}
}

void XCSBNode::clearCSB()
{
	CC_SAFE_RELEASE_NULL(m_pkTimeline);
	if (m_pkNode)
		m_pkNode->removeAllChildrenWithCleanup(true);
	m_pkNode = nullptr;
	
}

void XCSBNode::setNodeCallback(XLambda* luaFunction)
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
	m_asyncNodeCallback = callback;
}