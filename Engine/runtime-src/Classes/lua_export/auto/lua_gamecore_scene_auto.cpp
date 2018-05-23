#include "lua_gamecore_scene_auto.hpp"
#include "lua_game_core_scene.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_scene_GameMapInfo_getMoveableCount(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getMoveableCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getMoveableCount'", nullptr);
            return 0;
        }
        int ret = cobj->getMoveableCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getMoveableCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getMoveableCount'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getWidthInPixel(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getWidthInPixel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getWidthInPixel'", nullptr);
            return 0;
        }
        int ret = cobj->getWidthInPixel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getWidthInPixel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getWidthInPixel'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_GameMapInfo_getHeightInPixel(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getHeightInPixel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getHeightInPixel'", nullptr);
            return 0;
        }
        int ret = cobj->getHeightInPixel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getHeightInPixel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getHeightInPixel'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_LoadFromFile(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_LoadFromFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "GameMapInfo:LoadFromFile"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_LoadFromFile'", nullptr);
            return 0;
        }
        bool ret = cobj->LoadFromFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:LoadFromFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_LoadFromFile'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getHeight(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getHeight'", nullptr);
            return 0;
        }
        int ret = cobj->getHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getHeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getMapPosValue(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getMapPosValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        unsigned int arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "GameMapInfo:getMapPosValue");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "GameMapInfo:getMapPosValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getMapPosValue'", nullptr);
            return 0;
        }
        int ret = cobj->getMapPosValue(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getMapPosValue",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getMapPosValue'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getWidth(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getWidth'", nullptr);
            return 0;
        }
        int ret = cobj->getWidth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getWidth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getWidth'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_canMove(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_canMove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        unsigned int arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "GameMapInfo:canMove");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "GameMapInfo:canMove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_canMove'", nullptr);
            return 0;
        }
        bool ret = cobj->canMove(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:canMove",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_canMove'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_isShield(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_isShield'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        unsigned int arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "GameMapInfo:isShield");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "GameMapInfo:isShield");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_isShield'", nullptr);
            return 0;
        }
        bool ret = cobj->isShield(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:isShield",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_isShield'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getPosIndex(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getPosIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        unsigned int arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "GameMapInfo:getPosIndex");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "GameMapInfo:getPosIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getPosIndex'", nullptr);
            return 0;
        }
        int ret = cobj->getPosIndex(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getPosIndex",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getPosIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_release(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_release'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_release'", nullptr);
            return 0;
        }
        cobj->release();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:release",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_release'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getGridInfo(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getGridInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        unsigned int arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "GameMapInfo:getGridInfo");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "GameMapInfo:getGridInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getGridInfo'", nullptr);
            return 0;
        }
        tagMapGrid* ret = cobj->getGridInfo(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR tagMapGrid*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getGridInfo",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getGridInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_LoadFromChar(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_LoadFromChar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned char* arg0;
        unsigned long arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_ulong(tolua_S, 3, &arg1, "GameMapInfo:LoadFromChar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_LoadFromChar'", nullptr);
            return 0;
        }
        bool ret = cobj->LoadFromChar(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:LoadFromChar",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_LoadFromChar'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_initDefault(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_initDefault'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        unsigned int arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "GameMapInfo:initDefault");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "GameMapInfo:initDefault");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_initDefault'", nullptr);
            return 0;
        }
        cobj->initDefault(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:initDefault",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_initDefault'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_getUnitCount(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameMapInfo*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_GameMapInfo_getUnitCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_getUnitCount'", nullptr);
            return 0;
        }
        int ret = cobj->getUnitCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:getUnitCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_getUnitCount'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_GameMapInfo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    GameMapInfo* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_GameMapInfo_constructor'", nullptr);
            return 0;
        }
        cobj = new GameMapInfo();
        tolua_pushusertype(tolua_S,(void*)cobj,"GameMapInfo");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "GameMapInfo:GameMapInfo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_scene_GameMapInfo_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_scene_GameMapInfo_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameMapInfo)");
    return 0;
}

int lua_register_scene_GameMapInfo(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameMapInfo");
    tolua_cclass(tolua_S,"GameMapInfo","GameMapInfo","",nullptr);

    tolua_beginmodule(tolua_S,"GameMapInfo");
        tolua_function(tolua_S,"new",lua_scene_GameMapInfo_constructor);
        tolua_function(tolua_S,"getMoveableCount",lua_scene_GameMapInfo_getMoveableCount);
        tolua_function(tolua_S,"getWidthInPixel",lua_scene_GameMapInfo_getWidthInPixel);
        tolua_function(tolua_S,"getHeightInPixel",lua_scene_GameMapInfo_getHeightInPixel);
        tolua_function(tolua_S,"LoadFromFile",lua_scene_GameMapInfo_LoadFromFile);
        tolua_function(tolua_S,"getHeight",lua_scene_GameMapInfo_getHeight);
        tolua_function(tolua_S,"getMapPosValue",lua_scene_GameMapInfo_getMapPosValue);
        tolua_function(tolua_S,"getWidth",lua_scene_GameMapInfo_getWidth);
        tolua_function(tolua_S,"canMove",lua_scene_GameMapInfo_canMove);
        tolua_function(tolua_S,"isShield",lua_scene_GameMapInfo_isShield);
        tolua_function(tolua_S,"getPosIndex",lua_scene_GameMapInfo_getPosIndex);
        tolua_function(tolua_S,"release",lua_scene_GameMapInfo_release);
        tolua_function(tolua_S,"getGridInfo",lua_scene_GameMapInfo_getGridInfo);
        tolua_function(tolua_S,"LoadFromChar",lua_scene_GameMapInfo_LoadFromChar);
        tolua_function(tolua_S,"initDefault",lua_scene_GameMapInfo_initDefault);
        tolua_function(tolua_S,"getUnitCount",lua_scene_GameMapInfo_getUnitCount);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameMapInfo).name();
    g_luaType[typeName] = "GameMapInfo";
    g_typeCast["GameMapInfo"] = "GameMapInfo";
    return 1;
}

