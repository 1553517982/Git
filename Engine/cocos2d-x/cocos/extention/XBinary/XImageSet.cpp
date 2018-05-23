#include "extention/XBinary/XImageSet.h"
const unsigned int MagicNumber = 0xfff2;
const unsigned int FileVersion = 7;	// 这个版本号是我自己加上去的，没有实质用途
NS_CC_BEGIN
std::string ReadString(const char * pBuff)
{
	int index = 0;
	while (pBuff[index])
		index++;
	return std::string(pBuff, index);
}

XImageSet::XImageSet(void)
	:m_pImageUnits(NULL)
{
}


XImageSet::~XImageSet(void)
{
}


bool XImageSet::Read(void* pkBuffer, unsigned int uBufferSize)
{
	//////////////////////////////////////////////////////////////////////////
	// 
	// 直接改成读取二进制的
	// 头部
	//WriteFile(newFile, nType, nOffiset);
	//WriteFile(newFile, path, nOffiset);
	//WriteFile(newFile, fileName, nOffiset);
#pragma pack(push,1)
	struct SBaseData
	{
		unsigned short x, y, width, height;
		short offsetX, offsetY;
		unsigned short sourceSizeX, sourceSizeY;
		bool bRotate;
	};
#pragma pack(pop)

#define _JHREAD_BUFFER( dstType, charBuf, offiset ) \
	memcpy( &dstType, charBuf + offiset, sizeof( dstType ) ); \
	offiset += sizeof( dstType );

	std::string path, fileName;
	char * pBuf = (char *)pkBuffer;
	int nOffiset = 0;

	char nType = 0;
	_JHREAD_BUFFER(nType, pBuf, nOffiset);
	//m_kFileHeader.unFileType = nType;
	path = ReadString(pBuf + nOffiset); nOffiset += path.length() + 1;
	fileName = ReadString(pBuf + nOffiset); nOffiset += fileName.length() + 1;
	m_textureName = path + fileName;

	unsigned short nSize = 0;
	_JHREAD_BUFFER(nSize, pBuf, nOffiset);
	unsigned int nOriginalSize = m_pImageUnits.size();
	m_pImageUnits.resize(nOriginalSize + nSize);
	SBaseData tmp;
	for (unsigned short i = nOriginalSize; i < m_pImageUnits.size(); i++)
	{
		std::string imgName = ReadString(pBuf + nOffiset); nOffiset += imgName.length() + 1;
		XImageUnit& imgUnit = m_pImageUnits[i];
		strncpy(imgUnit.textureName, m_textureName.c_str(), XBINARY_FILENAME_MAX_SIZE - 1);
		strncpy(imgUnit.imageName, (path + imgName).c_str(), XBINARY_FILENAME_MAX_SIZE - 1);
		_JHREAD_BUFFER(tmp, pBuf, nOffiset);
		// 不想外面那个类做内存对其（因为处理的地方对齐了反而不好搞），所以这里赋值
		imgUnit.x = tmp.x;
		imgUnit.y = tmp.y;
		imgUnit.width = tmp.width;
		imgUnit.height = tmp.height;
		imgUnit.sourceSizeX = tmp.sourceSizeX;
		imgUnit.sourceSizeY = tmp.sourceSizeY;
		imgUnit.offsetX = tmp.offsetX;
		imgUnit.offsetY = tmp.offsetY;
		imgUnit.rotation = tmp.bRotate;
	}
	//////////////////////////////////////////////////////////////////////////
	return true;
}

XImageUnitList * XImageSet::GetImageUnitList()
{
	return &m_pImageUnits;
}

NS_CC_END