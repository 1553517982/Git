#ifndef _NET_PACKET_H_
#define _NET_PACKET_H_
#include "../common/data_packet.h"
#include "cocos2d.h"
USING_NS_CC;

class NetPacket : public Ref, public DataPacket
{
public:
	enum NetPacketType
	{
		eIdle,
		eRecv,
		eSend
	};
protected:

	NetPacket()
		: DataPacket()
	{

	}

	NetPacket(void* buf, size_t size)
		: DataPacket(buf, size)
	{

	}
	NetPacket(BaseAllocator* allocator)
		: DataPacket(allocator)
	{
	}

public:
	~NetPacket()
	{

	}

	static NetPacket* create(BaseAllocator* allocator);

	// add by 启亮，为了兼容不需要网络池而使用的二进制编写内存方式
	static NetPacket* create();

	const char* readString();
	std::string readStringInBuff();			// 因为某些json文件要用到
	std::string readStringInSpecifyLength(unsigned int nLength);
	NetPacket * readPackForGivenLength( unsigned int nLength );
	unsigned char readByte();
	char readChar();
	unsigned short  readWord();
	short readShort();
	int readInt();
	unsigned int readUInt();	
	double readFloat(); 
	double readDouble();


	void writeByte(unsigned char btValue);   
	void writeChar(char cValue);   
	void writeWord(unsigned short wValue); 
	void writeShort(short wValue);  
	void writeInt(int nValue); 
	void writeUInt(unsigned int  uValue);	
	void writeFloat(float value); 
	void writeDouble(double value);
	UINT64 readUint64();
	INT64 readInt64();
	void writeUint64(UINT64 value);
	void writeInt64(INT64 value);
	void writeString(const char *str);
	void writeStringInGivenLength(const char *str, unsigned int nLength);
	void writePack(NetPacket * p);

	unsigned int getPacketSize();
	unsigned char getType() const { return m_ucType; }
	void setType(unsigned char val) { m_ucType = val; }
private:
    const char* readUint64String();
    const char* readInt64String();
	void writeUint64String(const char* uint64string);
	void writeInt64String(const char* int64string);
	unsigned char		m_ucType;

};
#endif