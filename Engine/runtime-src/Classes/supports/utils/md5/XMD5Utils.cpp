#include "cocos2d.h"
#include "XMD5Utils.h"
#include "FileIO.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "zlib.h"
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
//extern "C"
//{
//#endif

#include "md5/md5.h"
    
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
//};
//#endif

XMD5Utils::XMD5Utils()
{
	memset(m_digest,0,16);
	memset(m_string,0,33);
}

XMD5Utils :: ~XMD5Utils()
{
    
}

const char* XMD5Utils::processString(const char* szString)
{
	md5_t context;
	md5_init(&context);
	md5_process(&context, szString, strlen(szString));
	md5_finish(&context,m_digest);
	memset(m_string,0,33);
	md5_sig_to_string(m_digest,m_string,32);
	return m_string;
}

const char* XMD5Utils::processBuffer(const void* pFileBuffer, unsigned int fileSize)
{
	md5_t context;
	md5_init(&context);
	md5_process(&context, pFileBuffer, fileSize);
	md5_finish(&context,m_digest);
	memset(m_string,0,33);
	md5_sig_to_string(m_digest,m_string,32);
	return m_string;
}

const char* XMD5Utils::getDigestAsString()
{
	return m_string;
}

bool XMD5Utils::processFile(const char* filename)
{
	unsigned int downloadedFileSize = 0;
	FILE* fp = fopen(filename, "rb");
	if (!fp)
	{
		return false;
	}
	int curpos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	downloadedFileSize = ftell(fp);
	fseek(fp, curpos, SEEK_SET);
	char* pFileContent = new char[downloadedFileSize];//(char*)CCFileUtils::getFileData(CCFileUtils::fullPathFromRelativePath(fileName), "rb", &size);
	fread(pFileContent, sizeof(char), downloadedFileSize, fp);
	fclose(fp);

	processBuffer(pFileContent, downloadedFileSize);
	delete[] pFileContent;
	return true;
}

bool XMD5Utils::isSame(const char* szInput)
{
	return strcmp(m_string, szInput) == 0;
}

void processString(const char* szString, char pRes[33])
{
	unsigned char	m_digest[16];
	memset(m_digest, 0, 16);
	memset(pRes, 0, 33);

	md5_t context;
	md5_init(&context);
	md5_process(&context, szString, strlen(szString));
	md5_finish(&context, m_digest);
	md5_sig_to_string(m_digest, pRes, 32);
}

#ifndef __GB23122Utf8_H_  
#define __GB23122Utf8_H_  

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
const char* gb2u8(const char* gb2312)
{
	int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
#endif  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include <dlfcn.h>  

void(*ucnv_convert)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*) = 0;

bool openIcuuc()
{
	void* libFile = dlopen("/system/lib/libicuuc.so", RTLD_LAZY);
	if (libFile)
	{
		ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, "ucnv_convert_3_8");

		int index = 0;
		char fun_name[64];
		while (ucnv_convert == NULL)
		{
			sprintf(fun_name, "ucnv_convert_4%d", index++);
			ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, fun_name);
			if (ucnv_convert)
				return true;
			if (++index > 11)
				break;
		}
		dlclose(libFile);
	}
	return false;
}
const char* gb2u8(const char * gb2312)
{
	if (ucnv_convert == NULL)
	{
		openIcuuc();
	}
	if (ucnv_convert)
	{
		int err_code = 0;
		int len = strlen(gb2312);
		char* str = new char[len * 2 + 10];
		memset(str, 0, len * 2 + 10);
		ucnv_convert("utf-8", "gb2312", str, len * 2 + 10, gb2312, len, &err_code);
		if (err_code == 0)
		{
			return str;
		}
	}
	char test[256] = "gb23122utf8 error";
	char* str = new char[30];
	strcpy(str, test);
	return str;
}
#endif  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
const char* gb2u8(const char * gb2312)
{
	return gb2312;
}

#endif  

void saveKey(const char * pKey, const char * pValue)
{
	cocos2d::CNewLoader::Inst().saveKey(pKey, pValue);
}

const char * loadKey(const char * pKey)
{
	return cocos2d::CNewLoader::Inst().loadKey(pKey);
}

const char * getTimeFromSecond(unsigned int nSec)
{
	static char str[64] = { 0 };
	time_t timep = nSec;
	sprintf(str, "%s", asctime(gmtime(&timep)));
	return str;
}

#endif //__GB23122Utf8_H_  

#include "network/CCHTTPRequest.h"
#include "helpers/XLambda.h"
#include "network/ClientSocketProxy.h"
#include "network/net_packet.h"

