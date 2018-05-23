#include "XSpriteFrame.h"

XSpriteFrame* XSpriteFrame::createWithTexture(Texture2D* texture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize)
{
	XSpriteFrame *spriteFrame = new (std::nothrow) XSpriteFrame();
	spriteFrame->initWithTexture(texture, rect, rotated, offset, originalSize);
	spriteFrame->autorelease();

	return spriteFrame;
}

XSpriteFrame::XSpriteFrame() :
	m_FrameID(-1)
{

}

XSpriteFrame::~XSpriteFrame()
{
}

XSpriteFrame* XSpriteFrame::clone() const
{
	// no copy constructor	
	XSpriteFrame *copy = new (std::nothrow) XSpriteFrame();
	copy->initWithTextureFilename(_textureFilename.c_str(), _rectInPixels, _rotated, _offsetInPixels, _originalSizeInPixels);
	copy->setTexture(_texture);
	copy->setFrameID(m_FrameID);
	copy->autorelease();
	return copy;
}
