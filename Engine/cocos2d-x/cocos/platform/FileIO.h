#ifndef FILE_IO_H_0x3b201aaa_0xee3c_0x4586_0xab_0xa_0x37_0xec_0x63_0xf2_0xf7_0xf9
#define FILE_IO_H_0x3b201aaa_0xee3c_0x4586_0xab_0xa_0x37_0xec_0x63_0xf2_0xf7_0xf9
/**********************************************************************
*	File name:FileIO.h
*	LastestAuthor: Raymond   
*	Version:2.0
*	LastestEditData:2012-04-03
*	File Description:
*		不能处理过大文件（如2G或者以上）
*
*	Other:
*
*	PublicFunctionList:
*		// 指定文件
*		// path，文件路径
*		// true则文件存在，false则文件不存在
*		// 只能支持2G以下文件
*		bool FileOpen(String & path);
*
*		// 关闭指定文件
*		bool FileClose();
*		
*		// 写入文件
*		// pFileData：文件信息
*		// nSize：信息长度
*		// nStart：从文件起始点开始写入，默认值0的话，即由从文件开始覆盖式写入。
*		// 假如没有指定文件的话则会返回false。其它失败也一样
*		bool WriteFile(void * pFileData, FILE_INT nSize, FILE_INT nStart = 0);
*		
*		// 读取文件
*		// pFileData：文件信息
*		// nStart：获取的起始位置
*		// nSize：信息获取的长度，假如此长度大于可以获取的长度，那么，此值将会被改变
*		// 假如没有指定文件的话则会返回false。其它失败也一样
*		// 读取出来之后，需要把指针转换成char*，然后delete []
*		bool ReadFile(void *& pFileData, FILE_INT nStart, FILE_INT & nSize);
*
*		// 获取当前文件的大小
*		// 假如文件不存在则返回-1
*		FILE_INT GetFileSize();
*
*		// 删除文件
*		static bool RemoveFile(String & str);
*
*		// 创建文件夹
*		static bool MakeDir(String & str);
*		
*		// 删除文件夹
*		static bool RemoveDir(String & str);
*
*	
*	ProtectedFunctionList:
*
*	PrivateFunctionList:
*
*
*	EditHistory(Data, Author, Modification'sDescription): 
*			2010-06-24，Raymond，1.0版完成。其中cpp利用c语言公共接口完成
*			2010-06-25，Raymond，增加接口，负责删除文件
*			2010-06-25，Raymond，优化WriteFile接口
*			2010-06-25，Raymond，修正两个比较大的错误，新增MakeDir及RemoveDir两个接口处理文件夹
*			2010-06-26，Raymond，删除一些没必要的变量
*			2010-08-10，Raymond，增加一个判断文件是否存在的接口
*			2011-10-15，Raymond，被改成Might引擎里面的一个类，即把String改为const char*
*			2012-04-03，Raymond，ReadFile改成用返回值表示读取了多少个字节
***********************************************************************/

typedef unsigned int FILE_INT;

#ifdef WIN32
class __declspec(dllexport) FileIO
#else
class FileIO
#endif
{
public:
	FileIO(void);
	~FileIO(void);

	// 指定文件
	// path，文件路径
	// true则文件存在，false则文件不存在
	// 只能支持2G以下文件
	bool FileOpen( const char * szPath, bool bNeedWrite, bool bCreateIfNotExist );

	// 判断文件是否存在，不打开
	static bool IfFileExist( const char * szPath );

	// 关闭指定文件
	bool FileClose();

	// 写入文件
	// pFileData：文件信息
	// nSize：信息长度
	// nStart：从文件起始点开始写入，默认值0的话，即由从文件开始覆盖式写入。
	// 假如没有指定文件的话则会返回false。其它失败也一样
	// 强烈注意！！！！！很恶心的遇到一次。估计windows底层是有写入缓冲这个设定，
	// 在调用write之后，绝对不要直接read出来。实在要read，必须要先调用FileClose，重新调用FileOpen再read。否则不保证数据正确性。
	bool WriteFile( const void * pFileData, FILE_INT nSize, FILE_INT nStart = 0 );

	// 读取文件
	// pFileData：内存指针，内存大小要保证大于nSize
	// nStart：获取的起始位置
	// nSize：想要信息获取的长度
	FILE_INT ReadFile( void * pFileData, FILE_INT nStart, FILE_INT nSize );

	// 获取当前文件的大小
	// 假如文件不存在则返回0
	FILE_INT GetFileSize();

	// 删除文件
	static bool RemoveFile( const char * str );

	// 文件更名
	static bool ReName( const char * oldName, const char * newName );

	// 删除文件夹
	static void RemoveDir(const char * str);

	// 清空文件夹
	static void ClearFolder(const char * path);

protected:
	void *m_pFile;
	FILE_INT m_nFileSize;	// 以单字节char的file的长度
	bool m_bOpen;
};


#endif
