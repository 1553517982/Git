#pragma once
#ifndef _XAsyncLoaderCallback_H
#define _XAsyncLoaderCallback_H

#include "XCommon.h"

USING_NS_CC;

enum XAsyncLoaderCode
{
	eOK,
	eProgress,
	eFileLoadError,
	eNotFound,
	eCancel,
	eDownloadError,
	eUnzipError,
	eQuit
};
//totalToDownload,nowDownloaded, localfileSize
struct XDownloadProgress
{
	int totalToDownload;
	int nowDownloaded;
	int localfileSize;
};

class XAsyncLoaderRet
{
public:
	XAsyncLoaderRet(int ret, Ref* _data, const std::string& _ID) :
		m_nRet(ret),
		m_pkData(_data),
		m_customID(_ID)
	{

	}
	int ret() const { return m_nRet; }
	Ref* data() const { return m_pkData; }
	const std::string& customID() const { return m_customID; }
	const std::string& getMessage() const { return m_strMessage; }
	void setMessage(const std::string& val) { m_strMessage = val; }
private:
	int			m_nRet;
	std::string m_customID;
	std::string m_strMessage;

	Ref*		m_pkData;
};


class XAsyncLoader;
class XAsyncLoaderCallback;


typedef std::function<void(const XAsyncLoaderRet*)> XAsyncLoaderFunction;
typedef std::set<XAsyncLoaderCallback*>	XAsyncLoaderCallbackMap;

class XAsyncLoaderCallback : public Ref
{
	friend XAsyncLoader;
protected:
	XAsyncLoaderCallback();
	~XAsyncLoaderCallback();
public:
	//static XAsyncLoaderCallback* create();
	virtual void cancel();
	bool isIdle() const { return m_callback == nullptr; }
	void init(XAsyncLoaderFunction callback);
	virtual void reset();

	static XAsyncLoaderCallback* create();
	virtual void onAsyncLoad(const XAsyncLoaderRet* ret);
	void* getUserdata() const { return m_pkUserdata; }
	void setUserdata(void* val) { m_pkUserdata = val; }

protected:
	void setOwner(std::shared_ptr<XAsyncLoader> owner);
	std::weak_ptr<XAsyncLoader>			m_owner;
	XAsyncLoaderFunction				m_callback;
	void*								m_pkUserdata;

};

class XAsyncLoadOption
{
public:
	XAsyncLoadOption();
	virtual ~XAsyncLoadOption();

	virtual void init(const char* filename, const char* customID, unsigned char priority, XAsyncLoaderFunction callback);

	std::string				m_filename;
	std::string				m_customID;
	unsigned char			m_priority;
	XAsyncLoaderFunction	m_callback;
#ifdef _DEBUG
public:
	std::string				m_strTraceback;
#endif
};

#endif