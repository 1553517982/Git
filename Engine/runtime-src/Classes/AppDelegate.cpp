#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"
#include "supports/XResource/XResourceUtils.h"
#include "supports/download/XDownloader.h"
#include "helpers/ResourceHelpers.h"
#include "helpers/ScriptCallbackHelpers.h"
#include "lua_export/auto/lua_gamecore_helpers_auto.hpp"
#include "lua_export/auto/lua_gamecore_ccsext_auto.hpp"
#include "lua_export/auto/lua_gamecore_scene_auto.hpp"
#include "lua_export/auto/lua_gui_common_auto.hpp"
#include "helpers/SceneHelper.h"
#include "network/CCNetworkLoop.h"
#include "helpers/XLambda.h"
#include "cocostudio/CocoStudio.h"
#include "GUI/RichTextCreator.h"
#include "network/HttpClient.h"
#include "ui/UILoadingBar.h"
#include "ui/UIText.h"
#include "ui/UILayout.h"
// Readers
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"
#include "cocostudio/ActionTimeline/CCActionTimelineCache.h"
#include "XCommon.h"
#include "utils/md5/XMD5Utils.h"
#include "GUI/BreadthWidget.h"
#include <curl/curl.h>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX)
#include "ide-support/CodeIDESupport.h"
#endif

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#include "runtime/Runtime.h"
#include "ide-support/RuntimeLuaImpl.h"
#endif

//TOLUA_API int luaopen_gamecore_helpers_manual_export(lua_State* tolua_S);

extern "C"
{
	int luaopen_lfs_dir(lua_State *L);
}



static void AppDelegateStageHandler(int eEvent);

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
	
}

AppDelegate::~AppDelegate()
{
	ResourceHelpers::fini();	// added by aXing on 2017-4-17 里面有个异步回调的callback，要释放掉，要不然会出错
	CLuaHttp::Inst().Clear();
	ScriptHandlerMgr::destroyInstance();
    SimpleAudioEngine::end();
	CNewLoader::OnEnd();
#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
#endif

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	curl_global_init(CURL_GLOBAL_ALL);
#if defined (WIN32)		// 用于PC上开发
	UserDefault::getInstance()->setStringForKey("PLATFORM", "pc");
	UserDefault::getInstance()->setStringForKey("TEST_VERSION", "test");
#endif

#ifdef RAYMOND_PACK_DEBUG
	//UserDefault::getInstance()->setStringForKey("PACK", "1");
#endif

	EnterGame();
	return true;
}

//class YouMeVoiceEngineImp : public IYouMeCommonCallback,public IYouMeConferenceCallback
//{
//public:
//	static YouMeVoiceEngineImp *getInstance(){
//		static YouMeVoiceEngineImp inst;
//		return &inst;
//	}
//	virtual void onEvent(const YouMeEvent_t &event, const YouMeErrorCode &errcode)
//	{
//		switch (event)
//		{
//		case YOUME_INIT_OK:
//		{
//			int a = 0;
//			//主播模式
//			//IYouMeVoiceEngine::getInstance()->joinConference_2("123", "testroom", false, true, false, false);
//			//听众模式
//			IYouMeVoiceEngine::getInstance()->joinConference_2("125", "testroom", false, false, true, false);
//		}
//			break;
//		case YOUME_INIT_NOK:
//			
//			break;
//		default:
//			break;
//		}
//	}
//	virtual void onCallEvent(const YouMeCallEvent_t &event, const YouMeErrorCode_t &errCode){
//
//	}
//	virtual void onCommonStatusEvent(STATUS_EVENT_TYPE_t eventType, const std::string
//		&strUserID, int iStatus){
//	}
//	virtual void onMemberChangeEvent(const std::string &strUserIDs){
//
//	}
//};

void AppDelegate::EnterGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// 超级诡异的问题，在Android里面，初始化so是子线程做的，不在主线程做
	// 所以需要到这里开设置主线程id，进入FileUtils，因为需要检查线程安全
	std::thread::id currentThread = std::this_thread::get_id();
	FileUtils::getInstance()->setMainThread(currentThread);
#endif
	// added by aXing on 2017-4-10
	// 强行尝试添加sdcard到搜索路径
	std::string wpath = FileUtils::getInstance()->getWritablePath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static char buffer[512];
	GetCurrentDirectoryA(512, buffer);
	const std::vector<std::string> searchPaths;
	FileUtils::getInstance()->setSearchPaths(searchPaths);
	std::string sep = "\\";
	wpath = buffer + sep + wpath;
	std::replace(wpath.begin(), wpath.end(), '\\', '/');
	FileUtils::getInstance()->setWritablePath(wpath);
#endif
	FileUtils::getInstance()->addSearchPath(wpath, true);

//	CNewLoader::Inst().ReloadPack();

#if XBUILD_TYPE != XBUILD_GAME_TYPE
	"请将frameworks/cocos2d-x/cocos/platform/CCPlatformConfig.h XBUILD_TYPE设置为XBUILD_GAME_TYPE"
