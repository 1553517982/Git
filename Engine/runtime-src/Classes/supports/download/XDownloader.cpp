#include "XDownloader.h"
#include "XCommon.h"
#include "tinyxml2/tinyxml2.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdio>
#include <cerrno>
#include <algorithm> 
//#include "utils/unzip/XUnzipUtils.h"
#include "utils/md5/XMD5Utils.h"
#include "utils/XSystemUtils.h"


#define LOW_SPEED_LIMIT				1L
#define LOW_SPEED_TIME				5L
#define MAX_REDIRS					2
#define DEFAULT_TIMEOUT				5
#define HTTP_CODE_SUPPORT_RESUME    206
#define HTTP_CODE_OK				200
#define TEMP_EXT            ".temp"

#define CCDLOG XLOG

XDownloader* XDownloader::m_s_XDownloader = NULL;

static bool s_bDelete = false;

size_t fileWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

// Compare to batchDownloadProgressFunc, this only handles progress information notification
int downloadProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	XDownloadUnit* pkUnit = (XDownloadUnit*)ptr;
	XDownloader* pkDownloader = XDownloader::getInstance();
	if (pkDownloader->getNeedQuit())
	{
		return 1;
	}
	const std::string& filename = pkUnit->getLocalFilePath();
	unsigned int fileSize = pkUnit->getLocalFileSize();
	pkDownloader->onDownloadProgressInCocosThread(filename, fileSize, totalToDownload, nowDownloaded);
	return 0;
}

static bool cancelByName(const std::string& filename, XDownloaderCallbackGroupMap* item_map, XDownloadUnitList* items_list)
{
	bool bFound = false;
	for (XDownloadUnitList::iterator iter = items_list->begin();
		iter != items_list->end();
		iter++)
	{
		//找到需要取消的那个下载
		if ((*iter)->getLocalFilePath() == filename)
		{
			//从回调字典中找到回调对象
			XDownloaderCallbackGroupMap::iterator cb_iter = item_map->find(filename);
			if (cb_iter != item_map->end())
			{
				//通知调用者，自己被取消掉了
				cb_iter->second->onCancel();
				delete cb_iter->second;
				item_map->erase(cb_iter);
			}
			//删除等待
			delete *iter;
			items_list->erase(iter);
			bFound = true;
			break;
		}
	}
	return bFound;
}

static bool cancelByPriority(unsigned char p, XDownloaderCallbackGroupMap* item_map, XDownloadUnitList* items_list)
{
	for (XDownloadUnitList::iterator iter = items_list->begin();
		iter != items_list->end();
		/*pass*/)
	{
		if ((*iter)->getPriority() < p)
		{
			const std::string& key = (*iter)->getLocalFilePath();
			//找到需要取消的那个下载
			XDownloaderCallbackGroupMap::iterator cb_iter = item_map->find(key);
			if (cb_iter != item_map->end())
			{
				//取消下载
				cb_iter->second->onCancel();
				delete cb_iter->second;
				item_map->erase(cb_iter);

			}
			//删除等待
			delete *iter;
			items_list->erase(iter++);
			return true;
		}
		else
		{
			++iter;
		}
	}
	return false;
}

XDownloader::Options::Options(const std::string& _strFilename, const std::string& _strURL,
							  XDownloaderCallbackObject* _pkCallbackObject,
							  unsigned char _ucPriority, unsigned char _retryCount, bool _replace) :
							  pkCallbackObject(_pkCallbackObject),
							  strFilename(_strFilename),
							  strURL(_strURL),
							  strMD5(""),
							  bResumeSupport(false),
							  ucPriority(_ucPriority),
							  ucRetryCount(_retryCount),
							  uRemotefileSize(0),
							  bReplace(_replace)
{
	CC_SAFE_RETAIN(pkCallbackObject);
}

XDownloader::Options::~Options()
{
	CC_SAFE_RELEASE(pkCallbackObject);
}

void XDownloader::Options::setCallbackObject(XDownloaderCallbackObject* _pkCallbackObject)
{
	CC_SAFE_RELEASE(pkCallbackObject);
	pkCallbackObject = _pkCallbackObject;
	CC_SAFE_RETAIN(pkCallbackObject);

}

