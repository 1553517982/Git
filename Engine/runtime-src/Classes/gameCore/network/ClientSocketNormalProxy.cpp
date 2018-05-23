#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "cocos2d.h"
#include "XCommon.h"

#include "os_def.h"
#include "utils/encrypt/CRC.h"
#include "utils/encrypt/Encrypt.h"
#include "net_packet.h"
#include "base_socket.h"
#include "client_socket.h"
#include "ClientSocketNormalProxy.h"

ClientSocketNormalProxy :: ClientSocketNormalProxy()
{
	m_pSocket = new ClientSocket();
	m_bSendTGW = true;
}

ClientSocketNormalProxy :: ~ClientSocketNormalProxy()
{
	delete m_pSocket;
	m_pSocket = NULL;
}


void ClientSocketNormalProxy :: OnDisconnected()
{
	m_pSocket->OnDisconnected();
}

void ClientSocketNormalProxy :: GameTick()
{
	m_pSocket->LogicRun();
}

bool ClientSocketNormalProxy ::  connecting()
{
	return m_pSocket->connecting();
}

void ClientSocketNormalProxy::Close()
{
	m_pSocket->Close();
}

bool ClientSocketNormalProxy::connected()
{
	return m_pSocket->connected();
}

int  ClientSocketNormalProxy::ConnectSrv()
{
	return m_pSocket->ConnectSrv(m_bSendTGW);
}

void ClientSocketNormalProxy::SetHost(const char* host, int port)
{
	m_pSocket->SetHost(host,port);
}

NetPacket* ClientSocketNormalProxy::alloc(int sysId , int protoId)
{
	return m_pSocket->alloc(sysId,protoId);
}

int ClientSocketNormalProxy::SendToSrv(NetPacket* pack)
{
	return m_pSocket->SendToSrv(pack);
}

int ClientSocketNormalProxy::SendCmdToSrv(int sysId, int protoId)
{
	return m_pSocket->SendCmdToSrv(sysId,protoId);
}

void ClientSocketNormalProxy::setCallback(XLambda* uLuaHandle)
{
	return m_pSocket->setCallback(uLuaHandle);
}