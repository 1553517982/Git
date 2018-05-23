#include "XSlotAnimateSprite.h"
#include "cocos/2d/Animation/XAnimationCache.h"
#include "XCommon.h"
#include "XFrameModifier.h"
#include "cocos/2d/SlotAnimation/XSlotFrames.h"
#include "cocos/2d/SlotAnimation/XSlotAnimationConfig.h"


XSlotAnimateSprite::XSlotAnimateSprite() : m_nCurrentFrameID(-1), m_pkSlotFrames(nullptr)
{
	m_pkFrameCallback = [this](int frameID)
	{
		this->onFrameChange(frameID);
	};
}

XSlotAnimateSprite::~XSlotAnimateSprite()
{

}

XSlotAnimateSprite* XSlotAnimateSprite::create()
{
	XSlotAnimateSprite *sprite = new (std::nothrow) XSlotAnimateSprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void XSlotAnimateSprite::attachSlot(const char* szName, XSlotSprite* slot)
{
	if (m_kSlots.find(szName) == m_kSlots.end())
	{
		m_kSlots.insert(szName, slot);
		
	}
	bindSlot(slot);
}

void XSlotAnimateSprite::bindSlot(XSlotSprite* slot)
{
#ifdef X_DEBUG
	bool bFound = false;
	for (auto iter = m_kSlots.begin(); iter != m_kSlots.end(); iter++)
	{
		if (iter->second == slot)
		{
			bFound = true;
		}
	}
	if (!bFound)
	{
		XLOGERROR("XSlotAnimateSprite::bindSlot slot is no attached");
		return;
	}
#endif // X_DEBUG

	slot->setFlippedX(isFlippedX());
	if (m_pkSlotFrames)
	{
		XSlotFrames* frameset = m_pkSlotFrames->at(slot->getSlotType());
		slot->setCurrentAction(frameset);
	}
}

void XSlotAnimateSprite::detachSlot(const char* szName)
{
	auto iter = m_kSlots.find(szName);
	if (iter != m_kSlots.end())
	{
		iter->second->cancelLoadAsync();
		m_kSlots.erase(iter);
	}
}

void XSlotAnimateSprite::updateSlots()
{
	if (m_pkSlotFrames)
	{
		for (auto iter = m_kSlots.begin(); iter != m_kSlots.end(); iter++)
		{
			auto slot = iter->second;
			slot->setFlippedX(isFlippedX());
			XSlotFrames* frameset = m_pkSlotFrames->at(slot->getSlotType());
			slot->setCurrentAction(frameset);
		}
	}
}

bool XSlotAnimateSprite::_playAction(int actionID, bool repeatforever)
{
	int frameID = m_nCurrentFrameID;
	m_nCurrentFrameID = -1;

	bool ret = XAnimateSprite::playAction(actionID, repeatforever);
	if (frameID > 0 && ret)
	{
		bool bFlipX = isFlippedX();
		for (auto iter = m_kSlots.begin();
			iter != m_kSlots.end();
			iter++)
		{
			iter->second->setFlippedX(bFlipX);
			iter->second->setSpriteFrameByIndex(frameID,this);
		}
	}
	//m_nCurrentFrameID = -1;
	//m_nCurrentFrameID = m_pkAnimationConfig->m_actions.at(0);
	return ret;
}

void XSlotAnimateSprite::onFrameChange(int frameID)
{
	if (m_nCurrentFrameID != frameID)
	{
		m_nCurrentFrameID = frameID;
		bool bFlipX = isFlippedX();
		for (auto iter  = m_kSlots.begin();
			      iter != m_kSlots.end();
			      iter++)
		{
			auto slot = iter->second;
			iter->second->setFlippedX(bFlipX);
			iter->second->setSpriteFrameByIndex(frameID,this);
		}
	}
}

void XSlotAnimateSprite::loadSlotFrameConfig(const std::string& filename)
{
	// removed by aXing on 2017-4-15
	// 先注释掉，因为Android编译不过
//	m_pkSlotFrames = XSlotAnimationConfig::sharedManager()->getSlotFrames(filename.c_str());
}

XSlotSprite* XSlotAnimateSprite::getSlot(const std::string& name)
{
	return m_kSlots.at(name);
}
