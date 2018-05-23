#ifndef __XDownloader__
#define __XDownloader__
#include "platform/CCFileUtils.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "XDownloaderUnit.h"

USING_NS_CC;

#define MAX_DOWNLOAD_THREAD		2
#define DOWNLOAD_TRY_MAX		1

class XDownloader : public Ref
{
public:
	class Options
	{
		Options() {};
	public:
		Options(const std::string& _strFilename, const std::string& _strURL,
				XDownloaderCallbackObject* _pkCallbackObject,
				unsigned char _ucPriority, unsigned char _retryCount, bool bReplace);

		void setCallbackObject(XDownloaderCallbackObject*);
		XDownloaderCallbackObject* getCallbackObject() const { return pkCallbackObject; }

		virtual ~Options();

		Options* clone();

		std::string					strFilename;
		std::string					strURL;
		std::string					strMD5;
		bool						bResumeSupport;
		unsigned char				ucPriority;
		unsigned char				ucRetryCount;
		unsigned int				uRemotefileSize;
		// added by aXing on 2017-4-20
		// ���һ���Ƿ�����replace��ѡ��
		bool						bReplace;

	private:
		XDownloaderCallbackObject*	pkCallbackObject;

	};

		enum MD5Error
		{
			MD5FailedOpen,
			MD5FailedCompare,
		};

		enum ErrorCode
		{
			NON_ERROR,

			CREATE_FILE,

			NETWORK,

			NO_NEW_VERSION,

			UNCOMPRESS,

			CURL_UNINIT,

			CURL_MULTI_ERROR,

			CURL_EASY_ERROR,

			CURL_EASY_RESP_ERROR,

			INVALID_URL,

			INVALID_STORAGE_PATH,

			MD5_ERROR,

			UNZIP_ERROR,

			UNKNOWN_ERROR,	 // host == ""

			CANCELED,
		};

		enum ErrorSubCode
		{
			NO_OTHER_CODE
		};

		enum InitRetCode
		{
			OK,
			EMPTY_STORAGE_PATH,
			CANNOT_READ_XML,
			CANNOT_READ_ROOT,
			CANNOT_CREATE_DIR
		};

		XDownloader();
		~XDownloader();

		// ��ȡ��Դ����������
		static XDownloader*	getInstance();
			
		static void destroyInstance();

		//��ʼ��
		//@params
		//  fileList = �ļ��� : md5���
		//  host = Ĭ�����ص�ַhost
		//  �Ƿ񴴽����ر����ַ
		int  initialize(const std::string& fileList, const std::string& defaultHost, const std::string& storagePath);

		void cancelAll();

		void clearAll();


		void cancelWithPriority(unsigned char p);

		bool getContentSize(const std::string &srcUrl, double& contentSize) const;

		bool prepareHeader(void *curl, const std::string &srcUrl) const;

		void onDownloadProgressInCocosThread(const std::string filename, unsigned int localfileSize, double arg1, double arg2);

		//void onDecompressProgressInCocosThread(const std::string filename, double arg1, double arg2);

		bool downloadFile(XDownloader::Options& options);

		const char*		getMD5String(const char* szFilename);

		const char*		getHost() const { return m_defaultHost.c_str(); }

		//����ȫ�������ԣ�
		void			downloadAll();

		bool			getNeedQuit() const { return m_needQuit; }

		void			setNeedQuit(bool val) { m_needQuit = val; }

		void			cancelDownload(const std::string& filename);

	protected:

		void clearWaiting();

		void clearFinish();

		void clearCallbacks();

		void cancelCallbacks();

		void onDownloadProgress(const std::string& filename, unsigned int localfileSize, double arg1, double arg2);

		//void onDecompressProgress(const std::string& filename, double arg1, double arg2);

		void onFinish(XDownloadUnit* pkUnit);

		void onSuccess(XDownloadUnit* pkUnit);

		void onFailed(XDownloadUnit* pkUnit);

		//ÿ֡tick
		void downloadTick(float dt);

		void retryTick(float dt);

		int parseFileList(const std::string& fileList);

		void _downloadFileFromList(void);

		void _downloadFileInThread(XDownloadUnit* pkUnit);

		// �ȴ��˳�downloader
		void waitForQuit();

		bool _downloadFile(XDownloader::Options& options);


		//֧�ֵ��߳�
		std::list<std::thread>							  m_downloadThreads;
		std::mutex										  m_waitingMutex;
		std::mutex										  m_finishMutex;

		std::mutex										  m_sleepMutex;
		std::condition_variable							  m_sleepCondition;

		std::list<XDownloadUnit*>*						  m_download_waiting_list;
		std::list<XDownloadUnit*>*						  m_download_finish_list;
		std::list<XDownloadUnit*>*						  m_download_retry_list;

		std::map<std::string, XDownloaderCallbackGroup*>* m_download_callback_groups;
		std::map<std::string,std::string>				  m_mapDownloadMD5;
		std::string										  m_defaultHost;
		std::string										  m_defaultStoragePath;
		bool											  m_bDownloadInit;
		int												  m_asyncRefCount;
		int												  m_retryRefCount;
		std::atomic<bool>							      m_needQuit;
		static XDownloader*								  m_s_XDownloader;

		// ��¼��������ص��ļ��İ汾��
		// ��CNewLoader::LoadMD5Tab��ȡ
		std::map<std::string, std::string>				  m_files_versions;
};

typedef std::map<std::string, XDownloaderCallbackGroup*> XDownloaderCallbackGroupMap;
typedef std::list<XDownloadUnit*> XDownloadUnitList;
#endif /* defined(__AssetsManager__) */
