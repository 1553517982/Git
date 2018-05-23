#include "XSprite.h"
#include "supports/XResource/XAsyncLoaderManager.h"
#include "XResource/XResourceUtils.h"
#include "CCLuaEngine.h"

XSprite::XSprite(void) : m_pkCallback(nullptr), m_bAutoUpdateBlendFunc(false)
{

}

XSprite::~XSprite(void)
{
	if (m_pkCallback)
	{
		m_pkCallback->cancel();
		m_pkCallback->release();
	}
}

XSprite* XSprite::create()
{
	XSprite *sprite = new (std::nothrow) XSprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

XSprite* XSprite::create(const std::string& filename)
{
	XSprite *sprite = new (std::nothrow) XSprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool XSprite::initWithImageUnit(const std::string& filename)
{
	auto* pkFrame = XResourceUtils::getSpriteFrame(filename.c_str(), true);
	if (pkFrame)
	{
		setSpriteFrame(pkFrame);
		return true;
	}
	else
	{
		return false;
	}
}

void XSprite::loadTextureAsync(XAsyncLoadOption* option)
{
	if (!option)
	{
		XLOGERROR("loadTextureAsync option == null");
		return;
	}
	
	auto& skinName = option->m_filename;
	auto& customId = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;

	if (m_pkCallback == nullptr)
	{
		m_pkCallback = XAsyncLoaderCallback::create();
		m_pkCallback->retain();
	}
	m_pkCallback->init(load_callback);
	XAsyncLoaderManager::sharedManager()->loadTexture(skinName, customId, priority, m_pkCallback);

}

void XSprite::loadAnimationAsync(XAsyncLoadOption* option)
{
	if (!option)
	{
		XLOGERROR("loadAnimationAsync option == null");
		return;
	}

	auto& skinName = option->m_filename;
	auto& customId = option->m_customID;
	auto& load_callback = option->m_callback;
	auto priority = option->m_priority;

	if (m_pkCallback == nullptr)
	{
		m_pkCallback = XAsyncLoaderCallback::create();
		m_pkCallback->retain();
	}
	m_pkCallback->init(load_callback);
	XAsyncLoaderManager::sharedManager()->loadAnimation(skinName, customId, priority, m_pkCallback);
}

void XSprite::cancelLoadAsync()
{
	if (m_pkCallback)
	{
		m_pkCallback->cancel();
		m_pkCallback->release();
		m_pkCallback = nullptr;
	}
}

void XSprite::setRelativePosition(float x, float y)
{
	if (_parent)
	{
		const Size& sz = _parent->getContentSize();
		setPosition(sz.width* x, sz.height *y);
	}
}

void XSprite::updateBlendFunc()
{
	if (m_bAutoUpdateBlendFunc)
	{
		Sprite::updateBlendFunc();
	}
}

void XSprite::setXQuad(const V3F_C4B_T2F_Quad& quad)
{
	_quad = quad;
}

void XSprite::cleanup()
{
	if (m_pkCallback)
	{
		m_pkCallback->cancel();
		m_pkCallback->release();
		m_pkCallback = nullptr;
	}
	Sprite::cleanup();
}
//void setAsynLoadNotifier(int val);