#include "XAnimationFrame.h"

XAnimationFrame* XAnimationFrame::create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo)
{
	auto ret = new (std::nothrow) XAnimationFrame();
	if (ret && ret->initWithSpriteFrame(spriteFrame, delayUnits, userInfo))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

XAnimationFrame::XAnimationFrame() : 
	m_FrameID(-1)
{

}

XAnimationFrame::~XAnimationFrame()
{
}

XAnimationFrame* XAnimationFrame::clone() const
{
	// no copy constructor
	auto frame = new (std::nothrow) XAnimationFrame();
	frame->initWithSpriteFrame(_spriteFrame->clone(),
		_delayUnits,
		_userInfo);

	frame->setFrameID(m_FrameID);
	frame->autorelease();
	return frame;
}
