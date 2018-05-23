#include "XImageSet.h"
#include "XCommon.h"

//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
//copy整个文件
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End

const unsigned int MagicNumber = 0xfff2;
const unsigned int FileVersion = 3;

XImageSet::XImageSet(void) :
	m_pImageUnits(NULL),
	m_unImageUnitCount(0)
{
	memset(m_szTextureName,0,sizeof(m_szTextureName));
}


XImageSet::~XImageSet(void)
{
	if(m_pImageUnits)
		delete [] m_pImageUnits;

	//m_pImageUnits = NULL;
	//m_unImageUnitCount = 0;
}

bool XImageSet :: Initialize(const char* szImageSetName, unsigned int unCount )
{
	
	if(strlen(szImageSetName) >= XBINARY_RESERZE_MAX_SIZE)
		return false;
	//设置头文件
	strncpy(m_kFileHeader.szReserze,szImageSetName,XBINARY_RESERZE_MAX_SIZE - 1);
	m_kFileHeader.unFileType = X_FILE_IMAGESET;
	m_kFileHeader.unFileVersion = FileVersion;
	m_kFileHeader.unItemCount = unCount;


	strncpy(m_szTextureName,szImageSetName,XBINARY_RESERZE_MAX_SIZE - 1);
	//设置数量
	m_unImageUnitCount = unCount;
	if(m_pImageUnits)
		delete [] m_pImageUnits;
	m_pImageUnits = new XImageUnit[m_unImageUnitCount];

	return true;
}

bool XImageSet :: Set(XImageUnit* pkData, unsigned int i)
{
	XAssert(m_pImageUnits,"error");
	XAssert(i < m_unImageUnitCount, "error");
	if(m_pImageUnits && i < m_unImageUnitCount)
	{
		memcpy(&m_pImageUnits[i],pkData,sizeof(XImageUnit));
		m_pImageUnits[i].textureName = NULL;
		return true;
	}
	else
	{
		return false;
	}

}

bool XImageSet :: Read(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap)
{
//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
#if defined(XIMAGEUNIT_SLOW__READ)
	return ReadSlow(pkBuffer,uBufferSize,pkMap);
#endif
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End

	if(m_pImageUnits)
		return false;

	unsigned char* pkReader = (unsigned char*)pkBuffer;
	unsigned int nOffset = 0;
	unsigned int uReadMagic = 0;
	unsigned int nByteToRead = sizeof(m_kFileHeader);

	//读取头
	memcpy(&m_kFileHeader,pkBuffer,nByteToRead);
	strncpy(m_szTextureName,m_kFileHeader.szReserze,XBINARY_FILENAME_MAX_SIZE - 1);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	if(m_kFileHeader.unFileType != X_FILE_IMAGESET)
		return false;

	XAssert(m_kFileHeader.unFileVersion == FileVersion, "wrong file ver");
	if(m_kFileHeader.unFileVersion != FileVersion)
		return false;

	//有多少个ImageUnit
	m_unImageUnitCount = m_kFileHeader.unItemCount;
	m_pImageUnits = new XImageUnit[m_unImageUnitCount];
	nByteToRead = m_unImageUnitCount * sizeof(XImageUnit);
	memcpy(m_pImageUnits,pkReader, nByteToRead);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	//检查魔法数字
	nByteToRead = sizeof(MagicNumber);
	memcpy(&uReadMagic,pkReader,nByteToRead);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	XAssert(uReadMagic == MagicNumber,"wrong magic number");
	XAssert(nOffset == uBufferSize,"wrong size");

	//填充数据
	for(unsigned int i=0;i<m_unImageUnitCount;i++)
	{
		XImageUnit* pkData = &m_pImageUnits[i];
		pkData->textureName = m_szTextureName;
		if(pkMap)
		{
			XAssert(pkMap->find(pkData->imageName) == pkMap->end(),"already in");
			pkMap->insert(std::make_pair(pkData->imageName,pkData));
		}
	}
	return true;
}

bool XImageSet :: Save(const char* pFileName)
{
	if(!m_pImageUnits)
		return false;

	FILE* pFileOut =  fopen(pFileName,"wb+");
	if(!pFileOut)
		return false;

	strncpy(m_kFileHeader.szReserze,m_szTextureName,XBINARY_FILENAME_MAX_SIZE - 1);

	fwrite(&m_kFileHeader,sizeof(XBinaryHeader),1,pFileOut);
	fwrite(&m_pImageUnits[0],sizeof(XImageUnit),m_unImageUnitCount,pFileOut);
	fwrite(&MagicNumber,sizeof(MagicNumber),1,pFileOut);

	unsigned int uExpectFileSize = (sizeof(XBinaryHeader) + sizeof(XImageUnit) * m_unImageUnitCount) + sizeof(MagicNumber);
	unsigned int uFileSize = ftell(pFileOut);
	XAssert(uFileSize == uExpectFileSize,"error");
	fclose(pFileOut);
	return true;
}