XDownloader::Options* XDownloader::Options::clone()
{
	XDownloader::Options* newOption = new XDownloader::Options(strFilename, strURL, pkCallbackObject, ucPriority, ucRetryCount, bReplace);
	newOption->strMD5 = strMD5;
	newOption->bResumeSupport = bResumeSupport;
	newOption->uRemotefileSize = uRemotefileSize;
	newOption->bReplace = bReplace;
	return newOption;
}

XDownloader::XDownloader() :
m_download_waiting_list(NULL),
m_download_finish_list(NULL),
m_download_callback_groups(NULL),
m_asyncRefCount(0),
m_retryRefCount(0),
m_needQuit(false)//,
//m_bDownloadInit(false)
{

}

XDownloader::~XDownloader()
{

}

XDownloader* XDownloader::getInstance()
{
	if (!m_s_XDownloader)
		m_s_XDownloader = new (std::nothrow) XDownloader();
#ifdef _DEBUG
	if (s_bDelete)
	{
		CCASSERT(false,"");
	}
#endif // _DEBUG

	return m_s_XDownloader;
}

void XDownloader::destroyInstance()
{
	if (m_s_XDownloader)
	{
		m_s_XDownloader->waitForQuit();
		delete m_s_XDownloader;
		m_s_XDownloader = NULL;
#ifdef _DEBUG
		s_bDelete = true;
#endif
	}
}

void XDownloader::waitForQuit()
{
	if (m_download_callback_groups)
	{
		cancelCallbacks();
		// notify sub thread to quick
		clearWaiting();
		m_needQuit = true;

		//std::list<XThread*>::iterator iter = m_downloadThreads.begin();
		//for (/*pass*/; iter != m_downloadThreads.end(); iter++)
		//{
		//	m_sleepCondition.notify_one();
		//}
		
		/*
		for (std::list<XThread*>::iterator iter = m_downloadThreads.begin(); iter != m_downloadThreads.end(); iter++)
		{
			(*iter)->requestTerminate();
		}*/
		{
			std::lock_guard<std::mutex> lk(m_sleepMutex);
			m_sleepCondition.notify_all();
		} // mutex is unlocked automatically as the lock_guard goes out of scope

		for (std::list<std::thread>::iterator iter = m_downloadThreads.begin(); iter != m_downloadThreads.end(); iter++)
		{
			(*iter).join();
		}
		m_downloadThreads.clear();
		clearFinish();

		delete m_download_waiting_list;
		delete m_download_retry_list;
		delete m_download_finish_list;
		delete m_download_callback_groups;
		
	}
}

void XDownloader::clearWaiting()
{
	m_waitingMutex.lock();
	for (XDownloadUnitList::iterator iter = m_download_waiting_list->begin();
		iter != m_download_waiting_list->end();
		iter++)
	{
		delete *iter;
	}
	m_download_waiting_list->clear();
	m_waitingMutex.unlock();

	for (XDownloadUnitList::iterator iter = m_download_retry_list->begin();
		iter != m_download_retry_list->end();
		iter++)
	{
		delete *iter;
	}
	m_download_retry_list->clear();
}

void XDownloader::cancelCallbacks()
{
	for (XDownloaderCallbackGroupMap::iterator iter = m_download_callback_groups->begin();
		iter != m_download_callback_groups->end();
		iter++)
	{
		iter->second->onCancel();
		delete iter->second;
	}
}

void XDownloader::clearCallbacks()
{
	if (m_download_callback_groups == nullptr)
	{
		return;
	}
	for (XDownloaderCallbackGroupMap::iterator iter = m_download_callback_groups->begin();
		iter != m_download_callback_groups->end();
		iter++)
	{
		delete iter->second;
	}
}

void XDownloader::clearAll()
{
	if (m_download_callback_groups == nullptr)
	{
		return;
	}
	clearCallbacks();
	clearWaiting();
	clearFinish();
}

void XDownloader::cancelAll()
{
	cancelCallbacks();
	clearWaiting();
	clearFinish();
}

