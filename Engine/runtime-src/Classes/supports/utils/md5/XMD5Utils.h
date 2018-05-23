#ifndef __XMD5Utils_H__
#define __XMD5Utils_H__

enum ECheckState
{
	eCheckMFail = -1,					// check失败，不应该进入游戏，因为不知道版本号，这种情况多数于网络连接失败
	eBeforeCheck = 0,					// 未check，游戏初始化情况
	eCheckCanEnter = 1,					// 可以进入游戏，不需要更新
	eCheckNeedUpdateOnce = 2,			// 需要马上热更
	eCheckNeedUpdateTex = 3,			// 需要下载图片，不需要热更
};

class XMD5Utils
{
public:
	XMD5Utils();
	~XMD5Utils();
	const char* processBuffer(const void* pFileBuffer, unsigned int fileSize);
	bool		processFile(const char* filename);
	const char* processString(const char* szString);
	const char*	getDigestAsString(void);
	bool		isSame(const char* szInput);
	unsigned char	m_digest[16];
	char			m_string[33];
};

void processString(const char* szString, char pRes[33] );
const char* gb2u8(const char* gb2312);
void saveKey(const char * pKey, const char * pValue);
const char * loadKey(const char * pKey);
const char * getTimeFromSecond(unsigned int nSec);

#include "cocos2dx_extra.h"
#include "network/CCHTTPRequestDelegate.h"
NS_CC_EXTRA_BEGIN
class HTTPRequest;

// 因为VS2013出现过添加了新文件而编译不了的难以理解的bug，所以就这里写了

NS_CC_EXTRA_END

#include "cocostudio/ActionTimeline/CSLoader.h"
#include "assets-manager/Downloader.h"
#include "helpers/XLambda.h"

// 一加入新文件vs2013就编译不通过，直接写在这里了
class CLuaHttp
{
	class CLuaDelegate : public cocos2d::extra::HTTPRequestDelegate
	{
	protected:
		void requestError(const cocos2d::extension::Downloader::Error & err);
		void requestProgress(double totalToDownload, double nowDownload, const std::string & strUrl, const std::string & strId);
		void requestSuccess(const std::string & strUrl, const std::string & strPathAndName, const std::string & strId);

		void requestFinished(cocos2d::extra::HTTPRequest* request);
		void requestFailed(cocos2d::extra::HTTPRequest* request);
	};

protected:
	CLuaHttp();
	~CLuaHttp();

public:
	static CLuaHttp & Inst();

	// 因为析构时如果其它对象先析构了，会导致析构时报错，所以给个接口执行清理
	void Clear();
	
	void HttpRequest(const char * url, void * luaCallBackFun);

	void HttpRequest(const char * url, std::map<std::string, std::string> & m, void * luaCallBackFun);

	void DownRequest(string url, XLambda * successCB, XLambda * progressCB, XLambda * errorCB);

protected:
	static void requestError(const cocos2d::extension::Downloader::Error & err);
	static void requestProgress(double totalToDownload, double nowDownload, const std::string & strUrl, const std::string & strId);
	static void requestSuccess(const std::string & strUrl, const std::string & strPathAndName, const std::string & strId);

	struct SHttpMark
	{
		void * pFun;
		cocos2d::extra::HTTPRequestDelegate * pDelegate;
		cocos2d::extra::HTTPRequest * pRequest;
		std::string strUrl;
	};

	// 这里只有自己类可以调用
	struct SDownloadMark
	{
		SDownloadMark();

		~SDownloadMark();

		void InitData(XLambda * pSuccessCB, XLambda * pProgressCB, XLambda * pErrorCB, std::string strUrl);

		shared_ptr<cocos2d::extension::Downloader> GetDownloader();
		
		XLambda * pSuccessCB;
		XLambda * pProgressCB;
		XLambda * pErrorCB;
		shared_ptr<cocos2d::extension::Downloader> pDownloader;
		unsigned char *buffer;
		long bufSize;
		double totalSize;
		std::string strUrl;
	private:
		bool bInit;

		static const int DOWN_BUFFER_SIZE = 10 * 1024 * 1024;
	};
	typedef std::map< std::string, SHttpMark > CallMap;
	CallMap m_CallMap;

	typedef std::map< std::string, SDownloadMark > DownMap;
	DownMap m_DownMap;

private:
	void * GetFunByReq(cocos2d::extra::HTTPRequest* request);
	void DeleteRequest(cocos2d::extra::HTTPRequest* request); 
};




#endif