bool XImageSet :: Load(const char* pFileName, XImageUnitMap* pkMap)
{
	FILE * pFile;
	int lSize;
	char * buffer;
	size_t result;

	pFile = fopen ( pFileName , "rb" );
	if (pFile==NULL) 
	{
		return false;
	}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) 
	{
		fclose(pFile);
		return false;
	}

	// copy the file into the buffer:
	result = fread (buffer,1,lSize,pFile);
	if (result != lSize) {
		fclose(pFile);
		return false;
	}

	/* the whole file is now loaded in the memory buffer. */
	Read(buffer,lSize,pkMap);
	// terminate
	fclose (pFile);
	free (buffer);
	return true;
}

//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
#if defined(XIMAGEUNIT_SLOW__READ)
#define _READ_BUFFER(dst, buffer, size, offset)	\
	memcpy(dst,buffer, size);					\
	buffer += size;								\
	offset += size;								

#define _SKIP_BUFFER(buffer,size, offset)		\
	buffer += size;								\
	offset += size;		

//读取数据然后将数据返回到一个查找列表
bool XImageSet::ReadSlow(void* pkBuffer, unsigned int uBufferSize, XImageUnitMap* pkMap )
{
	if(m_pImageUnits)
		return false;
	
	if(!CreateFromBufferSlow(pkBuffer,uBufferSize))
		return false;

	//填充数据
	for(unsigned int i=0;i<m_unImageUnitCount;i++)
	{
		XImageUnit* pkData = &m_pImageUnits[i];
		pkData->textureName = m_szTextureName;
		if(pkMap)
		{
			XAssert(pkMap->find(pkData->imageName) == pkMap->end(),"already found");
			pkMap->insert(std::make_pair(pkData->imageName,pkData));
		}
	}
	return true;
}

bool XImageSet::CreateFromBufferSlow(void* pkBuffer, int uBufferSize)
{
	unsigned char* pkReader = (unsigned char*)pkBuffer;
	unsigned int nOffset = 0;
	unsigned int uReadMagic = 0;
	unsigned int nByteToRead = sizeof(m_kFileHeader);

	_READ_BUFFER(&(m_kFileHeader.unFileType),pkReader,2,nOffset);
	_READ_BUFFER(&(m_kFileHeader.unFileVersion),pkReader,2,nOffset);
	_READ_BUFFER(&(m_kFileHeader.unItemCount),pkReader,4,nOffset);
	_READ_BUFFER(&(m_kFileHeader.szReserze),pkReader,XBINARY_RESERZE_MAX_SIZE,nOffset);
	strncpy(m_szTextureName,m_kFileHeader.szReserze,XBINARY_RESERZE_MAX_SIZE - 1);

	if(m_kFileHeader.unFileType != X_FILE_IMAGESET)
		return false;

	XAssert(m_kFileHeader.unFileVersion == FileVersion,"wrong file ver");
	if(m_kFileHeader.unFileVersion != FileVersion)
		return false;

	//有多少个ImageUnit
	m_unImageUnitCount = m_kFileHeader.unItemCount;
	m_pImageUnits = new XImageUnit[m_unImageUnitCount];

	for(unsigned int i=0;i<m_unImageUnitCount; i++)
	{
		XImageUnit& pkUnit = m_pImageUnits[i];
		_READ_BUFFER(&(pkUnit.x),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.y),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.width),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.height),pkReader,2,nOffset);
		_SKIP_BUFFER(pkReader,4,nOffset);
		_READ_BUFFER(&(pkUnit.imageName),pkReader,XBINARY_FILENAME_MAX_SIZE,nOffset);
		_READ_BUFFER(&(pkUnit.rotation),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.offsetX),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.offsetY),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.sourceSizeX),pkReader,2,nOffset);
		_READ_BUFFER(&(pkUnit.sourceSizeY),pkReader,2,nOffset);
		_SKIP_BUFFER(pkReader,2,nOffset);
	}

	//检查魔法数字
	nByteToRead = sizeof(MagicNumber);
	memcpy(&uReadMagic,pkReader,nByteToRead);
	pkReader += nByteToRead;
	nOffset += nByteToRead;

	XAssert(uReadMagic == MagicNumber,"wrong magic number");
	XAssert(nOffset == uBufferSize,"wrong size");
	return true;
}
#endif
//MOD_FOR_64BIT by Shan Lu 2015-01-10 End
static std::map<std::string, int> _s_nameToIndexCache;

int XImageSet::nameToIndex(const char* szName)
{
	auto it = _s_nameToIndexCache.find(szName);
	if (it != _s_nameToIndexCache.end())
	{
		return it->second;
	}

	std::string id = szName;
	size_t nEnd = id.find_last_of(".");
	size_t nBegin = id.find_last_of("/");
	if (nEnd == std::string::npos || nBegin == std::string::npos)
	{
		XAssert(false, "nameToIndex error find path");
		return 0;
	}

	std::string szNumber = id.substr(nBegin + 1, nEnd - nBegin - 1);
	int nKey = -1;
	nKey = atoi(szNumber.c_str());
	XAssert(nKey >= 0, "nameToIndex error atoi");
	if (nKey < 0)
		nKey = 0;
	_s_nameToIndexCache.insert(std::make_pair(szName, nKey));
	return nKey;
}