void XDownloader::clearFinish()
{
	if (m_download_callback_groups == nullptr)
	{
		return;
	}
	m_finishMutex.lock();
	for (XDownloadUnitList::iterator iter = m_download_finish_list->begin();
		iter != m_download_finish_list->end();
		iter++)
	{
		delete *iter;
	}
	m_download_finish_list->clear();
	m_finishMutex.unlock();
}

int XDownloader::parseFileList(const std::string& fileList)
{
	int ret = InitRetCode::OK;
	FileUtils* _fileUtils = FileUtils::getInstance();

	tinyxml2::XMLElement* curNode = nullptr;
	do
	{
		tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();

		std::string xmlPath = FileUtils::getInstance()->fullPathForFilename(fileList);
		std::string xmlBuffer = FileUtils::getInstance()->getStringFromFile(xmlPath);

		if (xmlBuffer.empty())
		{
			XLOG("can not read xml file");
			ret = InitRetCode::CANNOT_READ_XML;
            delete xmlDoc;
			break;
		}
		xmlDoc->Parse(xmlBuffer.c_str(), xmlBuffer.size());

		// get root node
		const tinyxml2::XMLElement* rootNode = xmlDoc->RootElement();
		if (nullptr == rootNode)
		{
			XLOG("read root node error");
			ret = InitRetCode::CANNOT_READ_ROOT;
			break;
		}
		// find the node
		const tinyxml2::XMLElement* curNode = rootNode->FirstChildElement();
		while (nullptr != curNode)
		{
			const char* nodeName = curNode->Value();
			if (strcmp(nodeName, "dir") == 0)
			{
				const char* szValue = (const char*)(curNode->FirstChild()->Value());
				if (szValue)
				{
					std::string path = _fileUtils->getWritablePath() + szValue;
					if (!_fileUtils->createDirectory(path.c_str()))
					{
						ret = InitRetCode::CANNOT_CREATE_DIR;
						break;
					}
				}
			}
			else if (strcmp(nodeName, "file") == 0)
			{
				const char* ret = (const char*)(curNode->FirstChild()->Value());
				const char* md5 = (const char*)(curNode->Attribute("md5"));
				if (md5)
				{
					m_mapDownloadMD5.insert(std::make_pair(ret, md5));
				}
				else
				{
					CCDLOG("XDownloader::parseFileList md5 %s == NULL", ret);
				}
			}

			curNode = curNode->NextSiblingElement();
		}

		delete xmlDoc;

	} while (0);

	return ret;
}

//初始化
//@params
//  fileList = 文件名 : md5配对
//  host = 默认下载地址host
//  是否创建下载保存地址
int XDownloader::initialize(const std::string& fileList, const std::string& defaultHost, const std::string& storagePath)
{
	int ret = InitRetCode::OK;

	if (storagePath.empty())
	{
		m_defaultStoragePath = FileUtils::getInstance()->getWritablePath();
	}
	else
	{
		m_defaultStoragePath = storagePath;
	}

	m_defaultHost = defaultHost;

	FileUtils* _fileUtils = FileUtils::getInstance();

	std::string path = m_defaultStoragePath;
	if (!_fileUtils->createDirectory(path))
	{
		return InitRetCode::CANNOT_CREATE_DIR;
	}

	do
	{
		ret = parseFileList(fileList);
	} while (0);
	
	m_bDownloadInit = true;
	return ret;
}

