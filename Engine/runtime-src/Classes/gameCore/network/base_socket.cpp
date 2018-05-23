#ifndef _MSC_VER
#include <sys/ioctl.h>
#endif

#include "cocos2d.h"
#include "XCommon.h"
#include "os_def.h"
#include "base_socket.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
#include <arpa/inet.h>
#endif

#define TIME_OUT_TIME 5 //connect超时时间5秒

#define TSOCKET_SEND_ERROR 1
#define TSOCKET_SEND_BLOCKED 2
#define TSOCKET_RECV_NONE 3
#define TSOCKET_RECV_ERROR 4
#define TSOCKET_RECV_SOCKET_CLOSE 5

BaseSocket::BaseSocket()
{
	socket_ = INVALID_SOCKET;
	block_flag_ = false;
	connected_ = false;
	connectint_ = false;
}

BaseSocket::~BaseSocket()
{
	Close();
}

void BaseSocket::OnConnected()
{
}

void BaseSocket::OnDisconnected()
{
}

void BaseSocket::OnError(int,int)
{
}

void BaseSocket::Connected()
{
	OnConnected();
}

void BaseSocket::Disconnected()
{
	OnDisconnected();
}

void BaseSocket::SocketError(int errorOp, int errorCode)
{
	OnDisconnected();
	Close();
	OnError(errorOp, errorCode);
}

void BaseSocket::setSocket(const SOCKET socket)
{
	socket_ = socket;

	//设置了套接字后变更为制定的阻塞模式
	if (socket_ != INVALID_SOCKET)
	{
		connected_ = true;
		block_flag_ = !block_flag_;
		setBlockMode(!block_flag_);
	}
	else connected_ = false;
}

int BaseSocket::setBlockMode(const bool block)
{
	//if (block == block_flag_)
	//	return 0;

	if (socket_ != INVALID_SOCKET)
	{
#ifdef _MSC_VER
		u_long ulock = block ? 0 : 1;

		if (ioctlsocket(socket_, FIONBIO, &ulock))
		{
			return WSAGetLastError();
		}

#else
		bool ret = true;
		int flags = fcntl(socket_, F_GETFL, 0);

		if (block)
		{
			fcntl(socket_, F_SETFL, flags & ~O_NONBLOCK);
		}
		else
		{
			if (fcntl(socket_, F_SETFL, flags | O_NONBLOCK) == -1)
				ret = false;
		}

		if (!ret)
		{
			return errno;
		}

#endif
	}

	block_flag_ = block;
	return 0;
}

void BaseSocket::Close()
{
	if (socket_ != INVALID_SOCKET)
	{
		if (connected_)
		{
			Disconnected();
		}

		closesocket(socket_);
		socket_ = INVALID_SOCKET;
	}

	connected_ = false;
	connectint_ = false;
	block_flag_ = true;
}


int BaseSocket::getRecvBufSize(int* size)
{
	socklen_t oplen = sizeof(*size);
	int err = getsockopt(socket_, SOL_SOCKET, SO_RCVBUF, (char*)size, &oplen);
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::setRecvBufSize(int size)
{
	int err = setsockopt(socket_, SOL_SOCKET, SO_RCVBUF, (char*)&size, sizeof(size));
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::getSendBufSize(int* size)
{
	socklen_t oplen = sizeof(*size);
	int err = getsockopt(socket_, SOL_SOCKET, SO_SNDBUF, (char*)size, &oplen);
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::setSendBufSize(int size)
{
	int err = setsockopt(socket_, SOL_SOCKET, SO_SNDBUF, (char*)&size, sizeof(size));
	return err ? WSAGetLastError() : 0;
}


int BaseSocket::connect(const char* addr, const int port, bool block)
{
	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	char service[8];
	sprintf(service, "%d", port);

	int retval = getaddrinfo(addr, service, &hints, &result);
	if (retval != 0)
	{
		XLOG("host error, code = %d", retval);
	}
	else if (result != NULL)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		ptr = result;
		int errorNum = 0;
		struct hostent* host = getipnodebyname(addr, ptr->ai_family, ptr->ai_flags, &errorNum);
		XLOG("getaddrinfo response[0]");
		XLOG("Flags: 0x%x", ptr->ai_flags);
		if (ptr->ai_family == AF_INET)
		{
			if (host != NULL){
				retval = connect(inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list)), port, block);
			}
		}
		else if (ptr->ai_family == AF_INET6)
		{
			if (host != NULL){
				char ipStr[128];
				inet_ntop(AF_INET6, (struct in6_addr *)*host->h_addr_list, ipStr, 128);
				//const char* ipStr =  ;
				XLOG("ip : %s", ipStr);
				retval = connect6(ipStr, port, block);
			}
		}
#else
		retval = connect(inet_addr(addr), port, block);
#endif
		freeaddrinfo(result);
		return retval;
	}
	freeaddrinfo(result);
	return WSAGetLastError();
}

