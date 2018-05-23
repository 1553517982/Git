#ifndef __CCSIZE_H__
#define __CCSIZE_H__
#include "cocos2d.h"
NS_CC_BEGIN

class SizeTo : public ActionInterval
{
public:

	/** initializes the action with and width and height */
	bool initWithDuration(float duration, float sx, float sy);
	/**
	*  @js NA
	*  @lua NA
	*/
	virtual SizeTo* clone() const override;
	virtual void startWithTarget(Node *pTarget);
	virtual void update(float time);

public:

	/** creates the action with and width and a height */
	static SizeTo* create(float duration, float sx, float sy);
protected:
	float m_fWidth;
	float m_fHeight;
	float m_fStartWidth;
	float m_fStartHeight;
	float m_fEndWidth;
	float m_fEndHeight;
	float m_fDeltaWidth;
	float m_fDeltaHeight;
};

NS_CC_END

#endif 