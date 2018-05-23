#include "cocos2d.h"
#include "net_packet_pool.h"
#include "net_packet.h"
#include "XCommon.h"

USING_NS_CC;

static const int MAX_POOL_SIZE = 64;			 // 网络包池的最大数量
static const int MAX_NETPACKET_QUEUE_SIZE = 128; // 最多缓存的网络包
static const double MAX_EXECUTE_TIME = 0.2;		 // 最多处理包循环最大耗时，200ms

NetPacketPool::NetPacketPool() : 
	//m_netPacketExecutePerFrame(NETPACKET_EXECUTE_PER_FRAME),
	m_pkBaseAllocator(NULL)
{
	m_pkBaseAllocator = new BaseAllocator("ClientSocketPacketPool");
}

NetPacketPool::~NetPacketPool()
{
#ifdef X_DEBUG
	XLOG("NetPacketPool pool size %d alloc_total %d",
		m_netPacketPool.size(), 
		m_pkBaseAllocator->GetAllocCount());
#endif // _DEBUG


	clearRecvNetPacket();
	clearNetPacketPool();
	delete m_pkBaseAllocator;
}

NetPacket* NetPacketPool::createNetPacket(void* buf, size_t size)
{
	NetPacket* pkPacket = NULL;
	if(m_netPacketPool.empty())
	{
		pkPacket = NetPacket::create(m_pkBaseAllocator);
	}
	else
	{
		pkPacket = m_netPacketPool.front();
		m_netPacketPool.pop();
		pkPacket->autorelease();
	}
	if (buf)
	{
		// 写入
		pkPacket->writeBuf(buf, size);
//		pkPacket->setPosition(0);
	}
	return pkPacket;
}

void NetPacketPool::addExecuteQueue(void* buf, size_t size)
{
	NetPacket* pkPacket = createNetPacket(buf,size);
	if(pkPacket)
	{
		addExecuteQueue(pkPacket);
	}
}

void NetPacketPool::addExecuteQueue(NetPacket* pkPacket)
{
	pkPacket->setType(NetPacket::eRecv);
	pkPacket->retain();
	m_recvNetPackets.push(pkPacket);
}

void NetPacketPool::executeRecvNetPacket()
{
	int process = 0;

	double _last = cocos2d::utils::gettime();

	while(!m_recvNetPackets.empty())
	{
		double _now = cocos2d::utils::gettime();

		// 获取当前时间，如果执行时间总计超过 MAX_EXECUTE_TIME，跳出循环
		double timePassed = _now - _last;

		if(timePassed > MAX_EXECUTE_TIME)
		{
			break;
		}
		NetPacket* pkPacket = m_recvNetPackets.front();
		m_recvNetPackets.pop();
		bool ret = onExecuteRecvNetPacket(pkPacket);
		recycle(pkPacket);
		pkPacket->release();
		if(ret)
			break;
		process++;
	}
}
void NetPacketPool::clearRecvNetPacket()
{
	while(!m_recvNetPackets.empty())
	{
		NetPacket* pkPacket = m_recvNetPackets.front();
		m_recvNetPackets.pop();
		recycle(pkPacket);
	}
}

void NetPacketPool::clearNetPacketPool()
{
	while(!m_netPacketPool.empty())
	{
		NetPacket* pkPacket = m_netPacketPool.front();
		pkPacket->release();
		m_netPacketPool.pop();
	}
}


/*void NetPacketPool::logNetPacketPool()
{

}*/

void NetPacketPool::recycle(NetPacket* pkPacket)
{
	if(m_netPacketPool.size() > MAX_POOL_SIZE)
	{
		return;
	}
	pkPacket->clear();
	pkPacket->setType(0);
	pkPacket->retain();
	m_netPacketPool.push(pkPacket);
}

bool NetPacketPool::isExecuteQueueFull()
{
	return m_recvNetPackets.size() > MAX_NETPACKET_QUEUE_SIZE;
}

// added by Shan Lu 2014/12/30 End