#include "lua_gui_common_auto.hpp"
#include "lua_gui_common.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_guiex_RichTextCreator_setDefaultFontSize(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_setDefaultFontSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "RichTextCreator:setDefaultFontSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_setDefaultFontSize'", nullptr);
            return 0;
        }
        cobj->setDefaultFontSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:setDefaultFontSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_setDefaultFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_setDefaultFontName(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_setDefaultFontName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:setDefaultFontName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_setDefaultFontName'", nullptr);
            return 0;
        }
        cobj->setDefaultFontName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:setDefaultFontName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_setDefaultFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_getDefaultFontSize(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_getDefaultFontSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_getDefaultFontSize'", nullptr);
            return 0;
        }
        double ret = cobj->getDefaultFontSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:getDefaultFontSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_getDefaultFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_getDefaultFontOpacity(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_getDefaultFontOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_getDefaultFontOpacity'", nullptr);
            return 0;
        }
        int ret = cobj->getDefaultFontOpacity();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:getDefaultFontOpacity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_getDefaultFontOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_setDefaultFontOpacity(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_setDefaultFontOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "RichTextCreator:setDefaultFontOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_setDefaultFontOpacity'", nullptr);
            return 0;
        }
        cobj->setDefaultFontOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:setDefaultFontOpacity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_setDefaultFontOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_Parser(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_Parser'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:Parser");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_Parser'", nullptr);
            return 0;
        }
        cocos2d::ui::RichText* ret = cobj->Parser(arg0);
        object_to_luaval<cocos2d::ui::RichText>(tolua_S, "ccui.RichText",(cocos2d::ui::RichText*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:Parser",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_Parser'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_createFontWidthConfigFile(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_createFontWidthConfigFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:createFontWidthConfigFile");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "RichTextCreator:createFontWidthConfigFile");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "RichTextCreator:createFontWidthConfigFile");

        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "RichTextCreator:createFontWidthConfigFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_createFontWidthConfigFile'", nullptr);
            return 0;
        }
        bool ret = cobj->createFontWidthConfigFile(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:createFontWidthConfigFile",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_createFontWidthConfigFile'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_getDefaultFontColor(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_getDefaultFontColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_getDefaultFontColor'", nullptr);
            return 0;
        }
        cocos2d::Color3B ret = cobj->getDefaultFontColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:getDefaultFontColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_getDefaultFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_setDefaultFontColor(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_setDefaultFontColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "RichTextCreator:setDefaultFontColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_setDefaultFontColor'", nullptr);
            return 0;
        }
        cobj->setDefaultFontColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:setDefaultFontColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_setDefaultFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_LoadFontWidthConfig(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_LoadFontWidthConfig'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:LoadFontWidthConfig");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_LoadFontWidthConfig'", nullptr);
            return 0;
        }
        bool ret = cobj->LoadFontWidthConfig(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string arg0;
        bool arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:LoadFontWidthConfig");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "RichTextCreator:LoadFontWidthConfig");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_LoadFontWidthConfig'", nullptr);
            return 0;
        }
        bool ret = cobj->LoadFontWidthConfig(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:LoadFontWidthConfig",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_LoadFontWidthConfig'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_ParserWithSize(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_ParserWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::Size arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:ParserWithSize");

        ok &= luaval_to_size(tolua_S, 3, &arg1, "RichTextCreator:ParserWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_ParserWithSize'", nullptr);
            return 0;
        }
        cocos2d::ui::RichText* ret = cobj->ParserWithSize(arg0, arg1);
        object_to_luaval<cocos2d::ui::RichText>(tolua_S, "ccui.RichText",(cocos2d::ui::RichText*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:ParserWithSize",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_ParserWithSize'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_getDefaultFontName(lua_State* tolua_S)
{
    int argc = 0;
    RichTextCreator* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (RichTextCreator*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_RichTextCreator_getDefaultFontName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_getDefaultFontName'", nullptr);
            return 0;
        }
        std::string ret = cobj->getDefaultFontName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "RichTextCreator:getDefaultFontName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_getDefaultFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_RichTextCreator_convertAttrStr(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:convertAttrStr");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_convertAttrStr'", nullptr);
            return 0;
        }
        std::string ret = RichTextCreator::convertAttrStr(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "RichTextCreator:convertAttrStr",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_convertAttrStr'.",&tolua_err);
#endif
    return 0;
}
int lua_guiex_RichTextCreator_convertNormalStr(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "RichTextCreator:convertNormalStr");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_convertNormalStr'", nullptr);
            return 0;
        }
        std::string ret = RichTextCreator::convertNormalStr(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "RichTextCreator:convertNormalStr",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_convertNormalStr'.",&tolua_err);
#endif
    return 0;
}
int lua_guiex_RichTextCreator_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"RichTextCreator",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_RichTextCreator_getInstance'", nullptr);
            return 0;
        }
        RichTextCreator* ret = RichTextCreator::getInstance();
        object_to_luaval<RichTextCreator>(tolua_S, "RichTextCreator",(RichTextCreator*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "RichTextCreator:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_RichTextCreator_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_guiex_RichTextCreator_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RichTextCreator)");
    return 0;
}

