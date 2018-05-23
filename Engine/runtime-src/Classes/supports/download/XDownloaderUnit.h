#ifndef __XDownloaderUnit__
#define __XDownloaderUnit__
#include "cocos2d.h"
USING_NS_CC;

#define ERROR_CODE_SEP 10000

class XDownloadUnit
{
public:
	XDownloadUnit();
	~XDownloadUnit();

	void setPriority(unsigned char val) { m_uPriority = val; }
	unsigned char getPriority() const { return m_uPriority; }

	unsigned char getRetryCount() const { return m_nRetryCount; }
	void setRetryCount(unsigned char val) { m_nRetryCount = val; }

	const std::string& getLocalFilePath() const { return m_strLocalFilePath; }
	void setLocalFilePath(const std::string& val) { m_strLocalFilePath = val; }

	const std::string& getMD5String() const { return m_strMD5String; }
	void setMD5String(const std::string& val) { m_strMD5String = val; }

	const std::string& getURL() const { return m_strURL; }
	void setURL(const std::string& val) { m_strURL = val; }

	unsigned int getErrorcode() const { return m_errorcode; }
	void setErrorcode(unsigned short error, unsigned short extra) { m_errorcode = error * ERROR_CODE_SEP + extra; }

	bool getResumDownload() const { return m_bResumDownload; }
	void setResumDownload(bool val) { m_bResumDownload = val; }

	bool getProgress() const { return m_bProgress; }
	void setProgress(bool val) { m_bProgress = val; }

	unsigned int getRemoteFileSize() const { return m_remoteFileSize; }
	void setRemoteFileSize(unsigned int val) { m_remoteFileSize = val; }

	unsigned int getLocalFileSize() const { return m_localFileSize; }
	void setLocalFileSize(unsigned int val) { m_localFileSize = val; }

	static unsigned int mergeErrorcode(unsigned short error, unsigned short extra);

private:
	unsigned char									m_uPriority;				//优先度
	unsigned char									m_nRetryCount;				//重试次数
	unsigned int									m_errorcode;				//错误码
	unsigned int									m_remoteFileSize;			//远程文件size
	unsigned int									m_localFileSize;

	bool											m_bProgress;				//是否监听进度
	bool											m_bResumDownload;			//是否续传
	std::string										m_strLocalFilePath;			//本地目录
	std::string										m_strMD5String;				//MD5校验码
	std::string										m_strURL;					//下载地址
};

class XDownloaderCallbackObject : public Ref
{
protected:
	XDownloaderCallbackObject();
	XDownloaderCallbackObject(const std::string& customID);
public:
	// stage curl curl
	typedef std::function<void(unsigned int, unsigned int, unsigned int, const std::string &)> ErrorCallback;
	typedef std::function<void(double, double, const std::string &, const std::string &, unsigned int)> ProgressCallback;
	typedef std::function<void(const std::string &, const std::string &, const std::string &)> SuccessCallback;

	static XDownloaderCallbackObject* create(const std::string& customID);

	virtual ~XDownloaderCallbackObject();

	void setProgressCallback(const ProgressCallback &callback) { m_onProgress = callback; };

	void setSuccessCallback(const SuccessCallback &callback) { m_onSuccess = callback; };

	void setErrorCallback(const ErrorCallback &callback) { m_onError = callback; };

	ErrorCallback getErrorCallback() const { return m_onError; };

	ProgressCallback getProgressCallback() const { return m_onProgress; };

	SuccessCallback getSuccessCallback() const { return m_onSuccess; };

	const std::string& getCustomID() const { return m_strCustomID; }

	void setCustomID(const std::string& val) { m_strCustomID = val; }

private:
	ErrorCallback	 m_onError;

	ProgressCallback m_onProgress;

	SuccessCallback	 m_onSuccess;

	std::string		 m_strCustomID;

};

class XDownloaderCallbackGroup
{
protected:
	XDownloaderCallbackGroup(const char* szFile, const char* url, unsigned char p);
public:
	virtual ~XDownloaderCallbackGroup();

	static XDownloaderCallbackGroup* create(const char* szFile, const char* url, unsigned char p);

	void pushCallbackObject(XDownloaderCallbackObject* pkObject);

	void onDownload();

	void onFailed(unsigned int stage, unsigned int curlCode, unsigned int curlCode2);

	void onCancel();

	void onProgress(double totalToDownload, double nowDownloaded, unsigned int localfileSize);

	unsigned char									m_uPriority;
	std::string										m_strLocalFilePath;			//MD5校验码
	std::string										m_strURL;					//下载地址
	std::list<XDownloaderCallbackObject*>			m_callbackObjectList;		//回调对象列表
};
#endif
