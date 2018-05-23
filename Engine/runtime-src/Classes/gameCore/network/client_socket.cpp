#include "XCommon.h"
#include "gameCore/common/base_allocator.h"
#include "net_packet.h"
#include "client_socket.h"
#include "SocketDelegateProtocol.h"

#ifdef X_DEBUG
	#define SOCKET_LOG XLOG
#else
	#define SOCKET_LOG
#endif // _DEBUG

#define SOCKET_ERROR_LOG XLOG

ClientSocket::ClientSocket() : m_pkEventHandler(NULL)
{
	m_bSendTGW = true;
	m_status = NS_CONNECT;
	m_pkEventHandler = new SocketDelegateProtocolScript();
}

ClientSocket::~ClientSocket()
{
	delete m_pkEventHandler;
}

int ClientSocket::ConnectSrv(bool bSendTGW)
{
	if (connected())
	{
		return 0;
	}

	clearRecvNetPacket();

	int nErr = 0;

	// 创建套接字
	if (getSocket() == INVALID_SOCKET)
	{
		struct addrinfo *result = NULL;
		struct addrinfo *ptr = NULL;
		struct addrinfo hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		char service[8];
		sprintf(service, "%d", m_port);

		int retval = getaddrinfo(m_host, service, &hints, &result);
		if (retval != 0)
		{
			XLOG("host error, code = %d", retval);
			return retval;
		}
		else
		{
			SOCKET sock;
			
			ptr = result;
			if (ptr != NULL)
			{
				XLOG("getaddrinfo response[0]");
				XLOG("Flags: 0x%x", ptr->ai_flags);
				XLOG("Family: ");
				switch (ptr->ai_family)
				{
				case AF_UNSPEC:
					XLOG("Unspecified");
					break;
				case AF_INET:
					isIPV6_ = false;
					nErr = createSocket(&sock);	
					break;
				case AF_INET6:
					isIPV6_ = true;
					nErr = createSocket(&sock, AF_INET6);
					break;
				default:
					XLOG("Other %d", ptr->ai_family);
					break;
				}
			}
			socket_ = sock;
			freeaddrinfo(result);
		}
		
		if (nErr)
		{
			//cocos2d::CCLog("createSocket error, err=%d", WSAGetLastError());
			return false;
		}
	}

	//连接到服务器
	nErr = connect(m_host, m_port, false);
	
	if (nErr)
	{
		//cocos2d::CCLog("connect to srv fail,host:%s, port:%d, error:%d", m_host, m_port,ne);
		return nErr;
	}

	//	int bnodelay = 1;
	//	nErr = ::setsockopt(getSocket(), IPPROTO_TCP, TCP_NODELAY, (const char*)&bnodelay, sizeof(bnodelay));

//	m_status = NS_ENCRYREQ;
//	m_bSendTGW = bSendTGW;
	//cocos2d::CCLog("connect srv succ,host:%s, port:%d", m_host, m_port);

	m_status = NS_ENCRYREQ;
	return 0;
}

void ClientSocket::OnConnected()
{

}

void ClientSocket::OnDisconnected()
{
	m_status = NS_CONNECT;
	// 需要触发脚本

	m_buf.clear();
	//CCLog("ClientSocket::OnDisconnected(), buff size = %d, max size = %d", m_buf.size_, m_buf.max_size_);
	clearRecvNetPacket();
}

void ClientSocket::LogicRun()
{
	if (connected())
	{
		if (m_status == NS_ENCRYREQ)
		{
			//if(m_bSendTGW)
			//{
				//char TGWHeader[4096] = {0};
				//sprintf(TGWHeader,"tgw_l7_forward\r\nHost:%s:%d\r\n\r\n",m_host,m_port);
				//int	 TGWlen = strlen(TGWHeader);
				//int ret = send(TGWHeader, TGWlen);
				//SOCKET_LOG("TGWHeader [%s] [%d] [%d]",TGWHeader,TGWlen,ret);
			//}

	
			// 发送salt
			SendSalt();
			//m_status = NS_COMMU;

		}
		else
		{
			// 接收数据并处理
			Recv();
			ProcessNetMsg();
			if(m_status == NS_COMMU)
			{
				executeRecvNetPacket();
			}
		}
	}
	else
	{
		// 自动连接？ 或者可以由脚本做
		//CCLog("ClientSocket::LogicRun() is disconnected");
	}
}

