#include "SocketDelegateProtocol.h"
#include "cocos2d.h"
#include "net_packet.h"

USING_NS_CC;
SocketDelegateProtocolScript :: SocketDelegateProtocolScript() :
	m_Lambda(0)
{

}

SocketDelegateProtocolScript::~SocketDelegateProtocolScript()
{
	if (m_Lambda)
	{
		m_Lambda->cleanup();
	}
	CC_SAFE_RELEASE(m_Lambda);
}

void SocketDelegateProtocolScript::onCommuSucc()
{
	if (m_Lambda)
	{
		m_Lambda->begin();
		m_Lambda->pushInt(eOnCommuSucc);
		m_Lambda->invoke();
	}
}

void SocketDelegateProtocolScript::onRecv(NetPacket* pkPacket)
{
	pkPacket->setPosition(0);
	//int32_t uid = pkPacket->readInt();					// 江湖里面删掉，因为要与斩先的一样
	unsigned char sysid = pkPacket->readByte();
	unsigned char pid = pkPacket->readByte();
	unsigned int data_size = pkPacket->getLength();

	if (m_Lambda)
	{
		m_Lambda->begin();
		m_Lambda->pushInt(eOnRecv);	// 区分socket
		m_Lambda->pushObject(pkPacket, "NetPacket");
		//m_Lambda->pushInt(uid);
		m_Lambda->pushInt(sysid);
		m_Lambda->pushInt(pid);
		m_Lambda->pushInt(data_size);
		m_Lambda->invoke();
	}
}

void SocketDelegateProtocolScript::onSocketError(int code)
{
	if (m_Lambda)
	{
		m_Lambda->begin();
		m_Lambda->pushInt(eOnSocketError);
		m_Lambda->pushInt(code);
		m_Lambda->invoke();
	}
}

void SocketDelegateProtocolScript::onSocketError(const char* szCode)
{
	if (m_Lambda)
	{
		m_Lambda->begin();
		m_Lambda->pushInt(eOnSocketError);
		m_Lambda->pushString(szCode);
		m_Lambda->invoke();
	}
}
