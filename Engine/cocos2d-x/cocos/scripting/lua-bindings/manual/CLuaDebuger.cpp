#ifndef __CLUA_DEBUGER_CPP_2013_05_22__
#define __CLUA_DEBUGER_CPP_2013_05_22__
#ifndef RAYMOND_PACK_DEBUG

extern "C" 
{
	#include "lua.h"
}

#include "CLuaDebuger.h"
#include "CCPlatformMacros.h"
#include "CCConsole.h"
#include "Cocos2dxLuaLoader.h"
#include "CCLuaEngine.h"
#include <iostream>

#define NEAR_LINE 4	// 显示上3行跟下3行的附近代码

namespace cocos2d
{
	typedef unsigned int uint32;
	typedef int int32;

	CLuaBreakPoint::CLuaBreakPoint(std::string cmsModelName, uint32 nLineNum)
		:m_cmsModelName( cmsModelName )
		,m_nLineNum( nLineNum )
	{
		
	}

	const CLuaBreakPoint & CLuaBreakPoint::operator = ( const CLuaBreakPoint & otherPoint )
	{
		this->m_cmsModelName = otherPoint.m_cmsModelName;
		this->m_nLineNum = otherPoint.m_nLineNum;
		return *this;
	}

	bool CLuaBreakPoint::operator < ( const CLuaBreakPoint & otherPoint ) const
	{
		bool bRes = m_cmsModelName < otherPoint.m_cmsModelName;
		if( bRes )
			return true;
		else if( m_cmsModelName == otherPoint.m_cmsModelName )
			return m_nLineNum < otherPoint.m_nLineNum;
		else
			return false;
	}

	bool CLuaBreakPoint::operator == ( const CLuaBreakPoint & otherPoint ) const
	{
		return m_cmsModelName == otherPoint.m_cmsModelName && m_nLineNum == m_nLineNum;
	}

	std::string CLuaBreakPoint::GetModelName() const
	{
		return m_cmsModelName;
	}

	uint32 CLuaBreakPoint::GetLine() const
	{
		return m_nLineNum;
	}

	CLuaDebuger::CLuaDebuger( lua_State * pState )
		:m_pState( pState )
	{
	}

	CLuaDebuger::~CLuaDebuger()
	{
	}

	bool CLuaDebuger::_PrintFrame(lua_State * L, uint32 nLevel)	// 用于打印堆栈
	{
		lua_Debug ld;
		if (!lua_getstack(L, nLevel, &ld))	// 没东西？
			return false;

		//lua_getinfo( L, "n", &ld );
		//lua_getinfo( L, "S", &ld );
		//lua_getinfo( L, "l", &ld );
		lua_getinfo(L, "nSl", &ld);	// 跟上面是一样的，话说你lua这样搞，不看你代码怎么开发啊。。。

		//CMightLog & log = _GetScriptLog(L);
		//log << "###" << nLevel << " " << (ld.name ? ld.name : "(trunk)") << " " << ld.source << ":" << ld.currentline;
		//if (ld.source[0] == '@')
		//	log << ld.currentline;
		//log << endl;

		CCLOG("### %d %s %s:%d", nLevel, ld.name, ld.source, ld.currentline);

		return true;
	}

	int32 CLuaDebuger::_PrintStack(lua_State * L)
	{
		if (lua_gettop(L) && lua_isstring(L, -1))
		{
			CCLOG(lua_tostring(L, -1));
			lua_pop(L, 1);
		}

		for (int32 i = 0; _PrintFrame(L, i); i++);
		return 0;
	}

	void CLuaDebuger::_PrintValue(lua_State * L, int32 nIdx)
	{
		lua_pushvalue(L, nIdx);
		lua_getglobal(L, "dump");
		lua_insert(L, -2);
		lua_call(L, 1, 0);
	}

	bool CLuaDebuger::IsNum(const char & dt) const
	{
		return '0' <= dt && dt <= '9';
	}

	bool CLuaDebuger::IsNum(std::string & str) const
	{
		int nLength = str.length();
		if (0 == nLength)
			return false;
		const char * pBuff = str.c_str();
		for (int i = 0; i < nLength; i++)
		{
			if (!IsNum(pBuff[i]))
				return false;
		}
		return true;
	}

	void CLuaDebuger::StepOut()
	{
		lua_sethook( m_pState, HookProc, LUA_MASKCALL | LUA_MASKRET | (HaveBreakPoint()?LUA_MASKLINE:0), 0 );
		m_nRunningStackLevel = GetRunningStackLevel( m_pState );
		m_nBreakStackLevel = m_nRunningStackLevel - 1;
	}

