#include "lua_gamecore_ccsext_auto.hpp"
#include "lua_game_core_ccsext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_ccsext_XCSBNode_load(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_load'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		std::string arg0;
		bool arg1;

		ok &= luaval_to_std_string(tolua_S, 2, &arg0, "XCSBNode:load");

		ok &= luaval_to_boolean(tolua_S, 3, &arg1, "XCSBNode:load");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_load'", nullptr);
			return 0;
		}
		bool ret = cobj->load(arg0, arg1);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:load", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_load'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_clearCSB(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_clearCSB'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_clearCSB'", nullptr);
			return 0;
		}
		cobj->clearCSB();
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:clearCSB", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_clearCSB'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_play(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_play'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		std::string arg0;
		bool arg1;

		ok &= luaval_to_std_string(tolua_S, 2, &arg0, "XCSBNode:play");

		ok &= luaval_to_boolean(tolua_S, 3, &arg1, "XCSBNode:play");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_play'", nullptr);
			return 0;
		}
		bool ret = cobj->play(arg0, arg1);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:play", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_play'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_setSpriteFrameByIndex(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_setSpriteFrameByIndex'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		int arg0;
		cocos2d::Sprite* arg1;

		ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "XCSBNode:setSpriteFrameByIndex");

		ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 3, "cc.Sprite", &arg1, "XCSBNode:setSpriteFrameByIndex");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_setSpriteFrameByIndex'", nullptr);
			return 0;
		}
		cobj->setSpriteFrameByIndex(arg0, arg1);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:setSpriteFrameByIndex", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_setSpriteFrameByIndex'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_loadAsync(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_loadAsync'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		XAsyncLoadOption* arg0;
		bool arg1;

		ok &= luaval_to_object<XAsyncLoadOption>(tolua_S, 2, "XAsyncLoadOption", &arg0, "XCSBNode:loadAsync");

		ok &= luaval_to_boolean(tolua_S, 3, &arg1, "XCSBNode:loadAsync");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_loadAsync'", nullptr);
			return 0;
		}
		cobj->loadAsync(arg0, arg1);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:loadAsync", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_loadAsync'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_cancelLoadAsync(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_cancelLoadAsync'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_cancelLoadAsync'", nullptr);
			return 0;
		}
		cobj->cancelLoadAsync();
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:cancelLoadAsync", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_cancelLoadAsync'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_gotoFrameAndPlay(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif
	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_gotoFrameAndPlay'", nullptr);
		return 0;
	}
