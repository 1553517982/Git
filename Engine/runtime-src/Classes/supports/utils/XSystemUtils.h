// added by Shan Lu 2015/01/15 Begin
// 从AssetsManagerEx抽出来的方法，用于我们更新管理器和脚本使用
#include "cocos2d.h"
#include <string>
#ifndef _system_utils_H
#define _system_utils_H
USING_NS_CC;

class XSystemUtils
{
public:
	static bool renameFile(const std::string& abspath, const std::string &oldPath, const std::string &newPath);
	static bool removeFile(const std::string &path);
	static bool createDirectory(const char *path);
	static int deleteDirectoryFiles(const char* path);
	static int getFileSize(const std::string& filepath);
};

#endif // !_system_utils_H
// added by Shan Lu 2015/01/15 End