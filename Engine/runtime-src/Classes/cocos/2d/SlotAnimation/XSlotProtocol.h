#ifndef __XSlotProtocol_H__
#define __XSlotProtocol_H__

#include <string>
#include "cocos2d.h"
USING_NS_CC;

class XSlotProtocol
{
	protected:
		XSlotProtocol();
	public:
		virtual ~XSlotProtocol();

		virtual void setSpriteFrameByIndex(int index, Sprite* parent) = 0;
};

#endif /* defined(__CocoGUI__UISystem__) */