bool XDownloader::_downloadFile(XDownloader::Options& options)
{
	//if (!m_bDownloadInit)
	//	return false;

	bool bProgress = false;

	if (m_download_waiting_list == nullptr)
	{
		m_download_waiting_list    = new std::list<XDownloadUnit*>();
		m_download_finish_list	   = new std::list<XDownloadUnit*>();
		m_download_retry_list	   = new std::list<XDownloadUnit*>();

		m_download_callback_groups = new std::map<std::string, XDownloaderCallbackGroup*>();
		

		for (int i = 0; i < MAX_DOWNLOAD_THREAD; i++)
		{
			//XThread* _loadingThread = XThread::create(std::bind(&XDownloader::_downloadFileFromList, this, std::placeholders::_1));
			auto func = std::bind(&XDownloader::_downloadFileFromList, this);
			m_downloadThreads.push_back(std::thread(func));
		}

		m_needQuit = false;
	}

	//Shan Lu 2017-04-20 在下载之前检查创建目录 Begin
	//相对路径
	const std::string& relfile = options.strFilename;
	//绝对路径
	std::string targetFile = m_defaultStoragePath + options.strFilename;
	size_t index = targetFile.rfind('/');
	if (index != std::string::npos)
	{
		std::string storagePath = targetFile.substr(0, index + 1);
		FileUtils::getInstance()->createDirectory(storagePath);
	}
	//Shan Lu 2017-04-20 在下载之前检查创建目录 End

	auto callbackObject = options.getCallbackObject();
	if (callbackObject)
	{
		//如果已经有了下载，监听跳过下载，合并回调
		XDownloaderCallbackGroup* pkGroup = NULL;
		XDownloaderCallbackGroupMap::iterator cb_iter = m_download_callback_groups->find(relfile);
		if (cb_iter != m_download_callback_groups->end())
		{
			pkGroup = cb_iter->second;
			pkGroup->pushCallbackObject(callbackObject);
			return true;
		}
		else
		{
			//创建下载
			pkGroup = XDownloaderCallbackGroup::create(relfile.c_str(), options.strURL.c_str(), options.ucPriority);
			m_download_callback_groups->insert(std::make_pair(relfile, pkGroup));
			pkGroup->pushCallbackObject(callbackObject);
			//是否需要通知下载进度
			bProgress = callbackObject->getProgressCallback() != nullptr;
		}
	}

	XDownloadUnit* pkUnit = new (std::nothrow) XDownloadUnit();
	pkUnit->setLocalFilePath(relfile);
	pkUnit->setURL(options.strURL);
	pkUnit->setMD5String(options.strMD5);
	pkUnit->setPriority(options.ucPriority);
	pkUnit->setRetryCount(options.ucRetryCount);
	pkUnit->setResumDownload(options.bResumeSupport);
	pkUnit->setRemoteFileSize(options.uRemotefileSize);
	pkUnit->setProgress(bProgress);

	// add async struct into queue
	m_waitingMutex.lock();
	m_download_waiting_list->push_back(pkUnit);
	m_download_waiting_list->sort([](const XDownloadUnit* a, const XDownloadUnit* b){
		return a->getPriority() > b->getPriority();
	});
	m_waitingMutex.unlock();


	if (0 == m_asyncRefCount)
	{
		Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(XDownloader::downloadTick), this, 0, false);
	}
	++m_asyncRefCount;
	m_sleepCondition.notify_one();

	return true;
}

void XDownloader::_downloadFileFromList(void)
{
	XDownloadUnit *downloadUnit = nullptr;

	while (m_needQuit == false)
	{
		XDownloadUnitList *pWaitingList = m_download_waiting_list;
		m_waitingMutex.lock();
		if (pWaitingList->empty())
		{
			m_waitingMutex.unlock();
			std::unique_lock<std::mutex> lk(m_sleepMutex);
			m_sleepCondition.wait(lk);
			continue;
		}
		else
		{
			downloadUnit = pWaitingList->front();
			pWaitingList->pop_front();
			m_waitingMutex.unlock();
		}

		_downloadFileInThread(downloadUnit);

		// put the image info into the queue
		m_finishMutex.lock();
		m_download_finish_list->push_back(downloadUnit);
		m_finishMutex.unlock();
	}
}

