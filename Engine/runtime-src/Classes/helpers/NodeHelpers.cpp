/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "NodeHelpers.h"
#include "ui/UIHelper.h"
#include "ui/UIWidget.h"
#include "ui/UILayoutComponent.h"
#include "cocos2d.h"
#include "XCommon.h"
#include "cocostudio/CCObjectExtensionData.h"
NS_CC_BEGIN

namespace ui {

	static bool _activeLayout = true;

	Widget* NodeHelpers::seekWidgetByTag(Node* root, int tag)
	{
		if (!root)
		{
			return nullptr;
		}

		const auto& arrayRootChildren = root->getChildren();
		ssize_t length = arrayRootChildren.size();
		for (ssize_t i = 0; i < length; i++)
		{
			Widget* child = dynamic_cast<Widget*>(arrayRootChildren.at(i));
			if (child)
			{
				Widget* res = Helper::seekWidgetByTag(child, tag);
				if (res != nullptr)
				{
					return res;
				}
			}
		}
		return nullptr;
	}

	Widget* NodeHelpers::seekWidgetByName(Node* root, const std::string& name)
	{
		if (!root)
		{
			return nullptr;
		}

		const auto& arrayRootChildren = root->getChildren();
		for (auto& subWidget : arrayRootChildren)
		{
			Widget* child = dynamic_cast<Widget*>(subWidget);
			if (child)
			{
				Widget* res = Helper::seekWidgetByName(child, name);
				if (res != nullptr)
				{
					return res;
				}
			}
		}
		return nullptr;
	}

	/*temp action*/
	Widget* NodeHelpers::seekActionWidgetByActionTag(Node* root, int tag)
	{
		if (!root)
		{
			return nullptr;
		}

		const auto& arrayRootChildren = root->getChildren();
		for (auto& subWidget : arrayRootChildren)
		{
			Widget* child = dynamic_cast<Widget*>(subWidget);
			if (child)
			{
				Widget* res = Helper::seekActionWidgetByActionTag(child, tag);
				if (res != nullptr)
				{
					return res;
				}
			}
		}
		return nullptr;
	}

	void NodeHelpers::safeRemoveFromParent(Node* root, bool flag)
	{
		if (root)
		{
			root->retain();
			root->autorelease();
			root->removeFromParentAndCleanup(flag);
		}
	}

	void NodeHelpers::safeRemoveChild(Node* root, Node* child, bool flag)
	{
		if (root && child)
		{
			child->retain();
			child->autorelease();
			root->removeChild(child, flag);
		}
	}

	void NodeHelpers::safeRelease(Ref* obj)
	{
		obj->retain();
		obj->autorelease();
	}

	const char* NodeHelpers::getUserObject(Node* node)
	{
		static std::string ret;
		cocostudio::ObjectExtensionData* data = dynamic_cast<cocostudio::ObjectExtensionData*>(node->getUserObject());
		if (data)
		{
			ret = data->getCustomProperty().c_str();
			return ret.c_str();
		}
		return NULL;
	}

	void NodeHelpers::recursiveSetCascadeOpacityEnabled(Node* root, bool flag)
	{
		if (!root)
			return;

		const auto& arrayRootChildren = root->getChildren();
		ssize_t length = arrayRootChildren.size();
		for (ssize_t i = 0; i < length; i++)
		{
			auto* child = arrayRootChildren.at(i);
			if (child)
			{
				recursiveSetCascadeOpacityEnabled(child, flag);
			}
		}
		root->setCascadeOpacityEnabled(flag);
		//root->setCascadeOpacityEnabled(flag);
	}
}

NS_CC_END
