#include "XDownloaderUnit.h"
#include "XCommon.h"

#define CCDLOG cocos2d::log

XDownloadUnit::XDownloadUnit()
	: m_uPriority(0),
	  m_nRetryCount(0),				
	  m_bResumDownload(false),
	  m_errorcode(0),
	  m_bProgress(false),
	  m_localFileSize(0)
{

}


XDownloadUnit::~XDownloadUnit()
{

}

XDownloaderCallbackObject::XDownloaderCallbackObject(const std::string& customID) :
	m_strCustomID(customID),
	m_onError(nullptr),
	m_onProgress(nullptr),
	m_onSuccess(nullptr)
{

}

XDownloaderCallbackObject::XDownloaderCallbackObject()
{

}

XDownloaderCallbackObject::~XDownloaderCallbackObject()
{

}

XDownloaderCallbackObject* XDownloaderCallbackObject::create(const std::string& customID)
{
	XDownloaderCallbackObject* pkObject = new XDownloaderCallbackObject();
	pkObject->setCustomID(customID);
	pkObject->autorelease();
	return pkObject;
}

XDownloaderCallbackGroup::XDownloaderCallbackGroup(const char* szFile, const char* url, unsigned char p) :
	m_strLocalFilePath(szFile),
	m_strURL(url)
{

}

XDownloaderCallbackGroup::~XDownloaderCallbackGroup()
{
}

XDownloaderCallbackGroup* XDownloaderCallbackGroup::create(const char* szFile, const char* url, unsigned char p)
{
	XDownloaderCallbackGroup* pkObject = new XDownloaderCallbackGroup(szFile, url, p);
	return pkObject;
}

void XDownloaderCallbackGroup::pushCallbackObject(XDownloaderCallbackObject* pkObject)
{
	pkObject->retain();
	m_callbackObjectList.push_back(pkObject);
}

void XDownloaderCallbackGroup::onDownload()
{
	CCDLOG("XDownloaderUnit::onDownload begin %s", m_strLocalFilePath.c_str());
	//一个个通知下去
	for (std::list<XDownloaderCallbackObject*>::iterator iter = m_callbackObjectList.begin();
		iter != m_callbackObjectList.end();
		iter++)
	{
		XDownloaderCallbackObject* data = *iter;
		//调用一个队列
		const XDownloaderCallbackObject::SuccessCallback& successCallback = data->getSuccessCallback();
		if (successCallback != nullptr)
		{
			successCallback(m_strLocalFilePath, m_strURL, data->getCustomID());
		}
		data->release();
	}
	m_callbackObjectList.clear();
	//做完了！
	CCDLOG("XDownloaderUnit::onDownload end %s", m_strLocalFilePath.c_str());
}

void XDownloaderCallbackGroup::onFailed(unsigned int stage, unsigned int curlCode, unsigned int curlCode2)
{
//	CCDLOG("XDownloaderUnit::onFailed begin %s", m_strLocalFilePath.c_str());
	//一个个通知下去
	for (auto iter = m_callbackObjectList.begin();
			  iter != m_callbackObjectList.end();
			  iter++)
	{
		XDownloaderCallbackObject* data = *iter;
		//调用一个队列
		const XDownloaderCallbackObject::ErrorCallback& errorCallback = data->getErrorCallback();
		if (errorCallback != nullptr)
		{
			errorCallback(stage, curlCode, curlCode2, data->getCustomID());
		}
		data->release();
	}
	m_callbackObjectList.clear();
	//做完了！
//	CCDLOG("XDownloaderUnit::onFailed end %s", m_strLocalFilePath.c_str());
}

void XDownloaderCallbackGroup::onCancel()
{
//	CCDLOG("XDownloaderUnit::onCancel begin %s", m_strLocalFilePath.c_str());
	//一个个通知下去
	for (std::list<XDownloaderCallbackObject*>::iterator iter = m_callbackObjectList.begin();
		iter != m_callbackObjectList.end();
		iter++)
	{
		XDownloaderCallbackObject* data = *iter;
		/*
		//调用一个队列
		const XDownloaderCallbackObject::ErrorCallback& errorCallback = data->getErrorCallback();
		if (errorCallback != nullptr)
		{
			errorCallback(int(XDownloaderErrorCode::CANCELED),0,0,data->getCustomID());
		}
		*/
		//delete data;
		data->release();
	}
	m_callbackObjectList.clear();
	//做完了！
//	CCDLOG("XDownloaderUnit::onCancel end %s", m_strLocalFilePath.c_str());
}

void XDownloaderCallbackGroup::onProgress(double totalToDownload, double nowDownloaded, unsigned int localfileSize)
{
//	CCDLOG("XDownloaderUnit::onProgress begin %s", m_strLocalFilePath.c_str());
	//一个个通知下去
	for (std::list<XDownloaderCallbackObject*>::iterator iter = m_callbackObjectList.begin();
		iter != m_callbackObjectList.end();
		iter++)
	{
		XDownloaderCallbackObject* data = *iter;
		//调用一个队列
		const XDownloaderCallbackObject::ProgressCallback& progressCallback = data->getProgressCallback();
		if (progressCallback != nullptr)
		{
			progressCallback(totalToDownload, nowDownloaded, m_strURL, data->getCustomID(), localfileSize);
		}
	}
	//做完了！
//	CCDLOG("XDownloaderUnit::onProgress end %s", m_strLocalFilePath.c_str());
}