int BaseSocket::connect6(const char* addr, const int port, bool block)
{
	sockaddr_in6 addrin6;

	memset(&addrin6, 0, sizeof(addrin6));
	addrin6.sin6_family = AF_INET6;
	addrin6.sin6_port = htons((u_short)port);
	inet_pton(AF_INET6, addr, &addrin6.sin6_addr);
	XLOG("connect ipv6 addr: %s", addr);
	// added by aXing on 2013-3-22
	// 设置为非阻塞模式
	timeval		tm;
	fd_set		set;
	unsigned long ul = 1;
	//	ioctl(socket_, FIONBIO, &ul);		// unix api ?
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	ioctlsocket(socket_, FIONBIO, &ul);		//设置为非阻塞模式
#else
	ioctl(socket_, FIONBIO, &ul);
#endif
	bool		ret = false;
	int			err = -1;
	socklen_t	len;

	int connectResult = ::connect(socket_, (sockaddr*)&addrin6, sizeof(addrin6));

	int connect_err = WSAGetLastError();

	if (connectResult == -1)
	{
		XLOG("::connect error %d %s", connect_err, strerror(connect_err));

		tm.tv_sec = TIME_OUT_TIME;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(socket_, &set);
		int selectRet = select(socket_ + 1, NULL, &set, NULL, &tm);
		if (selectRet > 0)			// 检查连接
		{
			len = sizeof(err);
			getsockopt(socket_, SOL_SOCKET, SO_ERROR, (char*)&err, &len);
			ret = err == 0;
		}
		else
		{
			ret = false;
		}

		XLOG("::select result %d", selectRet);
	}
	else
		ret = true;

	XLOG("::connect result [2] = %d %d", connectResult, ret);

	ul = 0;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	ioctlsocket(socket_, FIONBIO, &ul); //设置为阻塞模式
#else
	ioctl(socket_, FIONBIO, &ul);
#endif
	if (ret)
	{
		// 设置是否阻塞模式
		setBlockMode(block);
		connected_ = true;
		connectint_ = false;
		Connected();

	}
	else
	{
		err = WSAGetLastError();
		XLOG("WSAGetLastError %d %s", err, strerror(err));
		if (err == WSAEWOULDBLOCK)
		{
			err = 0;
			connected_ = false;
			connectint_ = true;
		}
		Close();
		// added by aXing on 2013-3-23
		// 对于非阻塞式连接，错误码为-1的时候我们认为超时
		err = -1;
	}
	return err;
}

