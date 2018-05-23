#include "XGameTile.h"
#include "supports/XResource/XAsyncLoaderManager.h"

XGameTile::XGameTile()
{
	this->init();
	m_pkLoadCallback = XAsyncLoaderCallback::create();
	m_pkLoadCallback->retain();
}


XGameTile::~XGameTile()
{
	m_pkLoadCallback->cancel();
	CC_SAFE_RELEASE_NULL(m_pkLoadCallback);
}

XGameTile* XGameTile::create()
{
	XGameTile * ret = new (std::nothrow) XGameTile();
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

void XGameTile::loadAsync(const std::string&filename)
{
	m_pkLoadCallback->init(CC_CALLBACK_1(XGameTile::onTextureAsyncLoad, this));
#ifdef _DEBUG_TILE
	m_strTextureName = filename;
#define _TEXTURE_NAME m_strTextureName
#else
#define _TEXTURE_NAME ""
#endif // _DEBUG
	/*
	auto ptr = shared_ref_ptr(this);
	TextureCache::getInstance()->addImageAsync(filename, [=](Texture2D* tex)
	{
	if (tex)
	{
	XAsyncLoaderRet ret = XAsyncLoaderRet(eOK, tex, "");
	ptr->onTextureAsyncLoad(&ret);
	}
	});*/

	//auto ret = XAsyncLoaderRet(eOK, TextureCache::getInstance()->addImage(filename), "");
	//this->onTextureAsyncLoad(&ret);
	XAsyncLoaderManager::sharedManager()->loadTexture(filename, _TEXTURE_NAME, Priority::TILE, m_pkLoadCallback);
}

void XGameTile::onTextureAsyncLoad(const XAsyncLoaderRet* retCode)
{
	// 如果成功，提示成功
	XAsyncLoaderCode result = (XAsyncLoaderCode)retCode->ret();
#ifdef _DEBUG_TILE
	if (result == XAsyncLoaderCode::eOK && m_strTextureName == retCode.customID())
#else
	if (result == XAsyncLoaderCode::eOK)
#endif
	{
		Texture2D* pkTex2D = (Texture2D*)retCode->data();
		this->setTexture(pkTex2D);
		this->setTextureRect(Rect(0, 0, pkTex2D->getPixelsWide(), pkTex2D->getPixelsHigh()));
		this->setVisible(true);
	}
	else
	{
#ifdef _DEBUG_TILE
		XLOGERROR("load Texture Failed %s", m_strTextureName.c_str());
#else
		XLOGERROR("load Texture Failed");
		this->setTexture(nullptr);
#endif
	}
}

void XGameTile::cleanup()
{
	resetTile();
	Node::cleanup();
}

void XGameTile::resetTile()
{
	setTexture(NULL);
	m_pkLoadCallback->cancel();
}