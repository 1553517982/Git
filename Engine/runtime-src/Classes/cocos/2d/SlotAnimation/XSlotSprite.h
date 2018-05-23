#ifndef __XSlotSprite_H__
#define __XSlotSprite_H__

#include <string>
#include "cocos2d.h"
#include "cocos/2d/Sprite/XSprite.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "cocos/2d/SlotAnimation/XSlotFrames.h"
#include "cocos/2d/SlotAnimation/XSlotProtocol.h"
USING_NS_CC;

class XAnimationConfig;
/*! \class XSlotSprite
*  \brief [lua] SlotSprite 一个配件精灵
	@section 配件精灵系统解释
	配件精灵系统
	一个动画比如人物，本身是一个序列帧动画，再帧变化时驱动自己关联的配件根据配置来变换位置大小等。
	可以说是一个阉割的骨骼动画
*/
class XSlotSprite : public XSprite, public XSlotProtocol
{
	protected:
		XSlotSprite();
	public:
		virtual ~XSlotSprite();

		/**
		@brief 构造配件精灵
		@return XSlotSprite*
		*/
		static XSlotSprite* create();

		/**
		@brief	   设置皮肤，同步读取图片，并设置纹理
		@param 	   const std::string & skin
		@returns   void
		*/
		void setSkin(const std::string& skin);

		/**
		@brief	   设置当前皮肤的帧id
		@param 	   int index
		@returns   void
		*/
		virtual void setSpriteFrameByIndex(int index, Sprite* parent) override;

		/**
		@brief	   设置当前的配件配置，一般由XSlotAnimateSprite设置
		@param 	   XSlotFrames * pkAction
		@returns   void
		*/
		void setCurrentAction(XSlotFrames* pkAction);

		/**
		@brief	   获取配件类型
		@returns   const char*
		*/
		const char* getSlotType() const { return m_slotType.c_str(); }


		/**
		@brief	   设置配件类型
		@param 	   const std::string & val
		@returns   void
		*/
		void setSlotType(const std::string& val) { m_slotType = val; }

		/**
		@brief	   获取是否生效
		@returns   bool
		*/
		bool getEnable() const { return m_isSlotEnable; }

		/**
		@brief	   设置是否生效，如果不生效将会设置visible = false, 并每次循环都跳过自身处理，一般用于隐藏配件
		@param 	   bool val
		@returns   void
		*/
		void setEnable(bool val);

	protected:
		Map<unsigned int,SpriteFrame*>			m_spriteFramesOfCurrentAction;
		XSlotFrames*							m_pkSlotFrames;
		std::string								m_slotType;
		bool									m_isSlotEnable;
		int										m_nCurrentFrameID;
};

#endif /* defined(__CocoGUI__UISystem__) */
