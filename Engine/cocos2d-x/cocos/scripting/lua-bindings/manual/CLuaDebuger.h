#ifndef __CLUA_DEBUGER_H_2013_05_22__
#define __CLUA_DEBUGER_H_2013_05_22__

#ifndef RAYMOND_PACK_DEBUG

struct lua_State;
struct lua_Debug;
#include <set>
#include <string>
namespace cocos2d
{
	class CLuaBreakPoint
	{
		typedef unsigned int uint32;
		typedef int int32;

		std::string m_cmsModelName;
		uint32 m_nLineNum;
	
	public:
		CLuaBreakPoint(std::string cmsModelName, uint32 nLineNum);
		// 因为stl里面需要，所以重载一下
		const CLuaBreakPoint & operator =( const CLuaBreakPoint & otherPoint );
		bool operator < ( const CLuaBreakPoint & otherPoint ) const;
		bool operator == ( const CLuaBreakPoint & otherPoint ) const;

		std::string GetModelName() const;
		uint32 GetLine() const;
	};

	class CLuaDebuger
	{
		typedef unsigned int uint32;
		typedef int int32;

	public:
		CLuaDebuger( lua_State * pState );
		~CLuaDebuger();


		// 返回
		void StepOut();

		// 进入下一层
		void StepIn();

		// 进入下一行
		void StepNext();

		// 开始debug
		bool Debug();

	private:
		lua_State * m_pState;
		int32 m_nRunningStackLevel;
		int32 m_nBreakStackLevel;
		std::set< CLuaBreakPoint >	m_BreakPointSet;

		static int32 GetRunningStackLevel( lua_State * pState );
		static void HookProc( lua_State * pState, lua_Debug * pDebug );
		static uint32 GetCurLine( lua_State * pState, uint32 nLevel );

		void LineHook( lua_State * pState, lua_Debug * pDebug );
		bool HitBreakPoint( lua_State * pState, lua_Debug * pDebug );
		bool HaveBreakPoint();
		// 读取输入
		std::string ReadWord(bool bIsNewLine = false);
		// 打印出附近的代码
		void ShowFile(std::string cmsFile, int32 nLine);

		// 打印堆栈
		bool _PrintFrame(lua_State * L, uint32 nLevel);	// 用于打印堆栈
		int32 _PrintStack(lua_State * L);
		void _PrintValue(lua_State * L, int32 nIdx);
		bool IsNum(const char & dt) const;
		bool IsNum(std::string &) const;
	};
}

#endif

#endif