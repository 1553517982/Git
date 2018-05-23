#include "XLambda.h"
#include "CCLuaEngine.h"
#include "XCommon.h"

static LuaStack* s_pkLuaStack = NULL;
unsigned int XLambda::s_lambda_count = 0;

XLambda::XLambda()
{
	s_lambda_count++;
}

XLambda::~XLambda()
{
	s_lambda_count--;
}

XLambdaHolder::XLambdaHolder(XLambda* lambda) : m_lambda(NULL)
{
	XAssert(lambda != NULL, "lambda != NULL");
	CC_SAFE_RELEASE_NULL(m_lambda);
	m_lambda = lambda;
	CC_SAFE_RETAIN(m_lambda);
}

XLambdaHolder::~XLambdaHolder()
{
	CC_SAFE_RELEASE_NULL(m_lambda);
}

std::shared_ptr<XLambdaHolder> XLambdaHolder::create(XLambda* lambda)
{
	auto p = new XLambdaHolder(lambda);
	return std::shared_ptr<XLambdaHolder>(p);
}

XLambdaLua::XLambdaLua() : m_handle(0), m_argCount(0), m_bBegined(false)
{

}

XLambdaLua::~XLambdaLua()
{
	XAssert(s_pkLuaStack, "s_pkLuaStack == NULL");
	cleanup();

}


XLambdaLua* XLambdaLua::create(LUA_FUNCTION handle)
{
	auto p = new XLambdaLua();
	p->setLambda(handle);
	p->autorelease();
	return p;
}

void XLambdaLua::setLambda(LUA_FUNCTION handle)
{
	m_handle = handle;
	m_argCount = 0;
}

void XLambdaLua::pushInt(int val)
{
	XAssert(s_pkLuaStack, "s_pkLuaStack == NULL");
	XAssert(m_handle != 0, "m_handle == 0");
	s_pkLuaStack->pushInt(val);
	m_argCount++;
}

void XLambdaLua::pushFloat(float val)
{
	XAssert(s_pkLuaStack, "s_pkLuaStack == NULL");
	XAssert(m_handle != 0, "m_handle == 0");
	s_pkLuaStack->pushFloat(val);
	m_argCount++;
}

void XLambdaLua::pushString(const char* val)
{
	XAssert(s_pkLuaStack, "s_pkLuaStack == NULL");
	XAssert(m_handle != 0, "m_handle == 0");
	s_pkLuaStack->pushString(val);
	m_argCount++;
}
void XLambdaLua::pushObject(Ref* objectValue, const char* typeName)
{
	XAssert(s_pkLuaStack, "s_pkLuaStack == NULL");
	XAssert(m_handle != 0, "m_handle == 0");
	s_pkLuaStack->pushObject(objectValue, typeName);
	m_argCount++;
}

void XLambdaLua::pushValueMap(const ValueMap* dict)
{
	XAssert(s_pkLuaStack, "s_pkLuaStack == NULL");
	XAssert(m_handle != 0, "m_handle == 0");
	lua_State* _state = s_pkLuaStack->getLuaState();
	lua_newtable(_state);                                              /* L: table */
	for (auto it = dict->begin(); it != dict->end(); ++it)
	{
		lua_pushstring(_state, it->first.c_str());                     /* L: table key */
		lua_pushstring(_state, it->second.asString().c_str());         /* L: table key value */
		lua_rawset(_state, -3);										   /* table.key = value, L: table */
	}
	m_argCount++;
}

void XLambdaLua::cleanup()
{
	if (m_handle)
	{
		m_argCount = 0;
		m_bBegined = false;
		s_pkLuaStack->removeScriptHandler(m_handle);
		m_handle = 0;
	}
}

void XLambdaLua::begin()
{
	m_bBegined = true;
	m_argCount = 0;
}

int XLambdaLua::invoke()
{
	XAssert(m_bBegined, "m_bBegined == false");
	m_bBegined = false;
	XAssert(m_handle != 0, "m_handle == 0");
	int ret = -1;
	int arg = m_argCount;
	m_argCount = 0;
	if (m_handle)
	{	
		ret = s_pkLuaStack->executeFunctionByHandler(m_handle, arg);
	}
	else
	{
		auto L = s_pkLuaStack->getLuaState();

		if (arg > 0)
		{
			lua_pop(L, arg);
		}
		XLOGERROR("invoke lua function without handler");
	}

	return ret;
}

void XLambdaLua::init()
{
	s_pkLuaStack = LuaEngine::getInstance()->getLuaStack();
}
void XLambdaLua::fini()
{
	s_pkLuaStack = NULL;
}