CLuaHttp::CLuaHttp()
{

}

CLuaHttp::~CLuaHttp()
{

}

CLuaHttp & CLuaHttp::Inst()
{
	static CLuaHttp inst;
	return inst;
}

void CLuaHttp::Clear()
{
	m_CallMap.clear();
	m_DownMap.clear();
}

void CLuaHttp::HttpRequest(const char * url, void * luaCallBackFun)
{
	// 想同URL只会执行一次
	CallMap::iterator it = m_CallMap.find(url);
	if (it != m_CallMap.end())
	{
		return;	// 会报错，所以只能这么做
		//it->second.pRequest->cancel();
		//delete it->second.pDelegate;
		//m_CallMap.erase(it);
	}

	CLuaDelegate * pDelegate = new CLuaDelegate;
	cocos2d::extra::HTTPRequest * request = cocos2d::extra::HTTPRequest::createWithUrl(pDelegate, url);
	SHttpMark& mark = m_CallMap[url];
	mark.strUrl = url;
	request->setRequestUrl(mark.strUrl.c_str());
	mark.pDelegate = pDelegate;
	mark.pFun = luaCallBackFun;
	request->start();
}

void CLuaHttp::HttpRequest(const char * url, std::map<std::string, std::string> & m, void * luaCallBackFun)
{
	CallMap::iterator it = m_CallMap.find(url);
	if (it != m_CallMap.end())
	{
		return; // 会报错，所以只能这么做
		//it->second.pRequest->cancel();
		//delete it->second.pDelegate;
		//m_CallMap.erase(it);
	}

	CLuaDelegate * pDelegate = new CLuaDelegate;
	cocos2d::extra::HTTPRequest * request = cocos2d::extra::HTTPRequest::createWithUrl(pDelegate, url);
	for (std::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); it++)
		request->addPOSTValue(it->first.c_str(), it->second.c_str());
	SHttpMark& mark = m_CallMap[url];
	mark.strUrl = url;
	request->setRequestUrl(mark.strUrl.c_str());
	mark.pDelegate = pDelegate;
	mark.pFun = luaCallBackFun;
	request->start();
}

void CLuaHttp::DownRequest(string url, XLambda * successCB, XLambda * progressCB, XLambda * errorCB)
{
	std::string strUrl = url;
	DownMap::iterator it = m_DownMap.find(strUrl);
	if (it != m_DownMap.end())
		return;

	XLambda * pSuccessCB = successCB;
	XLambda * pProgressCB = progressCB;
	XLambda * pErrorCB = errorCB;

	SDownloadMark & downMark = m_DownMap[strUrl];
	downMark.InitData(pSuccessCB, pProgressCB, pErrorCB, strUrl);
	shared_ptr<cocos2d::extension::Downloader> pDowner = downMark.GetDownloader();
	pDowner->setSuccessCallback(&CLuaHttp::requestSuccess);
	pDowner->setErrorCallback(&CLuaHttp::requestError);
	pDowner->setProgressCallback(&CLuaHttp::requestProgress);
	pDowner->downloadToBufferAsync(strUrl, downMark.buffer, downMark.bufSize, url.c_str());
}

void CLuaHttp::requestError(const cocos2d::extension::Downloader::Error & err)
{
	CLuaHttp & http = CLuaHttp::Inst(); 

	DownMap::iterator it = http.m_DownMap.find(err.customId);
	if (it == http.m_DownMap.end())
		return;

	XLambda * pLam = it->second.pErrorCB;
	if (pLam)
	{
		pLam->begin();

		pLam->pushString(err.url.c_str());
		pLam->pushInt(int(err.code));
		pLam->pushString(err.message.c_str());
		pLam->invoke();
	}

	http.m_DownMap.erase(it);
}

void CLuaHttp::requestProgress(double totalToDownload, double nowDownload, const std::string & strUrl, const std::string & strId)
{
	CLuaHttp & http = CLuaHttp::Inst();

	DownMap::iterator it = http.m_DownMap.find(strUrl);
	if (it == http.m_DownMap.end())
		return;

	it->second.totalSize = totalToDownload;

	XLambda * pLam = it->second.pProgressCB;
	if (pLam)
	{
		pLam->begin();

		pLam->pushString(strUrl.c_str());
		pLam->pushFloat(totalToDownload);
		pLam->pushFloat(nowDownload);
		pLam->invoke();
	}

}

