#ifndef __XActionProtocol_H__
#define __XActionProtocol_H__
#include "cocos2d.h"

USING_NS_CC;

class XActionProtocol
{
public:
	XActionProtocol();
	virtual ~XActionProtocol() = 0;

	virtual void executeAction(Action* pkAction) = 0;

	virtual void movement(ActionInterval* pkAction, const Vec2& v);

	virtual void setSpeed(float speed);
};

#endif /* defined(__CocoGUI__UISystem__) */
