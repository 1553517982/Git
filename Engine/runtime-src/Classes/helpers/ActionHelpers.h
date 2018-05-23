#ifndef __ActionHelpers__
#define __ActionHelpers__

#include <string>
#include "cocos2d.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
USING_NS_CC;
/*! \class  ActionHelpers
*  \brief  用来方便创建Action
*
*
*/
class ActionHelpers
{
public:
	/*!
	* \brief 创建一个MoveTo的Action
	* \param float sx　来源x
	* \param float sy　来源y
	* \param float tx 目标x
	* \param float ty 目标y
	* \param float time 动画持续时间
	* \param int tag　动画的tag
	* \return ActionInterval*
	*/
	static ActionInterval* moveTo(float sx, float sy, float tx, float ty, float time, int tag);

	//remove begin
	static Action* removeWhenTimelineFinish(cocostudio::timeline::ActionTimeline* action);

	//remove begin
	static Action* removeWhenTimelineFinish(cocostudio::timeline::ActionTimeline* action, float delay, float fadeOut);

	static FiniteTimeAction* removeWhenActionFinish(FiniteTimeAction* action, float delay, float fadeOut);
	//remove end

	static FiniteTimeAction* delayRemove(float delay);

	// fade out begin
	static FiniteTimeAction* delayFadoutRemove(float delay, float fadeOut);

	static FiniteTimeAction* delayEaseInFadoutRemove(float delay, float ease, float fadeOut);

	static FiniteTimeAction* delayEaseOutFadoutRemove(float delay, float ease, float fadeOut);
	// fade in end

	// fade in begin
	static FiniteTimeAction* delayFadeIn(float delay, float fadeIn);

	static FiniteTimeAction* delayEaseInFadeIn(float delay, float ease, float fadeIn);

	static FiniteTimeAction* delayEaseOutFadeIn(float delay, float ease, float fadeIn);
	// fade in end
	
	static FiniteTimeAction* easeElasticInScale(float sx, float sy, float time, float ease);

	static FiniteTimeAction* easeElasticOutScale(float sx, float sy, float time, float ease);
};

#endif /* defined(__CocoGUI__UISystem__) */