int lua_scene_XSceneObject_getObjectID(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getObjectID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getObjectID'", nullptr);
            return 0;
        }
        int ret = cobj->getObjectID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getObjectID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getObjectID'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_serialize(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_serialize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_serialize'", nullptr);
            return 0;
        }
        const char* ret = cobj->serialize();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:serialize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_serialize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setFilename(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setFilename'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XSceneObject:setFilename");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setFilename'", nullptr);
            return 0;
        }
        cobj->setFilename(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setFilename",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setFilename'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_parse(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_parse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "XSceneObject:parse"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_parse'", nullptr);
            return 0;
        }
        bool ret = cobj->parse(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:parse",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_parse'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getAnimated(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getAnimated'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getAnimated'", nullptr);
            return 0;
        }
        bool ret = cobj->getAnimated();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getAnimated",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getAnimated'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_updateBoundRadius(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_updateBoundRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_updateBoundRadius'", nullptr);
            return 0;
        }
        cobj->updateBoundRadius();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:updateBoundRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_updateBoundRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setType(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "XSceneObject:setType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setType'", nullptr);
            return 0;
        }
        cobj->setType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setType'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getOwner(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getOwner'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getOwner'", nullptr);
            return 0;
        }
        XSceneObjectGroup* ret = cobj->getOwner();
        object_to_luaval<XSceneObjectGroup>(tolua_S, "XSceneObjectGroup",(XSceneObjectGroup*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getOwner",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getOwner'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setBoundOffsetX(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setBoundOffsetX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneObject:setBoundOffsetX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setBoundOffsetX'", nullptr);
            return 0;
        }
        cobj->setBoundOffsetX(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setBoundOffsetX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setBoundOffsetX'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setBoundOffsetY(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setBoundOffsetY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneObject:setBoundOffsetY");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setBoundOffsetY'", nullptr);
            return 0;
        }
        cobj->setBoundOffsetY(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setBoundOffsetY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setBoundOffsetY'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_updateDebug(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_updateDebug'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_updateDebug'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->updateDebug();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:updateDebug",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_updateDebug'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getRadiusColor(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getRadiusColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getRadiusColor'", nullptr);
            return 0;
        }
        cocos2d::Color4F ret = cobj->getRadiusColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getRadiusColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getRadiusColor'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getFilename(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getFilename'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getFilename'", nullptr);
            return 0;
        }
        const char* ret = cobj->getFilename();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getFilename",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getFilename'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getBoundOffset(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getBoundOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getBoundOffset'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getBoundOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getBoundOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getBoundOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getLayerZOrder(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getLayerZOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getLayerZOrder'", nullptr);
            return 0;
        }
        int ret = cobj->getLayerZOrder();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getLayerZOrder",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getLayerZOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getType(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getType'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->getType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getType'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setRadiusColor(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setRadiusColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "XSceneObject:setRadiusColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setRadiusColor'", nullptr);
            return 0;
        }
        cobj->setRadiusColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setRadiusColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setRadiusColor'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_wake(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_wake'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_wake'", nullptr);
            return 0;
        }
        cobj->wake();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:wake",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_wake'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setAnimated(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setAnimated'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XSceneObject:setAnimated");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setAnimated'", nullptr);
            return 0;
        }
        cobj->setAnimated(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setAnimated",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setAnimated'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setLayerZOrder(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setLayerZOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObject:setLayerZOrder");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setLayerZOrder'", nullptr);
            return 0;
        }
        cobj->setLayerZOrder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setLayerZOrder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setLayerZOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setBoundRadius(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setBoundRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneObject:setBoundRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setBoundRadius'", nullptr);
            return 0;
        }
        cobj->setBoundRadius(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setBoundRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setBoundRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setObjectID(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setObjectID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObject:setObjectID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setObjectID'", nullptr);
            return 0;
        }
        cobj->setObjectID(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setObjectID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setObjectID'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setBoundOffset(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setBoundOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneObject:setBoundOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setBoundOffset'", nullptr);
            return 0;
        }
        cobj->setBoundOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setBoundOffset",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setBoundOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getBoundOffsetX(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getBoundOffsetX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getBoundOffsetX'", nullptr);
            return 0;
        }
        double ret = cobj->getBoundOffsetX();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getBoundOffsetX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getBoundOffsetX'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getBoundOffsetY(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getBoundOffsetY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getBoundOffsetY'", nullptr);
            return 0;
        }
        double ret = cobj->getBoundOffsetY();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getBoundOffsetY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getBoundOffsetY'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_visibilityCheck(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_visibilityCheck'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        double arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneObject:visibilityCheck");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "XSceneObject:visibilityCheck");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_visibilityCheck'", nullptr);
            return 0;
        }
        bool ret = cobj->visibilityCheck(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:visibilityCheck",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_visibilityCheck'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setOwner(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setOwner'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        XSceneObjectGroup* arg0;

        ok &= luaval_to_object<XSceneObjectGroup>(tolua_S, 2, "XSceneObjectGroup",&arg0, "XSceneObject:setOwner");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setOwner'", nullptr);
            return 0;
        }
        cobj->setOwner(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setOwner",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setOwner'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getBoundRadius(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getBoundRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getBoundRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getBoundRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getBoundRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getBoundRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_sleep(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_sleep'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_sleep'", nullptr);
            return 0;
        }
        cobj->sleep();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:sleep",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_sleep'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_setLayerID(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_setLayerID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObject:setLayerID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_setLayerID'", nullptr);
            return 0;
        }
        cobj->setLayerID(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:setLayerID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_setLayerID'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_getLayerID(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObject* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObject*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObject_getLayerID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_getLayerID'", nullptr);
            return 0;
        }
        int ret = cobj->getLayerID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObject:getLayerID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_getLayerID'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObject_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XSceneObject",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObject_create'", nullptr);
            return 0;
        }
        XSceneObject* ret = XSceneObject::create();
        object_to_luaval<XSceneObject>(tolua_S, "XSceneObject",(XSceneObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XSceneObject:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObject_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XSceneObject_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XSceneObject)");
    return 0;
}

