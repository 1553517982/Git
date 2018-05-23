#include "XSlotSprite.h"
#include "cocos/2d/Animation/XAnimationCache.h"
#include "XCommon.h"
#include "XFrameModifier.h"
XSlotSprite::XSlotSprite() : m_pkSlotFrames(nullptr), m_isSlotEnable(true), m_nCurrentFrameID(-1)
{

}

XSlotSprite::~XSlotSprite()
{
	CC_SAFE_RELEASE(m_pkSlotFrames);
}

XSlotSprite* XSlotSprite::create()
{
	XSlotSprite *sprite = new (std::nothrow) XSlotSprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void XSlotSprite::setSkin(const std::string& skin)
{
	m_nCurrentFrameID = -1;
	m_spriteFramesOfCurrentAction.clear();
	XAnimationCache::getInstance()->getSpriteFrameMap(skin, &m_spriteFramesOfCurrentAction);
}

void XSlotSprite::setSpriteFrameByIndex(int index, Sprite* parent)
{
	m_nCurrentFrameID = index;

	if (!m_isSlotEnable)
	{
		return;
	}

	if (m_spriteFramesOfCurrentAction.empty())
		return;

	if (m_pkSlotFrames == nullptr)
	{
		return;
	}

	XFrameModifier* pkInfo = m_pkSlotFrames->getFrameModifierWithIndex(index);
	unsigned int frameID = 0;
	if (pkInfo)
	{
		frameID = pkInfo->m_nFrameIndex;
	}
	else
	{
		return;
	}
	SpriteFrame* pkFrame = m_spriteFramesOfCurrentAction.at(frameID);
	if (!pkFrame)
	{
#ifdef X_DEBUG
		XLOGERROR("WARRING: XSlotSprite(%s)::update frame missing %d", m_slotType.c_str(), frameID);
#endif // _DEBUG
		return;
	}
	//如果scale == 0就不显示了
	if (pkInfo->isVisible())
	{
		//if (m_nCurrentFrameID != frameID)
		//{
		setVisible(true);
		if (pkInfo)
		{
			pkInfo->apply(this, isFlippedX());
		}
		setSpriteFrame(pkFrame);
		//}
	}
	//否则显示
	else
	{
		setVisible(false);
	}
}

void XSlotSprite::setCurrentAction(XSlotFrames* pkAction)
{
	CC_SAFE_RELEASE(m_pkSlotFrames);
	m_pkSlotFrames = pkAction;
	CC_SAFE_RETAIN(m_pkSlotFrames);
}

void XSlotSprite::setEnable(bool val)
{
	m_isSlotEnable = val; 
	setVisible(val);
	if (val && m_nCurrentFrameID > 0)
	{
		setSpriteFrameByIndex(m_nCurrentFrameID,this);
	}
}