#endif
	argc = lua_gettop(tolua_S) - 1;
	do{
		if (argc == 2) {
			int arg0;
			ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "XCSBNode:gotoFrameAndPlay");

			if (!ok) { break; }
			bool arg1;
			ok &= luaval_to_boolean(tolua_S, 3, &arg1, "XCSBNode:gotoFrameAndPlay");

			if (!ok) { break; }
			bool ret = cobj->gotoFrameAndPlay(arg0, arg1);
			tolua_pushboolean(tolua_S, (bool)ret);
			return 1;
		}
	} while (0);
	ok = true;
	do{
		if (argc == 3) {
			int arg0;
			ok &= luaval_to_int32(tolua_S, 2, (int *)&arg0, "XCSBNode:gotoFrameAndPlay");

			if (!ok) { break; }
			int arg1;
			ok &= luaval_to_int32(tolua_S, 3, (int *)&arg1, "XCSBNode:gotoFrameAndPlay");

			if (!ok) { break; }
			bool arg2;
			ok &= luaval_to_boolean(tolua_S, 4, &arg2, "XCSBNode:gotoFrameAndPlay");

			if (!ok) { break; }
			bool ret = cobj->gotoFrameAndPlay(arg0, arg1, arg2);
			tolua_pushboolean(tolua_S, (bool)ret);
			return 1;
		}
	} while (0);
	ok = true;
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:gotoFrameAndPlay", argc, 3);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_gotoFrameAndPlay'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_getTimeLine(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_getTimeLine'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_getTimeLine'", nullptr);
			return 0;
		}
		cocostudio::timeline::ActionTimeline* ret = cobj->getTimeLine();
		object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline", (cocostudio::timeline::ActionTimeline*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:getTimeLine", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_getTimeLine'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_getNode(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_getNode'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_getNode'", nullptr);
			return 0;
		}
		cocos2d::Node* ret = cobj->getNode();
		object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node", (cocos2d::Node*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSBNode:getNode", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_getNode'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSBNode_create(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_create'", nullptr);
			return 0;
		}
		XCSBNode* ret = XCSBNode::create();
		object_to_luaval<XCSBNode>(tolua_S, "XCSBNode", (XCSBNode*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XCSBNode:create", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_create'.", &tolua_err);
#endif
	return 0;
}
int lua_ccsext_XCSBNode_setNodeCallback(lua_State* tolua_S)
{
	int argc = 0;
	XCSBNode* cobj = nullptr;
	bool ok = true;


#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSBNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSBNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSBNode_setNodeCallback'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		XLambda* arg0;
		ok &= luaval_to_object<XLambda>(tolua_S, 2, "XLambda", &arg0, "XCSBNode:setNodeCallback");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSBNode_setNodeCallback'", nullptr);
			return 0;
		}
		cobj->setNodeCallback(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XCSBNode:setNodeCallback", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSBNode_setNodeCallback'.", &tolua_err);
#endif
	return 0;
}

static int lua_ccsext_XCSBNode_finalize(lua_State* tolua_S)
{
	printf("luabindings: finalizing LUA object (XCSBNode)");
	return 0;
}

int lua_register_ccsext_XCSBNode(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "XCSBNode");
	tolua_cclass(tolua_S, "XCSBNode", "XCSBNode", "cc.Node", nullptr);

	tolua_beginmodule(tolua_S, "XCSBNode");
	tolua_function(tolua_S, "load", lua_ccsext_XCSBNode_load);
	tolua_function(tolua_S, "clearCSB", lua_ccsext_XCSBNode_clearCSB);
	tolua_function(tolua_S, "play", lua_ccsext_XCSBNode_play);
	tolua_function(tolua_S, "setSpriteFrameByIndex", lua_ccsext_XCSBNode_setSpriteFrameByIndex);
	tolua_function(tolua_S, "loadAsync", lua_ccsext_XCSBNode_loadAsync);
	tolua_function(tolua_S, "cancelLoadAsync", lua_ccsext_XCSBNode_cancelLoadAsync);
	tolua_function(tolua_S, "gotoFrameAndPlay", lua_ccsext_XCSBNode_gotoFrameAndPlay);
	tolua_function(tolua_S, "getTimeLine", lua_ccsext_XCSBNode_getTimeLine);
	tolua_function(tolua_S, "getNode", lua_ccsext_XCSBNode_getNode);
	tolua_function(tolua_S, "create", lua_ccsext_XCSBNode_create);
	tolua_function(tolua_S, "setNodeCallback", lua_ccsext_XCSBNode_setNodeCallback);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(XCSBNode).name();
	g_luaType[typeName] = "XCSBNode";
	g_typeCast["XCSBNode"] = "XCSBNode";
	return 1;
}

int lua_ccsext_XAnimateSprite_initWithActionFile(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_initWithActionFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
		std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2, &arg0, "XAnimateSprite:initWithActionFile");

        ok &= luaval_to_std_string(tolua_S, 3, &arg1, "XAnimateSprite:initWithActionFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_initWithActionFile'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithActionFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:initWithActionFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_initWithActionFile'.",&tolua_err);