bool XDownloader::getContentSize(const std::string &srcUrl, double& contentSize) const
{

	// Test server download resuming support with the first unit
	bool _supportResuming = false;
	CURL *header = curl_easy_init();
	// Make a resume request
	
	double contentLength = -1;

	curl_easy_setopt(header, CURLOPT_URL, srcUrl.c_str());
	curl_easy_setopt(header, CURLOPT_NOBODY, 1);
	curl_easy_setopt(header, CURLOPT_FOLLOWLOCATION, true);
	CURLcode code = curl_easy_perform(header);
	if (code == CURLE_OK)
	{
		long responseCode;
		curl_easy_getinfo(header, CURLINFO_RESPONSE_CODE, &responseCode);
		curl_easy_getinfo(header, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &contentLength);
		if (responseCode == HTTP_CODE_OK)
		{
			_supportResuming = true;
		}
	}
	curl_easy_cleanup(header);
	contentSize = contentLength;
	return _supportResuming;
}


bool XDownloader::prepareHeader(void *curl, const std::string &srcUrl) const
{
	curl_easy_setopt(curl, CURLOPT_URL, srcUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
	if (curl_easy_perform(curl) == CURLE_OK)
		return true;
	else
		return false;
}

void XDownloader::_downloadFileInThread(XDownloadUnit* pkUnit)
{
	const char* szURL = pkUnit->getURL().c_str();
	const char* szLocalFile = pkUnit->getLocalFilePath().c_str();
	double _remoteFileSize = pkUnit->getRemoteFileSize();
	bool _downloadOK = false;
	bool _needDownload = true;
	int  resume_size = 0;

	FILE* fp = NULL;
#if SUPPORT_RESUME //是否开启断点续存,默认禁用，原因是如果不是每个文件都有版本号，有出错的风险
	bool isResumeSupport = pkUnit->getResumDownload();
	//如果未知远端文件大小，且需要断点续存，从远端获取文件大小
	if (_remoteFileSize <= 0 && isResumeSupport)
	{
		isResumeSupport = getContentSize(szURL, _remoteFileSize);
	}
#endif

	std::string finalFile = m_defaultStoragePath + szLocalFile;
	std::string tempFile  = m_defaultStoragePath + szLocalFile + TEMP_EXT;

#if SUPPORT_RESUME //是否开启断点续存,默认禁用，原因是如果不是每个文件都有版本号，有出错的风险
	if (_remoteFileSize > 0)
	{
		//获取本地文件大小
		int size = XSystemUtils::getFileSize(tempFile);
		if (size > 0)
		{
			//if 本地文件大小 == 远端文件大小 then 文件下载完成
			if (size == _remoteFileSize)
			{
				XLOG("file %s already downloaded", tempFile.c_str());
				_needDownload = false;
			}
			else
			{
				resume_size = (int)size;
				fp = fopen(tempFile.c_str(), "ab");
			}
			pkUnit->setLocalFileSize(size);
		}
		else
		{
			fp = fopen(tempFile.c_str(), "wb+");
		}
	}
	else
	{
		fp = fopen(tempFile.c_str(), "wb+");
	}
#else
	fp = fopen(tempFile.c_str(), "wb+");
#endif

	CURLcode curL_res = CURLE_OK;
	if (_needDownload)
	{
		if (fp == nullptr)
		{
//			//创建目录 TODO，应该下载前创建好
//#ifdef COCOS2D_CUSTOM_FIX 
//			// 去掉文件名
//
//#endif
//			if (fp == nullptr)
//			{
			pkUnit->setErrorcode(ErrorCode::CREATE_FILE, ErrorSubCode::NO_OTHER_CODE);
			return;
			//}
		}

		CURL *curl = curl_easy_init();
		if (!curl)
		{
			pkUnit->setErrorcode(ErrorCode::CURL_EASY_ERROR, ErrorCode::CURL_UNINIT);
			return;
		}
#if SUPPORT_RESUME //是否开启断点续存,默认禁用，原因是如果不是每个文件都有版本号，有出错的风险
		//开始续传
		if (resume_size > 0)
		{
			char size_char[128] = { 0 };
			sprintf(size_char, "%ld-", resume_size);
			curl_easy_setopt(curl, CURLOPT_RANGE, size_char);
			CCDLOG("continue download %ld", resume_size);
		}
#endif
		// Download pacakge 设置写
		curl_easy_setopt(curl, CURLOPT_URL, pkUnit->getURL().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fileWriteFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		//  设置是否需要进度检查
		if (pkUnit->getProgress())
		{
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
			curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, pkUnit);
		}
		else
		{
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, 0L);
			curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, 0L);
		}
		/*
		CURLcode
		This is returned if CURLOPT_FAILONERROR is set TRUE and the HTTP server returns an error code that is >= 400.
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
		*/
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, DEFAULT_TIMEOUT);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
		//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curL_res = curl_easy_perform(curl);
		//是否执行成功
		if (curL_res != CURLE_OK)
		{
			pkUnit->setErrorcode(ErrorCode::CURL_EASY_ERROR, curL_res);
		}
		fclose(fp);
		// This can only be done after fclose
		// curl成功，还需要检查返回码是否200
		if (curL_res == CURLE_OK)
		{
			long responseCode;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
			if (responseCode != HTTP_CODE_OK && responseCode != HTTP_CODE_SUPPORT_RESUME)
			{
				pkUnit->setErrorcode(ErrorCode::CURL_EASY_RESP_ERROR, responseCode);
			}
		}
		//curl_easy_init 配对 curl_easy_cleanup
		curl_easy_cleanup(curl);
	}


	if (pkUnit->getErrorcode() == 0)
	{
		//如果没有错误,执行MD5
		std::string strMD5 = pkUnit->getMD5String();
		//如果有MD5传入的话
		if (!strMD5.empty())
		{
			//统一大小写
			std::transform(strMD5.begin(), strMD5.end(), strMD5.begin(), (int(*)(int))std::tolower);
			XMD5Utils md5;
			if (md5.processFile(tempFile.c_str()) == false)
			{
				pkUnit->setErrorcode(ErrorCode::MD5_ERROR, MD5Error::MD5FailedOpen);
			}
			else if (md5.isSame(strMD5.c_str()) == false)
			{
				pkUnit->setErrorcode(ErrorCode::MD5_ERROR, MD5Error::MD5FailedCompare);
			}
		}
	}

	//如果没有错误
	if (pkUnit->getErrorcode() == 0)
	{
		//重命名文件，将.tmp后缀去除
		std::string reltmp = szLocalFile;
		//加上temp後綴
		XSystemUtils::renameFile(m_defaultStoragePath, reltmp + TEMP_EXT, szLocalFile);
	}
	else
	{
		//如果有错误，移除已经下载的文件
		if ((getNeedQuit() == false) && (curL_res != CURLE_OPERATION_TIMEDOUT))
		{
			XSystemUtils::removeFile(tempFile);
		}
	}
}

