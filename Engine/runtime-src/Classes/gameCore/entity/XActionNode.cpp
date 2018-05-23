#include "XActionNode.h"
#include "XCommon.h"
#include "CCLuaEngine.h"
#include "helpers/XLambda.h"

XActionNode::XActionNode() : m_actionEventLambda(NULL)
{

}

XActionNode::~XActionNode()
{
	if (m_actionEventLambda)
	{
		m_actionEventLambda->cleanup();
	}
	CC_SAFE_RELEASE(m_actionEventLambda);
}

XActionNode* XActionNode::create()
{
	XActionNode * ret = new (std::nothrow) XActionNode();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}


void XActionNode::listenEvent(XLambda* val)
{
	CC_SAFE_RELEASE(m_actionEventLambda);
	m_actionEventLambda = val;
	CC_SAFE_RETAIN(m_actionEventLambda);
}

void XActionNode::onMoveToEnd()
{
	if (m_actionEventLambda)
	{
		m_actionEventLambda->begin();
		m_actionEventLambda->pushInt(eEntityMoveEnd);
		m_actionEventLambda->invoke();
	}
}
void XActionNode::moveTo(const Vec2& target, int movementInPixel)
{
	stopActionByTag(XDefault_Tags::eAnimateSpriteMoveTag);
	float dst = target.distance(_position);
	dst = dst / movementInPixel;
	ActionInterval* pkAction = MoveTo::create(dst, target);
	
	if (m_actionEventLambda)
	{
		auto event = [=]
		{
			this->onMoveToEnd();
		};
		pkAction = Sequence::createWithTwoActions(pkAction, CallFunc::create(event));
	}
	pkAction->setTag(XDefault_Tags::eAnimateSpriteMoveTag);
	runAction(pkAction);
}

void XActionNode::moveTo(float x, float y, int movementInPixel)
{
	moveTo(Vec2(x, y), movementInPixel);
}

void XActionNode::Jump(float sec, float height, float x, float y)
{
	cocos2d::Vec2 vec(x, y);
	ActionInterval* pkAction = JumpBy::create(sec, vec, height, 1);
	auto event = [=]{};
	pkAction = Sequence::createWithTwoActions(pkAction, CallFunc::create(event));
	pkAction->setTag(XDefault_Tags::eAnimateSpriteAnimateTag);
	runAction(pkAction);
}

void XActionNode::KnockDown(float duration, float xspeed, float yspeed)
{
	stopActionByTag(XDefault_Tags::eAnimateSpriteMoveTag);
	ActionInterval* pkAction = KnockDown::create(duration, xspeed, yspeed);

	if (m_actionEventLambda)
	{
		auto event = [=]
		{
		};
		pkAction = Sequence::createWithTwoActions(pkAction, CallFunc::create(event));
	}
	pkAction->setTag(XDefault_Tags::eAnimateSpriteMoveTag);
	runAction(pkAction);
}

void XActionNode::setPosition(float x, float y)
{
	Node::setPosition(x, y);
	setZOrder(y);
	reorderChild(this, -y);
}

void XActionNode::setLocation(float x, float y, float z)
{
	// 更新自己的x坐标
	setPositionX(x);
	//CCLog("_csbNode.y = %d", _csbNode->getPositionY());
	// 更新z值
	setPositionY(z);
}

