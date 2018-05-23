//#include "core/2D/XAnimateSprite8D.h"
//#define PI 3.1415926535897932385f
//
//
//XAnimateSprite8D::XAnimateSprite8D() : m_nDirectionID(1),
//									   m_nActionSubID(0),
//									   m_dirFlip(1,false),
//									   m_fSpeed(SP8D_MOVE_SPEED_BASE)
//{
//}
//
//XAnimateSprite8D::~XAnimateSprite8D()
//{
//
//}
//
//XAnimateSprite8D* XAnimateSprite8D::create()
//{
//	XAnimateSprite8D *sprite = new (std::nothrow) XAnimateSprite8D();
//	if (sprite && sprite->init())
//	{
//		sprite->autorelease();
//		return sprite;
//	}
//	CC_SAFE_DELETE(sprite);
//	return nullptr;
//}
//
//int XAnimateSprite8D::_getActionID(int dir)
//{
//	return dir * SP8D_DIRECTION_PREFIX_MODIFIER + m_nActionSubID;
//}
//
//void XAnimateSprite8D::setDirection(int direction_id, bool playAction)
//{
//	m_nDirectionID = direction_id;
//	m_dirFlip = XSpriteHelpers::dirToFlip(m_nDirectionID);
//	if (playAction)
//	{
//		_playAction(m_nActionSubID, m_bRepeatforever);
//	}
//}
//
//bool XAnimateSprite8D::_playAction(int actionID, bool repeatforever)
//{
//	m_nActionSubID = actionID;
//	actionID = _getActionID(m_dirFlip._dir);
//	setFlippedX(m_dirFlip._filp);
//	return XAnimateSprite::_playAction(actionID, repeatforever); 
//}
//
//void XAnimateSprite8D::faceTo(const Vec2& lookat, bool playAction)
//{
//	int dir = XSpriteHelpers::posTo8Dir(_position, lookat);
//	setDirection(dir, playAction);
//}
//
//void XAnimateSprite8D::moveTo(const Vec2& v, CallFunc* pkArriveCallback)
//{
//	if (_position == v)
//	{
//		stopActionByTag(SP8D_MOVE_SPEED_TAG);
//		return;
//	}
//	float dst = v.distance(_position);
//	dst = dst / SP8D_MOVE_PIXEL_PER_SECOND;
//	ActionInterval* pkAction = MoveTo::create(dst, v);
//	if (pkArriveCallback)
//	{
//		pkAction = Sequence::createWithTwoActions(pkAction, pkArriveCallback);
//	}
//	movement(pkAction, v);
//}
//
//void XAnimateSprite8D::stopMove()
//{
//	stopActionByTag(SP8D_MOVE_SPEED_TAG);
//}
//
//void XAnimateSprite8D::setMoveSpeed(float speed)
//{
//	m_fSpeed = speed;
//	Speed* pkAction = dynamic_cast<Speed*>(getActionByTag(SP8D_MOVE_SPEED_TAG));
//	if (pkAction)
//	{
//		float rate = m_fSpeed / SP8D_MOVE_SPEED_BASE;
//		pkAction->setSpeed(rate);
//	}
//}
//
//void XAnimateSprite8D::movement(ActionInterval* pkAction, const Vec2& v)
//{
//	stopActionByTag(SP8D_MOVE_SPEED_TAG);
//	faceTo(v, true);
//	//float dst = v.distanceSquared(_position);
//	Speed* pkSpeed = Speed::create(pkAction, m_fSpeed / SP8D_MOVE_SPEED_BASE);
//	pkSpeed->setTag(SP8D_MOVE_SPEED_TAG);
//	runAction(pkSpeed);
//}