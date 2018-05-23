#ifndef _NET_PACKET_POOL_H_
#define _NET_PACKET_POOL_H_
#include <queue>

class NetPacket;
class BaseAllocator;

class NetPacketPool
{
public:

	NetPacketPool();

	virtual ~NetPacketPool();

	// 放到执行队列里里面
	void		addExecuteQueue(void* buf, size_t size);

	// 执行包
	void		executeRecvNetPacket();
	// 清空包
	void		clearRecvNetPacket();
	// 清空池
	void		clearNetPacketPool();

	// 执行池是否已经爆满了，如果是的话就先不recv，由socket调用
	bool		isExecuteQueueFull();

protected:
	//实行单个NetPacket
	virtual	 bool onExecuteRecvNetPacket(NetPacket* pkNetPacket) = 0;

	// added by Shan Lu 2014/12/30 End
	// 创建包
	NetPacket*  createNetPacket(void* buf, size_t size);

	void		recycle(NetPacket* pkPacket);

private:
	// 放到等待执行队列
	void		addExecuteQueue(NetPacket* pkPacket);

	
	// added by Shan Lu 2014/12/30 Begin
	BaseAllocator*							m_pkBaseAllocator;
	std::queue<NetPacket*>					m_recvNetPackets;
	std::queue<NetPacket*>					m_netPacketPool;
	// added by Shan Lu 2014/12/30 End
};

#endif