void XDownloader::onDownloadProgress(const std::string& filename, unsigned int localfileSize, double arg1, double arg2)
{
	XDownloaderCallbackGroupMap::iterator iter = m_download_callback_groups->find(filename);
	if (iter != m_download_callback_groups->end())
	{
		iter->second->onProgress(arg1, arg2, localfileSize);
	}
}

void XDownloader::onDownloadProgressInCocosThread(const std::string filename, unsigned int localfileSize, double arg1, double arg2)
{
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([filename, localfileSize, arg1, arg2]{
		XDownloader::getInstance()->onDownloadProgress(filename, localfileSize, arg1, arg2);
	});
}


void XDownloader::onFinish(XDownloadUnit* pkUnit)
{
	//如果有errorCode是失败了
	if (pkUnit->getErrorcode())
	{
		onFailed(pkUnit);
	}
	else
	{
		onSuccess(pkUnit);
	}
}

void XDownloader::onSuccess(XDownloadUnit* pkUnit)
{
	CCDLOG("XDownloader::onSuccess %s %s ", pkUnit->getURL().c_str(), pkUnit->getLocalFilePath().c_str());
	const std::string& key = pkUnit->getLocalFilePath();
	XDownloaderCallbackGroupMap::iterator cb_iter = m_download_callback_groups->find(key);
	if (cb_iter != m_download_callback_groups->end())
	{
		//下载成功
		cb_iter->second->onDownload();
		//删除回调函数组
		delete cb_iter->second;
		m_download_callback_groups->erase(cb_iter);
	}
	//删除完成
	delete pkUnit;
}

