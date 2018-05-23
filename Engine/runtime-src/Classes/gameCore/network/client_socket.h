#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_

#define TAG_VALUE 0xCCEE		   //默认的包的开头的2个字节
#define HEAD_SUM 0x765D //默认的头部的CRC的值

#include "base_socket.h"
#include "net_buf.h"
#include "net_packet_pool.h"
#include "utils/encrypt/CRC.h"
#include "utils/encrypt/Encrypt.h"
#include "helpers/XLambda.h"

class SocketDelegateProtocol;

// 游戏中与服务器通信的类，负责网络的连接，crc验证，发送与接收数据等
class ClientSocket : public BaseSocket, public NetPacketPool
{
	static const int RECV_BUFFER_SIZE	 = 64 * 1024;
	static const int PROCESS_BUFFER_SIZE = 64 * 1024;
	static const int SEND_BUFFER_SIZE	 = 16 * 1024;
	// 网络状态
	enum Net_Status
	{
		NS_CONNECT = 1,			// 未连接状态
		//NS_POLICY_SEND,		// 发送flash认证，在本项目无用
		//NS_POLICY_WAIT,
		NS_ENCRYREQ,			// 发送加密crc请求到服务器
		NS_ENCRYACK,			// 服务器返回crc
		NS_COMMU,				// 正常通信状态, 在正常通信状态前，收到的网络包都由本组件处理，不会传到游戏逻辑

		
		NS_LOGIN_SERVER_READY,
	};
	// removed by Shan Lu 2015/01/12 Begin
	/*struct NetBuf
	{
		int size_;
		int max_size_;
		char* buf_;
		NetBuf()
		{
			size_ = 0;
			max_size_ = 0;
			buf_ = NULL;
		}
	};*/
	// removed by Shan Lu 2015/01/12 End
#pragma pack(push,4)
	typedef struct
	{
		uint16_t tag;
		uint16_t len;
		struct 
		{
			uint16_t dataSum;
			uint16_t hdrSum;
		} EncodePart;
	}DATAHEADER,*PDATAHEADER;

#pragma pack(pop)

	// added by aXing on 2015-5-19
	// 写一个新的网络包定义
	enum Pack_Status
	{
		PS_IDLE = 0					// 待机状态
	};

#pragma pack(push,4)
	typedef struct
	{
		// edited by aXing on 2015-5-26
		// 个人认为应该是服务器改的
		// 服务器做法是读取一个uint32，然后通过位移读取高低位，而不是直接定义两个uint16的类型。
		// 先用一个uint32做算了。
		//		uint16_t tag;
		uint32_t len;
	}DATAHEADER_N, *PDATAHEADER_N;
#pragma pack(pop)


public:
	ClientSocket();
	~ClientSocket();
	
	// 设置服务器ip和端口
	inline void SetHost(const char* host, int port)
	{
		_STRNCPY_A(m_host, host);
		m_port = port;
	}

	// 开始连接
	int ConnectSrv(bool bSendTGW);

	// 网络断开或者连接成功触发的事件
	virtual void OnConnected();
	virtual void OnDisconnected();

	// 游戏每一帧要执行的代码
	void LogicRun();

	// 获取一个网络包实例，可以往里面写数据
	// sysid和protoid分别是协议号
	// 注意，这里返回的NetPacket是个静态变量，所以，alloc和SendToSrv必须对应存在，且只能单线程使用
	NetPacket* alloc(int sysId = -1, int protoId = -1);

	// 发送网络包到服务器
	int SendToSrv(NetPacket* pack);

	// 发送一个无参数网络包到服务器
	int SendCmdToSrv(int sysId, int protoId);

	void setCallback(XLambda* uLuaHandle);

protected:
	virtual void OnError(int errorOp, int errorCode);

private:
	void SendSalt();
	void SendKeyCrc(int salt);	

	// 与服务器成功建立连接后触发
	void OnCommuSucc();

	int  Recv();

	void ProcessNetMsg();
	int  ProceNetMsg(const char* buf, int size);
	int  UnPacket(const char* src, int src_size, char* dst, int max_size, int& data_size, DATAHEADER** out_hdr);

protected:
	virtual bool onExecuteRecvNetPacket(NetPacket* pkNetPacket);
private:
	// added by Shan Lu 2015/01/14 Begin
	// 跳出逻辑循环的条件
	// 未连接或者不在通信状态
	bool exitProcessPacketLoop();

	// added by Shan Lu 2015/01/14 End

	// 加密组件
	Encrypt	m_coder;
	int m_salt;
	// 连接到的目的服务器和端口，支持域名
	char m_host[256];
	int m_port;

	int m_status;	// 网络组件的状态

	NetBuf	m_buf;
	bool	m_bSendTGW;

	SocketDelegateProtocol* m_pkEventHandler;
};

#endif

