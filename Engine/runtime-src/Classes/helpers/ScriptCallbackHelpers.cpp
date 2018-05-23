#include "ScriptCallbackHelpers.h"
#include "CCLuaEngine.h"
#include "XCommon.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "entity/XActionNode.h"
#include "XLambda.h"

static XLambda* s_appEventID = NULL;

static void _listenFrameEvent(XAnimateSprite* pkSprite, XLambda* handle)
{
	XAssert(pkSprite != NULL, "listenFrameEvent pkSprite == nullptr");
	if (pkSprite == NULL)
		return;

	XLambdaHolderPtr handePtr = XLambdaHolder::create(handle);
	pkSprite->setAnimationEventCallback([handePtr](int event_id, const ValueMap* value_map)
	{
		auto _lambda = handePtr->getLambda();
		if (value_map == nullptr)
		{
			_lambda->begin();
			_lambda->pushInt(event_id);
			_lambda->invoke();
		}
		else
		{
			_lambda->begin();
			_lambda->pushInt(event_id);
			_lambda->pushValueMap(value_map);
			_lambda->invoke();
		}
	});
}

static void _listenFrame(XAnimateSprite* pkSprite, XLambda* handle)
{
	XAssert(pkSprite != NULL, "listenFrameEvent pkSprite == nullptr");
	if (pkSprite == NULL)
		return;

	XLambdaHolderPtr handePtr = XLambdaHolder::create(handle);
	pkSprite->setFrameCallback([handePtr](int frame)
	{
		auto _lambda = handePtr->getLambda();
		_lambda->begin();
		_lambda->pushInt(frame);
		_lambda->invoke();
	});
}

/* ----------------------------------- */
void ScriptCallbackHelpers::fini()
{
	CC_SAFE_RELEASE_NULL(s_appEventID);
}

void ScriptCallbackHelpers::listenFrameEvent(XAnimateSprite* pkSprite, XLambda* handle)
{
	_listenFrameEvent(pkSprite, handle);
}


void ScriptCallbackHelpers::listenFrame(XAnimateSprite* pkSprite, XLambda* handle)
{
	_listenFrame(pkSprite, handle);
}

void ScriptCallbackHelpers::listenActionNodeEvent(XActionNode* node, XLambda* handle)
{
	XAssert(node != NULL, "listenActionNodeEvent pkSprite == nullptr");
	if (node == NULL)
		return;
	node->listenEvent(handle);
}

void ScriptCallbackHelpers::setLastFrameCallFunc(cocostudio::timeline::ActionTimeline* action, XLambda* handle)
{
	XAssert(action != NULL, "setLastFrameCallFunc action == nullptr");
	if (action == NULL)
		return;

	XLambdaHolderPtr handePtr = XLambdaHolder::create(handle);

	action->setLastFrameCallFunc([handePtr]()
	{
		auto _lambda = handePtr->getLambda();
		_lambda->begin();
		_lambda->invoke();
	});
}

void ScriptCallbackHelpers::setFrameEventCallFunc(cocostudio::timeline::ActionTimeline* action, XLambda* handle)
{
	XAssert(action != NULL, "setLastFrameCallFunc action == nullptr");
	if (action == NULL)
		return;

	XLambdaHolderPtr handePtr = XLambdaHolder::create(handle);

	action->setFrameEventCallFunc([handePtr](cocostudio::timeline::Frame* pkFrame)
	{
		cocostudio::timeline::EventFrame* eventFrame = dynamic_cast<cocostudio::timeline::EventFrame*>(pkFrame);
		if (eventFrame)
		{
			auto _lambda = handePtr->getLambda();
			_lambda->begin();
			_lambda->pushObject(eventFrame, "ccs.EventFrame");
			_lambda->invoke();
		}
	});
}


void ScriptCallbackHelpers::onAppEvent(unsigned int event, const std::string& code, const std::string& msg)
{
	if (s_appEventID)
	{
		s_appEventID->begin();
		s_appEventID->pushInt(event);
		s_appEventID->pushString(code.c_str());
		s_appEventID->pushString(msg.c_str());
		s_appEventID->invoke();
	}
}

void ScriptCallbackHelpers::listenAppEvents(XLambda* handle)
{
	CC_SAFE_RELEASE(s_appEventID);
	s_appEventID = handle;
	CC_SAFE_RETAIN(s_appEventID);
}

void ScriptCallbackHelpers::dispatchCustomEvent(std::string& eventname, ValueMap& arg)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventname, (void*)(&arg));
}

ValueMap& ScriptCallbackHelpers::eventCustomUserDataAsTable(EventCustom* event)
{
	ValueMap* p = (ValueMap*)event->getUserData();
	return (*p);
}