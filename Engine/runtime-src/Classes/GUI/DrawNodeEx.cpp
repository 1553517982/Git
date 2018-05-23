#include "DrawNodeEx.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "2d/CCActionCatmullRom.h"
#include "platform/CCGL.h"

USING_NS_CC;
DrawNodeEx::DrawNodeEx() :_lineWidth(2.0f)
{
}


DrawNodeEx::~DrawNodeEx()
{
}

DrawNodeEx* DrawNodeEx::create()
{
	DrawNodeEx* ret = new (std::nothrow) DrawNodeEx();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

bool DrawNodeEx::init()
{
	return DrawNode::init();
}

void DrawNodeEx::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (_bufferCount)
	{
		_customCommand.init(_globalZOrder, transform, flags);
		_customCommand.func = CC_CALLBACK_0(DrawNodeEx::onDraw, this, transform, flags);
		renderer->addCommand(&_customCommand);
	}

	if (_bufferCountGLPoint)
	{
		_customCommandGLPoint.init(_globalZOrder, transform, flags);
		_customCommandGLPoint.func = CC_CALLBACK_0(DrawNodeEx::onDrawGLPoint, this, transform, flags);
		renderer->addCommand(&_customCommandGLPoint);
	}

	if (_bufferCountGLLine)
	{
		_customCommandGLLine.init(_globalZOrder, transform, flags);
		_customCommandGLLine.func = CC_CALLBACK_0(DrawNodeEx::onDrawGLLineEx, this, transform, flags);
		renderer->addCommand(&_customCommandGLLine);
	}
}

void DrawNodeEx::onDrawGLLineEx(const cocos2d::Mat4 &transform, uint32_t flags)
{
	auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR);
	glProgram->use();
	glProgram->setUniformsForBuiltins(transform);

	GL::blendFunc(_blendFunc.src, _blendFunc.dst);

	if (_dirtyGLLine)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vboGLLine);
		glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacityGLLine, _bufferGLLine, GL_STREAM_DRAW);
		_dirtyGLLine = false;
	}
	if (Configuration::getInstance()->supportsShareableVAO())
	{
		GL::bindVAO(_vaoGLLine);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vboGLLine);
		GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
		// vertex
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
		// color
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
		// texcood
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
	}
	glLineWidth(_lineWidth);
	glDrawArrays(GL_LINES, 0, _bufferCountGLLine);

	if (Configuration::getInstance()->supportsShareableVAO())
	{
		GL::bindVAO(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _bufferCountGLLine);
	CHECK_GL_ERROR_DEBUG();
}