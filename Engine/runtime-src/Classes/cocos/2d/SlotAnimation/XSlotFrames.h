#ifndef __XSlotFrames_H__
#define __XSlotFrames_H__
#include "cocos2d.h"
#include "XFrameModifier.h"

USING_NS_CC;
// 某个Slot和父亲帧之间的关系
class XSlotFrames : public Ref
{
private:
	XSlotFrames();
public:
	XSlotFrames(tXFrameModifierMap* pkFrameModifiers);
	~XSlotFrames();

	XFrameModifier* getFrameModifierWithIndex(unsigned int index);

	int getModifierCount();

	static XSlotFrames* create(tXFrameModifierMap* pkFrameModifiers);

public:
	tXFrameModifierMap*	m_pkFrameModifiers;
};

#endif 