#endif
	// set default FPS
	Director::getInstance()->setAnimationInterval(1.0 / 60.0f);
	//Director::getInstance()->setStageCallback(AppDelegateStageHandler);

	// register lua module
	auto engine = LuaEngine::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	lua_State* L = engine->getLuaStack()->getLuaState();
	XLambdaLua::init();
	lua_module_register(L);
	register_all_helpers(L);
	register_all_ccsext(L);
	register_all_scene(L);
	register_all_guiex(L);
	//register_youmeim_manual(L);		// 注册语音接口
	//register_youmetalk_manual(L);
	//luaopen_gamecore_helpers_manual_export(L);
	register_scene_helper(L);
	luaopen_lfs_dir(L);

	//IYouMeVoiceEngine::getInstance()->init(YouMeVoiceEngineImp::getInstance(), YouMeVoiceEngineImp::getInstance(), "YOUME6DCF1DBFF3D0A3A591EBBC558910EF7F58DCAC10", "v84/FzblC80n9n/hESKC2n8kwyseWUQ1oF07Te35btAP5lubkxGK+jrR5Hh6VFK3kr9YpY+rgDkIH6PnQZpu6A/7S0/AgrlVzcgHzI6yYP6saQ56zWrrDjbVpYKUrAiDSOlZSTK2TYZQFhlE5hbpTe1mBNa8ntYbokUm881Xp/MBAAE=");
	

	register_all_packages();

	XResourceUtils::init();
	ResourceHelpers::init();
	register_all_packages();


	LuaStack* stack = engine->getLuaStack();
	stack->setXXTEAKeyAndSign("lx_cy_key", strlen("lx_cy_key"), "lx_cy_sign", strlen("lx_cy_sign"));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//static char buffer[512];
	//GetCurrentDirectoryA(512, buffer);
	//FileUtils::getInstance()->addSearchPath(buffer, true);
	//FileUtils::getInstance()->addSearchPath(buffer, true);
#endif // _DEBUG

	CCNetworkLoop::sharedManager()->start();

	XDownloader::getInstance()->initialize("", "", FileUtils::getInstance()->getWritablePath());

//#ifndef RAYMOND_PACK_DEBUG
	// 判断一下有没有main.lua，有则运行，否则直接运行代码
	FileUtils* utils = FileUtils::getInstance();
	ssize_t chunkSize = 0;
	char * pBuff = (char *)utils->getFileData("main.lua", "rb", &chunkSize);
	if (pBuff)
	{
		engine->executeBuff(pBuff, chunkSize);
		free(pBuff);
	}
	//engine->executeScriptFile( "main" );
//#else
//	//executeString
//	const char * pExe =
//		"require 'gamecore.application'\n"
//		"local function main()\n"
//		"application:run()\n"
//		"end\n"
//		"xpcall(main, __G__TRACKBACK__)";
//	int nSize = strlen(pExe);
//	engine->executeBuff(pExe, nSize);
//
//#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static int _AppShowState = -1;
#endif

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_AppShowState = 0;
	XLOG("AppDelegate::applicationDidEnterBackground()");
#endif

    Director::getInstance()->stopAnimation();

	CCNetworkLoop::sharedManager()->stop();
	AppDelegateStageHandler(eApplicationDidEnterBackground);
	ResourceHelpers::purgeCache();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (_AppShowState > 0)
		return;
	_AppShowState = 1;
#endif

	XLOG("AppDelegate::applicationWillEnterForeground()");
    Director::getInstance()->startAnimation();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//CustomGLProgramCache::getInstance()->reloadGLProgram();
#endif
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	CCNetworkLoop::sharedManager()->start();
	AppDelegateStageHandler(eApplicationWillEnterForeground);

}

void AppDelegateStageHandler(int eEvent)
{
	ScriptCallbackHelpers::onAppEvent(eEvent, "", "");

	switch (eEvent)
	{
		case eApplicationStart:
			XResourceUtils::init();
		break;

		case eApplicationDidEnterBackground:
#ifdef _DEBUG
			//XLOG("%s", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
#endif // _DEBUG
			break;

		case eApplicationWillEnterForeground:
			break;

		case eApplicationMemoryWarning:
			break;

		case eApplicationRestart:
			CCNetworkLoop::sharedManager()->start();
			break;

			// CCDirector reset begin
		case eApplicationResetBegin:
			ScriptCallbackHelpers::fini();
			XResourceUtils::fini();
			RichTextCreator::destroyInstance();
			ResourceHelpers::fini();
			CCNetworkLoop::sharedManager()->stop();
			CCNetworkLoop::purgeSharedManager();
			network::HttpClient::destroyInstance();
			cocostudio::timeline::ActionTimelineCache::destroyInstance();
			cocostudio::destroyCocosStudio();
			PoolManager::getInstance()->getCurrentPool()->clear();
			//CustomGLProgramCache::destroyInstance();
			break;

			// CCDirector reset end
		case eApplicationResetEnd:
			break;

			// CCDirector purgeDirector after reset
		case eApplicationExitBegin:
			break;

			// CCDirector Delete
		case eApplicationExitEnd:
			curl_global_cleanup();
			break;
	}
}



