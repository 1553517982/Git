#ifndef __XFrameModifier_H__
#define __XFrameModifier_H__
#include "cocos2d.h"
USING_NS_CC;

class XFrameTransform;

/*! \class XFrameModifier
*  \brief XFrameModifier 记录每一帧的变换（XFrameTransform的容器）和帧id
*
*
*/
//每一帧的变化
class XFrameModifier
{
public:
	XFrameModifier();
	virtual ~XFrameModifier();

	/*!
	* \brief	   应用修改
	* \param 	   Node * pkSprite
	* \param 	   bool bFlipX
	* \returns   void
	*/void apply(Node* pkSprite, bool bFlipX);

	/*!
	* \brief 创建XFrameModifier
	* \return XFrameModifier*
	*/
	static XFrameModifier* create();

	int					getFrameID();
	Vec2				getPosition();
	Vec2				getScale();
	int					getZOrder();
	float				getRotation();

	void				setFrameID(int id);
	void				setPosition(float x, float y);
	void				setScale(float x, float y);
	void				setZOrder(int n);
	void				setRotation(float r);

	bool				isVisible(void);

	unsigned int		m_nFrameIndex;

	XFrameTransform*	m_pkXFrameTransform;
};

typedef std::map<int, XFrameModifier*> tXFrameModifierMap;

#endif 
