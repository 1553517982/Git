#ifndef __XSlotAnimateSprite_H__
#define __XSlotAnimateSprite_H__

#include <string>
#include "cocos2d.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "cocos/2d/SlotAnimation/XSlotSprite.h"
#include "cocos/2d/SlotAnimation/XSlotFrames.h"

USING_NS_CC;

class XAnimationConfig;
class XSlotFrames;
/*! \class XSlotSprite
*  \brief [lua] SlotSprite 一个格子精灵
*
*
*/
class XSlotAnimateSprite : public XAnimateSprite
{
	protected:
		XSlotAnimateSprite();
	public:
		virtual ~XSlotAnimateSprite();

		/**
		@brief 构造动画精灵
		@return XSlotSprite*
		*/
		static XSlotAnimateSprite* create();

		/**
		@brief	   添加一个配件
		@param 	   const char * szName
		@param 	   XSlotSprite * slot
		@returns   void
		*/
		void	attachSlot(const char* szName, XSlotSprite* slot);


		/**
		@brief	   移除一个配件
		@param 	   const char * szName
		@returns   void
		*/
		void	detachSlot(const char* szName);

		/**
		@brief	   更新所有子配件，与之和自己同步，一般用于异步加载结束
		@returns   void
		*/
		void	updateSlots();

		/**
		@brief	   读取配件配置，用于播放动画时驱动自己的slot变换
		@param 	   const std::string & filename
		@returns   void
		*/
		void	loadSlotFrameConfig(const std::string & filename);

		/**
		@brief	   获取Slot配件
		@param 	   const std::string & name
		@returns   XSlotSprite*
		*/
		XSlotSprite* getSlot(const std::string& name);
		
		/**
		@brief	   为配件加载上自己身上的SlotFrameConfig，假设slot已经存在于自己身上
		@param 	   XSlotSprite * slot
		@returns   void
		*/
		void bindSlot(XSlotSprite* slot);
		
		/**
		@brief	   帧改变时的回调
		@param 	   int frameID
		@returns   void
		*/
		virtual	void onFrameChange(int frameID);
		
	protected:
		virtual bool								_playAction(int actionID, bool repeatforever);
		Map<std::string, XSlotFrames*>*				m_pkSlotFrames;
		Map<std::string, XSlotSprite*>				m_kSlots;
		int											m_nCurrentFrameID;
};

#endif /* defined(__CocoGUI__UISystem__) */
