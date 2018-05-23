#include "cocos/2d/SizeTo.h"

NS_CC_BEGIN

SizeTo* SizeTo::create(float duration, float sx, float sy)
{
	SizeTo *pSizeTo = new (std::nothrow) SizeTo();
	pSizeTo->initWithDuration(duration, sx, sy);
	pSizeTo->autorelease();

	return pSizeTo;
}

bool SizeTo::initWithDuration(float duration, float sx, float sy)
{
	if (ActionInterval::initWithDuration(duration))
	{
		m_fEndWidth = sx;
		m_fEndHeight = sy;

		return true;
	}

	return false;
}

SizeTo* SizeTo::clone() const
{
	// no copy constructor
	auto a = new (std::nothrow) SizeTo();
	a->initWithDuration(_duration,m_fEndWidth,m_fEndHeight);
	a->autorelease();
	return a;
}

void SizeTo::startWithTarget(Node *pTarget)
{
	ActionInterval::startWithTarget(pTarget);
// 	if (dynamic_cast<gui::Widget*>(_target) != NULL)
// 	{
// 		gui::Widget *widget = dynamic_cast<gui::Widget*>(_target);
// 		m_fStartWidth = widget->getSize().width;
// 		m_fStartHeight = widget->getSize().height;
// 	}
// 	else
	{
		m_fStartWidth = pTarget->getContentSize().width;
		m_fStartHeight = pTarget->getContentSize().height;
	}
	m_fDeltaWidth = m_fEndWidth - m_fStartWidth;
	m_fDeltaHeight = m_fEndHeight - m_fStartHeight;
}

void SizeTo::update(float time)
{
	if (_target)
	{
		float width = m_fStartWidth + m_fDeltaWidth * time;
		float height = m_fStartHeight + m_fDeltaHeight * time;
// 		if (dynamic_cast<gui::Widget*>(m_pTarget) != NULL)
// 		{
// 			gui::Widget *widget = dynamic_cast<gui::Widget*>(m_pTarget);
// 			widget->setSize(Size(width, height));
// 		}
// 		else
		{
			_target->setContentSize(Size(width, height));
		}
	}
}
NS_CC_END