#endif

    return 0;
}
int lua_ccsext_XAnimateSprite_setDefaultFrame(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_setDefaultFrame'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XAnimateSprite:setDefaultFrame");

            if (!ok) { break; }
            cobj->setDefaultFrame(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "XAnimateSprite:setDefaultFrame"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XAnimateSprite:setDefaultFrame");

            if (!ok) { break; }
            cobj->setDefaultFrame(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "XAnimateSprite:setDefaultFrame",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_setDefaultFrame'.",&tolua_err);
#endif

    return 0;
}

int lua_ccsext_XAnimateSprite_playAction(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_playAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XAnimateSprite:playAction");

        ok &= luaval_to_boolean(tolua_S, 3, &arg1, "XAnimateSprite:playAction");

        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_playAction'", nullptr);
            return 0;
        }
        bool ret = cobj->playAction(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:playAction",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_playAction'.",&tolua_err);
#endif

    return 0;
}

int lua_ccsext_XAnimateSprite_playAnimation(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_playAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        const char* arg0;
        double arg1;
        bool arg2;
        int arg3;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "XAnimateSprite:playAnimation"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_number(tolua_S, 3,&arg1, "XAnimateSprite:playAnimation");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "XAnimateSprite:playAnimation");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "XAnimateSprite:playAnimation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_playAnimation'", nullptr);
            return 0;
        }
        bool ret = cobj->playAnimation(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:playAnimation",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_playAnimation'.",&tolua_err);
#endif

    return 0;
}

int lua_ccsext_XAnimateSprite_setPosition(lua_State* tolua_S)
{
	int argc = 0;
	XAnimateSprite* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XAnimateSprite", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XAnimateSprite*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_setPosition'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		double arg0, arg1;

		ok &= luaval_to_number(tolua_S, 2, &arg0, "XAnimateSprite:setPosition");
		ok &= luaval_to_number(tolua_S, 3, &arg1, "XAnimateSprite:setPosition");

		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XAnimateSprite_setPosition'", nullptr);
			return 0;
		}
		cobj->setPosition(arg0, arg1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:setPosition", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XAnimateSprite_setPosition'.", &tolua_err);
#endif

	return 0;
}

int lua_ccsext_XAnimateSprite_Jump(lua_State* tolua_S)
{
	int argc = 0;
	XAnimateSprite* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XAnimateSprite", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XAnimateSprite*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_Jump'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		double arg0, arg1;

		ok &= luaval_to_number(tolua_S, 2, &arg0, "XAnimateSprite:setActionID");
		ok &= luaval_to_number(tolua_S, 3, &arg1, "XAnimateSprite:setActionID");

		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XAnimateSprite_Jump'", nullptr);
			return 0;
		}
		cobj->Jump( arg0, arg1 );
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:Jump", argc, 4);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XAnimateSprite_Jump'.", &tolua_err);
#endif

	return 0;
}

int lua_ccsext_XAnimateSprite_KnockDown(lua_State* tolua_S)
{
	int argc = 0;
	XAnimateSprite* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XAnimateSprite", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XAnimateSprite*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_KnockDown'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 3)
	{
		double arg[3];

		for (int i = 0; i < 3; i++)
			ok &= luaval_to_number(tolua_S, 2 + i, &arg[i], "XAnimateSprite:setActionID");

		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XAnimateSprite_KnockDown'", nullptr);
			return 0;
		}
		cobj->KnockDown(arg[0], arg[1], arg[2]);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:KnockDown", argc, 3);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XAnimateSprite_KnockDown'.", &tolua_err);
#endif

	return 0;
}

int lua_ccsext_XAnimateSprite_setActionID(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_setActionID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XAnimateSprite:setActionID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_setActionID'", nullptr);
            return 0;
        }
        cobj->setActionID(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:setActionID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_setActionID'.",&tolua_err);
#endif

    return 0;
}

int lua_ccsext_XAnimateSprite_getActionID(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_getActionID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_getActionID'", nullptr);
            return 0;
        }
        int ret = cobj->getActionID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:getActionID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_getActionID'.",&tolua_err);
