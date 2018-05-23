#pragma once
#include "2d/CCDrawNode.h"

//扩展DrawNode 可以设置线宽
class DrawNodeEx :
	public cocos2d::DrawNode
{
public:
	static DrawNodeEx* create();

	void setLineWidth(float width) { _lineWidth = width; }
	float getLineWidth()			{ return  _lineWidth; }

	void onDrawGLLineEx(const cocos2d::Mat4 &transform, uint32_t flags);
	// Overrides
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

CC_CONSTRUCTOR_ACCESS:
	DrawNodeEx();
	~DrawNodeEx();
	virtual bool init() override;

protected:
	float		_lineWidth;
};

