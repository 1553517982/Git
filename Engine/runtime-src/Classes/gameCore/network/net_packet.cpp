#include "XCommon.h"
#include "net_packet.h"
#include "CommonFun.h"

// MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
// 整个文件
// MOD_FOR_64BIT by Shan Lu 2015-01-10 End

NetPacket* NetPacket::create(BaseAllocator* allocator)
{
	NetPacket* pkObject = new NetPacket(allocator);
	pkObject->setType(eIdle);
	pkObject->autorelease();
	return pkObject;
}

NetPacket* NetPacket::create()
{
	NetPacket* pkObject = new NetPacket();
	pkObject->setType(eIdle);
	pkObject->autorelease();
	return pkObject;
}

void NetPacket::writeString(const char *str)
{
	if (str == NULL)
	{
		str = "";
	}
	DataPacket::writeString(str);
}

void NetPacket::writeStringInGivenLength(const char *str, unsigned int nLength)
{
	writeBuf(str, nLength);
}

void NetPacket::writePack(NetPacket * p)
{
	writeBuf(p->getMemoryPtr(), p->getSize());
}

const char* NetPacket::readString()
{
	const char* result;
	this->operator >> (result);
	return result;
}

std::string NetPacket::readStringInBuff()
{
	if (!offset_)
		return "";

	char * pTmp = offset_;
	while (pTmp[0] && pTmp < end_ptr_)
		pTmp++;
	char * pRes = offset_;
	offset_ = pTmp + 1;		// 处理指针偏移
	if (offset_ > data_end_) 
		offset_ = data_end_; // offset不能超过data_end的范围
	return std::string(pRes, pTmp - pRes);
}

std::string NetPacket::readStringInSpecifyLength(unsigned int nLength)
{
	if (data_end_ - offset_ < nLength || 0 == nLength)
	{
		XLOGERROR("nLenght is too long or wrong, %d", nLength);
		return "";
	}
	std::string strRes(offset_, nLength);
	offset_ += nLength;
	return strRes;
} 

NetPacket * NetPacket::readPackForGivenLength(unsigned int nLength)
{
	if (data_end_ - offset_ < nLength || 0 == nLength)
	{
		XLOGERROR("nLenght is too long or wrong %d", nLength);
		return 0;
	}

	NetPacket * pNet = NetPacket::create();
	pNet->writeBuf(offset_, nLength);
	offset_ += nLength;
	return pNet;
}

unsigned char NetPacket::readByte()
{
	unsigned char bResult = 0;
	this->operator >> (bResult);
	return bResult;
}

char NetPacket::readChar()
{
	char cResult = 0;
	this->operator >> (cResult);
	return cResult;
}

unsigned short NetPacket::readWord()
{
	unsigned short wValue = 0;
	this->operator >> (wValue);
	return wValue;
}

short NetPacket::readShort()
{
	short wValue = 0;
	this->operator >> (wValue);
	return wValue;
}

int NetPacket::readInt()
{
	int nValue = 0;
	this->operator >> (nValue);
	return nValue;
}

unsigned int NetPacket::readUInt()
{
	unsigned int uValue = 0;
	this->operator >> (uValue);
	return uValue;
}

void NetPacket::writeByte(unsigned char btValue)
{
	this->operator << (btValue);
}

void NetPacket::writeChar(char cValue)
{
	this->operator << (cValue);
}

void NetPacket::writeWord(unsigned short wValue)
{
	this->operator << (wValue);
}

void NetPacket::writeShort(short wValue)
{
	this->operator << (wValue);
}

void NetPacket::writeInt(int  nValue)
{
	this->operator << (nValue);
}

void NetPacket::writeUInt(unsigned int  uValue)
{
	this->operator << (uValue);
}

double NetPacket::readFloat()
{
	float val = 0;
	this->operator >> (val);
	return val;
}
void NetPacket::writeFloat(float value)
{
	this->operator << (value);
}

double NetPacket::readDouble()
{
	double val = 0;
	this->operator >> (val);
	return val;
}

void NetPacket::writeDouble(double value)
{
	this->operator << (value);
}

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "ZXUtils.h"

UINT64 NetPacket::readUint64()
{
	UINT64 lValue = 0;
	this->operator >> (lValue);
	return lValue;
	//return this->readUint64String();

}
const char* NetPacket::readUint64String()
{
	UINT64 lValue = 0;

	this->operator >> (lValue);

	//    char s[255];
	//    sprintf(s,"0x%llx", lValue);
	//
	const char *c = commonFunction::UINT64_TO_STRING(lValue);
	return c;

}

INT64 NetPacket::readInt64()
{
	INT64 lValue = 0;
	this->operator >> (lValue);
	return lValue;
	//return this->readInt64String();
}

const char* NetPacket::readInt64String()
{
	INT64 lValue = 0;

	this->operator >> (lValue);

	//    char s[255];
	//    sprintf(s,"0x%llx", lValue);

	const char *c = commonFunction::INT64_TO_STRING(lValue);

	return c;
}

void NetPacket::writeUint64(UINT64 d)
{
	this->operator << (d);
	//this->writeUint64String(d);
}

void NetPacket::writeUint64String(const char* uint64string)
{

	UINT64 lValue = commonFunction::STRING_TO_UINT64(uint64string);
	//    sscanf(uint64string,"%llx",&lValue);
	this->operator << (lValue);
}

void NetPacket::writeInt64(INT64 d)
{
	this->operator << (d);
}
void NetPacket::writeInt64String(const char* int64string)
{
	INT64 lValue = commonFunction::STRING_TO_INT64(int64string);
	//    sscanf(int64string,"%llx",&lValue);
	this->operator << (lValue);
}

unsigned int NetPacket::getPacketSize()
{
	return getAvaliableBufLen();
}