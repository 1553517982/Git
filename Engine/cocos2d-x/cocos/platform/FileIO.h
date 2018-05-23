#ifndef FILE_IO_H_0x3b201aaa_0xee3c_0x4586_0xab_0xa_0x37_0xec_0x63_0xf2_0xf7_0xf9
#define FILE_IO_H_0x3b201aaa_0xee3c_0x4586_0xab_0xa_0x37_0xec_0x63_0xf2_0xf7_0xf9
/**********************************************************************
*	File name:FileIO.h
*	LastestAuthor: Raymond   
*	Version:2.0
*	LastestEditData:2012-04-03
*	File Description:
*		���ܴ�������ļ�����2G�������ϣ�
*
*	Other:
*
*	PublicFunctionList:
*		// ָ���ļ�
*		// path���ļ�·��
*		// true���ļ����ڣ�false���ļ�������
*		// ֻ��֧��2G�����ļ�
*		bool FileOpen(String & path);
*
*		// �ر�ָ���ļ�
*		bool FileClose();
*		
*		// д���ļ�
*		// pFileData���ļ���Ϣ
*		// nSize����Ϣ����
*		// nStart�����ļ���ʼ�㿪ʼд�룬Ĭ��ֵ0�Ļ������ɴ��ļ���ʼ����ʽд�롣
*		// ����û��ָ���ļ��Ļ���᷵��false������ʧ��Ҳһ��
*		bool WriteFile(void * pFileData, FILE_INT nSize, FILE_INT nStart = 0);
*		
*		// ��ȡ�ļ�
*		// pFileData���ļ���Ϣ
*		// nStart����ȡ����ʼλ��
*		// nSize����Ϣ��ȡ�ĳ��ȣ�����˳��ȴ��ڿ��Ի�ȡ�ĳ��ȣ���ô����ֵ���ᱻ�ı�
*		// ����û��ָ���ļ��Ļ���᷵��false������ʧ��Ҳһ��
*		// ��ȡ����֮����Ҫ��ָ��ת����char*��Ȼ��delete []
*		bool ReadFile(void *& pFileData, FILE_INT nStart, FILE_INT & nSize);
*
*		// ��ȡ��ǰ�ļ��Ĵ�С
*		// �����ļ��������򷵻�-1
*		FILE_INT GetFileSize();
*
*		// ɾ���ļ�
*		static bool RemoveFile(String & str);
*
*		// �����ļ���
*		static bool MakeDir(String & str);
*		
*		// ɾ���ļ���
*		static bool RemoveDir(String & str);
*
*	
*	ProtectedFunctionList:
*
*	PrivateFunctionList:
*
*
*	EditHistory(Data, Author, Modification'sDescription): 
*			2010-06-24��Raymond��1.0����ɡ�����cpp����c���Թ����ӿ����
*			2010-06-25��Raymond�����ӽӿڣ�����ɾ���ļ�
*			2010-06-25��Raymond���Ż�WriteFile�ӿ�
*			2010-06-25��Raymond�����������Ƚϴ�Ĵ�������MakeDir��RemoveDir�����ӿڴ����ļ���
*			2010-06-26��Raymond��ɾ��һЩû��Ҫ�ı���
*			2010-08-10��Raymond������һ���ж��ļ��Ƿ���ڵĽӿ�
*			2011-10-15��Raymond�����ĳ�Might���������һ���࣬����String��Ϊconst char*
*			2012-04-03��Raymond��ReadFile�ĳ��÷���ֵ��ʾ��ȡ�˶��ٸ��ֽ�
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

	// ָ���ļ�
	// path���ļ�·��
	// true���ļ����ڣ�false���ļ�������
	// ֻ��֧��2G�����ļ�
	bool FileOpen( const char * szPath, bool bNeedWrite, bool bCreateIfNotExist );

	// �ж��ļ��Ƿ���ڣ�����
	static bool IfFileExist( const char * szPath );

	// �ر�ָ���ļ�
	bool FileClose();

	// д���ļ�
	// pFileData���ļ���Ϣ
	// nSize����Ϣ����
	// nStart�����ļ���ʼ�㿪ʼд�룬Ĭ��ֵ0�Ļ������ɴ��ļ���ʼ����ʽд�롣
	// ����û��ָ���ļ��Ļ���᷵��false������ʧ��Ҳһ��
	// ǿ��ע�⣡���������ܶ��ĵ�����һ�Ρ�����windows�ײ�����д�뻺������趨��
	// �ڵ���write֮�󣬾��Բ�Ҫֱ��read������ʵ��Ҫread������Ҫ�ȵ���FileClose�����µ���FileOpen��read�����򲻱�֤������ȷ�ԡ�
	bool WriteFile( const void * pFileData, FILE_INT nSize, FILE_INT nStart = 0 );

	// ��ȡ�ļ�
	// pFileData���ڴ�ָ�룬�ڴ��СҪ��֤����nSize
	// nStart����ȡ����ʼλ��
	// nSize����Ҫ��Ϣ��ȡ�ĳ���
	FILE_INT ReadFile( void * pFileData, FILE_INT nStart, FILE_INT nSize );

	// ��ȡ��ǰ�ļ��Ĵ�С
	// �����ļ��������򷵻�0
	FILE_INT GetFileSize();

	// ɾ���ļ�
	static bool RemoveFile( const char * str );

	// �ļ�����
	static bool ReName( const char * oldName, const char * newName );

	// ɾ���ļ���
	static void RemoveDir(const char * str);

	// ����ļ���
	static void ClearFolder(const char * path);

protected:
	void *m_pFile;
	FILE_INT m_nFileSize;	// �Ե��ֽ�char��file�ĳ���
	bool m_bOpen;
};


#endif
