#include "XSlotHolderSprite.h"
#include "cocos/2d/Animation/XAnimationCache.h"
#include "XCommon.h"
#include "XFrameModifier.h"
#include "cocos/2d/SlotAnimation/XSlotAnimateSprite.h"

XSlotHolderSprite::XSlotHolderSprite()
{

}

XSlotHolderSprite::~XSlotHolderSprite()
{

}

XSlotHolderSprite* XSlotHolderSprite::create()
{
	XSlotHolderSprite *sprite = new (std::nothrow) XSlotHolderSprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


void XSlotHolderSprite::setSpriteFrameByIndex(int index, Sprite* parent)
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

		for (auto it = _children.begin(); it != _children.end(); it++)
		{
			XSlotProtocol* casted = dynamic_cast<XSlotProtocol*>((*it));
			if (casted)
			{
				casted->setSpriteFrameByIndex(frameID, this);
			}
		}
	}
	//否则显示
	else
	{
		setVisible(false);
	}
}