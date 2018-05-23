#pragma once
#ifndef _XAsyncLoader_H
#define _XAsyncLoader_H
#include "XCommon.h"
#include "XResource/XAsyncLoaderCallbacks.h"
#include <set>

USING_NS_CC;

class XAsyncLoaderManager;
typedef std::function<void(void)> XAsyncLoaderCancelCB;

class XAsyncLoaderErrorData : public Ref
{
public:
	XAsyncLoaderErrorData(int code0, int code1, int code2) : m_code0(code0), m_code1(code1), m_code2(code2)
	{

	}
	int m_code0;
	int m_code1;
	int m_code2;
	static XAsyncLoaderErrorData* create(int code0, int code1, int code2);
};

class XAsyncLoader : public std::enable_shared_from_this<XAsyncLoader>
{
	friend XAsyncLoaderManager;
protected:
	XAsyncLoader();
public:
	virtual ~XAsyncLoader();

	virtual void cancel();

	virtual void onAsyncLoad(const XAsyncLoaderRet* ret);

	void init(const std::string& filename, const std::string& customID, const std::string& key, unsigned char p);

	void clearCallback();

	void addCallback(XAsyncLoaderCallback* callback);

	void setCancelCallback(XAsyncLoaderCancelCB val) { m_cancelCallback = val; }

	unsigned int id() const { return m_nID; }

	virtual void removeCallback(XAsyncLoaderCallback* callback);

	bool isValid() const { return m_loadCallbacks.empty() == false; }

	const char* getLoaderKey() const { return m_loaderKey.c_str(); }

	bool getRegistered() const { return m_bRegistered; }

	//bool getMarkRemove() const { return m_bMarkRemove; }

	//void setMarkRemove(bool val) { m_bMarkRemove = val; }

	virtual void start(void* param) = 0;

	virtual void cleanup() {};

protected:

	void setRegistered(bool val) { m_bRegistered = val; }

	virtual void removeReference();

	virtual void onNobodyCares();

	
	unsigned int				m_nID;
	unsigned int				m_priority;
	std::string					m_strFilename;
	std::string					m_customID;
	std::string					m_loaderKey;
	XAsyncLoaderCallbackMap		m_loadCallbacks;
	XAsyncLoaderCancelCB		m_cancelCallback;
	bool						m_bLoopingEvents;
	bool						m_bRegistered;
	//bool						m_bMarkRemove;

};

typedef std::shared_ptr<XAsyncLoader>	XAsyncLoaderPtr;

typedef std::map<std::string, XAsyncLoaderPtr>	XAsyncLoaderPtrMap;

typedef std::unordered_map<unsigned int, XAsyncLoaderPtr>	XAsyncLoaderPtrIntMap;


#endif // !_XAsyncLoader_H