#ifndef __NodeHelpers__
#define __NodeHelpers__

#include <string>
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

namespace ui {

	class Widget;

	/*! \class  NodeHelpers
	*  \brief  节点Node的帮助操作类
	*/
	class NodeHelpers
	{
	public:

		/**
		@brief 根据Tag查找Widget
		@param root
		@param tag
		@return Widget*
		@lua
		*/
		static Widget* seekWidgetByTag(Node* root, int tag);

		/**
		@brief 根据名字查找Widget
		@param root
		@param name
		@return Widget*
		*/
		static Widget* seekWidgetByName(Node* root, const std::string& name);

		/**
		@brief 根据Action的tag来找Widget
		@param root
		@param tag
		@return Widget*
		*/
		static Widget* seekActionWidgetByActionTag(Node* root, int tag);

		/**
		@brief 先retain 然后调用 removeFromParent 最后autorelease 
		主要是处理关闭按钮，关闭自身时有可能出的问题，HJH UI系统使用
		@param root
		@param flag
		@return void
		*/
		static void	   safeRemoveFromParent(Node* root, bool flag);

		/**
		@brief 先retain 然后调用 safeRemoveChild 最后autorelease
		主要是处理关闭按钮，关闭自身时有可能出的问题，HJH UI系统使用
		@param root
		@param Child
		@param flag
		@return void
		*/
		static void	   safeRemoveChild(Node* root, Node* Child, bool flag);

		/**
		@brief 调用retain 然后调用 autorelease
		@param obj
		@return void
		*/
		static void	   safeRelease(Ref* obj);

		static const char*	   getUserObject(Node* node);

		static void		recursiveSetCascadeOpacityEnabled(Node* root, bool flag);
	};
}

NS_CC_END

#endif /* defined(__CocoGUI__UISystem__) */
