#include "utils/XSystemUtils.h"



#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include <sys/stat.h>
#include <regex>
#include "dirent_win32.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include <ftw.h>
#endif

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif

bool XSystemUtils::renameFile(const std::string& abspath, const std::string &oldPath, const std::string &newPath)
{
	//const std::string& abspath, const std::string &oldPath, const std::string &newPath
	return FileUtils::getInstance()->renameFile(abspath, oldPath, newPath);

	//std::string oldAbsolutePath = FileUtils::getInstance()->fullPathForFilename(oldPath);
	//std::string newAbsolutePath = FileUtils::getInstance()->fullPathForFilename(newPath);
	//std::regex pat("\\/");
	//std::string _old = std::regex_replace(oldPath, pat, "\\");
	//std::string _new = std::regex_replace(newPath, pat, "\\");

	//int oldIndex = _old.rfind("\\");
	//int newIndex = _new.rfind("\\");
	//if (oldIndex != -1 && newIndex != -1)
	//{
	//	std::string path = _old.substr(0, oldIndex + 1);		// 路径需要保留"/"
	//	std::string oldName = _old.substr(oldIndex + 1);
	//	int newIndex = _new.rfind("\\");
	//	std::string newName = _new.substr(newIndex + 1);
	//	
	//}
	//return false;
}

bool XSystemUtils::removeFile(const std::string &path)
{
	return FileUtils::getInstance()->removeFile(path);
}

bool XSystemUtils::createDirectory(const char *path)
{
	return FileUtils::getInstance()->createDirectory(path);
}

int XSystemUtils::getFileSize(const std::string& filepath)
{
	return (int)FileUtils::getInstance()->getFileSize(filepath);
}


int XSystemUtils::deleteDirectoryFiles(const char* dir_name)
{
	std::string path = dir_name;
	return (int)FileUtils::getInstance()->removeDirectory(path);
}