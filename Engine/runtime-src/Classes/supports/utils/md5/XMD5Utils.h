#ifndef __XMD5Utils_H__
#define __XMD5Utils_H__

enum ECheckState
{
	eCheckMFail = -1,					// checkʧ�ܣ���Ӧ�ý�����Ϸ����Ϊ��֪���汾�ţ����������������������ʧ��
	eBeforeCheck = 0,					// δcheck����Ϸ��ʼ�����
	eCheckCanEnter = 1,					// ���Խ�����Ϸ������Ҫ����
	eCheckNeedUpdateOnce = 2,			// ��Ҫ�����ȸ�
	eCheckNeedUpdateTex = 3,			// ��Ҫ����ͼƬ������Ҫ�ȸ�
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

// ��ΪVS2013���ֹ���������ļ������벻�˵���������bug�����Ծ�����д��

NS_CC_EXTRA_END

#include "cocostudio/ActionTimeline/CSLoader.h"
#include "assets-manager/Downloader.h"
#include "helpers/XLambda.h"

// һ�������ļ�vs2013�ͱ��벻ͨ����ֱ��д��������
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

	// ��Ϊ����ʱ������������������ˣ��ᵼ������ʱ�������Ը����ӿ�ִ������
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

	// ����ֻ���Լ�����Ե���
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
