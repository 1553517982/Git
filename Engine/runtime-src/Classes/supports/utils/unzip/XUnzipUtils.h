// added by Shan Lu 2015/01/15 Begin
// ��AssetsManagerEx������ķ������������Ǹ��¹������ͽű�ʹ��
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
		OK,					 // ��ѹ�ɹ�
		NO_ROOT_PATH,	 	 // zip�ļ�û��Ŀ¼��Ϣ
		NO_ZIP_FILE,		 // zip�ļ�ûû���ҵ�
		NO_ZIP_INFO,		 // zip�ļ�û����Ϣ
		CANNOT_READ,		 // �޷���ȡZIP�ļ�
		CANNOT_MKDIR,		 // �޷������ļ���
		CANNOT_EXTRACT,		 // �޷���ѹ�ļ�
		CANNOT_CREATE_FILE,	 // �޷������ļ�
		CANNOT_READ_FILE,	 // �޷���Zip��ȡ�ļ�
		CANNOT_READ_NEXTFILE // �޷���ȡ��һ���ļ�
	};
	
	static std::string basename(const std::string& filename);


	//************************************
	// Method:    decompress
	// FullName:  cocos2d::extension::systemUtils::decompress
	// Access:    public static 
	// Returns:   int
	// Qualifier: ��ѹzip�ļ�
	// Parameter: const std::string & filename			��ѹ�ļ���
	// Parameter: unsigned int progressThreshold		ÿ���ٸ��ļ��ر�һ�ν�ѹ����
	// Parameter: decompressProgressCallback progress	��ѹ���Ȼص�
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