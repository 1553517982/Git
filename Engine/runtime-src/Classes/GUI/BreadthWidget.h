#ifndef __BREADTHWIDGET_H__
#define __BREADTHWIDGET_H__

#include "ui/UIWidget.h"

USING_NS_CC;

/*
 -- added by aXing on 2017-3-25
 -- 创建一个适用于广度遍历的容器
 -- 用于类似背包等，儿子元素都是相似，而且贴图都在一齐的情况，尽量减少DC
 */

class BreadthWidget : public ui::Widget
{
public:
	BreadthWidget(void);

	virtual ~BreadthWidget();

	static BreadthWidget* create();

	/**
	* @js NA
	*/
	virtual void visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

};

#endif