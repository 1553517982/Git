#include "XResource/XResourceUtils.h"
#include "XResource/XAsyncLoaderManager.h"
#include "download/XDownloader.h"
#include "cocos/2d/Animation/XAnimationCache.h"
//#include "cocos/2d/SlotAnimation/XSlotAnimationConfig.h"
#include "cocos/studio_ext/XCSLoader.h"
#include "cocos/studio_ext/XCSLoaderRet.h"
//#include "supports/utils/unzip/XUnzipUtils.h"
#include <stdio.h>
USING_NS_CC;

#define DEFAULT_CONNECTION_TIMEOUT 8

static FileUtils								*s_fileUtils;
static std::string								s_storagePath;
static TextureCache								*s_textureCache;
//static XImageSetMgr								*s_pkNewImageSetManager;
static XResourceDataBase						*s_pkXResourceDataBase;
void XResourceUtils::init()
{
	s_textureCache = Director::getInstance()->getTextureCache();
	s_fileUtils = FileUtils::getInstance();
//	s_pkNewImageSetManager = new XImageSetMgr();
	s_pkXResourceDataBase = new XResourceDataBase();
//	XDownloader::getInstance()->initialize("cache.xml", "192.168.25.138/test/", "");
}

void XResourceUtils::fini()
{
	//TODO
//	XUnzipUtils::purgeSharedUtils();
	XDownloader::destroyInstance();
//	XAnimationCache::destroyInstance();
	XAsyncLoaderManager::purgeSharedManager();
//	XSlotAnimationConfig::purgeSharedManager();
//	CC_SAFE_DELETE(s_pkNewImageSetManager);
	CC_SAFE_DELETE(s_pkXResourceDataBase);
}

void XResourceUtils::setStoragePath(const std::string& storagePath)
{
	if (s_storagePath.size() > 0)
		s_fileUtils->removeDirectory(s_storagePath);

	s_storagePath = storagePath;
	adjustPath(s_storagePath);
	s_fileUtils->createDirectory(s_storagePath);
}

void XResourceUtils::adjustPath(std::string &path)
{
	if (path.size() > 0 && path[path.size() - 1] != '/')
	{
		path.append("/");
	}
}

//XImageUnitList*	XResourceUtils::getFrameList(const char* filename)
//{
//	XFrameList* pkData = s_pkNewImageSetManager->getFrameList(filename);
//	if (!pkData)
//	{
//		std::string message("找不到frame list:");
//		message += std::string(filename);
//		cocos2d::MessageBox(message.c_str(), "找不到数据");
//		return NULL;
//	}
//	return pkData->Data();
//}

void XResourceUtils::unbindImageAsync(const std::string& path)
{
	s_textureCache->unbindImageAsync(path);
}

void XResourceUtils::loadImageAsync(const std::string& path, const std::function<void(Texture2D*)>& callback)
{
	s_textureCache->addImageAsync(path, callback);
}

bool XResourceUtils::loadImageSet(const char* filename)
{
	return false;
//	return s_pkNewImageSetManager->loadImageSet(filename);
}

bool XResourceUtils::loadFrameSet(const char* filename)
{
	return false;
//	return s_pkNewImageSetManager->loadFrameSet(filename);
}

//XImageUnit* XResourceUtils::findImageUnit(const char* filename, bool bCreateWhenNotFound)
//{
//	return s_pkNewImageSetManager->findImageUnit(filename, bCreateWhenNotFound);
//}

bool XResourceUtils::loadDependency(const char* filename)
{
	return s_pkXResourceDataBase->loadDependency(filename);
}

bool XResourceUtils::loadResourceConfig(const char* filename)
{
	return s_pkXResourceDataBase->loadConfig(filename);
}

SpriteFrame* XResourceUtils::getSpriteFrame(const char* filename, bool bCreateWhenNotFound)
{
	return nullptr;
//	return s_pkNewImageSetManager->getSpriteFrame(filename,bCreateWhenNotFound);
}

XResourceDataBase* XResourceUtils::getResourceDataBase()
{
	return s_pkXResourceDataBase;
}

XCSLoadRet* XResourceUtils::loadCSB(const char* filename, bool bWithTimeline, bool bCache, const ccNodeLoadCallback &callback)
{
	return XCSLoader::getInstance()->loadCSB(filename, bWithTimeline, bCache, callback);
}