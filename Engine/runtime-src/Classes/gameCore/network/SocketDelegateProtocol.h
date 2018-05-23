#ifndef _SocketDelegateProtocol_H_
#define _SocketDelegateProtocol_H_

#include "helpers/XLambda.h"

/*! \class SocketDelegateProtocol
 *  \brief socket事件回调类
 *
 * Some socket事件回调类
 */
class NetPacket;

class SocketDelegateProtocol
{
	public:
		SocketDelegateProtocol()			{};
		virtual ~SocketDelegateProtocol()   {};

		/** 
		 *  
		 *  @brief 连接第一次成功，如果验证失败服务器会主动断开，
		 *  仅仅做日志使用
		 *  @return void
		*/
		virtual void onCommuSucc() = 0;

		/** 
		 *  
		 *  @brief 收到网络包
		 *  @param NetPacket * pkPacket 网络包数据部分
		 *  @return void
		*/
		virtual void onRecv(NetPacket* pkPacket) = 0;

		/** 
		 *  
		 *  @brief socket 错误回调
		 *  @param int code
		 *  @return void
		*/
		virtual void onSocketError(int code) = 0;

		/** 
		 *  
		 *  @brief socket 错误回调， 预留
		 *  @param const char * szCode
		 *  @return void
		*/
		virtual void onSocketError(const char* szCode) = 0;

		/**
		*
		*  @brief socket 设置连接结果lua回调处理
		*  @param unsigned int val
		*  @return void
		*/
		virtual void setHandle(XLambda* handle) = 0;
};


/*! \class SocketDelegateProtocolScript
 *  \brief 让socket消息回调到脚本
 *
 * 装饰器
 */
class SocketDelegateProtocolScript : public SocketDelegateProtocol
{
public:
	enum
	{
		eOnCommuSucc,
		eOnRecv,
		eOnSocketError,
	};
	SocketDelegateProtocolScript();
	virtual ~SocketDelegateProtocolScript();

	virtual void onCommuSucc();

	virtual void onRecv(NetPacket* pkPacket);

	virtual void onSocketError(int code);

	virtual void onSocketError(const char* szCode);

	XLambda* getHandle() const { return m_Lambda; }

	void setHandle(XLambda* handle) { 
		CC_SAFE_RELEASE(m_Lambda);
		m_Lambda = handle;
		CC_SAFE_RETAIN(m_Lambda);
	}

private:
	XLambda*   m_Lambda;

};

#endif

