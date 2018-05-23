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
		* �������ʼ����һ��������Զ��ʹ��
		* @param [in] pStreamArray Ҫ�����char*ָ��
		* @param [in] nSize���ڴ��С
		*/
		bool Init(const char * pStreamArray, uint32 nCharCount);

		/**
		* ����Read֮�󣬻�õ���Ӧ�Ľ��
		* @param [out] pResultArray ��ȡ��ָ��
		* @param [out] nSize ��ȡ�Ĵ�С
		*/
		bool GetResult(const char * & pResultArray, uint32 & nCharCount);

		/**
		* �����Ŀ�ʼ��������һ��ΪnMark���ַ�ʱͣ������
		* @param [in] nMark Ҫ�жϵ��ַ�
		*/
		bool Read(char Mark);

	protected:
		// ����Readʱ��λ�ü�¼
		uint32 m_nReadCurPos;
		uint32 m_nReadLastPos;

		// ��¼�ⲿ�����ָ�뼰��С�������ⲿҪȷ��ָ�뼰��С��ȷ
		const char * m_pExternStream;
		uint32 m_nExternTCharCount;
		// �Ƿ��ʼ����
		bool m_bInit;
	};

public:
	CTableFile();
	~CTableFile();

	/**
	 * ָ���ļ���ֻ��֧��2G�����ļ�
	 * @param strPath �ļ�·��
	 * @return true���ļ������򿪣�false���ļ���ʧ��
	 */
	//bool LoadTableFile(CMString strPath);

	/**
	 * �����ڴ����
	 * @param buff �ڴ�
	 * @return true�������򿪣������ʧ��
	 */
	bool LoadTableBuff(const char* contentStr, uint32 nLength);

	/**
	 * ��ȡ�ļ���Ϣ
	 * @param nRow ��
	 * @param nColumn ��
	 * @param nDefault Ĭ��
	 * @return ��ȡ������ֵ
	 */
	int32 GetInteger(uint32 nRow, uint32 nColumn, int32 nDefault = 0);

	/**
	 * ��ȡ�ļ���Ϣ
	 * @param nRow ��
	 * @param nColumn ��
	 * @return ��ȡ���ַ���
	 */
	string GetString(uint32 nRow, uint32 nColumn);

	/**
	 * ��ȡ�ļ���Ϣ
	 * @param nRow ��
	 * @param nColumn ��
	 * @
	 * @return ��ȡ�ĸ���ֵ
	 */
	float GetReal(uint32 nRow, uint32 nColumn, float rDefault = 0.0);

	/**
	 * ��ȡ����
	 * @return ����
	 */
	uint32 GetHeight();

	/**
	 * ��ȡ����
	 * @return ����
	 */
	uint32 GetWidth();

	/**
	 * ��ձ��
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