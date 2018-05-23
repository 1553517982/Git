#include "ClientSocketProxy.h"
#include "CCNetworkLoop.h"

ClientSocketProxy* ClientSocketProxy::ToCS(void* cs)
{
	return (ClientSocketProxy*)cs;
}

int ClientSocketProxy::initSocket1(unsigned char type, const char* pszOSVer, const char* pszInstallPath)
{
	return CCNetworkLoop::sharedManager()->initSocket(type, pszOSVer, pszInstallPath);
}

ClientSocketProxy* ClientSocketProxy::getSocket1()
{
	return CCNetworkLoop::sharedManager()->getSocketProxy1();
}

int ClientSocketProxy::initSocket2(unsigned char type, const char* pszOSVer, const char* pszInstallPath)
{
	return CCNetworkLoop::sharedManager()->initSocket2(type, pszOSVer, pszInstallPath);
}

ClientSocketProxy* ClientSocketProxy::getSocket2()
{
	return CCNetworkLoop::sharedManager()->getSocketProxy2();
}

