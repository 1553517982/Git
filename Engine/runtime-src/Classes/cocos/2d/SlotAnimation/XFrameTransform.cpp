#include "XFrameTransform.h"
#include "XCommon.h"

XFrameTransform::XFrameTransform() :
m_nZOrder(0),
m_kScale(1, 1),
m_fRot(0)
/*,m_pkColor(NULL) */
{
}

XFrameTransform::~XFrameTransform()
{
	/* delete m_pkColor; */
}

void XFrameTransform::apply(Node* pkNode, bool bFlipX)
{
	XAssert(pkNode, "XFrameTransform::apply pkNode == NULL");
	XAssert(pkNode->getParent(), "XFrameTransform::apply pkNode->getParent() == NULL");
	if (bFlipX)
	{
		pkNode->setPosition(Vec2(-m_kPos.x, m_kPos.y));
		pkNode->setRotation(-m_fRot);
	}
	else
	{
		pkNode->setPosition(m_kPos);
		pkNode->setRotation(m_fRot);
	}
	pkNode->setScaleX(m_kScale.x);
	pkNode->setScaleY(m_kScale.y);
	if (m_nZOrder != 0)
	{
		pkNode->getParent()->reorderChild(pkNode, m_nZOrder);
	}
	pkNode->setSkewX(m_kSkew.x);
	pkNode->setSkewY(m_kSkew.y);
	/*if(m_pkColor)
	{
	pkSprite->setOpacity(m_pkColor->m_uOpacity);
	pkSprite->setColor(m_pkColor->m_kColor);
	}*/
}