void XDownloader::onFailed(XDownloadUnit* pkUnit)
{
	
	int count = pkUnit->getRetryCount();
	if (count > 0)
	{
		CCDLOG("XDownloader::onRetry %s %s %d", pkUnit->getURL().c_str(), pkUnit->getLocalFilePath().c_str(), pkUnit->getErrorcode());
		pkUnit->setRetryCount(count - 1);
		m_download_retry_list->push_back(pkUnit);
		if (m_retryRefCount == 0)
		{
			Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(XDownloader::retryTick), this, 1.0, false);
		}
		m_retryRefCount++;
	}
	else
	{
		CCDLOG("XDownloader::onFailed %s %s %d", pkUnit->getURL().c_str(), pkUnit->getLocalFilePath().c_str(), pkUnit->getErrorcode());
		const std::string& key = pkUnit->getLocalFilePath();
		XDownloaderCallbackGroupMap::iterator cb_iter = m_download_callback_groups->find(key);
		if (cb_iter != m_download_callback_groups->end())
		{
			//下载失败
			unsigned int code = pkUnit->getErrorcode();
			cb_iter->second->onFailed(code / ERROR_CODE_SEP, code % ERROR_CODE_SEP, code);
			delete cb_iter->second;
			m_download_callback_groups->erase(cb_iter);
		}
		//删除等待
		delete pkUnit;
	}
}

void XDownloader::downloadTick(float dt)
{
	// 取完成列表
	XDownloadUnitList* finishList = m_download_finish_list;
	m_finishMutex.lock();

	if (m_download_finish_list->empty())
	{
		m_finishMutex.unlock();
	}
	else
	{
		XDownloadUnit *pkUnit = m_download_finish_list->front();
		m_download_finish_list->pop_front();
		m_finishMutex.unlock();
		
		//处理完成下载
		onFinish(pkUnit);

		--m_asyncRefCount;
		if (0 == m_asyncRefCount)
		{
			Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(XDownloader::downloadTick), this);
		}
	}
}

void XDownloader::retryTick(float dt)
{
	if (!m_download_retry_list->empty())
	{
		XDownloadUnit* pkUnit = m_download_retry_list->front();
		m_download_retry_list->pop_front();

		//重试
		m_waitingMutex.lock();
		m_download_waiting_list->push_back(pkUnit);
		m_waitingMutex.unlock();

		if (0 == m_asyncRefCount)
		{
			Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(XDownloader::downloadTick), this, 0, false);
		}
		++m_asyncRefCount;
		m_sleepCondition.notify_one();
	}

	m_retryRefCount--;
	if ( 0 == m_retryRefCount )
	{
		Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(XDownloader::retryTick), this);
	}
}


bool XDownloader::downloadFile(XDownloader::Options& options)
{
	if (options.strURL.empty() && m_defaultHost.empty())
	{
		return false;
	}

	//如果没用填写url就是用默认url
	if (options.strURL.empty())
	{ 
		options.strURL = m_defaultHost + options.strFilename;
	}

	//如果没有填写md5到文件里面找
	if (options.strMD5.empty())
	{
		std::map<std::string, std::string>::iterator iter = m_mapDownloadMD5.find(options.strFilename);
		if (iter != m_mapDownloadMD5.end())
		{
			options.strMD5 = iter->second;
		}
	}

	if (FileUtils::getInstance()->isAbsolutePath(options.strFilename))
	{
		CCLOGERROR("XDownloader::downloadFile %s", options.strFilename.c_str());
		CCASSERT(false, "options.strFilename should be relative");
	}
	options.strFilename = options.strFilename;
	return _downloadFile(options);
}



