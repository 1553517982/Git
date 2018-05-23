/*! \class CCNetworkLoop
 *  \brief 网络消息Loop
 *
 * 
 */

#ifndef __CCNetworkLoop_H__
#define __CCNetworkLoop_H__

#include "cocos2d.h"


USING_NS_CC;

class ClientSocketProxy;

class CCNetworkLoop : public Ref
{
public:

	enum SOCKETTYPE
	{
		eCSOCKET = 0,
		eTSOCKET = 1
	};

	static CCNetworkLoop*	sharedManager();
	static void				purgeSharedManager();

	CCNetworkLoop();
	~CCNetworkLoop();

	/** 
	 *  
	 *  @brief 每帧的轮询函数
	 *  @param float dt
	 *  @return void
	*/
	void					tick(float dt);
	/** 
	 *  
	 *  @brief 开始tick
	 *  @return void
	*/
	void					start();
	/** 
	 *  
	 *  @brief 结束tick
	 *  @return void
	*/
	void					stop();
	/** 
	 *  
	 *  @brief 初始化socket
	 *  @param unsigned char type
	 *  @param const char * pszOSVer
	 *  @param const char * pszInstallPath
	 *  @return int
	*/
	int						initSocket(unsigned char type, const char* pszOSVer, const char* pszInstallPath);
	ClientSocketProxy*		getSocketProxy1() const { return m_pSocketInterface; }

	// added by aXing on 2017-5-31
	// 因为需求，需要频繁的切换socket，所以在引擎里面再new多一个socket出来
	int						initSocket2(unsigned char type, const char* pszOSVer, const char* pszInstallPath);
	ClientSocketProxy*	    getSocketProxy2() const { return m_pSocket2; }

private:
	static CCNetworkLoop*	m_pShareLooper;
	ClientSocketProxy*		m_pSocketInterface;
	bool					m_bPaused;

	// added by aXing on 2017-5-31
	// 因为需求，需要频繁的切换socket，所以在引擎里面再new多一个socket出来
	ClientSocketProxy*		m_pSocket2;
	
};

#endif