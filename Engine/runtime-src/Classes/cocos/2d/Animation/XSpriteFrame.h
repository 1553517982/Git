#include "cocos2d.h"
#include <map>
#include <list>
#include <string>
#include "extention/XBinary/XImageSet.h"
#include "cocostudio/DictionaryHelper.h"
#ifndef __XSpriteFrame__
#define __XSpriteFrame__
USING_NS_CC;
class XSpriteFrame : public SpriteFrame
{
public:
	
	static XSpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

	int getFrameID() const { return m_FrameID; }

	void setFrameID(int val) { m_FrameID = val; }

	// Overrides
	virtual XSpriteFrame *clone() const override;

protected:
	/**
	* @js ctor
	*/
	XSpriteFrame();
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~XSpriteFrame();

protected:
	int		m_FrameID;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(XSpriteFrame);
};
#endif