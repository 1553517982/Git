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


	//----- 初始化完成
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

	// 没找到，把最后的一段发出来，所以同样return true
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
//	pFile->PReadFile(&buff[0], 0, buff.GetSize());	// 整个文件读出来。
//
//	// 然后判断是否为压缩文件
//	if (nSize > 4 && 0 == memcmp(COMPRESS_FILE_HEAD, &buff[0], 4))
//		buff = Uncompress(buff);	// 解压
//
//	// 坑爹的excel，后面会带一串00000000的。所以不能不这么做了
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
 * 获取文件信息
 * @param nRow 行
 * @param nColumn 列
 * @return 获取的字符串
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
	// 根据\t、\r、\r\n等分解文件
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

			if (pArray[nArraySize - 1] == '\n')		// 非尾部，因为nArraySize肯定不为0，否则if就会返回false
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
					// 防止有\r出现
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
