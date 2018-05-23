#ifndef _CLIENT_ClientSocketInterfaceNormal_H_
#define _CLIENT_ClientSocketInterfaceNormal_H_
#include "ClientSocketProxy.h"
#include <helpers/XLambda.h>

class ClientSocket;

class ClientSocketNormalProxy : public ClientSocketProxy
{
	public:
		ClientSocketNormalProxy();

		virtual ~ClientSocketNormalProxy();

		//script export
		virtual void Close();
		virtual bool connected();
		virtual int  ConnectSrv();
		virtual void SetHost(const char* host, int port);
		virtual NetPacket* alloc(int sysId = -1, int protoId = -1);
		virtual int SendToSrv(NetPacket* pack);
		virtual int SendCmdToSrv(int sysId, int protoId);

		virtual void OnDisconnected();
		virtual void GameTick();
		virtual bool connecting();

		virtual void setCallback(XLambda* uLuaHandle);

	private:
		ClientSocket* m_pSocket;
};

#endif