int lua_register_scene_XSceneObject(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XSceneObject");
    tolua_cclass(tolua_S,"XSceneObject","XSceneObject","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"XSceneObject");
        tolua_function(tolua_S,"getObjectID",lua_scene_XSceneObject_getObjectID);
        tolua_function(tolua_S,"serialize",lua_scene_XSceneObject_serialize);
        tolua_function(tolua_S,"setFilename",lua_scene_XSceneObject_setFilename);
        tolua_function(tolua_S,"parse",lua_scene_XSceneObject_parse);
        tolua_function(tolua_S,"getAnimated",lua_scene_XSceneObject_getAnimated);
        tolua_function(tolua_S,"updateBoundRadius",lua_scene_XSceneObject_updateBoundRadius);
        tolua_function(tolua_S,"setType",lua_scene_XSceneObject_setType);
        tolua_function(tolua_S,"getOwner",lua_scene_XSceneObject_getOwner);
        tolua_function(tolua_S,"setBoundOffsetX",lua_scene_XSceneObject_setBoundOffsetX);
        tolua_function(tolua_S,"setBoundOffsetY",lua_scene_XSceneObject_setBoundOffsetY);
        tolua_function(tolua_S,"updateDebug",lua_scene_XSceneObject_updateDebug);
        tolua_function(tolua_S,"getRadiusColor",lua_scene_XSceneObject_getRadiusColor);
        tolua_function(tolua_S,"getFilename",lua_scene_XSceneObject_getFilename);
        tolua_function(tolua_S,"getBoundOffset",lua_scene_XSceneObject_getBoundOffset);
        tolua_function(tolua_S,"getLayerZOrder",lua_scene_XSceneObject_getLayerZOrder);
        tolua_function(tolua_S,"getType",lua_scene_XSceneObject_getType);
        tolua_function(tolua_S,"setRadiusColor",lua_scene_XSceneObject_setRadiusColor);
        tolua_function(tolua_S,"wake",lua_scene_XSceneObject_wake);
        tolua_function(tolua_S,"setAnimated",lua_scene_XSceneObject_setAnimated);
        tolua_function(tolua_S,"setLayerZOrder",lua_scene_XSceneObject_setLayerZOrder);
        tolua_function(tolua_S,"setBoundRadius",lua_scene_XSceneObject_setBoundRadius);
        tolua_function(tolua_S,"setObjectID",lua_scene_XSceneObject_setObjectID);
        tolua_function(tolua_S,"setBoundOffset",lua_scene_XSceneObject_setBoundOffset);
        tolua_function(tolua_S,"getBoundOffsetX",lua_scene_XSceneObject_getBoundOffsetX);
        tolua_function(tolua_S,"getBoundOffsetY",lua_scene_XSceneObject_getBoundOffsetY);
        tolua_function(tolua_S,"visibilityCheck",lua_scene_XSceneObject_visibilityCheck);
        tolua_function(tolua_S,"setOwner",lua_scene_XSceneObject_setOwner);
        tolua_function(tolua_S,"getBoundRadius",lua_scene_XSceneObject_getBoundRadius);
        tolua_function(tolua_S,"sleep",lua_scene_XSceneObject_sleep);
        tolua_function(tolua_S,"setLayerID",lua_scene_XSceneObject_setLayerID);
        tolua_function(tolua_S,"getLayerID",lua_scene_XSceneObject_getLayerID);
        tolua_function(tolua_S,"create", lua_scene_XSceneObject_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XSceneObject).name();
    g_luaType[typeName] = "XSceneObject";
    g_typeCast["XSceneObject"] = "XSceneObject";
    return 1;
}

int lua_scene_XSceneLayer_onResume(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_onResume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_onResume'", nullptr);
            return 0;
        }
        cobj->onResume();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:onResume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_onResume'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_updateObjects(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_updateObjects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneLayer:updateObjects");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_updateObjects'", nullptr);
            return 0;
        }
        cobj->updateObjects(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:updateObjects",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_updateObjects'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_updateCamera(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_updateCamera'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneLayer:updateCamera");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_updateCamera'", nullptr);
            return 0;
        }
        cobj->updateCamera(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:updateCamera",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_updateCamera'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_setLayerType(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_setLayerType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneLayer:setLayerType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_setLayerType'", nullptr);
            return 0;
        }
        cobj->setLayerType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:setLayerType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_setLayerType'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getFileType(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getFileType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getFileType'", nullptr);
            return 0;
        }
        std::string ret = cobj->getFileType();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getFileType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getFileType'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_setParallax(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_setParallax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneLayer:setParallax");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "XSceneLayer:setParallax");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_setParallax'", nullptr);
            return 0;
        }
        bool ret = cobj->setParallax(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:setParallax",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_setParallax'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getLayerType(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getLayerType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getLayerType'", nullptr);
            return 0;
        }
        int ret = cobj->getLayerType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getLayerType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getLayerType'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_clearall(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_clearall'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneLayer:clearall");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_clearall'", nullptr);
            return 0;
        }
        cobj->clearall(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:clearall",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_clearall'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_setResPath(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_setResPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XSceneLayer:setResPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_setResPath'", nullptr);
            return 0;
        }
        cobj->setResPath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:setResPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_setResPath'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getSceneObject(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getSceneObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneLayer:getSceneObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getSceneObject'", nullptr);
            return 0;
        }
        XSceneObject* ret = cobj->getSceneObject(arg0);
        object_to_luaval<XSceneObject>(tolua_S, "XSceneObject",(XSceneObject*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getSceneObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getSceneObject'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_attach(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_attach'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        XSceneObject* arg0;
        int arg1;
        int arg2;
		bool arg3;

        ok &= luaval_to_object<XSceneObject>(tolua_S, 2, "XSceneObject",&arg0, "XSceneLayer:attach");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XSceneLayer:attach");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "XSceneLayer:attach");

		ok &= luaval_to_boolean(tolua_S, 5, &arg3, "XSceneLayer:attach");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_attach'", nullptr);
            return 0;
        }
		cobj->attach(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:attach",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_attach'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_onPause(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_onPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_onPause'", nullptr);
            return 0;
        }
        cobj->onPause();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:onPause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_onPause'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getLayerSize(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getLayerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getLayerSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getLayerSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getLayerSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getLayerSize'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneLayer_getParallaxOffset(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getParallaxOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getParallaxOffset'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getParallaxOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getParallaxOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getParallaxOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_setFileType(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_setFileType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XSceneLayer:setFileType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_setFileType'", nullptr);
            return 0;
        }
        cobj->setFileType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:setFileType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_setFileType'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_detach(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_detach'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneLayer:detach");

            if (!ok) { break; }
            cobj->detach(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            XSceneObject* arg0;
            ok &= luaval_to_object<XSceneObject>(tolua_S, 2, "XSceneObject",&arg0, "XSceneLayer:detach");

            if (!ok) { break; }
            cobj->detach(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            XSceneObject* arg0;
            ok &= luaval_to_object<XSceneObject>(tolua_S, 2, "XSceneObject",&arg0, "XSceneLayer:detach");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "XSceneLayer:detach");

            if (!ok) { break; }
            cobj->detach(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "XSceneLayer:detach",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_detach'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneLayer_getParallaxRatio(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getParallaxRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getParallaxRatio'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getParallaxRatio();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getParallaxRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getParallaxRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getResPath(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getResPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getResPath'", nullptr);
            return 0;
        }
        std::string ret = cobj->getResPath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getResPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getResPath'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getObjectIDs(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getObjectIDs'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getObjectIDs'", nullptr);
            return 0;
        }
        cocos2d::ValueVector ret = cobj->getObjectIDs();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getObjectIDs",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getObjectIDs'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_cameraCenter(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_cameraCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_cameraCenter'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->cameraCenter();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:cameraCenter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_cameraCenter'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_getObjectKeys(lua_State* tolua_S)
{
    int argc = 0;
    XSceneLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneLayer_getObjectKeys'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueVector arg0;

        ok &= luaval_to_ccvaluevector(tolua_S, 2, &arg0, "XSceneLayer:getObjectKeys");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_getObjectKeys'", nullptr);
            return 0;
        }
        cobj->getObjectKeys(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneLayer:getObjectKeys",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_getObjectKeys'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XSceneLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneLayer_create'", nullptr);
            return 0;
        }
        XSceneLayer* ret = XSceneLayer::create();
        object_to_luaval<XSceneLayer>(tolua_S, "XSceneLayer",(XSceneLayer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XSceneLayer:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneLayer_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XSceneLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XSceneLayer)");
    return 0;
}

int lua_register_scene_XSceneLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XSceneLayer");
    tolua_cclass(tolua_S,"XSceneLayer","XSceneLayer","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"XSceneLayer");
        tolua_function(tolua_S,"onResume",lua_scene_XSceneLayer_onResume);
        tolua_function(tolua_S,"updateObjects",lua_scene_XSceneLayer_updateObjects);
        tolua_function(tolua_S,"updateCamera",lua_scene_XSceneLayer_updateCamera);
        tolua_function(tolua_S,"setLayerType",lua_scene_XSceneLayer_setLayerType);
        tolua_function(tolua_S,"getFileType",lua_scene_XSceneLayer_getFileType);
        tolua_function(tolua_S,"setParallax",lua_scene_XSceneLayer_setParallax);
        tolua_function(tolua_S,"getLayerType",lua_scene_XSceneLayer_getLayerType);
        tolua_function(tolua_S,"clearall",lua_scene_XSceneLayer_clearall);
        tolua_function(tolua_S,"setResPath",lua_scene_XSceneLayer_setResPath);
        tolua_function(tolua_S,"getSceneObject",lua_scene_XSceneLayer_getSceneObject);
        tolua_function(tolua_S,"attach",lua_scene_XSceneLayer_attach);
        tolua_function(tolua_S,"onPause",lua_scene_XSceneLayer_onPause);
        tolua_function(tolua_S,"getLayerSize",lua_scene_XSceneLayer_getLayerSize);
        tolua_function(tolua_S,"getParallaxOffset",lua_scene_XSceneLayer_getParallaxOffset);
        tolua_function(tolua_S,"setFileType",lua_scene_XSceneLayer_setFileType);
        tolua_function(tolua_S,"detach",lua_scene_XSceneLayer_detach);
        tolua_function(tolua_S,"getParallaxRatio",lua_scene_XSceneLayer_getParallaxRatio);
        tolua_function(tolua_S,"getResPath",lua_scene_XSceneLayer_getResPath);
        tolua_function(tolua_S,"getObjectIDs",lua_scene_XSceneLayer_getObjectIDs);
        tolua_function(tolua_S,"cameraCenter",lua_scene_XSceneLayer_cameraCenter);
        tolua_function(tolua_S,"getObjectKeys",lua_scene_XSceneLayer_getObjectKeys);
        tolua_function(tolua_S,"create", lua_scene_XSceneLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XSceneLayer).name();
    g_luaType[typeName] = "XSceneLayer";
    g_typeCast["XSceneLayer"] = "XSceneLayer";
    return 1;
}