	void CLuaDebuger::StepIn()
	{
		lua_sethook( m_pState, HookProc, LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE, 0 );
		m_nRunningStackLevel = GetRunningStackLevel( m_pState );
		m_nBreakStackLevel = INT_MAX;
	}

	void CLuaDebuger::StepNext()
	{
		lua_sethook( m_pState, HookProc, LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE, 0 );
		m_nRunningStackLevel = GetRunningStackLevel( m_pState );
		m_nBreakStackLevel = m_nRunningStackLevel;
	}

	bool CLuaDebuger::Debug()
	{	
#ifdef WIN32
		_PrintStack( m_pState );
		int32 nCurLevel = 0;
		uint32 nCurLine = GetCurLine( m_pState, nCurLevel );
		while( true )
		{
			std::string cmsWord = this->ReadWord(true);
			
			if( cmsWord == "c" || cmsWord == "continue" )
			{
				if( !HaveBreakPoint() )
				{
					LuaEngine::getInstance()->m_pDebug = 0;
					delete this;
				}
				else
				{
					lua_sethook( m_pState, HookProc, LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE, 0 );
				}
				break;
			}
			else if( cmsWord == "help" )
			{
				CCLOG(
					"\n"
					"continue/c         continue program\n"
					"next/n             next line \n"
					"in/i               step in function \n"
					"out/o              step out function \n"
					"backtrace/bt       check the program trace \n"
					"frame/f n          step to the N frame \n"
					"print/p v          print the value V \n"
					"list/l             list the lua code around \n"
					//"load/lo file       reload the file \n"
					"break/b file:line  set a new breakpoint \n"
					"del/d n            delete the breakpoint \n"
					"info               check the breakpoint \n"
					"e	code			execute the code\n"
					"quit/exit/q        quit \n"
					);
			}
			else if( cmsWord == "quit" || cmsWord == "exit" || cmsWord == "q" )
			{
				//exit(0);
				return false;
			}
			else if( cmsWord == "next" || cmsWord == "n" )
			{
				StepNext();
				break;
			}
			else if( cmsWord == "in" || cmsWord == "i" )
			{
				StepIn();
				break;
			}
			else if( cmsWord == "out" || cmsWord == "o" )
			{
				StepOut();
				break;
			}
			else if( cmsWord == "backtrace" || cmsWord == "bt" )
			{
				for( int32 i = 0; _PrintFrame( m_pState, i ); i++ );
			}
			else if( cmsWord == "info" )
			{
				uint32 num = 1;
				for (std::set<CLuaBreakPoint>::iterator it = m_BreakPointSet.begin(); it != m_BreakPointSet.end(); it++, num++)
				{
					CCLOG("%d、%s:%d", num, it->GetModelName(), it->GetLine());
				}
			}
			else if( cmsWord == "list" || cmsWord == "l" )
			{
				lua_Debug ld;
				if( lua_getstack( m_pState, nCurLevel, &ld ) )
				{
					lua_getinfo( m_pState, "nSl", &ld );
					std::string cms = ld.source;
					ShowFile( cms, ld.currentline );
				}
			}
			else if( cmsWord == "frame" || cmsWord == "f" )
			{
				std::string cmsNum = ReadWord(false);

				if (!IsNum(cmsNum))
				{
					CCLOG("frame num");
					continue;
				}

				int nLevel = atoi( cmsNum.c_str() );

				lua_Debug ld;
				if( lua_getstack( m_pState, nLevel, &ld ) )
				{
					nCurLevel = nLevel;		// 记录当前去到的层
					nCurLine = GetCurLine( m_pState, nCurLevel );
				}
				_PrintFrame( m_pState, nCurLevel );
			}
			else if (cmsWord == "e")
			{
				std::string cms = ReadWord(false);
				if (cms.length() == 0)
				{
					CCLOG("e script");
					continue;
				}
				LuaEngine::getInstance()->RunString(cms);
			}
			else if( cmsWord == "print" || cmsWord == "p" )
			{
				std::string cms = ReadWord(false);
				if( cms.length() == 0 )
				{
					CCLOG("print name");
					continue;
				}			

				lua_Debug ld;
				if( lua_getstack( m_pState, nCurLevel, &ld ) )
				{
					std::string cmsDebugPrint;
					cmsDebugPrint = std::string("dump(") + cms + ")";
					
					bool bFound = false;
					const char * name = 0;
					int32 n = 1;
					while( !bFound && ( name = lua_getlocal( m_pState, &ld, n++ ) ) != 0 )
					{
						if( cms == name )
						{
							bFound = true;
							_PrintValue( m_pState, -1 );
						}
						lua_pop( m_pState, 1 );
					}	

					// 看看是不是闭包里面的
					n = 1;
					while( !bFound && ( name = lua_getupvalue( m_pState, -1, n++ ) ) != 0 )
					{
						if( cms == name )
						{
							bFound = true;
							_PrintValue( m_pState, -1 );
						}
						lua_pop( m_pState, 1 );
					}

					// 看看是不是全局变量
					if( !bFound )
					{
						lua_getglobal( m_pState, cms.c_str() );
						if( !lua_isnil( m_pState, -1 ) )
						{
							bFound = true;
							_PrintValue( m_pState, -1 );
						}
						lua_pop( m_pState, 1 );
					}

					if( !bFound )	// 可能是一个表达式什么的，尝试直接print
					{
						std::string cmsString = std::string("print(") + cms + ")";
						LuaEngine::getInstance()->RunString(cmsString);
					}
				}
			}
			//else if( cmsWord == "load" || cmsWord == "lo" )
			//{
			//	std::string cmsFile = ReadWord(false);
			//	if (0 == cmsFile.length())
			//		CCLOG("load file");
			//	else
			//	{
			//		//CMightScript * pScript = CMightScript::Inst( m_pState );
			//		bool bRes = JHLoadLuaFileToSys(m_pState, cmsFile.c_str());
			//		CCLOG("load %s %s", cmsFile.c_str(), (bRes ? "success" : "failed"));
			//	}
			//}
			else if( cmsWord == "break" || cmsWord == "b" )
			{
				lua_Debug ld;
				std::string cmsKeyWord = ReadWord(false);
				std::string cmsSource;
				int32 nBreakLine = nCurLine;
				
				if( cmsKeyWord.length() == 0 )
				{
					lua_getstack( m_pState, nCurLevel, &ld );
					lua_getinfo( m_pState, "S", &ld );
					cmsSource = ld.source;
				}
				else
				{
					if (IsNum(cmsKeyWord))
					{
						lua_getstack( m_pState, nCurLevel, &ld );
						lua_getinfo( m_pState, "S", &ld );
						cmsSource = ld.source;
						nBreakLine = atoi( cmsKeyWord.c_str() );
					}
					else
					{
						int32 nPos = cmsKeyWord.find( ":" );
						if( nPos == -1 )
						{
							CCLOG("break line or file:line" );
							continue;
						}

						cmsSource = std::string(cmsKeyWord.c_str(), nPos);// cmsKeyWord.Mid(0, nPos);
						std::string strLine = std::string( &(cmsKeyWord.c_str())[nPos + 1], cmsKeyWord.length() - nPos - 1);
						nBreakLine = atoi(strLine.c_str());
						//nBreakLine = Str2I( cmsKeyWord.Mid( nPos + 1, cmsKeyWord.GetLength() - nPos - 1 ) );
					}
				}

				if( cmsSource.length() && 0 != nBreakLine )
				{
					m_BreakPointSet.insert( CLuaBreakPoint( cmsSource, nBreakLine ) );
					CCLOG("break %s:%d", cmsSource.c_str(), nBreakLine);
					//CMightScript::_GetScriptLog( m_pState ) << "break " << cmsSource << ":" << nBreakLine << endl;
				}
				else
				{
					CCLOG("break line or file:line");
					//CMightScript::_GetScriptLog(m_pState) << "break 行号/ 文件:行号" << endl;
				}
			
			}
			else if( cmsWord == "del" || cmsWord == "d" )
			{
				std::string cmsNum = ReadWord(false);
				if (!IsNum(cmsNum))
					CCLOG("del break point num");
				else
				{
					int32 nNum = atoi( cmsNum.c_str() );
					int32 i = 1;
					for( std::set<CLuaBreakPoint>::iterator it = m_BreakPointSet.begin(); it != m_BreakPointSet.end(); it++, i++ )
					{	if( i == nNum ) { m_BreakPointSet.erase( it ); break; }	}
				}
			}
			else
			{
				CCLOG("can not reconize");
			}
		}
#endif

		return true;
	}

