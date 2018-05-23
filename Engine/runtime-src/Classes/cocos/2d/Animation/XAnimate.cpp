#include "XAnimate.h"
#include "XAnimationFrame.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "XCommon.h"
//
// Animate
//
XAnimate* XAnimate::create(Animation *animation)
{
	XAnimate *animate = new (std::nothrow) XAnimate();
	animate->initWithAnimation(animation);
	animate->autorelease();

	return animate;
}

XAnimate::XAnimate() : m_bListenEvent(false), m_bListenFrame(false)
{

}

XAnimate::~XAnimate()
{

}

XAnimate* XAnimate::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) XAnimate();
	a->initWithAnimation(_animation->clone());
	a->autorelease();
	return a;
}

void XAnimate::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	Sprite *sprite = static_cast<Sprite*>(target);

	CC_SAFE_RELEASE(_origFrame);

	if (_animation->getRestoreOriginalFrame())
	{
		_origFrame = sprite->getSpriteFrame();
		_origFrame->retain();
	}
	_nextFrame = 0;
	_executedLoops = 0;

	if (m_bListenEvent)
	{
		XAnimateSprite* pkTarget = dynamic_cast<XAnimateSprite*>(_target);
		if (pkTarget)
			pkTarget->onXAnimateEvent(this, eFrameStart, nullptr);
	}

}

XAnimate* XAnimate::reverse() const
{
	auto& oldArray = _animation->getFrames();
	Vector<AnimationFrame*> newArray(oldArray.size());

	if (oldArray.size() > 0)
	{
		for (auto iter = oldArray.crbegin(); iter != oldArray.crend(); ++iter)
		{
			AnimationFrame* animFrame = *iter;
			if (!animFrame)
			{
				break;
			}

			newArray.pushBack(animFrame->clone());
		}
	}

	Animation *newAnim = Animation::create(newArray, _animation->getDelayPerUnit(), _animation->getLoops());
	newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
	return XAnimate::create(newAnim);
}

void XAnimate::update(float t)
{
	// if t==1, ignore. Animation should finish with t==1
	if (t < 1.0f) {
		t *= _animation->getLoops();

		// new loop?  If so, reset frame counter
		unsigned int loopNumber = (unsigned int)t;
		if (loopNumber > _executedLoops) {
			_nextFrame = 0;
			_executedLoops++;
		}

		// new t for animations
		t = fmodf(t, 1.0f);
	}

	auto& frames = _animation->getFrames();
	auto numberOfFrames = frames.size();
	SpriteFrame *frameToDisplay = nullptr;

	XAnimateSprite* pkTarget = dynamic_cast<XAnimateSprite*>(_target);
	if (pkTarget == nullptr)
	{
		XLOGERROR("XAnimate::update cast failed");
		return;
	}
	for (int i = _nextFrame; i < numberOfFrames; i++) {
		float splitTime = _splitTimes->at(i);

		if (splitTime <= t) {
			AnimationFrame* frame = frames.at(i);
			frameToDisplay = frame->getSpriteFrame();
			pkTarget->setSpriteFrame(frameToDisplay);

			if (m_bListenFrame)
			{
				XAnimationFrame* casted = dynamic_cast<XAnimationFrame*>(frame);
				if (casted)
				{
					int frameID = casted->getFrameID();
					//_frameCallback(frameID);
					pkTarget->onXAnimateFrame(this, frameID);
				}
			}
			if (m_bListenEvent)
			{
				const ValueMap& dict = frame->getUserInfo();
				if (!dict.empty())
				{
					//_eventCallback(eFrameEvent, &dict);
					pkTarget->onXAnimateEvent(this, eFrameEvent, &dict);

				}
			}

			_nextFrame = i + 1;
		}
		// Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
		else {
			break;
		}
	}

	if (m_bListenEvent && isDone())
	{
		pkTarget->onXAnimateEvent(this, eFrameEnd, nullptr);
	}
}

bool XAnimate::initWithAnimation(Animation* animation)
{
	return Animate::initWithAnimation(animation);
}