int lua_scene_XPosNode_onTouchMoved(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_onTouchMoved'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "XPosNode:onTouchMoved");

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1, "XPosNode:onTouchMoved");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_onTouchMoved'", nullptr);
            return 0;
        }
        cobj->onTouchMoved(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:onTouchMoved",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_onTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_setVisibleName(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_setVisibleName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "XPosNode:setVisibleName"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_setVisibleName'", nullptr);
            return 0;
        }
        cobj->setVisibleName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:setVisibleName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_setVisibleName'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_onTouchEnded(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_onTouchEnded'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "XPosNode:onTouchEnded");

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1, "XPosNode:onTouchEnded");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_onTouchEnded'", nullptr);
            return 0;
        }
        cobj->onTouchEnded(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:onTouchEnded",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_onTouchEnded'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_getEnablePosChange(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_getEnablePosChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_getEnablePosChange'", nullptr);
            return 0;
        }
        bool ret = cobj->getEnablePosChange();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:getEnablePosChange",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_getEnablePosChange'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_isTouchInside(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_isTouchInside'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Touch* arg0;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "XPosNode:isTouchInside");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_isTouchInside'", nullptr);
            return 0;
        }
        bool ret = cobj->isTouchInside(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:isTouchInside",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_isTouchInside'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_initial(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_initial'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "XPosNode:initial");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_initial'", nullptr);
            return 0;
        }
        cobj->initial(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:initial",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_initial'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_onTouchCancelled(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_onTouchCancelled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "XPosNode:onTouchCancelled");

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1, "XPosNode:onTouchCancelled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_onTouchCancelled'", nullptr);
            return 0;
        }
        cobj->onTouchCancelled(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:onTouchCancelled",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_onTouchCancelled'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_onTouchBegan(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_onTouchBegan'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "XPosNode:onTouchBegan");

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1, "XPosNode:onTouchBegan");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_onTouchBegan'", nullptr);
            return 0;
        }
        bool ret = cobj->onTouchBegan(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:onTouchBegan",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_onTouchBegan'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_setDrawColor(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_setDrawColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "XPosNode:setDrawColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_setDrawColor'", nullptr);
            return 0;
        }
        cobj->setDrawColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:setDrawColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_setDrawColor'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_changePosition(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_changePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XPosNode:changePosition");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XPosNode:changePosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_changePosition'", nullptr);
            return 0;
        }
        cobj->changePosition(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:changePosition",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_changePosition'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_setOnPosChange(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_setOnPosChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<cocos2d::Vec2 (const cocos2d::Vec2 &)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_setOnPosChange'", nullptr);
            return 0;
        }
        cobj->setOnPosChange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:setOnPosChange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_setOnPosChange'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_setEnablePosChange(lua_State* tolua_S)
{
    int argc = 0;
    XPosNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XPosNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XPosNode_setEnablePosChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XPosNode:setEnablePosChange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_setEnablePosChange'", nullptr);
            return 0;
        }
        cobj->setEnablePosChange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XPosNode:setEnablePosChange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_setEnablePosChange'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XPosNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XPosNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Rect arg0;
        ok &= luaval_to_rect(tolua_S, 2, &arg0, "XPosNode:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XPosNode_create'", nullptr);
            return 0;
        }
        XPosNode* ret = XPosNode::create(arg0);
        object_to_luaval<XPosNode>(tolua_S, "XPosNode",(XPosNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XPosNode:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XPosNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XPosNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XPosNode)");
    return 0;
}

int lua_register_scene_XPosNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XPosNode");
    tolua_cclass(tolua_S,"XPosNode","XPosNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"XPosNode");
        tolua_function(tolua_S,"onTouchMoved",lua_scene_XPosNode_onTouchMoved);
        tolua_function(tolua_S,"setVisibleName",lua_scene_XPosNode_setVisibleName);
        tolua_function(tolua_S,"onTouchEnded",lua_scene_XPosNode_onTouchEnded);
        tolua_function(tolua_S,"getEnablePosChange",lua_scene_XPosNode_getEnablePosChange);
        tolua_function(tolua_S,"isTouchInside",lua_scene_XPosNode_isTouchInside);
        tolua_function(tolua_S,"initial",lua_scene_XPosNode_initial);
        tolua_function(tolua_S,"onTouchCancelled",lua_scene_XPosNode_onTouchCancelled);
        tolua_function(tolua_S,"onTouchBegan",lua_scene_XPosNode_onTouchBegan);
        tolua_function(tolua_S,"setDrawColor",lua_scene_XPosNode_setDrawColor);
        tolua_function(tolua_S,"changePosition",lua_scene_XPosNode_changePosition);
        tolua_function(tolua_S,"setOnPosChange",lua_scene_XPosNode_setOnPosChange);
        tolua_function(tolua_S,"setEnablePosChange",lua_scene_XPosNode_setEnablePosChange);
        tolua_function(tolua_S,"create", lua_scene_XPosNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XPosNode).name();
    g_luaType[typeName] = "XPosNode";
    g_typeCast["XPosNode"] = "XPosNode";
    return 1;
}