	int32 CLuaDebuger::GetRunningStackLevel( lua_State * pState )
	{
		lua_Debug ldeb;
		int32 nLevel = 0;
		for( ;lua_getstack( pState, nLevel, &ldeb );nLevel++ );
		return nLevel;
	}

	void CLuaDebuger::HookProc( lua_State * pState, lua_Debug * pDebug )
	{
		LuaEngine::getInstance()->m_pDebug->LineHook(pState, pDebug);
	}

	bool CLuaDebuger::HitBreakPoint(lua_State * pState, lua_Debug * pDebug)
	{
		if( !HaveBreakPoint() )
			return false;

		lua_getinfo( pState, "S", pDebug );
		lua_getinfo( pState, "l", pDebug );
		if( m_BreakPointSet.find( CLuaBreakPoint( pDebug->source, pDebug->currentline ) ) != m_BreakPointSet.end() )
			return true;
		return false;
	}

	bool CLuaDebuger::HaveBreakPoint()
	{
		return !m_BreakPointSet.empty();
	}

	void CLuaDebuger::LineHook( lua_State * pState, lua_Debug * pDebug )
	{
		bool bHitBreakPoint = HitBreakPoint( pState, pDebug );

		if( m_nBreakStackLevel != -1 )
		{
			switch( pDebug->event )
			{
			case LUA_HOOKCALL:
				m_nRunningStackLevel = GetRunningStackLevel( pState );
				if( m_nBreakStackLevel < m_nRunningStackLevel )
					lua_sethook( m_pState, HookProc, LUA_MASKCALL | LUA_MASKRET | (HaveBreakPoint()?LUA_MASKLINE:0), 0 );
				return;
			case LUA_HOOKRET:
				m_nRunningStackLevel = GetRunningStackLevel( pState ) - 1;
				if( m_nBreakStackLevel >= m_nRunningStackLevel )
					lua_sethook( m_pState, HookProc, LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE, 0 );
				return;
			// 5.1没？
			//case LUA_HOOKTAILCALL:
			//	break;
			case LUA_HOOKLINE:
				break;
			default:
				// why
				return;
			}

			if( !bHitBreakPoint && m_nBreakStackLevel >= 0 && m_nBreakStackLevel < m_nRunningStackLevel )
				return;

			m_nRunningStackLevel = m_nBreakStackLevel = -1;
		}
		else
		{
			if( !bHitBreakPoint || pDebug->event != LUA_HOOKLINE )
				return;
		}
		
		lua_sethook( pState, HookProc, 0, 0 );
	
		Debug();
	}
	std::string CLuaDebuger::ReadWord(bool bIsNewLine /*= false */)
	{
		//return GetCin( bIsNewLine );
#ifdef WIN32
		static char g_Cin[256];
		if (bIsNewLine)
			CCLOG("gdb()");
		std::cin >> g_Cin;
		//scanf("%s", g_Cin);
		return g_Cin;
#else
		return "";
#endif
	}