#endif

    return 0;
}
int lua_ccsext_XAnimateSprite_hasActionConfig(lua_State* tolua_S)
{
    int argc = 0;
    XAnimateSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XAnimateSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XAnimateSprite_hasActionConfig'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XAnimateSprite:hasActionConfig");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_hasActionConfig'", nullptr);
            return 0;
        }
        bool ret = cobj->hasActionConfig(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAnimateSprite:hasActionConfig",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_hasActionConfig'.",&tolua_err);
#endif

    return 0;
}

int lua_ccsext_XAnimateSprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XAnimateSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XAnimateSprite_create'", nullptr);
            return 0;
        }
        XAnimateSprite* ret = XAnimateSprite::create();
        object_to_luaval<XAnimateSprite>(tolua_S, "XAnimateSprite",(XAnimateSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XAnimateSprite:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XAnimateSprite_create'.",&tolua_err);
#endif
    return 0;
}

static int lua_ccsext_XAnimateSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XAnimateSprite)");
    return 0;
}

int lua_register_ccsext_XAnimateSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XAnimateSprite");
    tolua_cclass(tolua_S,"XAnimateSprite","XAnimateSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"XAnimateSprite");
        tolua_function(tolua_S,"initWithActionFile",lua_ccsext_XAnimateSprite_initWithActionFile);
        tolua_function(tolua_S,"setDefaultFrame",lua_ccsext_XAnimateSprite_setDefaultFrame);
		tolua_function(tolua_S, "playAction", lua_ccsext_XAnimateSprite_playAction);
		tolua_function(tolua_S, "playAnimation", lua_ccsext_XAnimateSprite_playAnimation);
		tolua_function(tolua_S, "KnockDown", lua_ccsext_XAnimateSprite_KnockDown);
		tolua_function(tolua_S, "Jump", lua_ccsext_XAnimateSprite_Jump);
		tolua_function(tolua_S, "setPosition", lua_ccsext_XAnimateSprite_setPosition);
        tolua_function(tolua_S,"setActionID",lua_ccsext_XAnimateSprite_setActionID);
        tolua_function(tolua_S,"getActionID",lua_ccsext_XAnimateSprite_getActionID);
        tolua_function(tolua_S,"hasActionConfig",lua_ccsext_XAnimateSprite_hasActionConfig);
        tolua_function(tolua_S,"create", lua_ccsext_XAnimateSprite_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XAnimateSprite).name();
    g_luaType[typeName] = "XAnimateSprite";
    g_typeCast["XAnimateSprite"] = "XAnimateSprite";
    return 1;
}

int lua_ccsext_XActionNode_KnockDown(lua_State* tolua_S)
{
	int argc = 0;
	XActionNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XActionNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XActionNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XActionNode_KnockDown'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 3)
	{
		double arg[3];

		for (int i = 0; i < 3;i++)
			ok &= luaval_to_number(tolua_S, 2+i, &arg[i], "XActionNode:KnockDown");


		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XActionNode_KnockDown'", nullptr);
			return 0;
		}
		cobj->KnockDown(arg[0], arg[1], arg[2]);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XActionNode:KnockDown", argc, 3);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XActionNode_KnockDown'.", &tolua_err);
#endif

	return 0;
}

int lua_ccsext_XActionNode_Jump(lua_State* tolua_S)
{
	int argc = 0;
	XActionNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XActionNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XActionNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XActionNode_Jump'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 4)
	{
		double arg[4];

		for (int i = 0; i < 4; i++)
			ok &= luaval_to_number(tolua_S, 2 + i, &arg[i], "XActionNode:KnockDown");
		
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XActionNode_Jump'", nullptr);
			return 0;
		}
		cobj->Jump(arg[0], arg[1], arg[2], arg[3]);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XActionNode:Jump", argc, 4);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XActionNode_Jump'.", &tolua_err);
#endif

	return 0;
}

