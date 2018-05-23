#include "XSlotFrames.h"

static int s_animation_action_count = 0;

XSlotFrames::XSlotFrames()
{

}

XSlotFrames::XSlotFrames(tXFrameModifierMap* pkFrameModifiers) :
m_pkFrameModifiers(pkFrameModifiers)
{
#ifdef X_DEBUG
	s_animation_action_count++;
#endif
}

XSlotFrames::~XSlotFrames()
{
#ifdef _DEBUG
	s_animation_action_count--;
#endif
	if (m_pkFrameModifiers)
	{
		for (tXFrameModifierMap::iterator iter = m_pkFrameModifiers->begin();
			iter != m_pkFrameModifiers->end();
			iter++)
		{
			delete iter->second;
		}
		delete m_pkFrameModifiers;
	}
}

XSlotFrames* XSlotFrames::create(tXFrameModifierMap* pkFrameModifiers)
{
	XSlotFrames* pkAction = new XSlotFrames(pkFrameModifiers);
	pkAction->autorelease();
	return pkAction;
}

int	XSlotFrames::getModifierCount()
{
	if (m_pkFrameModifiers)
		return m_pkFrameModifiers->size();
	return 0;
}

XFrameModifier* XSlotFrames::getFrameModifierWithIndex(unsigned int index)
{
	CCAssert(m_pkFrameModifiers, "m_pkFrameModifiers == NULL");
	tXFrameModifierMap::iterator iter = m_pkFrameModifiers->find(index);
	if (iter != m_pkFrameModifiers->end())
	{
		XFrameModifier*pkObj = iter->second;
		return pkObj;
	}
	return NULL;
}