typedef struct VerifyMsg
{
	uint32_t length;
	uint32_t crc;
	uint32_t role_id;
	uint32_t cmd;
	uint32_t para;
}VerifyMsg;
void ClientSocket::SendSalt()
{
	m_salt = (int)time(NULL);
	int ret = send((char*)&m_salt, sizeof(m_salt));
	//SOCKET_LOG("ClientSocket SendSalt>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>: ret=%d salt=%d size=%d", ret, m_salt, m_buf.size_);
	m_status = NS_ENCRYACK;
}

void ClientSocket::SendKeyCrc(int salt)
{
	SOCKET_LOG("ClientSocket SendKeyCrc %d", salt);
	m_coder.SetSelfSalt(salt);
	m_coder.SetTargetSalt(m_salt);
	unsigned short key = (unsigned short)m_coder.GetKeyCRC();
	send((char*)&key, sizeof(key));

	//CCLog("ClientSocket::SendKeyCrc>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> key = %d, buffsize=%d", key, m_buf.size_);
	m_status = NS_COMMU;	// 如果key不对，服务器会主动断开连接

	OnCommuSucc();
}

void ClientSocket::OnCommuSucc()
{
	if (m_pkEventHandler)
		m_pkEventHandler->onCommuSucc();
}

int ClientSocket::Recv()
{
	if(isExecuteQueueFull())
		return 0;

	char recv_buff[RECV_BUFFER_SIZE];
	int readLen = RECV_BUFFER_SIZE - m_buf.getSize();

	if (readLen <= 0)
	{
		SOCKET_ERROR_LOG("Recv() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>robot recv buf is full!!!!");
		return 0;
	}

	int err = recv(recv_buff, readLen);

	if (err > 0)
	{
		//CCLog("ClientSocket::Recv() >>>>>>>>>>>>>>>>>>>> err = %d, status = %d",err, m_status);
		// test
		//if(err > 80)
		//	return -2;
		if (m_status != NS_COMMU)
		{
			//m_buf.size_ = 0;
			m_buf.clear();
			//char temp_buff[MAX_RECV_BUFF] = {0};
			//memcpy(temp_buff, recv_buff, err);
			//CCLog("Recv() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>, status = %d, receive buff = %s", m_status, temp_buff);
		}

		m_buf.append(recv_buff,err);
	}
	else if (err == 0)
	{
		//CCLog("Recv() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> lost connection on server!");
		OnDisconnected();
	}
	
	return err;
}


void ClientSocket::ProcessNetMsg()
{
	//CCLog("---------ProcessNetMsg----------");
	if (!connected())
	{
		m_buf.clear();
		return;
	}

	// process code here
	int size = m_buf.getSize();
	char* buf = m_buf.getBuf();

	while (size > 0)
	{
		if (m_status != NS_COMMU)
		{
			int proc_size = ProceNetMsg(buf, size);
			size -= proc_size;
			buf += proc_size;

			if (proc_size <= 0)
			{
				size = 0;	// xiaojun at 2014-10-29 为了跨服战而修改
				break;
			}
		}
		else
		{
			char proc_buf[PROCESS_BUFFER_SIZE];
			int data_size = 0;
			DATAHEADER* hdr;
			int proc_size = UnPacket(buf, size, proc_buf, sizeof(proc_buf), data_size, &hdr);
			if (proc_size <= 0) break; // 没数据要处理

			size -= proc_size;
			buf += proc_size;

			if (data_size > 0)
			{
				addExecuteQueue(proc_buf,data_size);
			}
		}
	}

	if(size > 0)
		m_buf.copy(buf,size);
	else
		m_buf.clear();
	return;
}

int ClientSocket::ProceNetMsg(const char* buf, int size)
{
	//CCLog("ProceNetMsg");
	if (m_status == NS_ENCRYACK && size >= 4)
	{
		int salt = *(int*)(buf);
		if (salt == 0)		// xiaojun at 2014-10-29 为了跨服战而修改
			return 0;

		SendKeyCrc(salt);
		return sizeof(salt);
	}

	return 0;
}