int lua_ccsext_XActionNode_listenEvent(lua_State* tolua_S)
{
    int argc = 0;
    XActionNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XActionNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XActionNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XActionNode_listenEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        XLambda* arg0;

        ok &= luaval_to_object<XLambda>(tolua_S, 2, "XLambda",&arg0, "XActionNode:listenEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XActionNode_listenEvent'", nullptr);
            return 0;
        }
        cobj->listenEvent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XActionNode:listenEvent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XActionNode_listenEvent'.",&tolua_err);
#endif

    return 0;
}

int lua_ccsext_XActionNode_setZOrder(lua_State* tolua_S)
{
	int argc = 0;
	XActionNode* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XActionNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XActionNode*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XActionNode_setZOrder'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		int arg0;
		ok &= luaval_to_int32(tolua_S, 2, &arg0, "XActionNode:setZOrder");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XActionNode_setZOrder'", nullptr);
			return 0;
		}
		cobj->setZOrder(arg0);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XActionNode:setZOrder", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XActionNode_setZOrder'.", &tolua_err);
#endif

	return 0;
}


int lua_ccsext_XActionNode_onMoveToEnd(lua_State* tolua_S)
{
    int argc = 0;
    XActionNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XActionNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XActionNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XActionNode_onMoveToEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XActionNode_onMoveToEnd'", nullptr);
            return 0;
        }
        cobj->onMoveToEnd();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XActionNode:onMoveToEnd",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XActionNode_onMoveToEnd'.",&tolua_err);
#endif

    return 0;
}
int lua_ccsext_XActionNode_moveTo(lua_State* tolua_S)
{
    int argc = 0;
    XActionNode* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XActionNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (XActionNode*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ccsext_XActionNode_moveTo'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "XActionNode:moveTo");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "XActionNode:moveTo");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "XActionNode:moveTo");

            if (!ok) { break; }
            cobj->moveTo(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XActionNode:moveTo");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XActionNode:moveTo");

            if (!ok) { break; }
            cobj->moveTo(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "XActionNode:moveTo",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XActionNode_moveTo'.",&tolua_err);
#endif

    return 0;
}



int lua_ccsext_XActionNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XActionNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XActionNode_create'", nullptr);
            return 0;
        }
        XActionNode* ret = XActionNode::create();
        object_to_luaval<XActionNode>(tolua_S, "XActionNode",(XActionNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XActionNode:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XActionNode_create'.",&tolua_err);
#endif
    return 0;
}
int lua_ccsext_XActionNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    XActionNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_XActionNode_constructor'", nullptr);
            return 0;
        }
        cobj = new XActionNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"XActionNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XActionNode:XActionNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_XActionNode_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_ccsext_XActionNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XActionNode)");
    return 0;
}

int lua_register_ccsext_XActionNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XActionNode");
    tolua_cclass(tolua_S,"XActionNode","XActionNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"XActionNode");
        tolua_function(tolua_S,"new",lua_ccsext_XActionNode_constructor);
		tolua_function(tolua_S, "listenEvent", lua_ccsext_XActionNode_listenEvent);
		tolua_function(tolua_S, "KnockDown", lua_ccsext_XActionNode_KnockDown);
		tolua_function(tolua_S, "Jump", lua_ccsext_XActionNode_Jump);
        tolua_function(tolua_S,"onMoveToEnd",lua_ccsext_XActionNode_onMoveToEnd);
		tolua_function(tolua_S, "setZOrder", lua_ccsext_XActionNode_setZOrder);
        tolua_function(tolua_S,"moveTo",lua_ccsext_XActionNode_moveTo);
        tolua_function(tolua_S,"create", lua_ccsext_XActionNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XActionNode).name();
    g_luaType[typeName] = "XActionNode";
    g_typeCast["XActionNode"] = "XActionNode";
    return 1;
}
int lua_ccsext_SizeTo_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SizeTo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        double arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.SizeTo:create");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.SizeTo:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.SizeTo:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_ccsext_SizeTo_create'", nullptr);
            return 0;
        }
        cocos2d::SizeTo* ret = cocos2d::SizeTo::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::SizeTo>(tolua_S, "cc.SizeTo",(cocos2d::SizeTo*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SizeTo:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ccsext_SizeTo_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_ccsext_SizeTo_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SizeTo)");
    return 0;
}