int lua_scene_XSizeNode_setEnableSizeChange(lua_State* tolua_S)
{
    int argc = 0;
    XSizeNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSizeNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSizeNode_setEnableSizeChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XSizeNode:setEnableSizeChange");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_setEnableSizeChange'", nullptr);
            return 0;
        }
        cobj->setEnableSizeChange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSizeNode:setEnableSizeChange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_setEnableSizeChange'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSizeNode_setOnRectChange(lua_State* tolua_S)
{
    int argc = 0;
    XSizeNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSizeNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSizeNode_setOnRectChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (const cocos2d::Rect &)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_setOnRectChange'", nullptr);
            return 0;
        }
        cobj->setOnRectChange(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSizeNode:setOnRectChange",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_setOnRectChange'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSizeNode_getPosNode(lua_State* tolua_S)
{
    int argc = 0;
    XSizeNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSizeNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSizeNode_getPosNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_getPosNode'", nullptr);
            return 0;
        }
        XPosNode* ret = cobj->getPosNode();
        object_to_luaval<XPosNode>(tolua_S, "XPosNode",(XPosNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSizeNode:getPosNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_getPosNode'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSizeNode_getEnableSizeChange(lua_State* tolua_S)
{
    int argc = 0;
    XSizeNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSizeNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSizeNode_getEnableSizeChange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_getEnableSizeChange'", nullptr);
            return 0;
        }
        bool ret = cobj->getEnableSizeChange();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSizeNode:getEnableSizeChange",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_getEnableSizeChange'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSizeNode_changeSize(lua_State* tolua_S)
{
    int argc = 0;
    XSizeNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSizeNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSizeNode_changeSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSizeNode:changeSize");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XSizeNode:changeSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_changeSize'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->changeSize(arg0, arg1);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        bool arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSizeNode:changeSize");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XSizeNode:changeSize");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "XSizeNode:changeSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_changeSize'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->changeSize(arg0, arg1, arg2);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSizeNode:changeSize",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_changeSize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSizeNode_setSizeChangeLambda(lua_State* tolua_S)
{
    int argc = 0;
    XSizeNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSizeNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSizeNode_setSizeChangeLambda'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        XLambda* arg0;

        ok &= luaval_to_object<XLambda>(tolua_S, 2, "XLambda",&arg0, "XSizeNode:setSizeChangeLambda");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_setSizeChangeLambda'", nullptr);
            return 0;
        }
        cobj->setSizeChangeLambda(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSizeNode:setSizeChangeLambda",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_setSizeChangeLambda'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSizeNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XSizeNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Rect arg0;
        const char* arg1;
        ok &= luaval_to_rect(tolua_S, 2, &arg0, "XSizeNode:create");
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "XSizeNode:create"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSizeNode_create'", nullptr);
            return 0;
        }
        XSizeNode* ret = XSizeNode::create(arg0, arg1);
        object_to_luaval<XSizeNode>(tolua_S, "XSizeNode",(XSizeNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XSizeNode:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSizeNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XSizeNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XSizeNode)");
    return 0;
}

int lua_register_scene_XSizeNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XSizeNode");
    tolua_cclass(tolua_S,"XSizeNode","XSizeNode","XPosNode",nullptr);

    tolua_beginmodule(tolua_S,"XSizeNode");
        tolua_function(tolua_S,"setEnableSizeChange",lua_scene_XSizeNode_setEnableSizeChange);
        tolua_function(tolua_S,"setOnRectChange",lua_scene_XSizeNode_setOnRectChange);
        tolua_function(tolua_S,"getPosNode",lua_scene_XSizeNode_getPosNode);
        tolua_function(tolua_S,"getEnableSizeChange",lua_scene_XSizeNode_getEnableSizeChange);
        tolua_function(tolua_S,"changeSize",lua_scene_XSizeNode_changeSize);
        tolua_function(tolua_S,"setSizeChangeLambda",lua_scene_XSizeNode_setSizeChangeLambda);
        tolua_function(tolua_S,"create", lua_scene_XSizeNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XSizeNode).name();
    g_luaType[typeName] = "XSizeNode";
    g_typeCast["XSizeNode"] = "XSizeNode";
    return 1;
}

int lua_scene_XSceneObjectGroup_load(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_load'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        cocos2d::Size arg2;
        bool arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XSceneObjectGroup:load");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "XSceneObjectGroup:load");

        ok &= luaval_to_size(tolua_S, 4, &arg2, "XSceneObjectGroup:load");

        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "XSceneObjectGroup:load");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_load'", nullptr);
            return 0;
        }
        bool ret = cobj->load(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:load",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_load'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_onResume(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_onResume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_onResume'", nullptr);
            return 0;
        }
        cobj->onResume();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:onResume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_onResume'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_updateCamera(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_updateCamera'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XSceneObjectGroup:updateCamera");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_updateCamera'", nullptr);
            return 0;
        }
        cobj->updateCamera(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:updateCamera",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_updateCamera'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneObjectGroup_clearall(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_clearall'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObjectGroup:clearall");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_clearall'", nullptr);
            return 0;
        }
        cobj->clearall(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:clearall",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_clearall'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneObjectGroup_getLayerIDs(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_getLayerIDs'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_getLayerIDs'", nullptr);
            return 0;
        }
        cocos2d::ValueVector ret = cobj->getLayerIDs();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:getLayerIDs",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_getLayerIDs'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneObjectGroup_setLayerWithID(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setLayerWithID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        XSceneLayer* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObjectGroup:setLayerWithID");

        ok &= luaval_to_object<XSceneLayer>(tolua_S, 3, "XSceneLayer",&arg1, "XSceneObjectGroup:setLayerWithID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setLayerWithID'", nullptr);
            return 0;
        }
        cobj->setLayerWithID(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setLayerWithID",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setLayerWithID'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_setDebugNode(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setDebugNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "XSceneObjectGroup:setDebugNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setDebugNode'", nullptr);
            return 0;
        }
        cobj->setDebugNode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setDebugNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setDebugNode'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_cleanup(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_cleanup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_cleanup'", nullptr);
            return 0;
        }
        cobj->cleanup();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:cleanup",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_cleanup'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_onPause(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_onPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_onPause'", nullptr);
            return 0;
        }
        cobj->onPause();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:onPause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_onPause'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_getParallaxRoot(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_getParallaxRoot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_getParallaxRoot'", nullptr);
            return 0;
        }
        cocos2d::ParallaxNode* ret = cobj->getParallaxRoot();
        object_to_luaval<cocos2d::ParallaxNode>(tolua_S, "cc.ParallaxNode",(cocos2d::ParallaxNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:getParallaxRoot",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_getParallaxRoot'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_getLayer(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_getLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObjectGroup:getLayer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_getLayer'", nullptr);
            return 0;
        }
        XSceneLayer* ret = cobj->getLayer(arg0);
        object_to_luaval<XSceneLayer>(tolua_S, "XSceneLayer",(XSceneLayer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:getLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_getLayer'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneObjectGroup_setPreservedLayerID(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setPreservedLayerID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObjectGroup:setPreservedLayerID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setPreservedLayerID'", nullptr);
            return 0;
        }
        cobj->setPreservedLayerID(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setPreservedLayerID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setPreservedLayerID'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_setLayerVisible(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setLayerVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObjectGroup:setLayerVisible");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "XSceneObjectGroup:setLayerVisible");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setLayerVisible'", nullptr);
            return 0;
        }
        cobj->setLayerVisible(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setLayerVisible",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setLayerVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_updateLayers(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_updateLayers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Size arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "XSceneObjectGroup:updateLayers");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "XSceneObjectGroup:updateLayers");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_updateLayers'", nullptr);
            return 0;
        }
        cobj->updateLayers(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:updateLayers",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_updateLayers'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_setFixViewRadius(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setFixViewRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneObjectGroup:setFixViewRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setFixViewRadius'", nullptr);
            return 0;
        }
        cobj->setFixViewRadius(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setFixViewRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setFixViewRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_setParallaxRoot(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setParallaxRoot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ParallaxNode* arg0;

        ok &= luaval_to_object<cocos2d::ParallaxNode>(tolua_S, 2, "cc.ParallaxNode",&arg0, "XSceneObjectGroup:setParallaxRoot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setParallaxRoot'", nullptr);
            return 0;
        }
        cobj->setParallaxRoot(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setParallaxRoot",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setParallaxRoot'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_addToLayer(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_addToLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        XSceneObject* arg1;
		bool arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XSceneObjectGroup:addToLayer");

        ok &= luaval_to_object<XSceneObject>(tolua_S, 3, "XSceneObject",&arg1, "XSceneObjectGroup:addToLayer");

		ok &= luaval_to_boolean(tolua_S, 4, &arg2, "XSceneObjectGroup:attachToLayer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_addToLayer'", nullptr);
            return 0;
        }
        cobj->addToLayer(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:addToLayer",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_addToLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_getViewRadius(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_getViewRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_getViewRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getViewRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:getViewRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_getViewRadius'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneObjectGroup_setLookAt(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setLookAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneObjectGroup:setLookAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setLookAt'", nullptr);
            return 0;
        }
        cobj->setLookAt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setLookAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setLookAt'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_tickDebugVisible(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_tickDebugVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneObjectGroup:tickDebugVisible");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_tickDebugVisible'", nullptr);
            return 0;
        }
        cobj->tickDebugVisible(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:tickDebugVisible",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_tickDebugVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_setViewRadius(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_setViewRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneObjectGroup:setViewRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_setViewRadius'", nullptr);
            return 0;
        }
        cobj->setViewRadius(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:setViewRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_setViewRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_getObjectKeys(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_getObjectKeys'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_getObjectKeys'", nullptr);
            return 0;
        }
        cocos2d::ValueVector& ret = cobj->getObjectKeys();
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:getObjectKeys",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_getObjectKeys'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_leaveMap(lua_State* tolua_S)
{
    int argc = 0;
    XSceneObjectGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneObjectGroup_leaveMap'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_leaveMap'", nullptr);
            return 0;
        }
        cobj->leaveMap();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneObjectGroup:leaveMap",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_leaveMap'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneObjectGroup_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XSceneObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneObjectGroup_create'", nullptr);
            return 0;
        }
        XSceneObjectGroup* ret = XSceneObjectGroup::create();
        object_to_luaval<XSceneObjectGroup>(tolua_S, "XSceneObjectGroup",(XSceneObjectGroup*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XSceneObjectGroup:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneObjectGroup_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XSceneObjectGroup_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XSceneObjectGroup)");
    return 0;
}

