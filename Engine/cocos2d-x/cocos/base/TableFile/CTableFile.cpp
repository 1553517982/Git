#include "base/TableFile/CTableFile.h"
#include <stdlib.h>

NS_CC_BEGIN

CTableFile::CMStreamAssistant::CMStreamAssistant()
	: m_bInit(false)
	, m_nReadCurPos(0)
	, m_nReadLastPos(0)
{
}

CTableFile::CMStreamAssistant::~CMStreamAssistant()	{ }

bool CTableFile::CMStreamAssistant::Init(const char * pStreamArray, uint32 nCharCount)
{
	if (0 == pStreamArray || 0 == nCharCount)
		return false;

	m_pExternStream = pStreamArray;
	m_nExternTCharCount = nCharCount;


	//----- ��ʼ�����
	m_bInit = true;
	m_nReadCurPos = 0;
	return true;
}

bool CTableFile::CMStreamAssistant::Read(char nMark)
{
	if (!m_bInit)
		return false;

	if (m_nReadCurPos >= m_nExternTCharCount)
		return false;

	for (uint32 i = m_nReadCurPos; i < m_nExternTCharCount; i++)
	{
		if (m_pExternStream[i] == nMark)
		{
			m_nReadLastPos = m_nReadCurPos;
			m_nReadCurPos = i + 1;
			return true;
		}
	}

	// û�ҵ���������һ�η�����������ͬ��return true
	m_nReadLastPos = m_nReadCurPos;
	m_nReadCurPos = m_nExternTCharCount;
	return true;

}

bool CTableFile::CMStreamAssistant::GetResult(const char * & pResultArray, uint32 & nCharCount)
{
	if (!m_bInit)
		return false;
	if (m_nReadCurPos <= m_nReadLastPos)
		return false;
	if (m_nReadCurPos > m_nExternTCharCount + 1)
		return false;
	if (m_nReadLastPos > m_nExternTCharCount)
		return false;

	nCharCount = m_nReadCurPos - m_nReadLastPos;

	pResultArray = &(m_pExternStream[m_nReadLastPos]);
	return true;
}


CTableFile::CTableFile()
	:m_nMaxWidth(0)
{
}

CTableFile::~CTableFile()
{
	Clear();
}

//bool CTableFile::LoadTableFile(string strPath)
//{
//	if (0 == strPath.GetLength())
//		return false;
//
//	AptiIMightFile pFile = IMightFile::CreateInstance();
//	if (!pFile)
//		return false;
//
//	if (!pFile->PFileOpen(strPath))
//		return false;
//
//	uint32 nSize = pFile->PGetFileSize();
//	if (nSize == 0)
//		return false;
//
//	StreamBuff buff;
//	buff.New(nSize / sizeof(TChar));
//
//	pFile->PReadFile(&buff[0], 0, buff.GetSize());	// �����ļ���������
//
//	// Ȼ���ж��Ƿ�Ϊѹ���ļ�
//	if (nSize > 4 && 0 == memcmp(COMPRESS_FILE_HEAD, &buff[0], 4))
//		buff = Uncompress(buff);	// ��ѹ
//
//	// �ӵ���excel��������һ��00000000�ġ����Բ��ܲ���ô����
//	for (uint32 i = nSize - 1; i > 0; i--)
//	{
//		if (buff[i] != 0)
//			break;
//		nSize--;
//	}
//
//	pFile->PFileClose();
//
//	return LoadTableBuffInter((TChar*)&buff[0], nSize);
//}

bool CTableFile::LoadTableBuff(const char* contentStr, uint32 nLength)
{
	for (uint32 i = nLength - 1; i > 0; i--)
	{
		if (contentStr[i] != 0)
			break;
		nLength--;
	}
	m_nCurSize = nLength;
	m_pCurData = contentStr;
	return LoadTableBuffInter();
}

CTableFile::uint32 CTableFile::GetHeight()
{
	return (uint32)m_vecGroup.size();
}

CTableFile::uint32 CTableFile::GetWidth()
{
	return m_nMaxWidth;
}

/**
 * ��ȡ�ļ���Ϣ
 * @param nRow ��
 * @param nColumn ��
 * @return ��ȡ���ַ���
 */
string CTableFile::GetString(uint32 nRow, uint32 nColumn)
{
	uint32 nHeight = GetHeight();
	if (nRow >= nHeight)
	{
		return "";
	}

	const VecString & vecChildString = m_vecGroup[nRow];

	if (nColumn >= vecChildString.size())
	{
		return "";
	}

	return vecChildString[nColumn];
}

CTableFile::int32 CTableFile::GetInteger(uint32 nRow, uint32 nColumn, int32 nDefault)
{
	uint32 nHeight = GetHeight();
	if (nRow >= nHeight)
	{
		return nDefault;
	}

	const VecString & vecChildString = m_vecGroup[nRow];

	if (nColumn >= vecChildString.size())
	{
		return nDefault;
	}

	return atoi( vecChildString[nColumn].c_str() );
}

float CTableFile::GetReal(uint32 nRow, uint32 nColumn, float rDefault)
{
	uint32 nHeight = GetHeight();
	if (nRow >= nHeight)
	{
		return rDefault;
	}

	const VecString & vecChildString = m_vecGroup[nRow];

	if (nColumn >= vecChildString.size())
	{
		return rDefault;
	}

	return atof( vecChildString[nColumn].c_str());
}

void CTableFile::Clear()
{
	m_vecGroup.clear();
}

bool CTableFile::LoadTableBuffInter()
{
	Clear();
	// ����\t��\r��\r\n�ȷֽ��ļ�
	//CMStreamAssistant LineObj;
	//LineObj.Init(pFileData, nSize);
	CMStreamAssistant LineObj;
	LineObj.Init(m_pCurData, m_nCurSize);
	while (LineObj.Read('\n'))
	{
		const char * pArray;
		uint32 nArraySize = 0;
		if (LineObj.GetResult(pArray, nArraySize))
		{
			VecString vecString;
			CMStreamAssistant tableObj;

			if (pArray[nArraySize - 1] == '\n')		// ��β������ΪnArraySize�϶���Ϊ0������if�ͻ᷵��false
				nArraySize--;

			tableObj.Init(pArray, nArraySize);
			while (tableObj.Read('\t'))
			{
				const char * pStrArray;
				uint32 nStrArray = 0;
				if (tableObj.GetResult(pStrArray, nStrArray))
				{
					if (pStrArray[nStrArray - 1] == '\t')
						nStrArray--;

					string str(pStrArray, nStrArray);
					// ��ֹ��\r����
					int32 n = str.find_first_of('\r');
					if (n != -1)
						str.replace(n, 1, "");
					vecString.push_back(str);
				}
			}

			if (0 != vecString.size())
				m_vecGroup.push_back(vecString);
		}
	}

	m_nMaxWidth = 0;
	for (GroupString::iterator i = m_vecGroup.begin(); i != m_vecGroup.end(); i++)
	{
		if ((uint32)i->size() > m_nMaxWidth)
			m_nMaxWidth = (uint32)i->size();
	}
	if (1 == m_vecGroup.size() || m_nMaxWidth == 1)
		return false;
	return true;
}

NS_CC_END
