#ifndef __BREADTHWIDGET_H__
#define __BREADTHWIDGET_H__

#include "ui/UIWidget.h"

USING_NS_CC;

/*
 -- added by aXing on 2017-3-25
 -- ����һ�������ڹ�ȱ���������
 -- �������Ʊ����ȣ�����Ԫ�ض������ƣ�������ͼ����һ����������������DC
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