int lua_register_scene_XSceneObjectGroup(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XSceneObjectGroup");
    tolua_cclass(tolua_S,"XSceneObjectGroup","XSceneObjectGroup","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"XSceneObjectGroup");
        tolua_function(tolua_S,"load",lua_scene_XSceneObjectGroup_load);
        tolua_function(tolua_S,"onResume",lua_scene_XSceneObjectGroup_onResume);
        tolua_function(tolua_S,"updateCamera",lua_scene_XSceneObjectGroup_updateCamera);
        tolua_function(tolua_S,"clearall",lua_scene_XSceneObjectGroup_clearall);
        tolua_function(tolua_S,"getLayerIDs",lua_scene_XSceneObjectGroup_getLayerIDs);
        tolua_function(tolua_S,"setLayerWithID",lua_scene_XSceneObjectGroup_setLayerWithID);
        tolua_function(tolua_S,"setDebugNode",lua_scene_XSceneObjectGroup_setDebugNode);
        tolua_function(tolua_S,"cleanup",lua_scene_XSceneObjectGroup_cleanup);
        tolua_function(tolua_S,"onPause",lua_scene_XSceneObjectGroup_onPause);
        tolua_function(tolua_S,"getParallaxRoot",lua_scene_XSceneObjectGroup_getParallaxRoot);
        tolua_function(tolua_S,"getLayer",lua_scene_XSceneObjectGroup_getLayer);
        tolua_function(tolua_S,"setPreservedLayerID",lua_scene_XSceneObjectGroup_setPreservedLayerID);
        tolua_function(tolua_S,"setLayerVisible",lua_scene_XSceneObjectGroup_setLayerVisible);
        tolua_function(tolua_S,"updateLayers",lua_scene_XSceneObjectGroup_updateLayers);
        tolua_function(tolua_S,"setFixViewRadius",lua_scene_XSceneObjectGroup_setFixViewRadius);
        tolua_function(tolua_S,"setParallaxRoot",lua_scene_XSceneObjectGroup_setParallaxRoot);
        tolua_function(tolua_S,"addToLayer",lua_scene_XSceneObjectGroup_addToLayer);
        tolua_function(tolua_S,"getViewRadius",lua_scene_XSceneObjectGroup_getViewRadius);
        tolua_function(tolua_S,"setLookAt",lua_scene_XSceneObjectGroup_setLookAt);
        tolua_function(tolua_S,"tickDebugVisible",lua_scene_XSceneObjectGroup_tickDebugVisible);
        tolua_function(tolua_S,"setViewRadius",lua_scene_XSceneObjectGroup_setViewRadius);
        tolua_function(tolua_S,"getObjectKeys",lua_scene_XSceneObjectGroup_getObjectKeys);
        tolua_function(tolua_S,"leaveMap",lua_scene_XSceneObjectGroup_leaveMap);
        tolua_function(tolua_S,"create", lua_scene_XSceneObjectGroup_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XSceneObjectGroup).name();
    g_luaType[typeName] = "XSceneObjectGroup";
    g_typeCast["XSceneObjectGroup"] = "XSceneObjectGroup";
    return 1;
}

int lua_scene_XGameScene_updateCameraInPixels(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_updateCameraInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:updateCameraInPixels");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:updateCameraInPixels");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_updateCameraInPixels'", nullptr);
            return 0;
        }
        cobj->updateCameraInPixels(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:updateCameraInPixels",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_updateCameraInPixels'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_onResume(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_onResume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_onResume'", nullptr);
            return 0;
        }
        cobj->onResume();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:onResume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_onResume'.",&tolua_err);
#endif

    return 0;
}



int lua_scene_XGameScene_hideTiles(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_hideTiles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_hideTiles'", nullptr);
            return 0;
        }
        cobj->hideTiles();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:hideTiles",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_hideTiles'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_getSceneObjects(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_getSceneObjects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_getSceneObjects'", nullptr);
            return 0;
        }
        XSceneObjectGroup* ret = cobj->getSceneObjects();
        object_to_luaval<XSceneObjectGroup>(tolua_S, "XSceneObjectGroup",(XSceneObjectGroup*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:getSceneObjects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_getSceneObjects'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_mapPosToGLPos(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_mapPosToGLPos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XGameScene:mapPosToGLPos");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_mapPosToGLPos'", nullptr);
            return 0;
        }
        cobj->mapPosToGLPos(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:mapPosToGLPos",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_mapPosToGLPos'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_GLPositionToScreen(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_GLPositionToScreen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:GLPositionToScreen");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:GLPositionToScreen");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_GLPositionToScreen'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->GLPositionToScreen(arg0, arg1);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:GLPositionToScreen",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_GLPositionToScreen'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_cleanSceneObjects(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_cleanSceneObjects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_cleanSceneObjects'", nullptr);
            return 0;
        }
        cobj->cleanSceneObjects();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:cleanSceneObjects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_cleanSceneObjects'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XGameScene_getSceneNode(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_getSceneNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:getSceneNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_getSceneNode'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getSceneNode(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:getSceneNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_getSceneNode'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_cameraMoveInPixels(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_cameraMoveInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:cameraMoveInPixels");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:cameraMoveInPixels");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_cameraMoveInPixels'", nullptr);
            return 0;
        }
        cobj->cameraMoveInPixels(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:cameraMoveInPixels",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_cameraMoveInPixels'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_getCameraPositionInPixels(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_getCameraPositionInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_getCameraPositionInPixels'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getCameraPositionInPixels();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:getCameraPositionInPixels",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_getCameraPositionInPixels'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_screenToMap(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_screenToMap'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:screenToMap");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:screenToMap");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_screenToMap'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->screenToMap(arg0, arg1);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:screenToMap",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_screenToMap'.",&tolua_err);
#endif

    return 0;
}


int lua_scene_XGameScene_onPause(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_onPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_onPause'", nullptr);
            return 0;
        }
        cobj->onPause();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:onPause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_onPause'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_getMapBoundCheck(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_getMapBoundCheck'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_getMapBoundCheck'", nullptr);
            return 0;
        }
        bool ret = cobj->getMapBoundCheck();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:getMapBoundCheck",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_getMapBoundCheck'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_toPtr(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_toPtr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_toPtr'", nullptr);
            return 0;
        }
        void* ret = cobj->toPtr();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:toPtr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_toPtr'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_setIsShowTileProp(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_setIsShowTileProp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XGameScene:setIsShowTileProp");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_setIsShowTileProp'", nullptr);
            return 0;
        }
        cobj->setIsShowTileProp(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:setIsShowTileProp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_setIsShowTileProp'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_initWithMapFile(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_initWithMapFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        std::string arg1;
		std::string arg2;
		std::string arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XGameScene:initWithMapFile");

		ok &= luaval_to_std_string(tolua_S, 3, &arg2, "XGameScene:initWithMapFile");
		
		ok &= luaval_to_std_string(tolua_S, 4, &arg3, "XGameScene:initWithMapFile");

        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_initWithMapFile'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithMapFile(arg0, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:initWithMapFile",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_initWithMapFile'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XGameScene_loadMapInfo(lua_State* tolua_S)
{
	int argc = 0;
	XGameScene* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "XGameScene", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (XGameScene*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_scene_XGameScene_loadMapInfo'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		std::string arg0;
		int nIndex;
		ok &= luaval_to_int32(tolua_S, 2, &nIndex, "XGameScene:loadMapInfo");
		ok &= luaval_to_std_string(tolua_S, 3, &arg0, "XGameScene:loadMapInfo");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_scene_XGameScene_loadMapInfo'", nullptr);
			return 0;
		}
		bool ret = cobj->loadMapInfo(nIndex, arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:loadMapInfo", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_scene_XGameScene_loadMapInfo'.", &tolua_err);
#endif

	return 0;
}

int lua_scene_XGameScene_showTiles(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_showTiles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_showTiles'", nullptr);
            return 0;
        }
        cobj->showTiles();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:showTiles",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_showTiles'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_canMove(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_canMove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
		int arg_1;
        unsigned int arg0;
        unsigned int arg1;

		ok &= luaval_to_int32(tolua_S, 2, &arg_1, "XGameScene:canMove");
        ok &= luaval_to_uint32(tolua_S, 3,&arg0, "XGameScene:canMove");
        ok &= luaval_to_uint32(tolua_S, 4,&arg1, "XGameScene:canMove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_canMove'", nullptr);
            return 0;
        }
        bool ret = cobj->canMove(arg_1, arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:canMove",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_canMove'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_mapToScreen(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_mapToScreen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:mapToScreen");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:mapToScreen");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_mapToScreen'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->mapToScreen(arg0, arg1);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:mapToScreen",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_mapToScreen'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XGameScene_screenToGLPosition(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_screenToGLPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:screenToGLPosition");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:screenToGLPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_screenToGLPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->screenToGLPosition(arg0, arg1);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:screenToGLPosition",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_screenToGLPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_setMapBoundCheck(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_setMapBoundCheck'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XGameScene:setMapBoundCheck");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_setMapBoundCheck'", nullptr);
            return 0;
        }
        cobj->setMapBoundCheck(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:setMapBoundCheck",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_setMapBoundCheck'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_debugVisibleRect(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_debugVisibleRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:debugVisibleRect");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:debugVisibleRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_debugVisibleRect'", nullptr);
            return 0;
        }
        cobj->debugVisibleRect(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:debugVisibleRect",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_debugVisibleRect'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XGameScene_setIsDirty(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_setIsDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "XGameScene:setIsDirty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_setIsDirty'", nullptr);
            return 0;
        }
        cobj->setIsDirty(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:setIsDirty",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_setIsDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_mapToScreenAbsolute(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_mapToScreenAbsolute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XGameScene:mapToScreenAbsolute");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XGameScene:mapToScreenAbsolute");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_mapToScreenAbsolute'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->mapToScreenAbsolute(arg0, arg1);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:mapToScreenAbsolute",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_mapToScreenAbsolute'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_cameraMapPosition(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_cameraMapPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_cameraMapPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->cameraMapPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:cameraMapPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_cameraMapPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_clearAll(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_clearAll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_clearAll'", nullptr);
            return 0;
        }
        cobj->clearAll();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:clearAll",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_clearAll'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_leaveMap(lua_State* tolua_S)
{
    int argc = 0;
    XGameScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XGameScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XGameScene_leaveMap'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_leaveMap'", nullptr);
            return 0;
        }
        cobj->leaveMap();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XGameScene:leaveMap",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_leaveMap'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XGameScene_sharedScene(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XGameScene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XGameScene_sharedScene'", nullptr);
            return 0;
        }
        XGameScene* ret = XGameScene::sharedScene();
        object_to_luaval<XGameScene>(tolua_S, "XGameScene",(XGameScene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XGameScene:sharedScene",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XGameScene_sharedScene'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XGameScene_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XGameScene)");
    return 0;
}

