#ifndef __XAsyncLoaderManager_H__
#define __XAsyncLoaderManager_H__

#include <cocos2d.h>
#include <string>
#include <list>
#include "XResource/XAsyncLoader.h"
#include "download/XDownloader.h"

USING_NS_CC;

/*! \class XAsyncLoaderManager
*  \brief 这个类是需要负责异步加载
*
*
*/

class XAsyncLoaderManager : public Ref
{
public:
	enum  XAsyncLoaderState
	{
		eReady,
		eLoaded
	};
	XAsyncLoaderManager();
	~XAsyncLoaderManager();
	static XAsyncLoaderManager*	sharedManager();
	static void					purgeSharedManager();

	/**
	@brief	   异步加载纹理
	@param 	   const std::string & filename 需要异步加载的文件名
	@param 	   const std::string & customID 自定义ID，当回调时作为参数返回给调用者
	@param 	   unsigned char priority 加载优先度
	@param 	   XAsyncLoaderCallback * callback	加载完毕后的回调指针
	@returns   XAsyncLoaderPtr	异步加载器(智能指针) or NULL 如果即时返回就NULL
	*/
	int loadTexture(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback);
	
	int loadAnimation(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback);

	int loadWWW(XDownloader::Options& options, const std::string& customID, XAsyncLoaderCallback* callback);

	int loadCSBDependency(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback);

	int loadGroup(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback);

	int unzip(const std::string& filename, const std::string& customID, unsigned char priority, XAsyncLoaderCallback* callback);

	//void removeLoader(const std::string& loadername);

	//void loaderGCTick(float dt);

	//void scheduleLoaderGC();

	void cancelAll();

	XAsyncLoaderPtr findLoader(const std::string& filename);

	void removeLoader(const std::string& filename);

protected:
	XAsyncLoaderPtrMap							m_Loaders;
	FileUtils									*_fileUtils;
	TextureCache								*_textureCache;
	bool										m_bNeedCollect;
};

#endif