int lua_register_ccsext_SizeTo(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SizeTo");
    tolua_cclass(tolua_S,"SizeTo","cc.SizeTo","cc.ActionInterval",nullptr);

    tolua_beginmodule(tolua_S,"SizeTo");
        tolua_function(tolua_S,"create", lua_ccsext_SizeTo_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::SizeTo).name();
    g_luaType[typeName] = "cc.SizeTo";
    g_typeCast["SizeTo"] = "cc.SizeTo";
    return 1;
}

int lua_ccsext_XCSLoadRet_getTimeline(lua_State* tolua_S)
{
	int argc = 0;
	XCSLoadRet* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSLoadRet", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSLoadRet*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSLoadRet_getTimeline'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSLoadRet_getTimeline'", nullptr);
			return 0;
		}
		cocostudio::timeline::ActionTimeline* ret = cobj->getTimeline();
		object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline", (cocostudio::timeline::ActionTimeline*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSLoadRet:getTimeline", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSLoadRet_getTimeline'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSLoadRet_getNode(lua_State* tolua_S)
{
	int argc = 0;
	XCSLoadRet* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XCSLoadRet", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XCSLoadRet*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_ccsext_XCSLoadRet_getNode'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSLoadRet_getNode'", nullptr);
			return 0;
		}
		cocos2d::Node* ret = cobj->getNode();
		object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node", (cocos2d::Node*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XCSLoadRet:getNode", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSLoadRet_getNode'.", &tolua_err);
#endif

	return 0;
}
int lua_ccsext_XCSLoadRet_create(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "XCSLoadRet", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 1)
	{
		cocos2d::Node* arg0;
		ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node", &arg0, "XCSLoadRet:create");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_ccsext_XCSLoadRet_create'", nullptr);
			return 0;
		}
		XCSLoadRet* ret = XCSLoadRet::create(arg0);
		object_to_luaval<XCSLoadRet>(tolua_S, "XCSLoadRet", (XCSLoadRet*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XCSLoadRet:create", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_ccsext_XCSLoadRet_create'.", &tolua_err);
#endif
	return 0;
}
static int lua_ccsext_XCSLoadRet_finalize(lua_State* tolua_S)
{
	printf("luabindings: finalizing LUA object (XCSLoadRet)");
	return 0;
}

int lua_register_ccsext_XCSLoadRet(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "XCSLoadRet");
	tolua_cclass(tolua_S, "XCSLoadRet", "XCSLoadRet", "cc.Ref", nullptr);

	tolua_beginmodule(tolua_S, "XCSLoadRet");
	tolua_function(tolua_S, "getTimeline", lua_ccsext_XCSLoadRet_getTimeline);
	tolua_function(tolua_S, "getNode", lua_ccsext_XCSLoadRet_getNode);
	tolua_function(tolua_S, "create", lua_ccsext_XCSLoadRet_create);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(XCSLoadRet).name();
	g_luaType[typeName] = "XCSLoadRet";
	g_typeCast["XCSLoadRet"] = "XCSLoadRet";
	return 1;
}

TOLUA_API int register_all_ccsext(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccsext",0);
	tolua_beginmodule(tolua_S,"ccsext");

	lua_register_ccsext_XCSBNode(tolua_S);
	lua_register_ccsext_SizeTo(tolua_S);
	lua_register_ccsext_XActionNode(tolua_S);
	//lua_register_ccsext_XSprite(tolua_S);
	lua_register_ccsext_XAnimateSprite(tolua_S);
	lua_register_ccsext_XCSLoadRet(tolua_S);
	tolua_endmodule(tolua_S);
	return 1;
}