int lua_register_scene_XGameScene(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XGameScene");
    tolua_cclass(tolua_S,"XGameScene","XGameScene","cc.ParallaxNode",nullptr);

    tolua_beginmodule(tolua_S,"XGameScene");
        tolua_function(tolua_S,"updateCameraInPixels",lua_scene_XGameScene_updateCameraInPixels);
        tolua_function(tolua_S,"onResume",lua_scene_XGameScene_onResume);
        tolua_function(tolua_S,"hideTiles",lua_scene_XGameScene_hideTiles);
        tolua_function(tolua_S,"getSceneObjects",lua_scene_XGameScene_getSceneObjects);
        tolua_function(tolua_S,"mapPosToGLPos",lua_scene_XGameScene_mapPosToGLPos);
        tolua_function(tolua_S,"GLPositionToScreen",lua_scene_XGameScene_GLPositionToScreen);
        tolua_function(tolua_S,"cleanSceneObjects",lua_scene_XGameScene_cleanSceneObjects);
        tolua_function(tolua_S,"getSceneNode",lua_scene_XGameScene_getSceneNode);
        tolua_function(tolua_S,"cameraMoveInPixels",lua_scene_XGameScene_cameraMoveInPixels);
        tolua_function(tolua_S,"getCameraPositionInPixels",lua_scene_XGameScene_getCameraPositionInPixels);
        tolua_function(tolua_S,"screenToMap",lua_scene_XGameScene_screenToMap);
        tolua_function(tolua_S,"onPause",lua_scene_XGameScene_onPause);
        tolua_function(tolua_S,"getMapBoundCheck",lua_scene_XGameScene_getMapBoundCheck);
        tolua_function(tolua_S,"toPtr",lua_scene_XGameScene_toPtr);
        tolua_function(tolua_S,"setIsShowTileProp",lua_scene_XGameScene_setIsShowTileProp);
		tolua_function(tolua_S, "initWithMapFile", lua_scene_XGameScene_initWithMapFile);
		tolua_function(tolua_S, "loadMapInfo", lua_scene_XGameScene_loadMapInfo);
        tolua_function(tolua_S,"showTiles",lua_scene_XGameScene_showTiles);
        tolua_function(tolua_S,"canMove",lua_scene_XGameScene_canMove);
        tolua_function(tolua_S,"mapToScreen",lua_scene_XGameScene_mapToScreen);
        tolua_function(tolua_S,"screenToGLPosition",lua_scene_XGameScene_screenToGLPosition);
        tolua_function(tolua_S,"setMapBoundCheck",lua_scene_XGameScene_setMapBoundCheck);
        tolua_function(tolua_S,"debugVisibleRect",lua_scene_XGameScene_debugVisibleRect);
        tolua_function(tolua_S,"setIsDirty",lua_scene_XGameScene_setIsDirty);
        tolua_function(tolua_S,"mapToScreenAbsolute",lua_scene_XGameScene_mapToScreenAbsolute);
        tolua_function(tolua_S,"cameraMapPosition",lua_scene_XGameScene_cameraMapPosition);
        tolua_function(tolua_S,"clearAll",lua_scene_XGameScene_clearAll);
        tolua_function(tolua_S,"leaveMap",lua_scene_XGameScene_leaveMap);
        tolua_function(tolua_S,"sharedScene", lua_scene_XGameScene_sharedScene);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XGameScene).name();
    g_luaType[typeName] = "XGameScene";
    g_typeCast["XGameScene"] = "XGameScene";
    return 1;
}

int lua_scene_XLogicScene_getViewPortSize(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_getViewPortSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_getViewPortSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getViewPortSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:getViewPortSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_getViewPortSize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_zoom(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_zoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XLogicScene:zoom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_zoom'", nullptr);
            return 0;
        }
        cobj->zoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:zoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_zoom'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_resetViewPortSize(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_resetViewPortSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        double arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XLogicScene:resetViewPortSize");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XLogicScene:resetViewPortSize");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "XLogicScene:resetViewPortSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_resetViewPortSize'", nullptr);
            return 0;
        }
        cobj->resetViewPortSize(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:resetViewPortSize",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_resetViewPortSize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_getViewPortScale(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_getViewPortScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_getViewPortScale'", nullptr);
            return 0;
        }
        double ret = cobj->getViewPortScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:getViewPortScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_getViewPortScale'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_moveCameraMap(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_moveCameraMap'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XLogicScene:moveCameraMap");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XLogicScene:moveCameraMap");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_moveCameraMap'", nullptr);
            return 0;
        }
        cobj->moveCameraMap(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:moveCameraMap",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_moveCameraMap'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_getNode(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_getNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
		int nIndex = 1;
		ok &= luaval_to_int32(tolua_S, 2, &nIndex, "lua_scene_XLogicScene_getNode");

        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_getNode'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getNode( nIndex );
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:getNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_getNode'.",&tolua_err);
#endif

    return 0;
}


