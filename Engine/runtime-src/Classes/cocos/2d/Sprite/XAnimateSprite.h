#ifndef __XAnimateSprite_H__
#define __XAnimateSprite_H__

#include <string>
#include <map>
#include "cocos2d.h"
#include "supports/XResource/XAsyncLoaderCallbacks.h"
#include "cocos/studio_ext/XCSLoader.h"

USING_NS_CC;

class XAnimate;
class XAnimationConfig;
/*! \class XAnimateSprite
*  \brief [lua] 带多动作动画的精灵
*
*
*/
class XAnimateSprite : public cocos2d::Sprite
{
	friend XAnimate;

	protected:
		XAnimateSprite();
	public:
		virtual ~XAnimateSprite();

		/**
		@brief 构造动画精灵
		@return XAnimateSprite*
		*/
		static XAnimateSprite* create();

		/**
		@brief 初始化精灵皮肤和动画配置
		@param skinName			皮肤文件，plist
		@param actionFile		动作文件
		@param actionID			动作ID
		@param repeatforever	永远执行
		@return bool
		*/
		virtual bool initWithActionFile(std::string & skinName, std::string & actionFile);

		/**
		@brief 是否有动画Action Config
		@param id
		@return bool
		*/
		virtual bool hasActionConfig(int id);

		/**
		@brief 播放Action
		@param actionID
		@param repeatforever
		@return bool
		*/
		virtual bool playAction(int actionID, bool repeatforever);

		/*!
		* \brief 生成一个动画Action，由使用者决定如何播放
		* \param int actionID
		* \param bool repeatforever
		* \return FiniteTimeAction*
		*/
		virtual FiniteTimeAction* prepareAction(int actionID, bool repeatforever, StringMap * texStringMap);

		/**
		@brief 播放动画
		@param name					动画皮肤名字
		@param delayUnits			延迟单元，每帧间隔
		@param restoreOriginalFrame	是否恢复到第一帧
		@param loops				循环
		@return bool
		*/
		virtual bool playAnimation(const char* name, float delayUnits, bool restoreOriginalFrame, int loops);

		/**
		@brief 设置目标动画到特定帧
		@param name 目标动画名
		@param index
		@return void
		*/
		virtual void setDefaultFrame(const char* name, int index);

		/**
		@brief	   设置当前动画到特定帧
		@param 	   int index
		@returns   void
		*/
		virtual void setDefaultFrame(int index);

		/**
			使用跳跃
		*/
		void Jump(float sec, float height );

		/*
		 击飞
		*/
		void KnockDown(float duration, float xspeed, float yspeed);

		std::function<void(int, const ValueMap*)> getAnimationEventCallback() const { return m_pkAnimationEventCallback; }

		void setAnimationEventCallback(std::function<void(int, const ValueMap*)> val) { m_pkAnimationEventCallback = val; }

		std::function<void(int)> getFrameCallback() const { return m_pkFrameCallback; }
		void setFrameCallback(std::function<void(int)> val);

		virtual void cleanup();
		
		int getActionID() const { return m_nActionID; }
		
		void setActionID(int val) { m_nActionID = val; }

protected:

		void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);

		void onXAnimateEvent(XAnimate* who, int, const ValueMap*);
		
		void onXAnimateFrame(XAnimate* who, int);

		/**
		@brief 设置精灵皮肤，一个精灵跑起来需要调用 setSkin -> setActionConfig -> playAction
		@param filename
		@return bool
		*/
		virtual bool setSkinName(const char* filename);

		/**
		@brief 设置动画Action Config
		@param actionConfig
		@return void
		*/
		virtual void setActionConfig(const char* actionConfig);

		// added by aXing on 2017-4-9
		// 添加可以异步加载贴图的方法
		void loadAsync(const std::string&filename);

		void onTextureAsyncLoad(const XAsyncLoaderRet* retCode);

		void onTextureLoadEnd();

		std::string								  m_skinName;
		XAnimationConfig*						  m_pkAnimationConfig;
		int										  m_nActionID;					// 正在播放的动作id
		bool									  m_bRepeatforever;
		int										  m_nResumeActionID;			// 需要恢复的动作id(在异步过程中)
		bool									  m_bResumeRepeatforever;		// 需要恢复的动作，是否重复播放
		int										  m_nCheck;
		int										  m_nUpdateDelay;
		std::function<void(int)>				  m_pkFrameCallback;
		std::function<void(int, const ValueMap*)> m_pkAnimationEventCallback;

		// 异步加载图片函数指针
		Vector<XAsyncLoaderCallback*>			  m_pkLoadCallbacks;		// 用于记录异步加载图片的回调函数
		short									  m_loadedCount;		// 已经加载好的贴图数量(不会超过255张贴图吧)

		// 记住需要的贴图，引用计数加一，使得它们不会被释放掉
		XRefHolder*								  m_holder;
};

#endif /* defined(__CocoGUI__UISystem__) */
