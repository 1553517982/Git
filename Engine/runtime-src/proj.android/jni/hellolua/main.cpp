#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "ide-support/SimpleConfigParser.h"
#include "ide-support/CodeIDESupport.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz)
 {
	 
	//CCLog("cocos_android_app_init");
    LOGD("cocos_android_app_init");
	//LOGD( "a" );
    AppDelegate *pAppDelegate = new AppDelegate();
}

extern "C"
{
    bool Java_org_cocos2dx_lua_AppActivity_nativeIsLandScape(JNIEnv *env, jobject thisz)
    {
		bool bRes =SimpleConfigParser::getInstance()->isLanscape();

        return bRes;
    }

	bool Java_org_cocos2dx_lua_AppActivity_nativeIsDebug(JNIEnv *env, jobject thisz)
	{
		LOGD( "Java_org_cocos2dx_lua_AppActivity_nativeIsDebug" );
		
#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
        return true;
#else
        return false;
#endif
	}


}

