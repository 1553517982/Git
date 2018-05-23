// added by Shan Lu 2015/01/15 Begin
// 从AssetsManagerEx抽出来的方法，用于我们更新管理器和脚本使用
#include "cocos2d.h"
#include <string>
#ifndef _unzip_utils_H
#define _unzip_utils_H
USING_NS_CC;

class XUnzipUtils : Ref
{
public:
	typedef std::function<void(double, double)> decompressProgressCallback;
	typedef std::function<void(int)>			decompressFinishCallback;

	enum DecompressErrorCode
	{
		OK,					 // 解压成功
		NO_ROOT_PATH,	 	 // zip文件没有目录信息
		NO_ZIP_FILE,		 // zip文件没没有找到
		NO_ZIP_INFO,		 // zip文件没有信息
		CANNOT_READ,		 // 无法读取ZIP文件
		CANNOT_MKDIR,		 // 无法创建文件夹
		CANNOT_EXTRACT,		 // 无法解压文件
		CANNOT_CREATE_FILE,	 // 无法创建文件
		CANNOT_READ_FILE,	 // 无法从Zip读取文件
		CANNOT_READ_NEXTFILE // 无法读取下一个文件
	};
	
	static std::string basename(const std::string& filename);


	//************************************
	// Method:    decompress
	// FullName:  cocos2d::extension::systemUtils::decompress
	// Access:    public static 
	// Returns:   int
	// Qualifier: 解压zip文件
	// Parameter: const std::string & filename			解压文件名
	// Parameter: unsigned int progressThreshold		每多少个文件回报一次解压进度
	// Parameter: decompressProgressCallback progress	解压进度回调
	//************************************
	static int decompress(const std::string &filename, unsigned int progressThreshold, decompressProgressCallback progress);


	static XUnzipUtils*			sharedUtils();
	static void					purgeSharedUtils();

	int decompressAsync(const std::string &filename, unsigned int progressThreshold, decompressFinishCallback finish, decompressProgressCallback progress);

	void cancelDecompressAsync(const std::string &filename);

	void fini();
};

#endif // !_system_utils_H
// added by Shan Lu 2015/01/15 End