#include "cocos2d.h"
#include <map>
#include <list>
#include <string>
#ifndef __XAnimatie__
#define __XAnimatie__
USING_NS_CC;

class XAnimate;

/*! \class XAnimate
*  \brief [lua] 给XAnimateSprite使用的动画action，重点是可以更简单和高效地监听帧事件
*
*
*/

class XAnimate : public Animate
{
public:
	enum XAnimateEvent
	{
		eFrameStart,
		eFrameEvent,
		eFrameEnd
	};

	static XAnimate* create(Animation *animation);

	virtual XAnimate* clone() const override;
	virtual XAnimate* reverse() const override;
	virtual void startWithTarget(Node *target) override;
	virtual void update(float t) override;

	bool getListenEvent() const { return m_bListenEvent; }
	
	void setListenEvent(bool val) { m_bListenEvent = val; }

	bool getListenFrame() const { return m_bListenFrame; }

	void setListenFrame(bool val) { m_bListenFrame = val; }

protected:
	XAnimate();
	virtual ~XAnimate();

	/** initializes the action with an Animation and will restore the original frame when the animation is over */
	bool initWithAnimation(Animation *animation);

protected:
	
	bool m_bListenEvent;

	bool m_bListenFrame;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(XAnimate);
};
#endif