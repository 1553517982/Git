#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

/******************************************************************
 *
 *	$ 通用套接字处理类 $
 *
 *	- 主要功能 -
 *
 *	基本的套接字封装类，支持阻塞和非阻塞模式。
 *
 *****************************************************************/
#ifdef _MSC_VER
    #include <WinSock2.h>
	#include <Ws2tcpip.h>
    #define SOCKET_EMPTY_ERROR -0xffff
    #define SOCKET_EXCCESS_ERROR -0xffff + 1
#else


    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define SOCKET_EMPTY_ERROR -0xffff
    #define SOCKET_EXCCESS_ERROR -0xffff + 1
    #define SOCKET	int
    #define WSAGetLastError() errno
    #define WSAEWOULDBLOCK EWOULDBLOCK
    #define closesocket close
    #define OUT

		#include <errno.h>
        #include <sys/socket.h>
        #include <fcntl.h>
        #include <netinet/in.h>
        #include <netdb.h>
		#include <arpa/inet.h>

   /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        #import "errno.h"
        #import <sys/socket.h>
        #import <fcntl.h>
        #import <netinet/in.h>
        #import <netdb.h>
    #else
        #include <errno.h>
        #include <sys/socket.h>
        #include <fcntl.h>
        #include <netinet/in.h>
        #include <netdb.h>
    #endif*/
#endif

/*	基本TCP套接字类
*/
class BaseSocket
{
protected:
	SOCKET		socket_;		//套接字
	sockaddr_in	remote_addr_;	//远程地址
	bool		block_flag_;	//是否非阻塞模式
	bool		connected_;		//是否已建立连接
	bool		connectint_;	//是否正在连接
	// added by aXing on 2017-8-7
	bool		isIPV6_;		//是否IPV6
protected:
	//提供向最外层逻辑通知连接建立的事件
	virtual void OnConnected();
	//提供向最外层逻辑通知连接断开的事件
	virtual void OnDisconnected();
	//提供向最外层逻辑通知连接发生错误的事件
	virtual void OnError(int errorOp, int errorCode);
protected:
	//继承类通过重载此函数处理建立连接需要进行的操作
	virtual void Connected();
	//继承类通过重载此函数处理断开连接需要进行的操作
	virtual void Disconnected();
	//继承类通过重载此函数处理连接发生了错误的所需要进行的操作
	virtual void SocketError(int nErrorOp, int nErrorCode);
public:
	BaseSocket();
	virtual ~BaseSocket();
	static int InitSocketLib();
	static void UnintSocketLib();
	//获得SOCKET
	inline SOCKET getSocket()
	{
		return socket_;
	}
	//设置SOCKET
	void setSocket(const SOCKET socket);
	//获取是阻塞模式。true表示阻塞，false表示非阻塞
	inline bool getBlockMode()
	{
		return block_flag_;
	}
	//设置阻塞模式。true表示阻塞，false表示非阻塞，返回值为socket错误号，0表示成功
	int setBlockMode(const bool block);
	//判断SOCKET是否处于连接状态
	inline bool connected()
	{
		return connected_;
	}
	//判断SOCKET是否处于正在连接状态
	inline bool connecting()
	{
		return connectint_;
	}
	//断开连接并关闭套接字
	void Close();
	//获取远程的地址和端口的sockaddr_in结构
	inline void getRemoteAddr(sockaddr_in* addr_in)
	{
		*addr_in = remote_addr_;
	}
	//设置远程地址信息
	inline void setRemoteAddr(const sockaddr_in* addr_in)
	{
		remote_addr_ = *addr_in;
	}
	//获取接收缓冲区大小，返回值为socket错误号，0表示成功。
	int getRecvBufSize(int* size);
	//设置接收缓冲区大小，返回值为socket错误号，0表示成功。
	int setRecvBufSize(int size);
	//获取发送缓冲区大小，返回值为socket错误号，0表示成功。
	int getSendBufSize(int* size);
	//设置发送缓冲区大小，返回值为socket错误号，0表示成功。
	int setSendBufSize(int size);
	//通过32位IP地址连接到制定的端口，返回值为socket错误号，0表示成功。对于非阻塞模式返回0并不表示已经建立连接
	int connect(const u_long addr, const int port, bool block);
	//通过IPV6地址连接到制定的端口，返回值为socket错误号，0表示成功。对于非阻塞模式返回0并不表示已经建立连接
	int connect6(const char* addr, const int port, bool block);
	//通过IP地址字符串连接到指定的端口，返回值为socket错误号，0表示成功。对于非阻塞模式返回0并不表示已经建立连接
	// added by aXing on 2013-3-23
	// 对于非阻塞式连接，错误码为-1的时候我们认为超时
	int connect(const char* addr, const int port, bool block);
	//创建套接字，返回值为socket错误号，0表示成功且socket的内容被填充为新建立的socket
	static int createSocket(OUT SOCKET* socket, const int af = AF_INET, const int type = SOCK_STREAM, const int protocol = IPPROTO_TCP);
	//读取套接字内容。返回0表示连接已断开，返回SOCKET_ERROR表示发生错误，返回SOCKET_ERROR-1表示没有数据可读(仅对于非阻塞模式套接字)，否则表示实际接收的字节数
	virtual int recv(void* buf, int len, const int flags = 0);
	//向套接字写入内容，返回0表示连接已断开，返回SOCKET_ERROR表示发生错误，返回SOCKET_ERROR-1表示send操作会发生阻塞且没有数据被发送(仅对于非阻塞模式套接字)，否则返回发送的字节数。
	virtual int send(void* buf, int len, const int flags = 0);
};

#endif

