#ifndef _CLIENT_ClientSocketProxy_H_
#define _CLIENT_ClientSocketProxy_H_
#include <string>
#include <helpers/XLambda.h>


class ClientSocket;
// 游戏中与服务器通信的类，负责网络的连接，crc验证，发送与接收数据等
class NetPacket;

class ClientSocketProxy
{
	public:
		ClientSocketProxy() : 
		  m_strOsVerision(""),
		  m_nNetType(-1),
		  m_nISP(-1),
		  m_nTimeout(30),
		  m_bSendTGW(true)
		{

		}

		virtual ~ClientSocketProxy()
		{

		}
		//script export
		virtual void Close() = 0;
		virtual bool connected() = 0;
		virtual int  ConnectSrv() = 0;
		virtual void SetHost(const char* host, int port) = 0;
		virtual NetPacket* alloc(int sysId = -1, int protoId = -1) = 0;
		virtual int SendToSrv(NetPacket* pack) = 0;
		virtual int SendCmdToSrv(int sysId, int protoId) = 0;

		//gameEngine
		virtual void OnDisconnected() = 0;
		virtual void GameTick() = 0;
		virtual bool connecting() = 0; //是否初始化了
		
		//设置回调方法
		virtual void setCallback(XLambda* uLuaHandle) = 0;
		// 实在不想写虚函数了
		//QCloud
		void	SetOSVersion(const char* osVerision)
		{
			m_strOsVerision = osVerision;
		}

		void	SetParams(int nNetType, int nISP, int nTimeout = 30, bool bSendTGW = true)
		{
			m_nNetType = nNetType;
			m_nISP = nISP;
			m_nTimeout = nTimeout;
			m_bSendTGW = bSendTGW;
		}

		// 初始化第一个socket
		static int initSocket1(unsigned char type, const char* pszOSVer, const char* pszInstallPath);

		// 获得第一个socket
		static ClientSocketProxy* getSocket1();

		// 初始化第一个socket
		static int initSocket2(unsigned char type, const char* pszOSVer, const char* pszInstallPath);

		// 获得第二个socket
		static ClientSocketProxy* getSocket2();

		static ClientSocketProxy* ToCS(void* cs);

		
	
	protected:
		std::string		m_strOsVerision;
		int				m_nNetType;
		int				m_nISP;
		int				m_nTimeout;
		bool			m_bSendTGW;
	    XLambda*        m_callback;

};

#endif

