#include "XUnzipUtils.h"
#include "utils/XSystemUtils.h"
#include "XCommon.h"
#include "base/CCAsyncTaskPool.h"
#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip/unzip.h"
#endif

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512
static XUnzipUtils* s_sharedUtils = NULL;

typedef struct tJob
{
	tJob(const char* filename, std::function<void(void)> func) :
		m_strfilename(filename),
		m_funcJob(func)
	{

	}
	std::string					m_strfilename;
	std::function<void(void)>	m_funcJob;
	void doJob()
	{
		m_funcJob();
	}
}tJob;

static std::list<tJob*>			s_unzipJobsList;
static bool						s_schedulered = false;
std::string XUnzipUtils::basename(const std::string& path)
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(0, found);
	}
	else
	{
		return path;
	}
}

static void doNextJob(float)
{
	if (!s_unzipJobsList.empty())
	{
		auto job = s_unzipJobsList.back();
		s_unzipJobsList.pop_back();
		job->doJob();
		delete job;
	}
}
static void onDecompressProgressInCocosThread(XUnzipUtils::decompressProgressCallback progressCallback, double arg1, double arg2)
{
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([progressCallback,arg1, arg2]{
		progressCallback(arg1, arg2);
	});
}

static void onDecompressFinishInCocosThread(XUnzipUtils::decompressFinishCallback finishCallback, int ret)
{
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([finishCallback, ret]{
		finishCallback(ret);
		doNextJob(0);
	});
}

int XUnzipUtils::decompress(const std::string &zip, unsigned int progressThreshold, decompressProgressCallback progress)
{
	FileUtils* _fileUtils = FileUtils::getInstance();

	// Find root path for zip file
	size_t pos = zip.find_last_of("/\\");
	if (pos == std::string::npos)
	{
		XLOG("systemUtils : no root path specified for zip file %s\n", zip.c_str());
		return DecompressErrorCode::NO_ROOT_PATH;
	}
	const std::string rootPath = zip.substr(0, pos + 1);

	// Open the zip file
	unzFile zipfile = unzOpen(zip.c_str());
	if (!zipfile)
	{
		XLOG("systemUtils : can not open downloaded zip file %s\n", zip.c_str());
		return DecompressErrorCode::NO_ZIP_FILE;
	}

	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		XLOG("systemUtils : can not read file global info of %s\n", zip.c_str());
		unzClose(zipfile);
		return DecompressErrorCode::NO_ZIP_INFO;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			XLOG("systemUtils : can not read compressed file info\n");
			unzClose(zipfile);
			return DecompressErrorCode::CANNOT_READ;
		}
		const std::string fullPath = rootPath + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			//There are not directory entry in some case.
			//So we need to create directory when decompressing file entry
			if (!XSystemUtils::createDirectory(basename(fullPath).c_str()))
			{
				// Failed to create directory
				XLOG("systemUtils : can not create directory %s\n", fullPath.c_str());
				unzClose(zipfile);
				return DecompressErrorCode::CANNOT_MKDIR;
			}
		}
		else
		{
			// Entry is a file, so extract it.
			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				XLOG("systemUtils : can not extract file %s\n", fileName);
				unzClose(zipfile);
				return DecompressErrorCode::CANNOT_EXTRACT;
			}

			// Create a file to store current file.
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (!out)
			{
				XLOG("systemUtils : can not create decompress destination file %s\n", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return DecompressErrorCode::CANNOT_CREATE_FILE;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					XLOG("systemUtils : can not read zip file %s, error code is %d\n", fileName, error);
					fclose(out);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return DecompressErrorCode::CANNOT_READ_FILE;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				XLOG("systemUtils : can not read next file for decompressing\n");
				unzClose(zipfile);
				return DecompressErrorCode::CANNOT_READ_NEXTFILE;
			}
		}

		if (progress && progressThreshold > 0 && i % progressThreshold == 0)
		{
			progress(i, global_info.number_entry);
		}
	}

	unzClose(zipfile);
	return DecompressErrorCode::OK;
}

XUnzipUtils* XUnzipUtils::sharedUtils()
{
	if (s_sharedUtils)
		return s_sharedUtils;
	s_sharedUtils = new XUnzipUtils();
	return s_sharedUtils;
}
void XUnzipUtils::purgeSharedUtils()
{
	if (s_sharedUtils)
	{
		s_sharedUtils->fini();
	}
	CC_SAFE_RELEASE_NULL(s_sharedUtils);
}

int XUnzipUtils::decompressAsync(const std::string &filename, unsigned int progressThreshold, decompressFinishCallback finish, decompressProgressCallback progress)
{
	AsyncTaskPool::TaskCallBack finishCallback = [=](void*){};

	decompressProgressCallback progressFunc = nullptr;
	if (progress)
	{
		progressFunc = std::bind(onDecompressProgressInCocosThread, progress, std::placeholders::_1, std::placeholders::_2);
	}


	auto jobfunc = [=](void)
	{
		AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, finishCallback, nullptr, [=]()
		{
			int ret = decompress(filename, progressThreshold, progressFunc);
			onDecompressFinishInCocosThread(finish, ret);
		});
	};

	bool isEmptyJobList = s_unzipJobsList.empty();
	auto job = new tJob(filename.c_str(), jobfunc);
	s_unzipJobsList.push_back(job);
	
	if (isEmptyJobList)
	{
		std::string key = "unzip";
		auto scheduler = Director::getInstance()->getScheduler();
		scheduler->schedule(doNextJob, this, 0.0f, 1, 0.0f, false, key);
	}
	return 0;
}

void XUnzipUtils::cancelDecompressAsync(const std::string &filename)
{
	for (auto i = s_unzipJobsList.begin(); i != s_unzipJobsList.end(); i++)
	{
		if ((*i)->m_strfilename == filename)
		{
			delete (*i);
			s_unzipJobsList.erase(i);
		}
	}
}

void XUnzipUtils::fini()
{
	for (auto i = s_unzipJobsList.begin(); i != s_unzipJobsList.end(); i++)
	{
		delete (*i);
	}
	s_unzipJobsList.clear();
}