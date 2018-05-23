#ifndef __XActionNode_H__
#define __XActionNode_H__
#include "cocos2d.h"
class XLambda;

USING_NS_CC;

class XActionNode : public Node
{
public:
	enum XActionNodeEvent
	{
		eEntityMoveEnd,
	};

	XActionNode();
	
	virtual ~XActionNode();

	static XActionNode* create();

	void moveTo(const Vec2& target, int movementInPixel);

	void moveTo(float x, float y, int movementInPixel);

	void Jump(float sec, float height, float x, float y);

	void KnockDown(float duration, float xspeed, float yspeed);

	void listenEvent(XLambda* val);

	//virtual void setPosition(float x, float y) override;
	
	void onMoveToEnd();

	void setPosition(float x, float y);

	void setLocation(float x, float y, float z);
protected:
	XLambda* m_actionEventLambda;

};

#endif /* defined(__CocoGUI__UISystem__) */