int lua_register_guiex_RichTextCreator(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"RichTextCreator");
    tolua_cclass(tolua_S,"RichTextCreator","RichTextCreator","",nullptr);

    tolua_beginmodule(tolua_S,"RichTextCreator");
        tolua_function(tolua_S,"setDefaultFontSize",lua_guiex_RichTextCreator_setDefaultFontSize);
        tolua_function(tolua_S,"setDefaultFontName",lua_guiex_RichTextCreator_setDefaultFontName);
        tolua_function(tolua_S,"getDefaultFontSize",lua_guiex_RichTextCreator_getDefaultFontSize);
        tolua_function(tolua_S,"getDefaultFontOpacity",lua_guiex_RichTextCreator_getDefaultFontOpacity);
        tolua_function(tolua_S,"setDefaultFontOpacity",lua_guiex_RichTextCreator_setDefaultFontOpacity);
        tolua_function(tolua_S,"Parser",lua_guiex_RichTextCreator_Parser);
        tolua_function(tolua_S,"createFontWidthConfigFile",lua_guiex_RichTextCreator_createFontWidthConfigFile);
        tolua_function(tolua_S,"getDefaultFontColor",lua_guiex_RichTextCreator_getDefaultFontColor);
        tolua_function(tolua_S,"setDefaultFontColor",lua_guiex_RichTextCreator_setDefaultFontColor);
        tolua_function(tolua_S,"LoadFontWidthConfig",lua_guiex_RichTextCreator_LoadFontWidthConfig);
        tolua_function(tolua_S,"ParserWithSize",lua_guiex_RichTextCreator_ParserWithSize);
        tolua_function(tolua_S,"getDefaultFontName",lua_guiex_RichTextCreator_getDefaultFontName);
        tolua_function(tolua_S,"convertAttrStr", lua_guiex_RichTextCreator_convertAttrStr);
        tolua_function(tolua_S,"convertNormalStr", lua_guiex_RichTextCreator_convertNormalStr);
        tolua_function(tolua_S,"getInstance", lua_guiex_RichTextCreator_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(RichTextCreator).name();
    g_luaType[typeName] = "RichTextCreator";
    g_typeCast["RichTextCreator"] = "RichTextCreator";
    return 1;
}

int lua_guiex_EventRichText_setUserStringData(lua_State* tolua_S)
{
    int argc = 0;
    EventRichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"EventRichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (EventRichText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_EventRichText_setUserStringData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "EventRichText:setUserStringData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_EventRichText_setUserStringData'", nullptr);
            return 0;
        }
        cobj->setUserStringData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "EventRichText:setUserStringData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_EventRichText_setUserStringData'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_EventRichText_getUserStringData(lua_State* tolua_S)
{
    int argc = 0;
    EventRichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"EventRichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (EventRichText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_guiex_EventRichText_getUserStringData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_EventRichText_getUserStringData'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getUserStringData();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "EventRichText:getUserStringData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_EventRichText_getUserStringData'.",&tolua_err);
#endif

    return 0;
}
int lua_guiex_EventRichText_constructor(lua_State* tolua_S)
{
    int argc = 0;
    EventRichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "EventRichText:EventRichText");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_guiex_EventRichText_constructor'", nullptr);
            return 0;
        }
        cobj = new EventRichText(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"EventRichText");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "EventRichText:EventRichText",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_guiex_EventRichText_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_guiex_EventRichText_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventRichText)");
    return 0;
}

int lua_register_guiex_EventRichText(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"EventRichText");
    tolua_cclass(tolua_S,"EventRichText","EventRichText","cc.EventCustom",nullptr);

    tolua_beginmodule(tolua_S,"EventRichText");
        tolua_function(tolua_S,"new",lua_guiex_EventRichText_constructor);
        tolua_function(tolua_S,"setUserStringData",lua_guiex_EventRichText_setUserStringData);
        tolua_function(tolua_S,"getUserStringData",lua_guiex_EventRichText_getUserStringData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(EventRichText).name();
    g_luaType[typeName] = "EventRichText";
    g_typeCast["EventRichText"] = "EventRichText";
    return 1;
}


int lua_guiex_BreadthWidget_create(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "guiex.BreadthWidget", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_guiex_BreadthWidget_create'", nullptr);
			return 0;
		}
		BreadthWidget* ret = BreadthWidget::create();
		object_to_luaval<BreadthWidget>(tolua_S, "guiex.BreadthWidget", (BreadthWidget*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "guiex.BreadthWidget:create", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_guiex_BreadthWidget_create'.", &tolua_err);
#endif
	return 0;
}

int lua_register_guiex_BreadthWidget(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "guiex.BreadthWidget");
	tolua_cclass(tolua_S, "BreadthWidget", "guiex.BreadthWidget", "ccui.Widget", nullptr);

	tolua_beginmodule(tolua_S, "BreadthWidget");
		tolua_function(tolua_S, "create", lua_guiex_BreadthWidget_create);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(BreadthWidget).name();
	g_luaType[typeName] = "guiex.BreadthWidget";
	g_typeCast["BreadthWidget"] = "guiex.BreadthWidget";
	return 1;
}

TOLUA_API int register_all_guiex(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"guiex",0);
	tolua_beginmodule(tolua_S,"guiex");

	lua_register_guiex_EventRichText(tolua_S);
	lua_register_guiex_RichTextCreator(tolua_S);
	lua_register_guiex_BreadthWidget(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

