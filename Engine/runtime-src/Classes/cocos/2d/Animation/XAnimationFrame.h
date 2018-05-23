#include "cocos2d.h"
#include <map>
#include <list>
#include <string>
#include "extention/XBinary/XImageSet.h"
//#include "cocostudio/DictionaryHelper.h"
#ifndef __XAnimationFrame__
#define __XAnimationFrame__
USING_NS_CC;
class XAnimationFrame : public AnimationFrame
{
public:
	/**
	* Creates the animation frame with a spriteframe, number of delay units and a notification user info.
	*
	* @param spriteFrame The animation frame with a spriteframe.
	* @param delayUnits Number of delay units.
	* @param userInfo A notification user info.
	* @since 3.0
	*/
	static XAnimationFrame* create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo);


	// Overrides
	virtual XAnimationFrame *clone() const override;

	int getFrameID() const { return m_FrameID; }

	void setFrameID(int val) { m_FrameID = val; }

protected:
	/**
	* @js ctor
	*/
	XAnimationFrame();
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~XAnimationFrame();

protected:
	int		m_FrameID;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(XAnimationFrame);
};
#endif