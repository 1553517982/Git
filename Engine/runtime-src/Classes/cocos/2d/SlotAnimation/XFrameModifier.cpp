#include "XFrameModifier.h"
#include "XFrameTransform.h"

#include "XCommon.h"

XFrameModifier::XFrameModifier() :
m_pkXFrameTransform(NULL)
{
}

XFrameModifier::~XFrameModifier()
{
	if (m_pkXFrameTransform)
		delete m_pkXFrameTransform;
}

void XFrameModifier::apply(Node* pkSprite, bool bFlipX)
{
	if (m_pkXFrameTransform)
		m_pkXFrameTransform->apply(pkSprite, bFlipX);
}

int	XFrameModifier::getFrameID()
{
	return m_nFrameIndex;
}

Vec2	XFrameModifier::getPosition()
{
	if (m_pkXFrameTransform)
		return m_pkXFrameTransform->m_kPos;
	return Vec2(0, 0);
}

Vec2	XFrameModifier::getScale()
{
	if (m_pkXFrameTransform)
		return m_pkXFrameTransform->m_kScale;
	return Vec2(1, 1);
}

int	XFrameModifier::getZOrder()
{
	if (m_pkXFrameTransform)
		return m_pkXFrameTransform->m_nZOrder;
	return 0;
}

float XFrameModifier::getRotation()
{
	if (m_pkXFrameTransform)
		return m_pkXFrameTransform->m_fRot;
	return 0;
}

void XFrameModifier::setFrameID(int id)
{
	m_nFrameIndex = id;
}

void XFrameModifier::setPosition(float x, float y)
{
	if (!m_pkXFrameTransform)
	{
		m_pkXFrameTransform = new XFrameTransform();
	}
	m_pkXFrameTransform->m_kPos = Vec2(x, y);
}

void XFrameModifier::setScale(float x, float y)
{
	if (!m_pkXFrameTransform)
	{
		m_pkXFrameTransform = new XFrameTransform();
	}
	m_pkXFrameTransform->m_kScale = Vec2(x, y);
}

void XFrameModifier::setZOrder(int n)
{
	if (!m_pkXFrameTransform)
	{
		m_pkXFrameTransform = new XFrameTransform();
	}
	m_pkXFrameTransform->m_nZOrder = n;
}

void XFrameModifier::setRotation(float r)
{
	if (!m_pkXFrameTransform)
	{
		m_pkXFrameTransform = new XFrameTransform();
	}
	m_pkXFrameTransform->m_fRot = r;
}

XFrameModifier* XFrameModifier::create()
{
	XFrameModifier*pkObj = new XFrameModifier();
	return pkObj;
}


bool XFrameModifier::isVisible(void)
{
	if (m_pkXFrameTransform)
		return (m_pkXFrameTransform->m_kScale.x != 0) && (m_pkXFrameTransform->m_kScale.y != 0);
	else
		return false;
}