void CLuaHttp::requestSuccess(const std::string & strUrl, const std::string & strPathAndName, const std::string & strId)
{
	CLuaHttp & http = CLuaHttp::Inst();

	DownMap::iterator it = http.m_DownMap.find(strUrl);
	if (it == http.m_DownMap.end())
		return;

	XLambda * pLam = it->second.pSuccessCB;
	if (pLam)
	{

		NetPacket * pack = NetPacket::create();
		
		pLam->begin();
		pLam->pushString(strUrl.c_str());
		pack->writeBuf(it->second.buffer, it->second.totalSize);
		pack->setPosition(0);
		pLam->pushObject(pack, "NetPacket");
		pLam->invoke();
	}

	http.m_DownMap.erase(it);
}

void * CLuaHttp::GetFunByReq(cocos2d::extra::HTTPRequest* request)
{
	if (!request)
		return 0;
	std::string strUrl = request->getRequestUrl();
	CallMap::iterator it = m_CallMap.find(strUrl);
	if (it != m_CallMap.end())
		return (it->second).pFun;
	return 0;
}

void CLuaHttp::DeleteRequest(cocos2d::extra::HTTPRequest* request)
{
	if (!request)
		return;
	std::string strUrl = request->getRequestUrl();
	CallMap::iterator it = m_CallMap.find(strUrl);
	if (it != m_CallMap.end())
	{
		request->cancel();
		delete it->second.pDelegate;
		m_CallMap.erase(it);
	}
}

void CLuaHttp::CLuaDelegate::requestFinished(cocos2d::extra::HTTPRequest* request)
{
	int state = request->getState();
	if (state == kCCHTTPRequestStateCompleted)
	{
		// 通知回调
		void * pFun = CLuaHttp::Inst().GetFunByReq(request);
		if (pFun)
		{			
			XLambda * pLam = (XLambda *)(pFun);
			
			NetPacket * pack = NetPacket::create();
			pLam->begin();
			void * pBuff = request->getResponseData();
			pack->writeBuf(pBuff, request->getResponseDataLength());
			pack->setPosition(0);
			free(pBuff);
			pLam->pushObject(pack, "NetPacket");
			pLam->invoke();
			pLam->release();

		}
	}

	// 然后删除记录
	CLuaHttp::Inst().DeleteRequest(request);
}

void CLuaHttp::CLuaDelegate::requestFailed(cocos2d::extra::HTTPRequest* request)
{
	void * pFun = CLuaHttp::Inst().GetFunByReq(request);
	if (pFun)
	{
		XLambda * pLam = (XLambda *)(pFun);
		pLam->begin();
		pLam->invoke();
		pLam->release();
	}

	CLuaHttp::Inst().DeleteRequest(request);
}

CLuaHttp::SDownloadMark::SDownloadMark()
	: pSuccessCB(0)
	, pProgressCB(0)
	, pErrorCB(0)
	, buffer(0)
	, bufSize(0)
	, bInit(false)
{
}

CLuaHttp::SDownloadMark::~SDownloadMark()
{
	if (pSuccessCB)
	{
		pSuccessCB->release();
		pSuccessCB = 0;
	}
	if (pProgressCB)
	{
		pProgressCB->release();
		pProgressCB = 0;
	}
	if (pErrorCB)
	{ 
		pErrorCB->release();
		pErrorCB = 0;
	}
	if (buffer)
	{
		free(buffer);
		buffer = 0;
	}
	bufSize = 0;
}

void CLuaHttp::SDownloadMark::InitData(XLambda * pSuccessCB, XLambda * pProgressCB, XLambda * pErrorCB, std::string strUrl)
{
	if (bInit)
		return;
	bInit = true;
	this->pDownloader = pDownloader;
	this->pSuccessCB = pSuccessCB;
	if (this->pSuccessCB)
		this->pSuccessCB->retain();

	this->pProgressCB = pProgressCB;
	if (this->pProgressCB)
		this->pProgressCB->retain();

	this->pErrorCB = pErrorCB;
	if (this->pErrorCB)
		this->pErrorCB->retain();

	this->strUrl = strUrl;

	this->GetDownloader();

	this->buffer = (unsigned char *)malloc(DOWN_BUFFER_SIZE);

	this->bufSize = DOWN_BUFFER_SIZE;
}

shared_ptr<cocos2d::extension::Downloader> CLuaHttp::SDownloadMark::GetDownloader()
{
	if (!pDownloader)
		this->pDownloader = shared_ptr<cocos2d::extension::Downloader> (new cocos2d::extension::Downloader);
	return pDownloader->shared_from_this();
}
