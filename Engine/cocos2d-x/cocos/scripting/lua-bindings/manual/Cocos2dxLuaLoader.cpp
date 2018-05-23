/****************************************************************************
Copyright (c) 2011-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "Cocos2dxLuaLoader.h"
#include <string>
#include <algorithm>

#include "CCLuaStack.h"
#include "CCLuaEngine.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
using namespace std;
#if ( ( defined WIN32 ) || ( defined __APPLE__ ) )
#include <map>
#include <string>

using namespace cocos2d;
class CLuaPackFile
{
	struct SFileData
	{
		unsigned int nDataOffiset;
		unsigned int nDataLength;
	};

public:
	static CLuaPackFile & Inst()
	{
		static CLuaPackFile inst;
		return inst;
	}
	CLuaPackFile()
	{
		// 打开lua包
		FileUtils* utils = FileUtils::getInstance();
		ssize_t chunkSize = 0;
		pBuff = utils->getFileData("LuaPack.luap", "rb", &chunkSize);
		if (pBuff)
		{
			// 首先读取一次，看看文件名长度
			unsigned int nNameLength = 0;
			unsigned int nFileOffiset = 0;
			do
			{
				nNameLength = *(unsigned int *)(pBuff + nFileOffiset);
				if (nNameLength == 0xFFFFFFFF)
					break;
				nFileOffiset += (nNameLength + sizeof(unsigned int) * 3);	// 其中一个是名字长度，一个是文件位置偏移，一个是文件长度
			} while (nFileOffiset < chunkSize);

			nFileOffiset += sizeof(unsigned int);	// 最后还有个0xFFFFFFFF

			// 然后重新读一次
			nNameLength = 0;
			unsigned int nCurOffiset = 0;
			do
			{
				nNameLength = *(unsigned int *)(pBuff + nCurOffiset);
				if (nNameLength == 0xFFFFFFFF)
					break;

				SFileData & data = m_FileMap[string((char *)(pBuff + nCurOffiset + sizeof(unsigned int)), nNameLength)];

				data.nDataOffiset = nFileOffiset;
				data.nDataLength = *(unsigned int *)(pBuff + nCurOffiset + nNameLength + sizeof(unsigned int) * 2);
				nFileOffiset += data.nDataLength;

				nCurOffiset += (nNameLength + sizeof(unsigned int) * 3);	// 其中一个是名字长度，一个是文件位置偏移，一个是文件长度
			} while (nCurOffiset < chunkSize);
		}
	}
	~CLuaPackFile()
	{
		if (pBuff)
			free(pBuff);
	}
	// 获取文件
	bool LoadFile(string strName, char ** pData, unsigned int * pLength)
	{
		FileMap::iterator it = m_FileMap.find(strName);
		if (it == m_FileMap.end())
			return false;
		*pLength = it->second.nDataLength;
		*pData = (char *)(pBuff + it->second.nDataOffiset);
		return true;
	}

	unsigned char * pBuff;
	typedef std::map< string, SFileData > FileMap;
	FileMap m_FileMap;
};

#endif	// #ifdef WIN32

using namespace cocos2d; 

extern "C"
{
	static const std::string FILE_EXT = ".lua";

	int cocos2dx_lua_loader(lua_State *L)
	{
		std::string filename(luaL_checkstring(L, 1));

		char * pData = 0;
		unsigned int nDataLength = 0;

		if (CNewLoader::Inst().LoadOutSideLua( filename, &pData, &nDataLength ) )
		{
			LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
			stack->luaLoadBuffer(L, pData, nDataLength, (filename + FILE_EXT).c_str());

			// 如果是外部的，就得free一下
			free(pData);
			return true;
		}
		else if (!JHLoadLuaFile((filename + FILE_EXT).c_str(), &pData, &nDataLength, false))
		{
			CCLOG("can not get file data of %s", (filename + FILE_EXT).c_str());
			return false;
		}
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->luaLoadBuffer(L, pData, nDataLength, (filename + FILE_EXT).c_str());
		return true;
	}

	bool JHLoadLuaFile(const char * strName, char ** pData, unsigned int * pLength, bool bNeedAddBack)
	{
		//size_t pos = filename.rfind(BYTECODE_FILE_EXT);
		//if (pos != std::string::npos)
		//{
		//	filename = filename.substr(0, pos);
		//}
		//else
		//{
		//	pos = filename.rfind(NOT_BYTECODE_FILE_EXT);
		//	if (pos == filename.length() - NOT_BYTECODE_FILE_EXT.length())
		//	{
		//		filename = filename.substr(0, pos);
		//	}
		//}

		string filename = strName;
		
		int pos = filename.find_first_of(".");
		while (pos != std::string::npos)
		{
			filename.replace(pos, 1, "/");
			pos = filename.find_first_of(".");
		}

		// 这个很无语
		pos = filename.find_first_of("/lua");
		while (-1 != pos)
		{
			if (pos == filename.length() - 4 || pos == filename.length() - 5)	// lua 及luac
				filename.replace(pos, 1, ".");
			pos = filename.find("/lua", pos + 1);
		}

		// search file in package.path
		//unsigned char* chunk = nullptr;
		//ssize_t chunkSize = 0;
		//std::string chunkName;

		/*
		FileUtils* utils = FileUtils::getInstance();

		lua_getglobal(L, "package");
		lua_getfield(L, -1, "path");
		std::string searchpath(lua_tostring(L, -1));
		lua_pop(L, 1);
		size_t begin = 0;
		size_t next = searchpath.find_first_of(";", 0);

		do
		{
		if (next == std::string::npos)
		next = searchpath.length();
		std::string prefix = searchpath.substr(begin, next);
		if (prefix[0] == '.' && prefix[1] == '/')
		{
		prefix = prefix.substr(2);
		}

		pos = prefix.find("?.lua");
		chunkName = prefix.substr(0, pos) + filename + FILE_EXT;
		if (utils->isFileExist(chunkName))
		{
		chunk = utils->getFileData(chunkName.c_str(), "rb", &chunkSize);
		break;
		}

		begin = next + 1;
		next = searchpath.find_first_of(";", begin);
		} while (begin < (int)searchpath.length());

		*/
		std::string strFileName = bNeedAddBack ? filename + FILE_EXT : filename;
				
		if (CNewLoader::Inst().SyncLoadFile(strFileName.c_str(), pData, pLength))
			return true;
		else
		{
#if ( defined WIN32 && !defined RAYMOND_PACK_DEBUG )
			if (CLuaPackFile::Inst().LoadFile(strFileName, pData, pLength))
				return true;
#endif
			return false;
		}
	}
}

extern bool JHLoadLuaFileToSys(lua_State *L, const char * strName)
{
	std::string filename(luaL_checkstring(L, 1));

	char * pData = 0;
	unsigned int nDataLength = 0;

	if (CNewLoader::Inst().LoadOutSideLua(filename, &pData, &nDataLength))
	{
		LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
		stack->luaLoadBuffer(L, pData, nDataLength, (filename + FILE_EXT).c_str());

		// 如果是外部的，就得free一下
		free(pData);
		return true;
	}
	else if (!JHLoadLuaFile(strName, &pData, &nDataLength))
	{
		CCLOG("can not get file data of %s", (filename + FILE_EXT).c_str());
		return false;
	}
	LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->luaLoadBuffer(L, pData, nDataLength, (filename + FILE_EXT).c_str());
	return true;
}

