#ifndef __XFrameTransform_H__
#define __XFrameTransform_H__
#include "cocos2d.h"
USING_NS_CC;

/*! \class XFrameTransform
*  \brief XFrameTransform 一般的帧变换，包括位置，缩放，切边，深度和旋转
*
*
*/

class XFrameTransform
{
public:
	XFrameTransform();
	~XFrameTransform();
	void apply(Node* pkSprite, bool bFlipX);
	Vec2			m_kPos;
	Vec2			m_kScale;
	Vec2			m_kSkew;
	int				m_nZOrder;
	float			m_fRot;
	/*HFrameColor*	m_pkColor;*/
};

#endif 