int ClientSocket::UnPacket(const char* src, int src_size, char* dst, int max_size, int& data_size, DATAHEADER** out_hdr)
{
	const int hdr_size = sizeof(DATAHEADER);
	bool tagFlag = false;
	int offset = 0;

	for (; offset < src_size - 1; offset++)
	{
		uint16_t* tag_pos = (uint16_t*)(src + offset);

		if (*tag_pos == TAG_VALUE)
		{
			tagFlag = true;
			break;
		}
	}

	if (!tagFlag)
	{
		offset++;
		return offset;
	}

	int p_size = offset;
	int left = src_size - offset;

	if (left < hdr_size)
	{
		return p_size;
	}

	const char* real_data = src + offset;
	*out_hdr = (PDATAHEADER)real_data;

	DATAHEADER hdr_data;// = *((PDATAHEADER)(real_data));
	memcpy(&hdr_data, real_data, sizeof(hdr_data));
	PDATAHEADER hdr = &hdr_data;

	int pack_size = hdr->len + hdr_size;

	if (pack_size > left) return p_size;

	if (hdr->len <= max_size)
	{
		memcpy(dst, (void*)(real_data + hdr_size), hdr->len);
		data_size = hdr->len;
	}
	p_size = offset + pack_size;
	return p_size;
}

NetPacket* ClientSocket::alloc(int sysId, int protoId)
{
	if (sysId != -1)
	{
		uint8_t hdr[2];
		hdr[0] = (uint8_t)sysId;
		hdr[1] = (uint8_t)protoId;
		NetPacket* pkPacket =  createNetPacket(hdr, sizeof(hdr));
		pkPacket->setType(NetPacket::eSend);
		return pkPacket;
	}
	else
	{
		NetPacket* pkPacket = createNetPacket(NULL, 0);
		pkPacket->setType(NetPacket::eSend);
		return pkPacket;
	}
	
}

int ClientSocket::SendToSrv(NetPacket* pack)
{
	if (m_status != NS_COMMU)
	{
		//CCLog("ClientSocket::SendToSrv>>>>>>>>>>>>>>>>> m_status = %d", m_status);
		return SOCKET_ERROR;
	}

	if (!pack)
		return SOCKET_EMPTY_ERROR;

	const char* buf = pack->getMemoryPtr();
	int size = pack->getPosition();

	char data[2048];

	if (size > sizeof(data))
	{
		return SOCKET_EXCCESS_ERROR;
	}

	DATAHEADER* hdr = (DATAHEADER*)data;
	hdr->tag = TAG_VALUE;
	hdr->len = (uint16_t)size;

	char* data_buf = data + sizeof(DATAHEADER);
	memcpy(data_buf, buf, size);
	hdr->EncodePart.dataSum = Encrypt::CRC16(data_buf, size);
	hdr->EncodePart.hdrSum = HEAD_SUM;
	hdr->EncodePart.hdrSum = Encrypt::CRC16(data, sizeof(DATAHEADER));
	const int partsize = sizeof(hdr->EncodePart);
	char part[partsize];
	m_coder.Encode((char*)& (hdr->EncodePart), partsize, part);
	memcpy((char*)& (hdr->EncodePart), part, partsize);
	return send(data, sizeof(DATAHEADER) + size);
}

int ClientSocket::SendCmdToSrv(int sysId, int protoId)
{
	NetPacket* newPack = alloc(sysId, protoId);
	return SendToSrv(newPack);
}
void ClientSocket::setCallback(XLambda* uLuaHandle){
	m_pkEventHandler->setHandle(uLuaHandle);
}
void ClientSocket::OnError(int errorOp, int errorCode)
{
	char strCode[256] = {0};
	sprintf(strCode,"%d:%d",errorOp,errorCode);
	if (m_pkEventHandler)
		m_pkEventHandler->onSocketError(strCode);
}

bool ClientSocket::exitProcessPacketLoop()
{
	return (connected_ == false) || (m_status != NS_COMMU);
}

bool ClientSocket::onExecuteRecvNetPacket(NetPacket* pkNetPacket)
{
	if (m_pkEventHandler)
		m_pkEventHandler->onRecv(pkNetPacket);

	return exitProcessPacketLoop();
}
