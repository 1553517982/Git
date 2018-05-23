#include "main.h"
#include "SimulatorWin.h"
#include <shellapi.h>
#include "ConsoleNode.h"
#include "minidump.h"
#include <direct.h>

#if _MSC_VER > 1700
#if ( defined RAYMOND_PACK_DEBUG )
#pragma comment(lib,"libcocos2d_PackDebug.lib")
#elif ( defined _DEBUG )
#pragma comment(lib,"libcocos2d_debug.lib")
#else
#pragma comment(lib,"libcocos2d.lib")
#endif
#pragma comment(lib,"libSpine.lib")
#pragma comment(lib,"libsimulator.lib")
#else
#pragma comment(lib,"libcocos2d.lib")
#pragma comment(lib,"libSpine.lib")
#pragma comment(lib,"libsimulator.lib")
#endif

LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	char creashFile[100];
	getcwd(creashFile, 100);
	strcat(creashFile, "\\game.dmp");
	CreateMiniDump(pExceptionInfo, creashFile);
	return EXCEPTION_EXECUTE_HANDLER;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	ConsoleNode::instance()->startCatchConsole();
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    auto simulator = SimulatorWin::getInstance();
    int ret = simulator->run();
	return ret;
}
