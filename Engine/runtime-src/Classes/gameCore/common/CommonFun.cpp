
#include "CommonFun.h"
#include "cocos2d.h"

namespace commonFunction
{
	//////////////////////////////////
	std::string coverMulitByteToWideChar(const char *data)
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		{
			WCHAR wszBuf[kMaxLogLen + 1] = { 0 };
			MultiByteToWideChar(CP_UTF8, 0, data, -1, wszBuf, sizeof(wszBuf));
			CHAR szBuf[kMaxLogLen + 1] = { 0 };
			WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
			return std::string(szBuf);
		}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
		char buf[kMaxLogLen + 1];
		XSNPRINTFA(buf, sizeof(buf) / sizeof(char), "%c",data);
		return std::string(buf);
	}
#endif

		return std::string("");
	}

	//////////////////////////////////
	long coverToUnicodeIndex(const char *data)
	{
		if (!data)
			return 0;

		std::string tempInfo(data);
		unsigned long returnInfo = 0;
		unsigned short cur = 0;

		for (std::string::reverse_iterator it = tempInfo.rbegin(); it != tempInfo.rend(); it++)
		{
			unsigned short temp = (unsigned short)(unsigned char)*it;
			if (tempInfo.size() > 1)
			{
				if (cur == tempInfo.size() - 1)
					temp &= 0x0f;
				else
					temp &= 0x3f;
			}
			returnInfo |= temp << (6 * cur);
			cur++;
		}

		return returnInfo;
	}

	//////////////////////////////////
	long coverToUTF8Index(const char *data)
	{
		if (!data)
			return 0;

		std::string tempInfo(data);
		unsigned long returnInfo = 0;
		unsigned short cur = 0;

		for (std::string::iterator it = tempInfo.begin(); it != tempInfo.end(); it++)
		{
			returnInfo |= (long)(unsigned char)*it << (8 * cur);
			cur++;
		}

		return returnInfo;
	}

	//////////////////////////////////
	int XSNPRINTFA(char *dst, int len, const char *format, ...)
	{
		if (NULL == dst || len <= 0 || NULL == format) return -1;
		va_list va;
		va_start(va, format);
		int ret = vsnprintf(dst, len, format, va);
		if (ret >= len) ret = -1;
		va_end(va);
		dst[len - 1] = '\0';
		return ret;
	}

	//////////////////////////////////
	int VSNPRINTFA(char* dst, int len, const char* format, va_list args)
	{
		if (NULL == dst || len <= 0 || NULL == format) return -1;
		int ret = vsnprintf(dst, len, format, args);
		if (ret >= len) ret = -1;
		dst[len - 1] = '\0';
		return ret;
	}

	//////////////////////////////////
	unsigned short getUTF8Len(char arg)
	{
		unsigned short len = 1;
		for (int i = 0; i < 6; i++)
		{
			if (arg & 0x80)
				len++;
			else
			{
				if (i > 1)
					len -= 1;
				break;
			}
			arg <<= 1;
		}
		return len;
	}

	//////////////////////////////////
	unsigned short getUTF8Len(char *arg)
	{
		char temp = *arg;
		unsigned short len = 1;
		for (int i = 0; i < 6; i++)
		{
			if (temp & 0x80)
				len++;
			else
			{
				if (i > 1)
					len -= 1;
				break;
			}
			temp <<= 1;
		}
		return len;
	}

	//////////////////////////////////
	void splitInofByTarget(const char *arg, const char *tar, std::list<std::string> &info)
	{
		char *temp = strtok(const_cast<char*>(arg), tar);
		while (temp != NULL)
		{
			std::string spriteinfo(temp);
			info.push_back(spriteinfo);
			temp = strtok(NULL, tar);
		}
	}

	UINT64 STRING_TO_UINT64(const char* string)
	{
		UINT64 lValue = 0;
		sscanf(string, "%llx", &lValue);
		return lValue;
	}
	const char* UINT64_TO_STRING(UINT64 value)
	{
		static char s[64];
		sprintf(s, "0x%llx", value);
		const char *c = s;
		return c;
	}

	INT64 STRING_TO_INT64(const char* string)
	{
		INT64 lValue = 0;
		sscanf(string, "%llx", &lValue);
		return lValue;
	}
	const char* INT64_TO_STRING(INT64 value)
	{
		static char s[64];
		sprintf(s, "0x%llx", value);
		const char *c = s;
		return c;
	}
}
