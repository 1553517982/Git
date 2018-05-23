#include "XSceneBackgroundLayer.h"
//#include "supports/CustomShader/CustomGLProgramCache.h"
//#include <set>
//#include "json/document.h"
//#include "json/stringbuffer.h"
//#include "json/writer.h"
//#define _JsonHelper cocostudio::DictionaryHelper::getInstance()

XSceneBackgroundLayer::XSceneBackgroundLayer()
{
	//m_pkRoot = Node::create();
	//this->addChild(m_pkRoot);
	m_pkBackground = cocos2d::CCSprite::create();
	this->addChild(m_pkBackground);
	m_pkBackground->setAnchorPoint(Vec2(0, 0));
	
}

XSceneBackgroundLayer::~XSceneBackgroundLayer()
{

}

XSceneBackgroundLayer * XSceneBackgroundLayer::create()
{
	XSceneBackgroundLayer * ret = new (std::nothrow) XSceneBackgroundLayer();
	if (ret && ret->init())
	{
		//ret->setBackground(strBackground);
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void XSceneBackgroundLayer::onPause()
{
	m_pkBackground->setTexture(NULL);
//	m_pkBackground->cancelLoadAsync();
}

void XSceneBackgroundLayer::onResume()
{
	setBackground(m_strBackground);
}

void XSceneBackgroundLayer::setShadername(const std::string& name)
{
	m_strShadername = name;
}

void XSceneBackgroundLayer::setBackground(const std::string& strBackground)
{
	//m_strBackground = strBackground;

	//char buf[256] = { 0 };
	//snprintf(buf, 255, "%s%d/%s", m_strResPath.c_str(), m_nLayerID, strBackground.c_str());
	//std::string fullPath = buf;

	//XAsyncLoadOption option;
	//auto func = [=](const XAsyncLoaderRet* ret)
	//{
	//	if (ret->ret() == XAsyncLoaderCode::eOK)
	//	{
	//		m_pkBackground->setTexture(fullPath);
	//		auto tex = m_pkBackground->getTexture();
	//		if (!m_strShadername.empty() && tex)
	//		{
	//			if (m_UVTranslate.x != 0.0f || m_UVTranslate.y != 0.0f)
	//			{
	//				Texture2D::TexParams param;
	//				param.magFilter = GL_LINEAR;
	//				param.minFilter = GL_LINEAR;
	//				param.wrapS = GL_REPEAT;
	//				param.wrapT = GL_REPEAT;
	//				tex->setTexParameters(param);
	//				//schedule(func);
	//				auto glProgramState = GLProgramState::create(CustomGLProgramCache::getInstance()->getGLProgram(m_strShadername.c_str()));
	//				if (glProgramState)
	//				{
	//					glProgramState->setUniformVec2("v_texRate", m_UVTranslate);
	//					m_pkBackground->setGLProgramState(glProgramState);
	//				}
	//			}
	//		}

	//	}
	//};
	//option.init(fullPath.c_str(), "", Priority::TILE, func);
	//m_pkBackground->loadTextureAsync(&option);
}

void XSceneBackgroundLayer::initUVTranslate(float x, float y)
{
	m_UVTranslate.x = x;
	m_UVTranslate.y = y;
	m_strShadername = "cs_uvTranslate";
}

void XSceneBackgroundLayer::transfomUV(float dt)
{
	//V3F_C4B_T2F_Quad quad = m_pkBackground->getQuad();
	//quad.bl.texCoords.u += m_UVTranslate.x;
	//quad.bl.texCoords.v += m_UVTranslate.y;

	//quad.tl.texCoords.u += m_UVTranslate.x;
	//quad.tl.texCoords.v += m_UVTranslate.y;

	//quad.br.texCoords.u += m_UVTranslate.x;
	//quad.br.texCoords.v += m_UVTranslate.y;

	//quad.tr.texCoords.u += m_UVTranslate.x;
	//quad.tr.texCoords.v += m_UVTranslate.y;
	//m_pkBackground->setXQuad(quad);
}

void XSceneBackgroundLayer::readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix)
{
	//XSceneLayer::readLayer(entry, layerID, parent, prefix);

	//std::string bg = _JsonHelper->getStringValue_json(entry, "bg", "");
	//m_basePos.x = _JsonHelper->getFloatValueFromArray_json(entry, "pos", 0, 0.0f);
	//m_basePos.y = _JsonHelper->getFloatValueFromArray_json(entry, "pos", 1, 0.0f);

	//m_baseScale.x = _JsonHelper->getFloatValueFromArray_json(entry, "scale", 0, 1.0f);
	//m_baseScale.y = _JsonHelper->getFloatValueFromArray_json(entry, "scale", 1, 1.0f);

	//m_UVTranslate.x = _JsonHelper->getFloatValueFromArray_json(entry, "uvTranslate", 0, 1.0f);
	//m_UVTranslate.y = _JsonHelper->getFloatValueFromArray_json(entry, "uvTranslate", 1, 1.0f);

	//if (m_UVTranslate.x != 0.0f || m_UVTranslate.y != 0.0f)
	//{
	//	initUVTranslate(m_UVTranslate.x, m_UVTranslate.y);
	//}
	//m_pkBackground->setPosition(m_basePos);
	//m_pkBackground->setScale(m_baseScale.x, m_baseScale.y);
	//setBackground(bg.c_str());
}

void XSceneBackgroundLayer::setBasePos(cocos2d::Vec2 val)
{
	m_basePos = val;
	m_pkBackground->setPosition(val);
}

void XSceneBackgroundLayer::setBaseScale(cocos2d::Vec2 val)
{
	m_baseScale = val;
	m_pkBackground->setScale(val.x,val.y);
}

void XSceneBackgroundLayer::setUVTranslate(cocos2d::Vec2 val)
{
	/*
	m_UVTranslate = val;
	auto tex = m_pkBackground->getTexture();
	if (!m_strShadername.empty() && tex)
	{
		if (m_UVTranslate.x != 0.0f || m_UVTranslate.y != 0.0f)
		{
			Texture2D::TexParams param;
			param.magFilter = GL_LINEAR;
			param.minFilter = GL_LINEAR;
			param.wrapS = GL_REPEAT;
			param.wrapT = GL_REPEAT;
			tex->setTexParameters(param);
			//schedule(func);
			//auto glProgramState = GLProgramState::create(CustomGLProgramCache::getInstance()->getGLProgram(m_strShadername.c_str()));
			//if (glProgramState)
			//{
			//	glProgramState->setUniformVec2("v_texRate", m_UVTranslate);
			//	m_pkBackground->setGLProgramState(glProgramState);
			//}
		}
	}
	*/
}