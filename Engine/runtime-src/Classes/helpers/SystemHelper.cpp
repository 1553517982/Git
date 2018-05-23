#include "SystemHelpers.h"
#include "cocos2d.h"
#include "base/ccUtils.h"
#include "XCommon.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#include <CommDlg.h>
#define NO_WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料
#include <shlobj.h>
#endif
static const int _MAX_LOG_LENGTH = 16 * 1024;

USING_NS_CC;

// Obtains the absolute path from any other path.
// Returns the input path if the absolute path couldn't be resolved.
static std::string _getAbsolutePath(const std::string &filepath) {
#ifdef _WIN32
	char abs_path[MAX_PATH];
#if defined(WP8) || defined(WINRT)
	return 0
#else
	return GetFullPathNameA(filepath.c_str(), MAX_PATH, abs_path, nullptr)
#endif
#else
	char abs_path[PATH_MAX];
	return realpath(filepath.c_str(), abs_path)
#endif
		? abs_path
		: filepath;
}

void SystemHelpers::messageBox(const char* title, const char* content)
{
	if (title && content)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		WCHAR wszBuf[1024] = { 0 };
		MultiByteToWideChar(CP_UTF8, 0, title, -1, wszBuf, sizeof(wszBuf));
		CHAR szBuf[4096 + 1] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);

		WCHAR wszBuf2[1024] = { 0 };
		MultiByteToWideChar(CP_UTF8, 0, content, -1, wszBuf2, sizeof(wszBuf2));
		CHAR szBuf2[4096 + 1] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, wszBuf2, sizeof(wszBuf2), szBuf2, sizeof(szBuf2), NULL, FALSE);
#else
		const char* szBuf2 = content;
		const char* szBuf = title;
#endif
		cocos2d::MessageBox(szBuf2, szBuf);
	}

}

float SystemHelpers::gettime()
{
	return cocos2d::utils::gettime();
}

void SystemHelpers::log(const char* szText, unsigned short colorIndex)
{
	if (szText)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		HANDLE hconsole;
		hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hconsole, colorIndex);
		XLOG(szText);
		SetConsoleTextAttribute(hconsole, 0x0007);
#else	
		XLOG(szText);
#endif
	}
}

void SystemHelpers::formatlog(unsigned short colorIndex, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	char buf[_MAX_LOG_LENGTH];
	vsnprintf(buf, _MAX_LOG_LENGTH - 3, format, args);
	log(buf, colorIndex);
	va_end(args);
}

void SystemHelpers::addSearchPath(const char* path)
{
	FileUtils::getInstance()->addSearchPath(_getAbsolutePath(path));
}

std::string SystemHelpers::fromClipboard()
{
	static char s_clipboard[_MAX_LOG_LENGTH] = { 0 };
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (::OpenClipboard(NULL))
	{
		//获得剪贴板数据
		HGLOBAL hMem = GetClipboardData(CF_TEXT);
		if (NULL != hMem)
		{
			char* lpStr = (char*)::GlobalLock(hMem);
			if (NULL != lpStr)
			{
				strcpy(s_clipboard, lpStr);
				::GlobalUnlock(hMem);
			}
		}
		::CloseClipboard();
		return s_clipboard;
	}
#endif
	return s_clipboard;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)

{

	if (uMsg == BFFM_INITIALIZED)

	{

		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	}

	return 0;

}
#endif

std::string SystemHelpers::pathDialog(const char* title, const char* defaultPath)
{
	if (title == nullptr || defaultPath == nullptr)
	{
		XLOGERROR("pathDialog null");
		return "";
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	std::string default_path = _getAbsolutePath(defaultPath);
	XLOG("pathDialog default = %s", default_path.c_str());
	char result[MAX_PATH] = { 0 };

	const char *data = title;
	WCHAR wszBuf[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_UTF8, 0, data, -1, wszBuf, sizeof(wszBuf));

	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = wszBuf;
	bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_EDITBOX;

	const char *szDefaultPath = default_path.c_str();
	static WCHAR wszDefaultPath[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_UTF8, 0, szDefaultPath, -1, wszDefaultPath, sizeof(wszDefaultPath));


	bi.lParam = (long)(wszDefaultPath);//初始化路径，形如(_T("c:\\Symbian"));
	bi.lpfn = BrowseCallbackProc;

	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return "";
	}
	SHGetPathFromIDList(idl, szBuffer);
	WideCharToMultiByte(CP_ACP, 0, szBuffer, sizeof(szBuffer), result, sizeof(result), NULL, FALSE);
	return result;
#endif
	return "";
}

//取32位中的低16位的前8位数
unsigned int SystemHelpers::low8Word(unsigned int number){
	return (number & 0xff);
}
//取32位中的低16位的后8位数
unsigned int SystemHelpers::high8Word(unsigned int number){
	return (number >> 8);
}

unsigned int SystemHelpers::lowByte(unsigned int number)
{
	return (number & 0xffff);
}

unsigned int SystemHelpers::highByte(unsigned int number)
{
	return (number >> 16);
}

int SystemHelpers::rshift(int number, int pos)
{
	return (number >> pos);
}

int SystemHelpers::lshift(int number, int pos)
{
	return (number << pos);
}

unsigned int SystemHelpers::bor(unsigned int n1, unsigned int n2)
{
	return n1 & n2;
}

unsigned int SystemHelpers::band(unsigned int n1, unsigned int n2)
{
	return n1 & n2;
}

unsigned int SystemHelpers::binvert(unsigned int n1)
{
	return ~n1;
}

unsigned int SystemHelpers::bclear(unsigned int n1, unsigned int n2)
{
	return n1 & (~n2);
}