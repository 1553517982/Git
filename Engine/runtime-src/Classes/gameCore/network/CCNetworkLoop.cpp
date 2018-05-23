#include "CCNetworkLoop.h"
#include "network/base_socket.h"
#include "network/ClientSocketNormalProxy.h"
#include "XCommon.h"
///#include "script_support/CCScriptMessageDispatcher.h"
#define GAMELOG XLOG
CCNetworkLoop* CCNetworkLoop::m_pShareLooper = NULL;

CCNetworkLoop::CCNetworkLoop() :
 m_pSocketInterface(NULL),
 m_bPaused(true),
 m_pSocket2(NULL)
{

}

CCNetworkLoop::~CCNetworkLoop()
{
	stop();
	if(m_pSocketInterface)
	{
		m_pSocketInterface->Close();
		CC_SAFE_DELETE(m_pSocketInterface);
	}
	if (m_pSocket2)
	{
		m_pSocket2->Close();
		CC_SAFE_DELETE(m_pSocket2);
	}
}

CCNetworkLoop* CCNetworkLoop::sharedManager()
{
	if(m_pShareLooper)
		return m_pShareLooper;
	m_pShareLooper = new CCNetworkLoop();
	return m_pShareLooper;
}

void CCNetworkLoop::purgeSharedManager()
{
	CC_SAFE_DELETE(m_pShareLooper);
}

int CCNetworkLoop::initSocket(unsigned char socket_type, const char* pszOSVer, const char* pszInstallPath)
{
	if(m_pSocketInterface)
		return 0;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	socket_type = CCNetworkLoop::eCSOCKET;
#endif

	GAMELOG("GameEngine::initSocket %d %s %s",socket_type,pszOSVer,pszInstallPath);
	if(socket_type == CCNetworkLoop::eCSOCKET)
	{

		int e = BaseSocket::InitSocketLib();
		if( e == 0)
			m_pSocketInterface = new ClientSocketNormalProxy();

		GAMELOG("initSocket Socket Type == eCSOCKET %d",e);
		return e;
	}
	else if(socket_type == CCNetworkLoop::eTSOCKET)
	{

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//int e = QCloudSocketAndroid::InitSocketLib(pszOSVer,pszInstallPath);
		//if(e == 0)
			//m_pSocketInterface = new QCloudSocketAndroidProxy();

		GAMELOG("initSocket Socket Type == eTSOCKE T%d",-0xffff);
		return -0xfffff;
#endif
	}
	return -1;
}

int CCNetworkLoop::initSocket2(unsigned char socket_type, const char* pszOSVer, const char* pszInstallPath)
{
	if (m_pSocket2)
		return 0;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	socket_type = CCNetworkLoop::eCSOCKET;
#endif

	GAMELOG("GameEngine::initSocket %d %s %s", socket_type, pszOSVer, pszInstallPath);
	if (socket_type == CCNetworkLoop::eCSOCKET)
	{

		int e = BaseSocket::InitSocketLib();
		if (e == 0)
			m_pSocket2 = new ClientSocketNormalProxy();

		GAMELOG("initSocket Socket Type == eCSOCKET %d", e);
		return e;
	}
	else if (socket_type == CCNetworkLoop::eTSOCKET)
	{

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//int e = QCloudSocketAndroid::InitSocketLib(pszOSVer,pszInstallPath);
		//if(e == 0)
		//m_pSocketInterface = new QCloudSocketAndroidProxy();

		GAMELOG("initSocket Socket Type == eTSOCKE T%d", -0xffff);
		return -0xfffff;
#endif
	}
	return -1;
}

void CCNetworkLoop::start(void)
{
	if (!m_bPaused)
		return;

	m_bPaused = false;
	Director::getInstance()->getScheduler()->schedule(schedule_selector(CCNetworkLoop::tick), this, 0.0, false);
}

void CCNetworkLoop::stop(void)
{
	if (m_bPaused)
		return;

	m_bPaused = true;
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(CCNetworkLoop::tick), this);
}

void CCNetworkLoop::tick(float dt)
{	// LP TODO 
	//CCScriptMessageDispatcher::sharedManager()->tick(dt);

	// 先执行第一个socket的内容
	// GameTick里面会判断是否正在连接中
	if(m_pSocketInterface)
		m_pSocketInterface->GameTick();

	if (m_pSocket2)
	{
		m_pSocket2->GameTick();
	}
}