	uint32 CLuaDebuger::GetCurLine( lua_State * pState, uint32 nLevel )
	{
		lua_Debug ld;
		lua_getstack( pState, nLevel, &ld );
		lua_getinfo( pState, "l", &ld );
		return ld.currentline;
	}

	void CLuaDebuger::ShowFile(std::string cmsFile, int32 nLine)
	{
		char * pData = 0;
		unsigned int nFileSize = 0;
		if( !JHLoadLuaFile(cmsFile.c_str(), &pData, &nFileSize, false) )
		{
			CCLOG("can not load the file");
			return;
		}
		
		if( 0 == nFileSize )
		{
			CCLOG("file size wrong");
			return;
		}

		int32 nStartLine = nLine - NEAR_LINE;
		nStartLine = nStartLine > 0 ? nStartLine : 0;

		int32 nEndLine = nLine + NEAR_LINE;
		int32 nCurLine = 1;
		uint32 nCurReadPos = 0;
		while( nCurLine < nStartLine )
		{
			for( ; nCurReadPos < nFileSize; nCurReadPos++ )
			{
				if (pData[nCurReadPos] == '\n')
				{
					nCurLine++;
					nCurReadPos++;
					break;
				}
			}

			if( nCurReadPos >= nFileSize )
			{
				CCLOG("file error");
				return;
			}
		}
		
		int32 nStartPos = nCurReadPos;
		while( nCurLine < nEndLine )
		{
			for( ; nCurReadPos < nFileSize; nCurReadPos++ )
			{
				if (pData[nCurReadPos] == '\n')
				{
					nCurLine++;
					nCurReadPos++;
					break;
				}
			}

			if( nCurReadPos >= nFileSize )
			{
				std::string cms = std::string(&pData[nStartPos], nCurReadPos - nStartPos);
				int nPos = cms.find_first_of("\n");
				std::string tmp;
				if (-1 != nPos)
					tmp = std::string(cms.c_str(), nPos);

				CCLOG("%d\t%s", nCurLine, tmp.c_str());
				nStartPos = nCurReadPos;
				break;
			}

			std::string cms = std::string(&pData[nStartPos], nCurReadPos - nStartPos);
			int nPos = cms.find_first_of("\n");
			std::string tmp;
			if (-1 != nPos)
				tmp = std::string(cms.c_str(), nPos);

			CCLOG("%d\t%s", nCurLine - 1, tmp.c_str());
			nStartPos = nCurReadPos;
		}
	}
}

#endif

#endif