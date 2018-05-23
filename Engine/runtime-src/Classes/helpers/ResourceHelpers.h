#ifndef __ResourceHelpers_H__
#define __ResourceHelpers_H__

#include <string>
#include "base/CCValue.h"
#include "supports/XResource/XAsyncLoaderCallbacks.h"
#include "cocos/studio_ext/XCSLoaderRet.h"

/*! \class  ResourceHelpers
*  \brief  资源管理器，主要面向脚本
*
*
*/
class XLambda;

class ResourceHelpers
{
public:
	static void init();

	/** \example test_Downloader.lua
	*/
	/** \example test_XSlotAnimateSprite.lua
	*/

	static void fini();

	/*!
	* \brief 读取动画依赖
	* \param const char * szFilename
	* \return bool
	*/
	static bool loadDependency(const char* szFilename);

	/*!
	* added by aXing on 2017-3-24
	* \brief 读取绝对路径的资源对照plist路径
	* \param const char * szFilename
	* \return bool
	*/
	static bool LoadResourceTab(const char* szFilename);

	/*!
	* added by aXing on 2017-3-24
	* \brief 读取动画依赖 替代原有的loadDependency
	* \param const char * szFilename
	* \return bool
	*/
	static bool loadAnimationTab(const char* szFilename);

	/*!
	* added by aXing on 2017-5-19
	* \brief 读取边玩边下载的MD5码表和下载版本路径
	* \param const char * szFilename
	* \return bool
	*/
	static bool loadMD5Tab(const char* szFilename);

	/*
	 读取plist等配置
	 */
	static bool loadConfigPack(const char * szConfigPack);

	/*!
	* \brief 清除Cache
	* \return void
	*/
	static void purgeCache();

	/*!
	* \brief 异步读取动画
	* \param XAsyncLoadOption* option
	* \return unsigned int 返回handler用来cancel
	\sa test_XSlotAnimateSprite.lua
	*/
	static  unsigned int loadAnimationAsync(XAsyncLoadOption* option, unsigned int handle);

	/*!
	* \brief 异步加载纹理
	* \param XAsyncLoadOption* option
	* \return unsigned int 返回handler用来cancel
	*/
	static  unsigned int loadTextureAsync(XAsyncLoadOption* option, unsigned int handle);

	/*!
	* \brief 下载
	* \param lua_State * L table 和三个Lua回调函输 
	* \return bool
	* \section download 参数
	参数1 = okFunction 成功下载函数<br/>
	参数2 = errorFunction 下载失败函数<br/>
	参数3 = progressFunction 下载/解压进度函数, </br>
	如果有多次调用监听同一个下载进度，只有第一次调用才会成功监听，<br/>
	其他的不会受到通知. 这个是因为Curl的参数在第一次调用时，下载监听已经被设置好了，后面无法改变，也没啥意义。<br/>
	{<br/>
	file = 下载的文件<br/>
	url  = 下载URL<br/>
	priority = 优先度(可选)<br/>
	retry = 重试(可选)<br/>
	md5 = 较验用的md5(可选)<br/>
	fileSize = 文件大小(可选)<br/>
	}<br/>
	\sa test_Downloader.lua
	*/
	static int loadWWW(cocos2d::ValueMap& pkMap, XLambda* okFunction, XLambda* errorFunction, XLambda* progressFunction, unsigned int handle);

	// 开启一个直接调用XDownload的方法
	// 会无视硬盘是否有文件，直接下载
//	static bool download(ValueMap& pkMap, XLambda* okFunction, XLambda* errorFunction, XLambda* progressFunction, unsigned int handle);

	/*!
	* \brief 取消异步加载
	* \param unsigned int handle 之前创建的Handle
	* \return void
	*/
	static void cancelLoadAsync(unsigned int handle);

	/*!
	* \brief 创建一个异步加载的Option
	* \param const char * filename 文件名
	* \param const char * customID 用户定制ID
	* \param unsigned char priority 优先度
	* \param XLambda* handle 脚本回调
	* \return XAsyncLoadOption* 异步加载option
	*/
	static XAsyncLoadOption* getAsyncLoadOption(const char* filename,
		const char* customID,
		unsigned char priority,
		XLambda* handle);

	/*!
	* \brief 
	* \param const char * filename
	* \param const char * customID
	* \param unsigned char priority
	* \param XLambda* luaFunction
	* \return unsigned int
	*/
	static unsigned int loadCSBTextureAsync(XAsyncLoadOption* option, unsigned int handle);

	static unsigned int unzipLoaderAsync(XAsyncLoadOption* option, unsigned int handle);

	static unsigned int loadGroupAsync(XAsyncLoadOption* option, unsigned int handle);

	static XCSLoadRet* loadCSB(const char* filename, bool bWithTimeline, bool bCache, XLambda* luaFunction);

	static void purgeCSBCache();

	static void cancelAllAsyncLoadScript();

	static void cancelAllAsyncLoad();

	static int decompressAsync(const char* filename, unsigned int progressThreshold, XLambda* finish, XLambda* progress);

	static void listenAsyncFinish(XLambda* finish);

	static void cancelDecompressAsync(const char* filename);

	/*!
	* \brief 读取csb依赖
	* \param const char * szFilename
	* \return bool
	*/
	static bool loadResourceConfig(const char* szFilename);
};

#endif /* defined(__CocoGUI__UISystem__) */
