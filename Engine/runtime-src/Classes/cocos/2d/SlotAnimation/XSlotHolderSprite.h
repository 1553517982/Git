#ifndef __XSlotHolderSprite_H__
#define __XSlotHolderSprite_H__

#include <string>
#include "cocos2d.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "cocos/2d/SlotAnimation/XSlotFrames.h"
#include "cocos/2d/SlotAnimation/XSlotSprite.h"

USING_NS_CC;

class XAnimationConfig;
/*! \class XSlotHolderSprite
*  \brief [lua] XSlotHolderSprite 一个配件精灵容器，拥有XAnimateSprite作为子控件；
*	并通过自身的frameID驱动，自己的子XAnimateSprite，一般用来做配件上面的动画特效，比如武器的发光效果
*
*
*/
class XSlotHolderSprite : public XSlotSprite
{
	protected:
		XSlotHolderSprite();
	public:
		virtual ~XSlotHolderSprite();

		/**
		@brief 构造动画精灵
		@return XSlotSprite*
		*/
		static XSlotHolderSprite* create();

		virtual void setSpriteFrameByIndex(int index, Sprite* parent) override;
};

#endif /* defined(__CocoGUI__UISystem__) */