void XDownloader::cancelDownload(const std::string& filename)
{
	//cancelDownload 一個不能存在的文件
	if (m_download_waiting_list == NULL)
		return;

	std::string storagePath;
	if (!FileUtils::getInstance()->isAbsolutePath(storagePath))
	{
		storagePath = m_defaultStoragePath + filename;
	}
	else
	{
		storagePath = filename;
	}

	bool bFound = false;
	m_waitingMutex.lock();
	bFound = cancelByName(storagePath, m_download_callback_groups, m_download_waiting_list);
	m_waitingMutex.unlock();

	if (bFound)
	{
		XLOGINFO("XDownloader::cancelDownload from waiting", filename.c_str());
		return;
	}

	m_finishMutex.lock();
	bFound = cancelByName(storagePath, m_download_callback_groups, m_download_finish_list);
	m_finishMutex.unlock();

	if (bFound)
	{
		XLOGINFO("XDownloader::cancelDownload from finish", filename.c_str());
		return;
	}

	bFound = cancelByName(storagePath, m_download_callback_groups, m_download_retry_list);
	if (bFound)
	{
		XLOGINFO("XDownloader::cancelDownload from retry", filename.c_str());
		return;
	}
}

void XDownloader::cancelWithPriority(unsigned char p)
{
	bool ret = true;
	m_waitingMutex.lock();
	ret = cancelByPriority(p, m_download_callback_groups, m_download_waiting_list);
	m_waitingMutex.unlock();

	m_finishMutex.lock();
	ret = cancelByPriority(p, m_download_callback_groups, m_download_finish_list);
	m_finishMutex.unlock();

	ret = cancelByPriority(p, m_download_callback_groups, m_download_retry_list);
}

void XDownloader::downloadAll()
{
	/*
	int i = 0;
	for (std::map<std::string, std::string>::iterator iter = m_mapDownloadMD5.begin();
		iter != m_mapDownloadMD5.end();
		iter++)
	{
		if (i > 200)
			i = 0;
		XDownloaderCallbackObject* pkObject = XDownloaderCallbackObject::create(iter->first);
		
		XDownloaderCallbackObject::ErrorCallback onError = [](unsigned int code0, unsigned int code1, unsigned int code2, const std::string customID)
		{
			CCDLOG("onErrorCallback %d %d %d %s", code0, code1, code2, customID.c_str());
		};

		pkObject->setErrorCallback(onError);

		XDownloaderCallbackObject::SuccessCallback onSucess = [](const std::string & filename, const std::string & url, const std::string & customID)
		{
			CCDLOG("onErrorCallback %s %s %s", filename.c_str(), url.c_str(), customID.c_str());
		};

		pkObject->setSuccessCallback(onSucess);

		XDownloaderCallbackObject::ProgressCallback onProgress = [](unsigned int code0, double code1, double code2, const std::string& url, const std::string& customID)
		{
			CCDLOG("onProgressCallback %d %f %f %s %s", code0, code1, code2, url.c_str(), customID.c_str());
		};
		pkObject->setProgressCallback(onProgress);

		downloadFile(iter->first.c_str(), NULL, iter->second.c_str(), pkObject, false, i++, 1, true);
	}


	XDownloaderCallbackObject* pkObject = XDownloaderCallbackObject::create("test.zip");

	XDownloaderCallbackObject::ErrorCallback onError = [](unsigned int code0, unsigned int code1, unsigned int code2, const std::string customID)
	{
		CCDLOG("onErrorCallback %d %d %d %s", code0, code1, code2, customID.c_str());
	};

	pkObject->setErrorCallback(onError);

	XDownloaderCallbackObject::SuccessCallback onSucess = [](const std::string & filename, const std::string & url, const std::string & customID)
	{
		CCDLOG("onSuccessCallback %s %s %s", filename.c_str(), url.c_str(), customID.c_str());
	};

	pkObject->setSuccessCallback(onSucess);

	XDownloaderCallbackObject::ProgressCallback onProgress = [](unsigned int code0, double code1, double code2, const std::string& url, const std::string& customID)
	{
		CCDLOG("onProgressCallback %d %f %f %s %s", code0, code1, code2, url.c_str(), customID.c_str());
	};
	pkObject->setProgressCallback(onProgress);


	downloadFile("cache/test.zip", "http://qzrz.dl.hoolaigames.com/ftnj_android/update/010100/ftnj_android_update_1.01.00_1.01.01.zip", "ecdb6b998c8406ee5a0fa7d029351377", pkObject, true, 0, 1, true);
	*/
}
