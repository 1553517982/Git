
#ifndef __XResourceManager__
#define __XResourceManager__
#include "cocos2d.h"
#include "cocos-ext.h"

//#include "XBinary/XImageSetMgr.h"
//#include "XResource/XFrameAsyncLoader.h"
#include "platform/CCFileUtils.h"
#include "XResource/XResourceDataBase.h"
#include "cocos/studio_ext/XCSLoaderRet.h"
#include "cocostudio/ActionTimeline/CSLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

class XResourceUtils
{
public:
	static void init(void);

	static void fini(void);

	static void loadImageAsync(const std::string& path, const std::function<void(Texture2D*)>& callback);

	static void unbindImageAsync(const std::string& path);

	static void setStoragePath(const std::string& storagePath);

	static void adjustPath(std::string &path);

//	static XImageUnitList*	getFrameList(const char* filename);

	static bool loadImageSet(const char* filename);

	static bool loadFrameSet(const char* filename);

	static bool loadDependency(const char* filename);

	static bool loadResourceConfig(const char* filename);

//	static XImageUnit* findImageUnit(const char* filename, bool bCreateWhenNotFound);

	static SpriteFrame* getSpriteFrame(const char* filename, bool bCreateWhenNotFound);

	static XResourceDataBase* getResourceDataBase();

	static XCSLoadRet* loadCSB(const char* filename, bool bWithTimeline, bool bCache, const ccNodeLoadCallback &callback);

};
#endif