int lua_scene_XLogicScene__setViewPortSize(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene__setViewPortSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        double arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XLogicScene:_setViewPortSize");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XLogicScene:_setViewPortSize");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "XLogicScene:_setViewPortSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene__setViewPortSize'", nullptr);
            return 0;
        }
        cobj->_setViewPortSize(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:_setViewPortSize",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene__setViewPortSize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_init(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_init'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_setCameraOffset(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_setCameraOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XLogicScene:setCameraOffset");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XLogicScene:setCameraOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_setCameraOffset'", nullptr);
            return 0;
        }
        cobj->setCameraOffset(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:setCameraOffset",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_setCameraOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_cameraMapPosition(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_cameraMapPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_cameraMapPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->cameraMapPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:cameraMapPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_cameraMapPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_setViewPortSize(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_setViewPortSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        double arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XLogicScene:setViewPortSize");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XLogicScene:setViewPortSize");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "XLogicScene:setViewPortSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_setViewPortSize'", nullptr);
            return 0;
        }
        cobj->setViewPortSize(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:setViewPortSize",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_setViewPortSize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_moveCamera(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_moveCamera'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "XLogicScene:moveCamera");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "XLogicScene:moveCamera");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_moveCamera'", nullptr);
            return 0;
        }
        cobj->moveCamera(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:moveCamera",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_moveCamera'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_getSceneNode(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_getSceneNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_getSceneNode'", nullptr);
            return 0;
        }
        XGameScene* ret = cobj->getSceneNode();
        object_to_luaval<XGameScene>(tolua_S, "XGameScene",(XGameScene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:getSceneNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_getSceneNode'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_getViewPortVisibleSize(lua_State* tolua_S)
{
    int argc = 0;
    XLogicScene* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XLogicScene*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XLogicScene_getViewPortVisibleSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_getViewPortVisibleSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getViewPortVisibleSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XLogicScene:getViewPortVisibleSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_getViewPortVisibleSize'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XLogicScene_sharedScene(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XLogicScene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XLogicScene_sharedScene'", nullptr);
            return 0;
        }
        XLogicScene* ret = XLogicScene::sharedScene();
        object_to_luaval<XLogicScene>(tolua_S, "XLogicScene",(XLogicScene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XLogicScene:sharedScene",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XLogicScene_sharedScene'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XLogicScene_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XLogicScene)");
    return 0;
}

int lua_register_scene_XLogicScene(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XLogicScene");
    tolua_cclass(tolua_S,"XLogicScene","XLogicScene","cc.Scene",nullptr);

    tolua_beginmodule(tolua_S,"XLogicScene");
        tolua_function(tolua_S,"getViewPortSize",lua_scene_XLogicScene_getViewPortSize);
        tolua_function(tolua_S,"zoom",lua_scene_XLogicScene_zoom);
        tolua_function(tolua_S,"resetViewPortSize",lua_scene_XLogicScene_resetViewPortSize);
        tolua_function(tolua_S,"getViewPortScale",lua_scene_XLogicScene_getViewPortScale);
        tolua_function(tolua_S,"moveCameraMap",lua_scene_XLogicScene_moveCameraMap);
        tolua_function(tolua_S,"getNode",lua_scene_XLogicScene_getNode);
        tolua_function(tolua_S,"_setViewPortSize",lua_scene_XLogicScene__setViewPortSize);
        tolua_function(tolua_S,"init",lua_scene_XLogicScene_init);
        tolua_function(tolua_S,"setCameraOffset",lua_scene_XLogicScene_setCameraOffset);
        tolua_function(tolua_S,"cameraMapPosition",lua_scene_XLogicScene_cameraMapPosition);
        tolua_function(tolua_S,"setViewPortSize",lua_scene_XLogicScene_setViewPortSize);
        tolua_function(tolua_S,"moveCamera",lua_scene_XLogicScene_moveCamera);
        tolua_function(tolua_S,"getSceneNode",lua_scene_XLogicScene_getSceneNode);
        tolua_function(tolua_S,"getViewPortVisibleSize",lua_scene_XLogicScene_getViewPortVisibleSize);
        tolua_function(tolua_S,"sharedScene", lua_scene_XLogicScene_sharedScene);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XLogicScene).name();
    g_luaType[typeName] = "XLogicScene";
    g_typeCast["XLogicScene"] = "XLogicScene";
    return 1;
}

int lua_scene_XSceneBackgroundLayer_getBaseScale(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_getBaseScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_getBaseScale'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getBaseScale();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:getBaseScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_getBaseScale'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_getBasePos(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_getBasePos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_getBasePos'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getBasePos();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:getBasePos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_getBasePos'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_setUVTranslate(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_setUVTranslate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneBackgroundLayer:setUVTranslate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_setUVTranslate'", nullptr);
            return 0;
        }
        cobj->setUVTranslate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:setUVTranslate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_setUVTranslate'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_setBasePos(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_setBasePos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneBackgroundLayer:setBasePos");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_setBasePos'", nullptr);
            return 0;
        }
        cobj->setBasePos(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:setBasePos",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_setBasePos'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_setBackground(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_setBackground'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XSceneBackgroundLayer:setBackground");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_setBackground'", nullptr);
            return 0;
        }
        cobj->setBackground(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:setBackground",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_setBackground'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_setShadername(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_setShadername'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "XSceneBackgroundLayer:setShadername");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_setShadername'", nullptr);
            return 0;
        }
        cobj->setShadername(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:setShadername",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_setShadername'.",&tolua_err);
#endif

    return 0;
}

int lua_scene_XSceneBackgroundLayer_setBaseScale(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_setBaseScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "XSceneBackgroundLayer:setBaseScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_setBaseScale'", nullptr);
            return 0;
        }
        cobj->setBaseScale(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:setBaseScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_setBaseScale'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_getUVTranslate(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_getUVTranslate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_getUVTranslate'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getUVTranslate();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:getUVTranslate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_getUVTranslate'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_transfomUV(lua_State* tolua_S)
{
    int argc = 0;
    XSceneBackgroundLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (XSceneBackgroundLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_scene_XSceneBackgroundLayer_transfomUV'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "XSceneBackgroundLayer:transfomUV");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_transfomUV'", nullptr);
            return 0;
        }
        cobj->transfomUV(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XSceneBackgroundLayer:transfomUV",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_transfomUV'.",&tolua_err);
#endif

    return 0;
}
int lua_scene_XSceneBackgroundLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XSceneBackgroundLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_scene_XSceneBackgroundLayer_create'", nullptr);
            return 0;
        }
        XSceneBackgroundLayer* ret = XSceneBackgroundLayer::create();
        object_to_luaval<XSceneBackgroundLayer>(tolua_S, "XSceneBackgroundLayer",(XSceneBackgroundLayer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XSceneBackgroundLayer:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_scene_XSceneBackgroundLayer_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_scene_XSceneBackgroundLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XSceneBackgroundLayer)");
    return 0;
}

int lua_register_scene_XSceneBackgroundLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XSceneBackgroundLayer");
    tolua_cclass(tolua_S,"XSceneBackgroundLayer","XSceneBackgroundLayer","XSceneLayer",nullptr);

    tolua_beginmodule(tolua_S,"XSceneBackgroundLayer");
        tolua_function(tolua_S,"getBaseScale",lua_scene_XSceneBackgroundLayer_getBaseScale);
        tolua_function(tolua_S,"getBasePos",lua_scene_XSceneBackgroundLayer_getBasePos);
        tolua_function(tolua_S,"setUVTranslate",lua_scene_XSceneBackgroundLayer_setUVTranslate);
        tolua_function(tolua_S,"setBasePos",lua_scene_XSceneBackgroundLayer_setBasePos);
        tolua_function(tolua_S,"setBackground",lua_scene_XSceneBackgroundLayer_setBackground);
        tolua_function(tolua_S,"setShadername",lua_scene_XSceneBackgroundLayer_setShadername);
        tolua_function(tolua_S,"setBaseScale",lua_scene_XSceneBackgroundLayer_setBaseScale);
        tolua_function(tolua_S,"getUVTranslate",lua_scene_XSceneBackgroundLayer_getUVTranslate);
        tolua_function(tolua_S,"transfomUV",lua_scene_XSceneBackgroundLayer_transfomUV);
        tolua_function(tolua_S,"create", lua_scene_XSceneBackgroundLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XSceneBackgroundLayer).name();
    g_luaType[typeName] = "XSceneBackgroundLayer";
    g_typeCast["XSceneBackgroundLayer"] = "XSceneBackgroundLayer";
    return 1;
}
TOLUA_API int register_all_scene(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"scene",0);
	tolua_beginmodule(tolua_S,"scene");

	lua_register_scene_XSceneObject(tolua_S);
	lua_register_scene_XPosNode(tolua_S);
	lua_register_scene_XSizeNode(tolua_S);
	lua_register_scene_XSceneObjectGroup(tolua_S);
	lua_register_scene_XLogicScene(tolua_S);
	lua_register_scene_XSceneLayer(tolua_S);
	lua_register_scene_XSceneBackgroundLayer(tolua_S);
	lua_register_scene_XGameScene(tolua_S);
	lua_register_scene_GameMapInfo(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

