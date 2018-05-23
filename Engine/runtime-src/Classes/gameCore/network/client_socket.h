#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_

#define TAG_VALUE 0xCCEE		   //Ĭ�ϵİ��Ŀ�ͷ��2���ֽ�
#define HEAD_SUM 0x765D //Ĭ�ϵ�ͷ����CRC��ֵ

#include "base_socket.h"
#include "net_buf.h"
#include "net_packet_pool.h"
#include "utils/encrypt/CRC.h"
#include "utils/encrypt/Encrypt.h"
#include "helpers/XLambda.h"

class SocketDelegateProtocol;

// ��Ϸ���������ͨ�ŵ��࣬������������ӣ�crc��֤��������������ݵ�
class ClientSocket : public BaseSocket, public NetPacketPool
{
	static const int RECV_BUFFER_SIZE	 = 64 * 1024;
	static const int PROCESS_BUFFER_SIZE = 64 * 1024;
	static const int SEND_BUFFER_SIZE	 = 16 * 1024;
	// ����״̬
	enum Net_Status
	{
		NS_CONNECT = 1,			// δ����״̬
		//NS_POLICY_SEND,		// ����flash��֤���ڱ���Ŀ����
		//NS_POLICY_WAIT,
		NS_ENCRYREQ,			// ���ͼ���crc���󵽷�����
		NS_ENCRYACK,			// ����������crc
		NS_COMMU,				// ����ͨ��״̬, ������ͨ��״̬ǰ���յ�����������ɱ�����������ᴫ����Ϸ�߼�

		
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
	// дһ���µ����������
	enum Pack_Status
	{
		PS_IDLE = 0					// ����״̬
	};

#pragma pack(push,4)
	typedef struct
	{
		// edited by aXing on 2015-5-26
		// ������ΪӦ���Ƿ������ĵ�
		// �����������Ƕ�ȡһ��uint32��Ȼ��ͨ��λ�ƶ�ȡ�ߵ�λ��������ֱ�Ӷ�������uint16�����͡�
		// ����һ��uint32�����ˡ�
		//		uint16_t tag;
		uint32_t len;
	}DATAHEADER_N, *PDATAHEADER_N;
#pragma pack(pop)


public:
	ClientSocket();
	~ClientSocket();
	
	// ���÷�����ip�Ͷ˿�
	inline void SetHost(const char* host, int port)
	{
		_STRNCPY_A(m_host, host);
		m_port = port;
	}

	// ��ʼ����
	int ConnectSrv(bool bSendTGW);

	// ����Ͽ��������ӳɹ��������¼�
	virtual void OnConnected();
	virtual void OnDisconnected();

	// ��Ϸÿһ֡Ҫִ�еĴ���
	void LogicRun();

	// ��ȡһ�������ʵ��������������д����
	// sysid��protoid�ֱ���Э���
	// ע�⣬���ﷵ�ص�NetPacket�Ǹ���̬���������ԣ�alloc��SendToSrv�����Ӧ���ڣ���ֻ�ܵ��߳�ʹ��
	NetPacket* alloc(int sysId = -1, int protoId = -1);

	// �����������������
	int SendToSrv(NetPacket* pack);

	// ����һ���޲����������������
	int SendCmdToSrv(int sysId, int protoId);

	void setCallback(XLambda* uLuaHandle);

protected:
	virtual void OnError(int errorOp, int errorCode);

private:
	void SendSalt();
	void SendKeyCrc(int salt);	

	// ��������ɹ��������Ӻ󴥷�
	void OnCommuSucc();

	int  Recv();

	void ProcessNetMsg();
	int  ProceNetMsg(const char* buf, int size);
	int  UnPacket(const char* src, int src_size, char* dst, int max_size, int& data_size, DATAHEADER** out_hdr);

protected:
	virtual bool onExecuteRecvNetPacket(NetPacket* pkNetPacket);
private:
	// added by Shan Lu 2015/01/14 Begin
	// �����߼�ѭ��������
	// δ���ӻ��߲���ͨ��״̬
	bool exitProcessPacketLoop();

	// added by Shan Lu 2015/01/14 End

	// �������
	Encrypt	m_coder;
	int m_salt;
	// ���ӵ���Ŀ�ķ������Ͷ˿ڣ�֧������
	char m_host[256];
	int m_port;

	int m_status;	// ���������״̬

	NetBuf	m_buf;
	bool	m_bSendTGW;

	SocketDelegateProtocol* m_pkEventHandler;
};

#endif

