#ifndef _C_MIGHT_TABLE_FILE_H_
#define _C_MIGHT_TABLE_FILE_H_

#include "platform/CCPlatformMacros.h"
#include <string>
#include <vector>
using namespace std;

NS_CC_BEGIN

class CC_DLL CTableFile
{
public:
	typedef unsigned int uint32;
	typedef int int32;
private:
	class CMStreamAssistant
	{
	public:
		CMStreamAssistant();
		virtual ~CMStreamAssistant();

		/**
		* 助手类初始化，一个对象可以多次使用
		* @param [in] pStreamArray 要处理的char*指针
		* @param [in] nSize，内存大小
		*/
		bool Init(const char * pStreamArray, uint32 nCharCount);

		/**
		* 调用Read之后，会得到相应的结果
		* @param [out] pResultArray 获取的指针
		* @param [out] nSize 获取的大小
		*/
		bool GetResult(const char * & pResultArray, uint32 & nCharCount);

		/**
		* 从流的开始，当遇到一个为nMark的字符时停下来。
		* @param [in] nMark 要判断的字符
		*/
		bool Read(char Mark);

	protected:
		// 调用Read时的位置记录
		uint32 m_nReadCurPos;
		uint32 m_nReadLastPos;

		// 记录外部传入的指针及大小，所以外部要确保指针及大小正确
		const char * m_pExternStream;
		uint32 m_nExternTCharCount;
		// 是否初始化了
		bool m_bInit;
	};

public:
	CTableFile();
	~CTableFile();

	/**
	 * 指定文件，只能支持2G以下文件
	 * @param strPath 文件路径
	 * @return true则文件正常打开，false则文件打开失败
	 */
	//bool LoadTableFile(CMString strPath);

	/**
	 * 调用内存加载
	 * @param buff 内存
	 * @return true则正常打开，否则打开失败
	 */
	bool LoadTableBuff(const char* contentStr, uint32 nLength);

	/**
	 * 获取文件信息
	 * @param nRow 行
	 * @param nColumn 列
	 * @param nDefault 默认
	 * @return 获取的整数值
	 */
	int32 GetInteger(uint32 nRow, uint32 nColumn, int32 nDefault = 0);

	/**
	 * 获取文件信息
	 * @param nRow 行
	 * @param nColumn 列
	 * @return 获取的字符串
	 */
	string GetString(uint32 nRow, uint32 nColumn);

	/**
	 * 获取文件信息
	 * @param nRow 行
	 * @param nColumn 列
	 * @
	 * @return 获取的浮点值
	 */
	float GetReal(uint32 nRow, uint32 nColumn, float rDefault = 0.0);

	/**
	 * 获取行数
	 * @return 行数
	 */
	uint32 GetHeight();

	/**
	 * 获取列数
	 * @return 列数
	 */
	uint32 GetWidth();

	/**
	 * 清空表格
	 */
	void Clear();

protected:
	bool LoadTableBuffInter();

	typedef std::vector< string > VecString;
	typedef std::vector< VecString > GroupString;

	GroupString m_vecGroup;

	const char * m_pCurData;
	uint32 m_nCurSize;
protected:
	uint32 m_nMaxWidth;
};

NS_CC_END

#endif