int BaseSocket::connect(const u_long addr, const int port, bool block)
{
	sockaddr_in addrin;

	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = addr;
	addrin.sin_port = htons((u_short)port);

	// added by aXing on 2013-3-22
	// 设置为非阻塞模式
	timeval		tm;
	fd_set		set;
	unsigned long ul = 1;
	//	ioctl(socket_, FIONBIO, &ul);		// unix api ?
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	ioctlsocket(socket_, FIONBIO, &ul);		//设置为非阻塞模式
#else
	ioctl(socket_, FIONBIO, &ul);
#endif
	bool		ret = false;
	int			err = -1;
	socklen_t	len;

	int connectResult = ::connect(socket_, (sockaddr*)&addrin, sizeof(addrin));

	int connect_err = WSAGetLastError();

	if ( connectResult == -1)
	{
		XLOG("::connect error %d %s",connect_err,strerror(connect_err));

		tm.tv_sec	= TIME_OUT_TIME;
		tm.tv_usec	= 0;
		FD_ZERO(&set);
		FD_SET(socket_, &set);
		int selectRet = select(socket_ + 1, NULL, &set, NULL, &tm);
		if( selectRet > 0)			// 检查连接
		{
			len = sizeof(err);
			getsockopt(socket_, SOL_SOCKET, SO_ERROR, (char*)&err, &len);
			ret = err == 0;
		}
		else
		{
			ret = false;
		}

		XLOG("::select result %d",selectRet);
	}
	else
		ret = true;

	XLOG("::connect result [2] = %d %d", connectResult, ret);

	ul = 0;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	ioctlsocket(socket_, FIONBIO, &ul); //设置为阻塞模式
#else
	ioctl(socket_, FIONBIO, &ul);
#endif
	if (ret)
	{
		// 设置是否阻塞模式
		setBlockMode(block);
		connected_ = true;
		connectint_ = false;
		Connected();

	}
	else
	{
		err = WSAGetLastError();
		XLOG("WSAGetLastError %d %s", err, strerror(err));
		if (err == WSAEWOULDBLOCK)
		{
			err = 0;
			connected_ = false;
			connectint_ = true;
		}
		Close();
		// added by aXing on 2013-3-23
		// 对于非阻塞式连接，错误码为-1的时候我们认为超时
		err = -1;
	}
	return err;

	//int err = ::connect(socket_, (sockaddr*)&addrin, sizeof(addrin));

	//if (err == 0)
	//{
	//	// 设置是否阻塞模式
	//	setBlockMode(block);
	//	connected_ = true;
	//	connectint_ = false;
	//	Connected();
	//}
	//else
	//{
	//	err = WSAGetLastError();

	//	if (err == WSAEWOULDBLOCK)
	//	{
	//		err = 0;
	//		connected_ = false;
	//		connectint_ = true;
	//	}
	//}

	//return err;
}

int BaseSocket::createSocket(SOCKET* socket, const int af, const int type, const int protocol)
{
	*socket = ::socket(af, type, protocol);

	if (*socket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	return 0;
}

int BaseSocket::recv(void* buf, int len, const int flags)
{
	int err = ::recv(socket_, (char*)buf, len, flags);

	if (err == 0)
	{
		SocketError(TSOCKET_RECV_SOCKET_CLOSE,0);
		return 0;
	}
	else if (err < 0)
	{
#ifdef _MSC_VER
		if (!block_flag_)
		{
			err = WSAGetLastError();

			if (err != WSAEWOULDBLOCK && err != 0)
			{
				SocketError(TSOCKET_RECV_ERROR,err);
				err = SOCKET_ERROR - err;
			}
			else err = SOCKET_ERROR - err;
		}
#else
		int recv_err = errno;
		if(recv_err == EAGAIN || recv_err == EWOULDBLOCK || recv_err == EINTR)
		{
			return -recv_err;
		}
		else
		{
			SocketError(TSOCKET_RECV_ERROR,recv_err);
			return 0;
		}
#endif
	}

	return err;
}

int BaseSocket::send(void* buf, int len, const int flags)
{
	char* ptr = (char*)buf;
	int ret = 0;
	while (len > 0)
	{
		int err = ::send(socket_, (char*)ptr, len, flags);

		if (err > 0)
		{
			ret += err;
			ptr += err;
			len -= err;
		}
#ifdef _MSC_VER
		else if (err < 0)
		{
			if (!block_flag_)
			{
				err = WSAGetLastError();

				if (err != WSAEWOULDBLOCK)
				{
					ret = SOCKET_ERROR - err;
					SocketError(TSOCKET_SEND_BLOCKED,err);
				}
				else if (ret == 0)
				{
					ret = SOCKET_ERROR - err;
				}
			}

			break;
		}
		else
		{
			err = WSAGetLastError();
			ret = SOCKET_ERROR - err;
			Close();
			break;
		}
#else
		else
		{
			int send_err = errno;
			if(send_err == EAGAIN || send_err == EWOULDBLOCK)
			{
				return -send_err;
			}
			else
			{
				SocketError(TSOCKET_SEND_ERROR,send_err);
				return 0;
			}
		}
#endif
	}
	return ret;
}
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include<signal.h>
#endif
int BaseSocket::InitSocketLib()
{
#ifdef _MSC_VER
	WSADATA Wsad;

	if (WSAStartup(0x0202, &Wsad))
		return GetLastError();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//http://blog.chinaunix.net/uid-23849526-id-142808.html
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) == -1 ||
		sigaction(SIGPIPE, &sa, 0) == -1) {
			XLOG("failed to ignore SIGPIPE; sigaction");
	}
#endif
	return 0;
}

void BaseSocket::UnintSocketLib()
{
#ifdef _MSC_VER
	WSACleanup();
#endif
}
