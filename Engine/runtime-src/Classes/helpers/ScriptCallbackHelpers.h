#ifndef __ScriptCallbackHelpers_H__
#define __ScriptCallbackHelpers_H__

#include <string>
#include "cocos2d.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
/*! \class  ScriptCallbackHelpers
*  \brief  脚本回调管理器，主要用于为C++对象绑定监听脚本函数
*
*
*/
class XAnimateSprite;
class XRenderSlotHolder;
class XActionNode;
class XLambda;

USING_NS_CC;

class ScriptCallbackHelpers
{
public:
	/*!
	* \brief 监听帧事件
	* \param XAnimateSprite * pkSprite
	* \param XLambda* handle
	* \return void
	*/
	static void listenFrameEvent(XAnimateSprite* pkSprite, XLambda* handle);

	/*!
	* \brief 监听帧事件
	* \param XRenderSlotHolder * pkSprite
	* \param XLambda* handle
	* \return void
	*/
	static void listenFrame(XAnimateSprite* pkSprite, XLambda* handle);

	/*!
	* \brief 监听ActionNode的事件，现在只有移动事件
	* \param XActionNode * node
	* \param XLambda* handle
	* \return void
	*/
	static void listenActionNodeEvent(XActionNode* node, XLambda* handle);

	/*!
	* \brief 监听帧事件
	* \param XAnimateSprite * pkSprite
	* \param XLambda* handle
	* \return void
	*/
	static void setLastFrameCallFunc(cocostudio::timeline::ActionTimeline* action, XLambda* handle);

	
	static void setFrameEventCallFunc(cocostudio::timeline::ActionTimeline* action, XLambda* handle);

	static void listenAppEvents(XLambda* handle);

	static void fini();

	static void onAppEvent(unsigned int event, const std::string& code, const std::string& msg);

	static void dispatchCustomEvent(std::string& eventname, cocos2d::ValueMap& arg);

	static cocos2d::ValueMap& eventCustomUserDataAsTable(cocos2d::EventCustom* event);
};

#endif /* defined(__CocoGUI__UISystem__) */
