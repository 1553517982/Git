#include "lua_gamecore_helpers_auto.hpp"
#include "lua_game_core_helpers.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "utils/md5/XMD5Utils.h"
#include "zlib.h"
#include "FileIO.h"
#include "base/TableFile/CTableFile.h"

#ifdef WIN32
#pragma warning( error:4715 )
#endif

int lua_helpers_ActionHelpers_moveTo(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        int arg5;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:moveTo");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:moveTo");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:moveTo");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "ActionHelpers:moveTo");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "ActionHelpers:moveTo");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ActionHelpers:moveTo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_moveTo'", nullptr);
            return 0;
        }
        cocos2d::ActionInterval* ret = ActionHelpers::moveTo(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:moveTo",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_moveTo'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayFadoutRemove(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        double arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayFadoutRemove");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:delayFadoutRemove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayFadoutRemove'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayFadoutRemove(arg0, arg1);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayFadoutRemove",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayFadoutRemove'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayEaseInFadeIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        double arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayEaseInFadeIn");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:delayEaseInFadeIn");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:delayEaseInFadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayEaseInFadeIn'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayEaseInFadeIn(arg0, arg1, arg2);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayEaseInFadeIn",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayEaseInFadeIn'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayEaseInFadoutRemove(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        double arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayEaseInFadoutRemove");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:delayEaseInFadoutRemove");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:delayEaseInFadoutRemove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayEaseInFadoutRemove'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayEaseInFadoutRemove(arg0, arg1, arg2);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayEaseInFadoutRemove",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayEaseInFadoutRemove'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayEaseOutFadeIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        double arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayEaseOutFadeIn");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:delayEaseOutFadeIn");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:delayEaseOutFadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayEaseOutFadeIn'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayEaseOutFadeIn(arg0, arg1, arg2);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayEaseOutFadeIn",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayEaseOutFadeIn'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_removeWhenTimelineFinish(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            cocostudio::timeline::ActionTimeline* arg0;
            ok &= luaval_to_object<cocostudio::timeline::ActionTimeline>(tolua_S, 2, "ccs.ActionTimeline",&arg0, "ActionHelpers:removeWhenTimelineFinish");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:removeWhenTimelineFinish");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:removeWhenTimelineFinish");
            if (!ok) { break; }
            cocos2d::Action* ret = ActionHelpers::removeWhenTimelineFinish(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Action>(tolua_S, "cc.Action",(cocos2d::Action*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocostudio::timeline::ActionTimeline* arg0;
            ok &= luaval_to_object<cocostudio::timeline::ActionTimeline>(tolua_S, 2, "ccs.ActionTimeline",&arg0, "ActionHelpers:removeWhenTimelineFinish");
            if (!ok) { break; }
            cocos2d::Action* ret = ActionHelpers::removeWhenTimelineFinish(arg0);
            object_to_luaval<cocos2d::Action>(tolua_S, "cc.Action",(cocos2d::Action*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ActionHelpers:removeWhenTimelineFinish",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_removeWhenTimelineFinish'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_easeElasticOutScale(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:easeElasticOutScale");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:easeElasticOutScale");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:easeElasticOutScale");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "ActionHelpers:easeElasticOutScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_easeElasticOutScale'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::easeElasticOutScale(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:easeElasticOutScale",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_easeElasticOutScale'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_removeWhenActionFinish(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::FiniteTimeAction* arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_object<cocos2d::FiniteTimeAction>(tolua_S, 2, "cc.FiniteTimeAction",&arg0, "ActionHelpers:removeWhenActionFinish");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:removeWhenActionFinish");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:removeWhenActionFinish");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_removeWhenActionFinish'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::removeWhenActionFinish(arg0, arg1, arg2);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:removeWhenActionFinish",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_removeWhenActionFinish'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayEaseOutFadoutRemove(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        double arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayEaseOutFadoutRemove");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:delayEaseOutFadoutRemove");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:delayEaseOutFadoutRemove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayEaseOutFadoutRemove'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayEaseOutFadoutRemove(arg0, arg1, arg2);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayEaseOutFadoutRemove",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayEaseOutFadoutRemove'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_easeElasticInScale(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:easeElasticInScale");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:easeElasticInScale");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ActionHelpers:easeElasticInScale");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "ActionHelpers:easeElasticInScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_easeElasticInScale'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::easeElasticInScale(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:easeElasticInScale",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_easeElasticInScale'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayRemove(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayRemove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayRemove'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayRemove(arg0);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayRemove",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayRemove'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ActionHelpers_delayFadeIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ActionHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        double arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "ActionHelpers:delayFadeIn");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ActionHelpers:delayFadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ActionHelpers_delayFadeIn'", nullptr);
            return 0;
        }
        cocos2d::FiniteTimeAction* ret = ActionHelpers::delayFadeIn(arg0, arg1);
        object_to_luaval<cocos2d::FiniteTimeAction>(tolua_S, "cc.FiniteTimeAction",(cocos2d::FiniteTimeAction*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ActionHelpers:delayFadeIn",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ActionHelpers_delayFadeIn'.",&tolua_err);
#endif
    return 0;
}
static int lua_helpers_ActionHelpers_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionHelpers)");
    return 0;
}

int lua_register_helpers_ActionHelpers(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ActionHelpers");
    tolua_cclass(tolua_S,"ActionHelpers","ActionHelpers","",nullptr);

    tolua_beginmodule(tolua_S,"ActionHelpers");
        tolua_function(tolua_S,"moveTo", lua_helpers_ActionHelpers_moveTo);
        tolua_function(tolua_S,"delayFadoutRemove", lua_helpers_ActionHelpers_delayFadoutRemove);
        tolua_function(tolua_S,"delayEaseInFadeIn", lua_helpers_ActionHelpers_delayEaseInFadeIn);
        tolua_function(tolua_S,"delayEaseInFadoutRemove", lua_helpers_ActionHelpers_delayEaseInFadoutRemove);
        tolua_function(tolua_S,"delayEaseOutFadeIn", lua_helpers_ActionHelpers_delayEaseOutFadeIn);
        tolua_function(tolua_S,"removeWhenTimelineFinish", lua_helpers_ActionHelpers_removeWhenTimelineFinish);
        tolua_function(tolua_S,"easeElasticOutScale", lua_helpers_ActionHelpers_easeElasticOutScale);
        tolua_function(tolua_S,"removeWhenActionFinish", lua_helpers_ActionHelpers_removeWhenActionFinish);
        tolua_function(tolua_S,"delayEaseOutFadoutRemove", lua_helpers_ActionHelpers_delayEaseOutFadoutRemove);
        tolua_function(tolua_S,"easeElasticInScale", lua_helpers_ActionHelpers_easeElasticInScale);
        tolua_function(tolua_S,"delayRemove", lua_helpers_ActionHelpers_delayRemove);
        tolua_function(tolua_S,"delayFadeIn", lua_helpers_ActionHelpers_delayFadeIn);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ActionHelpers).name();
    g_luaType[typeName] = "ActionHelpers";
    g_typeCast["ActionHelpers"] = "ActionHelpers";
    return 1;
}

int lua_helpers_NodeHelpers_getUserObject(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:getUserObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_getUserObject'", nullptr);
            return 0;
        }
        const char* ret = cocos2d::ui::NodeHelpers::getUserObject(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:getUserObject",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_getUserObject'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_seekActionWidgetByActionTag(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Node* arg0;
        int arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:seekActionWidgetByActionTag");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.NodeHelpers:seekActionWidgetByActionTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_seekActionWidgetByActionTag'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cocos2d::ui::NodeHelpers::seekActionWidgetByActionTag(arg0, arg1);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:seekActionWidgetByActionTag",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_seekActionWidgetByActionTag'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_seekWidgetByName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Node* arg0;
        std::string arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:seekWidgetByName");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.NodeHelpers:seekWidgetByName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_seekWidgetByName'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cocos2d::ui::NodeHelpers::seekWidgetByName(arg0, arg1);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:seekWidgetByName",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_seekWidgetByName'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_recursiveSetCascadeOpacityEnabled(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Node* arg0;
        bool arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:recursiveSetCascadeOpacityEnabled");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccui.NodeHelpers:recursiveSetCascadeOpacityEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_recursiveSetCascadeOpacityEnabled'", nullptr);
            return 0;
        }
        cocos2d::ui::NodeHelpers::recursiveSetCascadeOpacityEnabled(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:recursiveSetCascadeOpacityEnabled",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_recursiveSetCascadeOpacityEnabled'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_safeRemoveChild(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Node* arg0;
        cocos2d::Node* arg1;
        bool arg2;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:safeRemoveChild");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1, "ccui.NodeHelpers:safeRemoveChild");
        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.NodeHelpers:safeRemoveChild");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_safeRemoveChild'", nullptr);
            return 0;
        }
        cocos2d::ui::NodeHelpers::safeRemoveChild(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:safeRemoveChild",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_safeRemoveChild'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_seekWidgetByTag(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Node* arg0;
        int arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:seekWidgetByTag");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.NodeHelpers:seekWidgetByTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_seekWidgetByTag'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cocos2d::ui::NodeHelpers::seekWidgetByTag(arg0, arg1);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:seekWidgetByTag",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_seekWidgetByTag'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_safeRelease(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Ref* arg0;
        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0, "ccui.NodeHelpers:safeRelease");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_safeRelease'", nullptr);
            return 0;
        }
        cocos2d::ui::NodeHelpers::safeRelease(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:safeRelease",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_safeRelease'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_NodeHelpers_safeRemoveFromParent(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.NodeHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Node* arg0;
        bool arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.NodeHelpers:safeRemoveFromParent");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccui.NodeHelpers:safeRemoveFromParent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NodeHelpers_safeRemoveFromParent'", nullptr);
            return 0;
        }
        cocos2d::ui::NodeHelpers::safeRemoveFromParent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.NodeHelpers:safeRemoveFromParent",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NodeHelpers_safeRemoveFromParent'.",&tolua_err);
#endif
    return 0;
}
static int lua_helpers_NodeHelpers_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NodeHelpers)");
    return 0;
}

int lua_register_helpers_NodeHelpers(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.NodeHelpers");
    tolua_cclass(tolua_S,"NodeHelpers","ccui.NodeHelpers","",nullptr);

    tolua_beginmodule(tolua_S,"NodeHelpers");
        tolua_function(tolua_S,"getUserObject", lua_helpers_NodeHelpers_getUserObject);
        tolua_function(tolua_S,"seekActionWidgetByActionTag", lua_helpers_NodeHelpers_seekActionWidgetByActionTag);
        tolua_function(tolua_S,"seekWidgetByName", lua_helpers_NodeHelpers_seekWidgetByName);
        tolua_function(tolua_S,"recursiveSetCascadeOpacityEnabled", lua_helpers_NodeHelpers_recursiveSetCascadeOpacityEnabled);
        tolua_function(tolua_S,"safeRemoveChild", lua_helpers_NodeHelpers_safeRemoveChild);
        tolua_function(tolua_S,"seekWidgetByTag", lua_helpers_NodeHelpers_seekWidgetByTag);
        tolua_function(tolua_S,"safeRelease", lua_helpers_NodeHelpers_safeRelease);
        tolua_function(tolua_S,"safeRemoveFromParent", lua_helpers_NodeHelpers_safeRemoveFromParent);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::NodeHelpers).name();
    g_luaType[typeName] = "ccui.NodeHelpers";
    g_typeCast["NodeHelpers"] = "ccui.NodeHelpers";
    return 1;
}

int lua_helpers_XAsyncLoadOption_constructor(lua_State* tolua_S)
{
	int argc = 0;
	XAsyncLoadOption* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif



	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_XAsyncLoadOption_constructor'", nullptr);
			return 0;
		}
		cobj = new XAsyncLoadOption();
		tolua_pushusertype(tolua_S, (void*)cobj, "XAsyncLoadOption");
		tolua_register_gc(tolua_S, lua_gettop(tolua_S));
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "XAsyncLoadOption:XAsyncLoadOption", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_XAsyncLoadOption_constructor'.", &tolua_err);
#endif

	return 0;
}

static int lua_helpers_XAsyncLoadOption_finalize(lua_State* tolua_S)
{
	printf("luabindings: finalizing LUA object (XAsyncLoadOption)");
	return 0;
}

int lua_register_helpers_XAsyncLoadOption(lua_State* tolua_S)
{
	tolua_usertype(tolua_S, "XAsyncLoadOption");
	tolua_cclass(tolua_S, "XAsyncLoadOption", "XAsyncLoadOption", "", nullptr);

	tolua_beginmodule(tolua_S, "XAsyncLoadOption");
	tolua_function(tolua_S, "new", lua_helpers_XAsyncLoadOption_constructor);
	tolua_endmodule(tolua_S);
	std::string typeName = typeid(XAsyncLoadOption).name();
	g_luaType[typeName] = "XAsyncLoadOption";
	g_typeCast["XAsyncLoadOption"] = "XAsyncLoadOption";
	return 1;
}

int lua_helpers_ResourceHelpers_decompressAsync(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        const char* arg0;
        unsigned int arg1;
        XLambda* arg2;
        XLambda* arg3;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:decompressAsync"); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ResourceHelpers:decompressAsync");
        ok &= luaval_to_object<XLambda>(tolua_S, 4, "XLambda",&arg2, "ResourceHelpers:decompressAsync");
        ok &= luaval_to_object<XLambda>(tolua_S, 5, "XLambda",&arg3, "ResourceHelpers:decompressAsync");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_decompressAsync'", nullptr);
            return 0;
        }
        int ret = ResourceHelpers::decompressAsync(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:decompressAsync",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_decompressAsync'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_cancelDecompressAsync(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:cancelDecompressAsync"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_cancelDecompressAsync'", nullptr);
            return 0;
        }
        ResourceHelpers::cancelDecompressAsync(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:cancelDecompressAsync",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_cancelDecompressAsync'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_loadWWW(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        cocos2d::ValueMap arg0;
        XLambda* arg1;
        XLambda* arg2;
        XLambda* arg3;
        unsigned int arg4;
        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "ResourceHelpers:loadWWW");
        ok &= luaval_to_object<XLambda>(tolua_S, 3, "XLambda",&arg1, "ResourceHelpers:loadWWW");
        ok &= luaval_to_object<XLambda>(tolua_S, 4, "XLambda",&arg2, "ResourceHelpers:loadWWW");
        ok &= luaval_to_object<XLambda>(tolua_S, 5, "XLambda",&arg3, "ResourceHelpers:loadWWW");
        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ResourceHelpers:loadWWW");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_loadWWW'", nullptr);
            return 0;
        }
        int ret = ResourceHelpers::loadWWW(arg0, arg1, arg2, arg3, arg4);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadWWW",argc, 5);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_loadWWW'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_cancelAllAsyncLoad(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_cancelAllAsyncLoad'", nullptr);
            return 0;
        }
        ResourceHelpers::cancelAllAsyncLoad();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:cancelAllAsyncLoad",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_cancelAllAsyncLoad'.",&tolua_err);
#endif
    return 0;
}

int lua_helpers_ResourceHelpers_loadResourceConfig(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadResourceConfig"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_loadResourceConfig'", nullptr);
            return 0;
        }
        bool ret = ResourceHelpers::loadResourceConfig(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadResourceConfig",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_loadResourceConfig'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_cancelLoadAsync(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        unsigned int arg0;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ResourceHelpers:cancelLoadAsync");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_cancelLoadAsync'", nullptr);
            return 0;
        }
        ResourceHelpers::cancelLoadAsync(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:cancelLoadAsync",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_cancelLoadAsync'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_fini(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_fini'", nullptr);
            return 0;
        }
        ResourceHelpers::fini();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:fini",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_fini'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_init'", nullptr);
            return 0;
        }
        ResourceHelpers::init();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:init",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_init'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_loadTextureAsync(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 2)
	{
		XAsyncLoadOption* arg0;
		unsigned int arg1;
		ok &= luaval_to_object<XAsyncLoadOption>(tolua_S, 2, "XAsyncLoadOption", &arg0, "ResourceHelpers:loadTextureAsync");
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, "ResourceHelpers:loadTextureAsync");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ResourceHelpers_loadTextureAsync'", nullptr);
			return 0;
		}
		unsigned int ret = ResourceHelpers::loadTextureAsync(arg0, arg1);
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadTextureAsync", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_loadTextureAsync'.", &tolua_err);
#endif
	return 0;
}
int lua_helpers_ResourceHelpers_listenAsyncFinish(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        XLambda* arg0;
        ok &= luaval_to_object<XLambda>(tolua_S, 2, "XLambda",&arg0, "ResourceHelpers:listenAsyncFinish");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_listenAsyncFinish'", nullptr);
            return 0;
        }
        ResourceHelpers::listenAsyncFinish(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:listenAsyncFinish",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_listenAsyncFinish'.",&tolua_err);
#endif
    return 0;
}

int lua_helpers_ResourceHelpers_loadDependency(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadDependency"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_loadDependency'", nullptr);
            return 0;
        }
        bool ret = ResourceHelpers::loadDependency(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadDependency",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_loadDependency'.",&tolua_err);
#endif
    return 0;
}

int lua_helpers_ResourceHelpers_loadResourceTab(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 1)
	{
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadResourceTab"); arg0 = arg0_tmp.c_str();
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ResourceHelpers_loadResourceTab'", nullptr);
			return 0;
		}
		bool ret = ResourceHelpers::LoadResourceTab(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadResourceTab", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_loadResourceTab'.", &tolua_err);
#endif
	return 0;
}

int lua_helpers_ResourceHelpers_loadAnimationTab(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 1)
	{
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadAnimationTab"); arg0 = arg0_tmp.c_str();
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ResourceHelpers_loadAnimationTab'", nullptr);
			return 0;
		}
		bool ret = ResourceHelpers::loadAnimationTab(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadAnimationTab", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_loadAnimationTab'.", &tolua_err);
#endif
	return 0;
}

int lua_helpers_ResourceHelpers_loadMD5Tab(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 1)
	{
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadMD5Tab"); arg0 = arg0_tmp.c_str();
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'loadMD5Tab'", nullptr);
			return 0;
		}
		bool ret = ResourceHelpers::loadMD5Tab(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadMD5Tab", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_loadMD5Tab'.", &tolua_err);
#endif
	return 0;
}

int lua_helpers_ResourceHelpers_loadConfigPack(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 1)
	{
		const char* arg0;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadConfigPack"); arg0 = arg0_tmp.c_str();
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ResourceHelpers_loadConfigPack'", nullptr);
			return 0;
		}
		bool ret = ResourceHelpers::loadConfigPack(arg0);
		tolua_pushboolean(tolua_S, (bool)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadConfigPack", argc, 1);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_loadConfigPack'.", &tolua_err);
#endif
	return 0;
}

int lua_helpers_ResourceHelpers_purgeCSBCache(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_purgeCSBCache'", nullptr);
            return 0;
        }
        ResourceHelpers::purgeCSBCache();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:purgeCSBCache",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_purgeCSBCache'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_purgeCache(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_purgeCache'", nullptr);
            return 0;
        }
        ResourceHelpers::purgeCache();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:purgeCache",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_purgeCache'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ResourceHelpers_cancelAllAsyncLoadScript(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ResourceHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ResourceHelpers_cancelAllAsyncLoadScript'", nullptr);
            return 0;
        }
        ResourceHelpers::cancelAllAsyncLoadScript();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:cancelAllAsyncLoadScript",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ResourceHelpers_cancelAllAsyncLoadScript'.",&tolua_err);
#endif
    return 0;
}

int lua_helpers_ResourceHelpers_getAsyncLoadOption(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 4)
	{
		const char* arg0;
		const char* arg1;
		uint16_t arg2;
		XLambda* arg3;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:getAsyncLoadOption"); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ResourceHelpers:getAsyncLoadOption"); arg1 = arg1_tmp.c_str();
		ok &= luaval_to_uint16(tolua_S, 4, &arg2, "ResourceHelpers:getAsyncLoadOption");
		ok &= luaval_to_object<XLambda>(tolua_S, 5, "XLambda", &arg3, "ResourceHelpers:getAsyncLoadOption");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ResourceHelpers_getAsyncLoadOption'", nullptr);
			return 0;
		}
		XAsyncLoadOption* ret = ResourceHelpers::getAsyncLoadOption(arg0, arg1, arg2, arg3);
		object_to_luaval<XAsyncLoadOption>(tolua_S, "XAsyncLoadOption", (XAsyncLoadOption*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:getAsyncLoadOption", argc, 4);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_getAsyncLoadOption'.", &tolua_err);
#endif
	return 0;
}

int lua_helpers_ResourceHelpers_loadCSB(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ResourceHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 4)
	{
		const char* arg0;
		bool arg1;
		bool arg2;
		XLambda* arg3;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ResourceHelpers:loadCSB"); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_boolean(tolua_S, 3, &arg1, "ResourceHelpers:loadCSB");
		ok &= luaval_to_boolean(tolua_S, 4, &arg2, "ResourceHelpers:loadCSB");
		ok &= luaval_to_object<XLambda>(tolua_S, 5, "XLambda", &arg3, "ResourceHelpers:loadCSB");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ResourceHelpers_loadCSB'", nullptr);
			return 0;
		}
		XCSLoadRet* ret = ResourceHelpers::loadCSB(arg0, arg1, arg2, arg3);
		object_to_luaval<XCSLoadRet>(tolua_S, "XCSLoadRet", (XCSLoadRet*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ResourceHelpers:loadCSB", argc, 4);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ResourceHelpers_loadCSB'.", &tolua_err);
#endif
	return 0;
}

static int lua_helpers_ResourceHelpers_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ResourceHelpers)");
    return 0;
}

int lua_register_helpers_ResourceHelpers(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ResourceHelpers");
    tolua_cclass(tolua_S,"ResourceHelpers","ResourceHelpers","",nullptr);

    tolua_beginmodule(tolua_S,"ResourceHelpers");
        tolua_function(tolua_S,"decompressAsync", lua_helpers_ResourceHelpers_decompressAsync);
        tolua_function(tolua_S,"cancelDecompressAsync", lua_helpers_ResourceHelpers_cancelDecompressAsync);
        tolua_function(tolua_S,"loadWWW", lua_helpers_ResourceHelpers_loadWWW);
        tolua_function(tolua_S,"cancelAllAsyncLoad", lua_helpers_ResourceHelpers_cancelAllAsyncLoad);
        tolua_function(tolua_S,"loadResourceConfig", lua_helpers_ResourceHelpers_loadResourceConfig);
        tolua_function(tolua_S,"cancelLoadAsync", lua_helpers_ResourceHelpers_cancelLoadAsync);
        tolua_function(tolua_S,"fini", lua_helpers_ResourceHelpers_fini);
        tolua_function(tolua_S,"init", lua_helpers_ResourceHelpers_init);
		tolua_function(tolua_S, "loadTextureAsync", lua_helpers_ResourceHelpers_loadTextureAsync);
        tolua_function(tolua_S,"listenAsyncFinish", lua_helpers_ResourceHelpers_listenAsyncFinish);
        tolua_function(tolua_S,"loadDependency", lua_helpers_ResourceHelpers_loadDependency);
		tolua_function(tolua_S, "loadResourceTab", lua_helpers_ResourceHelpers_loadResourceTab);
		tolua_function(tolua_S, "loadAnimationTab", lua_helpers_ResourceHelpers_loadAnimationTab);
		tolua_function(tolua_S, "loadMD5Tab", lua_helpers_ResourceHelpers_loadMD5Tab);
		tolua_function(tolua_S,"loadConfigPack", lua_helpers_ResourceHelpers_loadConfigPack);
        tolua_function(tolua_S,"purgeCSBCache", lua_helpers_ResourceHelpers_purgeCSBCache);
        tolua_function(tolua_S,"purgeCache", lua_helpers_ResourceHelpers_purgeCache);
        tolua_function(tolua_S,"cancelAllAsyncLoadScript", lua_helpers_ResourceHelpers_cancelAllAsyncLoadScript);
		tolua_function(tolua_S, "getAsyncLoadOption", lua_helpers_ResourceHelpers_getAsyncLoadOption);
		tolua_function(tolua_S, "loadCSB", lua_helpers_ResourceHelpers_loadCSB);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ResourceHelpers).name();
    g_luaType[typeName] = "ResourceHelpers";
    g_typeCast["ResourceHelpers"] = "ResourceHelpers";
    return 1;
}

int lua_helpers_ScriptCallbackHelpers_setFrameEventCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocostudio::timeline::ActionTimeline* arg0;
        XLambda* arg1;
        ok &= luaval_to_object<cocostudio::timeline::ActionTimeline>(tolua_S, 2, "ccs.ActionTimeline",&arg0, "ScriptCallbackHelpers:setFrameEventCallFunc");
        ok &= luaval_to_object<XLambda>(tolua_S, 3, "XLambda",&arg1, "ScriptCallbackHelpers:setFrameEventCallFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_setFrameEventCallFunc'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::setFrameEventCallFunc(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:setFrameEventCallFunc",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_setFrameEventCallFunc'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_listenAppEvents(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        XLambda* arg0;
        ok &= luaval_to_object<XLambda>(tolua_S, 2, "XLambda",&arg0, "ScriptCallbackHelpers:listenAppEvents");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_listenAppEvents'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::listenAppEvents(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:listenAppEvents",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_listenAppEvents'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_listenFrameEvent(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            XAnimateSprite* arg0;
            ok &= luaval_to_object<XAnimateSprite>(tolua_S, 2, "XAnimateSprite",&arg0, "ScriptCallbackHelpers:listenFrameEvent");
            if (!ok) { break; }
            XLambda* arg1;
            ok &= luaval_to_object<XLambda>(tolua_S, 3, "XLambda",&arg1, "ScriptCallbackHelpers:listenFrameEvent");
            if (!ok) { break; }
            ScriptCallbackHelpers::listenFrameEvent(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ScriptCallbackHelpers:listenFrameEvent",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_listenFrameEvent'.",&tolua_err);
#endif
    return 0;
}

int lua_helpers_ScriptCallbackHelpers_listenFrame(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ScriptCallbackHelpers", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 2)
	{
		XAnimateSprite* arg0;
		XLambda* arg1;
		ok &= luaval_to_object<XAnimateSprite>(tolua_S, 2, "XAnimateSprite", &arg0, "ScriptCallbackHelpers:listenFrame");
		ok &= luaval_to_object<XLambda>(tolua_S, 3, "XLambda", &arg1, "ScriptCallbackHelpers:listenFrame");
		if (ok)
		{
			ScriptCallbackHelpers::listenFrame(arg0, arg1);
			lua_settop(tolua_S, 1);
		}
		else
		{
			luaL_error(tolua_S, "has wrong argument(s) in \"ScriptCallbackHelpers:listenFrame\"");
		}
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ScriptCallbackHelpers:listenFrame", argc, 2);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ScriptCallbackHelpers_listenFrame'.", &tolua_err);
#endif
	return 0;
}


int lua_helpers_ScriptCallbackHelpers_onAppEvent(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        unsigned int arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ScriptCallbackHelpers:onAppEvent");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ScriptCallbackHelpers:onAppEvent");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "ScriptCallbackHelpers:onAppEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_onAppEvent'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::onAppEvent(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:onAppEvent",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_onAppEvent'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_eventCustomUserDataAsTable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::EventCustom* arg0;
        ok &= luaval_to_object<cocos2d::EventCustom>(tolua_S, 2, "cc.EventCustom",&arg0, "ScriptCallbackHelpers:eventCustomUserDataAsTable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_eventCustomUserDataAsTable'", nullptr);
            return 0;
        }
        cocos2d::ValueMap& ret = ScriptCallbackHelpers::eventCustomUserDataAsTable(arg0);
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:eventCustomUserDataAsTable",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_eventCustomUserDataAsTable'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_fini(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_fini'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::fini();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:fini",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_fini'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_dispatchCustomEvent(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        cocos2d::ValueMap arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ScriptCallbackHelpers:dispatchCustomEvent");
        ok &= luaval_to_ccvaluemap(tolua_S, 3, &arg1, "ScriptCallbackHelpers:dispatchCustomEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_dispatchCustomEvent'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::dispatchCustomEvent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:dispatchCustomEvent",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_dispatchCustomEvent'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_listenActionNodeEvent(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        XActionNode* arg0;
        XLambda* arg1;
        ok &= luaval_to_object<XActionNode>(tolua_S, 2, "XActionNode",&arg0, "ScriptCallbackHelpers:listenActionNodeEvent");
        ok &= luaval_to_object<XLambda>(tolua_S, 3, "XLambda",&arg1, "ScriptCallbackHelpers:listenActionNodeEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_listenActionNodeEvent'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::listenActionNodeEvent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:listenActionNodeEvent",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_listenActionNodeEvent'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ScriptCallbackHelpers_setLastFrameCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ScriptCallbackHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocostudio::timeline::ActionTimeline* arg0;
        XLambda* arg1;
        ok &= luaval_to_object<cocostudio::timeline::ActionTimeline>(tolua_S, 2, "ccs.ActionTimeline",&arg0, "ScriptCallbackHelpers:setLastFrameCallFunc");
        ok &= luaval_to_object<XLambda>(tolua_S, 3, "XLambda",&arg1, "ScriptCallbackHelpers:setLastFrameCallFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ScriptCallbackHelpers_setLastFrameCallFunc'", nullptr);
            return 0;
        }
        ScriptCallbackHelpers::setLastFrameCallFunc(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ScriptCallbackHelpers:setLastFrameCallFunc",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ScriptCallbackHelpers_setLastFrameCallFunc'.",&tolua_err);
#endif
    return 0;
}
static int lua_helpers_ScriptCallbackHelpers_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ScriptCallbackHelpers)");
    return 0;
}

int lua_register_helpers_ScriptCallbackHelpers(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ScriptCallbackHelpers");
    tolua_cclass(tolua_S,"ScriptCallbackHelpers","ScriptCallbackHelpers","",nullptr);

    tolua_beginmodule(tolua_S,"ScriptCallbackHelpers");
        tolua_function(tolua_S,"setFrameEventCallFunc", lua_helpers_ScriptCallbackHelpers_setFrameEventCallFunc);
        tolua_function(tolua_S,"listenAppEvents", lua_helpers_ScriptCallbackHelpers_listenAppEvents);
		tolua_function(tolua_S, "listenFrameEvent", lua_helpers_ScriptCallbackHelpers_listenFrameEvent);
		tolua_function(tolua_S, "listenFrame", lua_helpers_ScriptCallbackHelpers_listenFrame);
        tolua_function(tolua_S,"onAppEvent", lua_helpers_ScriptCallbackHelpers_onAppEvent);
        tolua_function(tolua_S,"eventCustomUserDataAsTable", lua_helpers_ScriptCallbackHelpers_eventCustomUserDataAsTable);
        tolua_function(tolua_S,"fini", lua_helpers_ScriptCallbackHelpers_fini);
        tolua_function(tolua_S,"dispatchCustomEvent", lua_helpers_ScriptCallbackHelpers_dispatchCustomEvent);
        tolua_function(tolua_S,"listenActionNodeEvent", lua_helpers_ScriptCallbackHelpers_listenActionNodeEvent);
        tolua_function(tolua_S,"setLastFrameCallFunc", lua_helpers_ScriptCallbackHelpers_setLastFrameCallFunc);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ScriptCallbackHelpers).name();
    g_luaType[typeName] = "ScriptCallbackHelpers";
    g_typeCast["ScriptCallbackHelpers"] = "ScriptCallbackHelpers";
    return 1;
}

int lua_helpers_XLambdaLua_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"XLambdaLua",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::LUA_FUNCTION arg0;
        arg0= (toluafix_ref_function(tolua_S, 2, 0));
		ok &= (arg0 != 0);// LUA_FUNCTION_EXPORTED;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_XLambdaLua_create'", nullptr);
            return 0;
        }
        XLambdaLua* ret = XLambdaLua::create(arg0);
        object_to_luaval<XLambdaLua>(tolua_S, "XLambdaLua",(XLambdaLua*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "XLambdaLua:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_XLambdaLua_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_helpers_XLambdaLua_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (XLambdaLua)");
    return 0;
}

int lua_register_helpers_XLambdaLua(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"XLambdaLua");
    tolua_cclass(tolua_S,"XLambdaLua","XLambdaLua","XLambda",nullptr);

    tolua_beginmodule(tolua_S,"XLambdaLua");
        tolua_function(tolua_S,"create", lua_helpers_XLambdaLua_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(XLambdaLua).name();
    g_luaType[typeName] = "XLambdaLua";
    g_typeCast["XLambdaLua"] = "XLambdaLua";
    return 1;
}

int lua_helpers_SystemHelpers_messageBox(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        const char* arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SystemHelpers:messageBox"); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "SystemHelpers:messageBox"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_messageBox'", nullptr);
            return 0;
        }
        SystemHelpers::messageBox(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:messageBox",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_messageBox'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_bclear(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        unsigned int arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:bclear");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "SystemHelpers:bclear");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_bclear'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::bclear(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:bclear",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_bclear'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_rshift(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SystemHelpers:rshift");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "SystemHelpers:rshift");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_rshift'", nullptr);
            return 0;
        }
        int ret = SystemHelpers::rshift(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:rshift",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_rshift'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_log(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SystemHelpers:log"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_log'", nullptr);
            return 0;
        }
        SystemHelpers::log(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        const char* arg0;
        unsigned short arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SystemHelpers:log"); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SystemHelpers:log");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_log'", nullptr);
            return 0;
        }
        SystemHelpers::log(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:log",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_log'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_gettime(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_gettime'", nullptr);
            return 0;
        }
        double ret = SystemHelpers::gettime();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:gettime",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_gettime'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_lshift(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SystemHelpers:lshift");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "SystemHelpers:lshift");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_lshift'", nullptr);
            return 0;
        }
        int ret = SystemHelpers::lshift(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:lshift",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_lshift'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_binvert(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        unsigned int arg0;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:binvert");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_binvert'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::binvert(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:binvert",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_binvert'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_band(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        unsigned int arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:band");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "SystemHelpers:band");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_band'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::band(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:band",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_band'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_high8Word(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        unsigned int arg0;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:high8Word");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_high8Word'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::high8Word(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:high8Word",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_high8Word'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_low8Word(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        unsigned int arg0;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:low8Word");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_low8Word'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::low8Word(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:low8Word",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_low8Word'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_fromClipboard(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_fromClipboard'", nullptr);
            return 0;
        }
        std::string ret = SystemHelpers::fromClipboard();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:fromClipboard",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_fromClipboard'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_addSearchPath(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SystemHelpers:addSearchPath"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_addSearchPath'", nullptr);
            return 0;
        }
        SystemHelpers::addSearchPath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:addSearchPath",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_addSearchPath'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_highByte(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        unsigned int arg0;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:highByte");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_highByte'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::highByte(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:highByte",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_highByte'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_pathDialog(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        const char* arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SystemHelpers:pathDialog"); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "SystemHelpers:pathDialog"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_pathDialog'", nullptr);
            return 0;
        }
        std::string ret = SystemHelpers::pathDialog(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:pathDialog",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_pathDialog'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_bor(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        unsigned int arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:bor");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "SystemHelpers:bor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_bor'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::bor(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:bor",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_bor'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_SystemHelpers_lowByte(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SystemHelpers",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        unsigned int arg0;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "SystemHelpers:lowByte");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_SystemHelpers_lowByte'", nullptr);
            return 0;
        }
        unsigned int ret = SystemHelpers::lowByte(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SystemHelpers:lowByte",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_SystemHelpers_lowByte'.",&tolua_err);
#endif
    return 0;
}

static int lua_helpers_SystemHelpers_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SystemHelpers)");
    return 0;
}

int lua_register_helpers_SystemHelpers(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"SystemHelpers");
    tolua_cclass(tolua_S,"SystemHelpers","SystemHelpers","",nullptr);

    tolua_beginmodule(tolua_S,"SystemHelpers");
        tolua_function(tolua_S,"messageBox", lua_helpers_SystemHelpers_messageBox);
        tolua_function(tolua_S,"bclear", lua_helpers_SystemHelpers_bclear);
        tolua_function(tolua_S,"rshift", lua_helpers_SystemHelpers_rshift);
        tolua_function(tolua_S,"log", lua_helpers_SystemHelpers_log);
        tolua_function(tolua_S,"gettime", lua_helpers_SystemHelpers_gettime);
        tolua_function(tolua_S,"lshift", lua_helpers_SystemHelpers_lshift);
        tolua_function(tolua_S,"binvert", lua_helpers_SystemHelpers_binvert);
        tolua_function(tolua_S,"band", lua_helpers_SystemHelpers_band);
        tolua_function(tolua_S,"high8Word", lua_helpers_SystemHelpers_high8Word);
        tolua_function(tolua_S,"low8Word", lua_helpers_SystemHelpers_low8Word);
        tolua_function(tolua_S,"fromClipboard", lua_helpers_SystemHelpers_fromClipboard);
        tolua_function(tolua_S,"addSearchPath", lua_helpers_SystemHelpers_addSearchPath);
        tolua_function(tolua_S,"highByte", lua_helpers_SystemHelpers_highByte);
        tolua_function(tolua_S,"pathDialog", lua_helpers_SystemHelpers_pathDialog);
        tolua_function(tolua_S,"bor", lua_helpers_SystemHelpers_bor);
        tolua_function(tolua_S,"lowByte", lua_helpers_SystemHelpers_lowByte);

    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SystemHelpers).name();
    g_luaType[typeName] = "SystemHelpers";
    g_typeCast["SystemHelpers"] = "SystemHelpers";
    return 1;
}

int lua_helpers_NetPacket_create(lua_State* L)
{
	// 手写一个简单的
	object_to_luaval<NetPacket>(L, "NetPacket", (NetPacket*)NetPacket::create());
	return 1;	
}

int lua_helpers_NetPacket_writeString(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetPacket:writeString"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeString'", nullptr);
            return 0;
        }
        cobj->writeString(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeString'.",&tolua_err);
#endif

    return 0;
}

int lua_helpers_NetPacket_writeStringInGivenLength(lua_State* tolua_S)
{
	int argc = 0;
	NetPacket* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "NetPacket", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (NetPacket*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_helpers_NetPacket_writeStringInGivenLength'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 2)
	{
		const char* arg0;
		unsigned int arg1;
		std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetPacket:writeStringInGivenLength"); arg0 = arg0_tmp.c_str();
		ok &= luaval_to_uint32(tolua_S, 3, &arg1, "NetPacket:writeStringInGivenLength");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_NetPacket_writeStringInGivenLength'", nullptr);
			return 0;
		}
		cobj->writeStringInGivenLength(arg0, arg1);
		lua_settop(tolua_S, 1);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeStringInGivenLength", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_NetPacket_writeStringInGivenLength'.", &tolua_err);
#endif

	return 0;
}

int lua_helpers_NetPacket_writePack(lua_State* tolua_S)
{
	int argc = 0;
	NetPacket* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "NetPacket", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (NetPacket*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_helpers_NetPacket_writePack'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		NetPacket * pPack = 0;
		ok &= luaval_to_object<NetPacket>(tolua_S, 2, "NetPacket", &pPack, "lua_helpers_NetPacket_writePack");
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_NetPacket_writePack'", nullptr);
			return 0;
		}
		cobj->writePack(pPack);

		return 0;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writePack", argc, 2);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_NetPacket_writePack'.", &tolua_err);
#endif

	return 0;
}


int lua_helpers_NetPacket_writeShort(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeShort'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "NetPacket:writeShort");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeShort'", nullptr);
            return 0;
        }
        cobj->writeShort(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeShort",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeShort'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeInt64(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeInt64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        long long arg0;

        ok &= luaval_to_long_long(tolua_S, 2,&arg0, "NetPacket:writeInt64");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeInt64'", nullptr);
            return 0;
        }
        cobj->writeInt64(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeInt64",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeInt64'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readByte(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readByte'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readByte'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->readByte();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readByte",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readByte'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readUInt(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readUInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readUInt'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->readUInt();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readUInt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readUInt'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeWord(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeWord'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned short arg0;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "NetPacket:writeWord");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeWord'", nullptr);
            return 0;
        }
        cobj->writeWord(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeWord",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeWord'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readWord(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readWord'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readWord'", nullptr);
            return 0;
        }
        unsigned short ret = cobj->readWord();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readWord",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readWord'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readFloat(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readFloat'", nullptr);
            return 0;
        }
        double ret = cobj->readFloat();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readFloat",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readFloat'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readInt64(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readInt64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readInt64'", nullptr);
            return 0;
        }
        long long ret = cobj->readInt64();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readInt64",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readInt64'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeDouble(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeDouble'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "NetPacket:writeDouble");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeDouble'", nullptr);
            return 0;
        }
        cobj->writeDouble(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeDouble",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeDouble'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeFloat(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "NetPacket:writeFloat");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeFloat'", nullptr);
            return 0;
        }
        cobj->writeFloat(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeFloat",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeFloat'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeUInt(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeUInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "NetPacket:writeUInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeUInt'", nullptr);
            return 0;
        }
        cobj->writeUInt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeUInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeUInt'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readUint64(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readUint64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readUint64'", nullptr);
            return 0;
        }
        unsigned long long ret = cobj->readUint64();
        #pragma warning NO CONVERSION FROM NATIVE FOR unsigned long long;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readUint64",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readUint64'.",&tolua_err);
#endif

    return 0;
}

int lua_helpers_NetPacket_getSize(lua_State* tolua_S)
{
	int argc = 0;
	NetPacket* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "NetPacket", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (NetPacket*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_helpers_NetPacket_getSize'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_NetPacket_getSize'", nullptr);
			return 0;
		}
		unsigned int ret = cobj->getSize();
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:getSize", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_NetPacket_getSize'.", &tolua_err);
#endif

	return 0;
}

int lua_helpers_NetPacket_getPacketSize(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_getPacketSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_getPacketSize'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getPacketSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:getPacketSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_getPacketSize'.",&tolua_err);
#endif

    return 0;
}



int lua_helpers_NetPacket_readShort(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readShort'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readShort'", nullptr);
            return 0;
        }
        int32_t ret = cobj->readShort();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readShort",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readShort'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeChar(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeChar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "NetPacket:writeChar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeChar'", nullptr);
            return 0;
        }
        cobj->writeChar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeChar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeChar'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readInt(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readInt'", nullptr);
            return 0;
        }
        int ret = cobj->readInt();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readInt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readInt'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_getType(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_getType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_getType'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->getType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:getType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_getType'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeByte(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeByte'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "NetPacket:writeByte");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeByte'", nullptr);
            return 0;
        }
        cobj->writeByte(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeByte",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeByte'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readChar(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readChar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readChar'", nullptr);
            return 0;
        }
        int32_t ret = cobj->readChar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readChar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readChar'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readDouble(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readDouble'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readDouble'", nullptr);
            return 0;
        }
        double ret = cobj->readDouble();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readDouble",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readDouble'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readString(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_readString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_readString'", nullptr);
            return 0;
        }
        const char* ret = cobj->readString();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_readString'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_readStringInBuff(lua_State* tolua_S)
{
	int argc = 0;
	NetPacket* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "NetPacket", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (NetPacket*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_helpers_NetPacket_readStringInBuff'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_NetPacket_readStringInBuff'", nullptr);
			return 0;
		}
		std::string res = cobj->readStringInBuff();
		tolua_pushstring(tolua_S, (const char*)res.c_str());
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readStringInBuff", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_NetPacket_readStringInBuff'.", &tolua_err);
#endif

	return 0;
}

int lua_helpers_NetPacket_readStringInSpecifyLength(lua_State* tolua_S)
{
	int argc = 0;
	NetPacket* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "NetPacket", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (NetPacket*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_helpers_NetPacket_readStringInSpecifyLength'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		unsigned int nLength = 0;
		ok &= luaval_to_uint32(tolua_S, 2, &nLength, "readStringInSpecifyLength");

		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_NetPacket_readStringInSpecifyLength'", nullptr);
			return 0;
		}
		std::string res = cobj->readStringInSpecifyLength(nLength);
		tolua_pushstring(tolua_S, (const char*)res.c_str());
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readStringInSpecifyLength", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_NetPacket_readStringInSpecifyLength'.", &tolua_err);
#endif

	return 0;
}

int lua_helpers_NetPacket_readPackForGivenLength(lua_State* tolua_S)
{
	int argc = 0;
	NetPacket* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "NetPacket", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (NetPacket*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_helpers_NetPacket_readPackForGivenLength'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 1)
	{
		unsigned int nLength = 0;
		ok &= luaval_to_uint32(tolua_S, 2, &nLength, "readPackForGivenLength");

		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_NetPacket_readPackForGivenLength'", nullptr);
			return 0;
		}
		NetPacket * pack = cobj->readPackForGivenLength(nLength);
		object_to_luaval<NetPacket>(tolua_S, "NetPacket", (NetPacket*)pack);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:readPackForGivenLength", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_NetPacket_readPackForGivenLength'.", &tolua_err);
#endif

	return 0;
}

int lua_helpers_NetPacket_writeUint64(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeUint64'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned long long arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned long long
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeUint64'", nullptr);
            return 0;
        }
        cobj->writeUint64(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeUint64",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeUint64'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_NetPacket_writeInt(lua_State* tolua_S)
{
    int argc = 0;
    NetPacket* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetPacket",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetPacket*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_NetPacket_writeInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "NetPacket:writeInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_NetPacket_writeInt'", nullptr);
            return 0;
        }
        cobj->writeInt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetPacket:writeInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_NetPacket_writeInt'.",&tolua_err);
#endif

    return 0;
}
static int lua_helpers_NetPacket_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetPacket)");
    return 0;
}

int lua_register_helpers_NetPacket(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"NetPacket");
    tolua_cclass(tolua_S,"NetPacket","NetPacket","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NetPacket");
        tolua_function(tolua_S,"writeString",lua_helpers_NetPacket_writeString);
		tolua_function(tolua_S, "writeStringInGivenLength", lua_helpers_NetPacket_writeStringInGivenLength);
		tolua_function(tolua_S, "writePack", lua_helpers_NetPacket_writePack);
        tolua_function(tolua_S,"writeShort",lua_helpers_NetPacket_writeShort);
        tolua_function(tolua_S,"writeInt64",lua_helpers_NetPacket_writeInt64);
        tolua_function(tolua_S,"readByte",lua_helpers_NetPacket_readByte);
        tolua_function(tolua_S,"readUInt",lua_helpers_NetPacket_readUInt);
        tolua_function(tolua_S,"writeWord",lua_helpers_NetPacket_writeWord);
        tolua_function(tolua_S,"readWord",lua_helpers_NetPacket_readWord);
        tolua_function(tolua_S,"readFloat",lua_helpers_NetPacket_readFloat);
        tolua_function(tolua_S,"readInt64",lua_helpers_NetPacket_readInt64);
        tolua_function(tolua_S,"writeDouble",lua_helpers_NetPacket_writeDouble);
        tolua_function(tolua_S,"writeFloat",lua_helpers_NetPacket_writeFloat);
        tolua_function(tolua_S,"writeUInt",lua_helpers_NetPacket_writeUInt);
        tolua_function(tolua_S,"readUint64",lua_helpers_NetPacket_readUint64);
		tolua_function(tolua_S, "getSize", lua_helpers_NetPacket_getSize);
        tolua_function(tolua_S,"getPacketSize",lua_helpers_NetPacket_getPacketSize);
        tolua_function(tolua_S,"readShort",lua_helpers_NetPacket_readShort);
        tolua_function(tolua_S,"writeChar",lua_helpers_NetPacket_writeChar);
        tolua_function(tolua_S,"readInt",lua_helpers_NetPacket_readInt);
        tolua_function(tolua_S,"getType",lua_helpers_NetPacket_getType);
        tolua_function(tolua_S,"writeByte",lua_helpers_NetPacket_writeByte);
        tolua_function(tolua_S,"readChar",lua_helpers_NetPacket_readChar);
        tolua_function(tolua_S,"readDouble",lua_helpers_NetPacket_readDouble);
        tolua_function(tolua_S,"readString",lua_helpers_NetPacket_readString);
		tolua_function(tolua_S, "readStringInBuff", lua_helpers_NetPacket_readStringInBuff);
		tolua_function(tolua_S, "readStringInSpecifyLength", lua_helpers_NetPacket_readStringInSpecifyLength);
		tolua_function(tolua_S, "readPackForGivenLength", lua_helpers_NetPacket_readPackForGivenLength);
        tolua_function(tolua_S,"writeUint64",lua_helpers_NetPacket_writeUint64);
        tolua_function(tolua_S,"writeInt",lua_helpers_NetPacket_writeInt);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(NetPacket).name();
    g_luaType[typeName] = "NetPacket";
    g_typeCast["NetPacket"] = "NetPacket";
    return 1;
}

int lua_helpers_ClientSocketProxy_alloc(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_alloc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_alloc'", nullptr);
            return 0;
        }
        NetPacket* ret = cobj->alloc();
        object_to_luaval<NetPacket>(tolua_S, "NetPacket",(NetPacket*)ret);
        return 1;
    }
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ClientSocketProxy:alloc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_alloc'", nullptr);
            return 0;
        }
        NetPacket* ret = cobj->alloc(arg0);
        object_to_luaval<NetPacket>(tolua_S, "NetPacket",(NetPacket*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ClientSocketProxy:alloc");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ClientSocketProxy:alloc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_alloc'", nullptr);
            return 0;
        }
        NetPacket* ret = cobj->alloc(arg0, arg1);
        object_to_luaval<NetPacket>(tolua_S, "NetPacket",(NetPacket*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:alloc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_alloc'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_GameTick(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_GameTick'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_GameTick'", nullptr);
            return 0;
        }
        cobj->GameTick();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:GameTick",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_GameTick'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_SendToSrv(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_SendToSrv'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        NetPacket* arg0;

        ok &= luaval_to_object<NetPacket>(tolua_S, 2, "NetPacket",&arg0, "ClientSocketProxy:SendToSrv");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SendToSrv'", nullptr);
            return 0;
        }
        int ret = cobj->SendToSrv(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:SendToSrv",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_SendToSrv'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_ConnectSrv(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_ConnectSrv'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_ConnectSrv'", nullptr);
            return 0;
        }
        int ret = cobj->ConnectSrv();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:ConnectSrv",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_ConnectSrv'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_SendCmdToSrv(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_SendCmdToSrv'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ClientSocketProxy:SendCmdToSrv");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ClientSocketProxy:SendCmdToSrv");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SendCmdToSrv'", nullptr);
            return 0;
        }
        int ret = cobj->SendCmdToSrv(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:SendCmdToSrv",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_SendCmdToSrv'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_OnDisconnected(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_OnDisconnected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_OnDisconnected'", nullptr);
            return 0;
        }
        cobj->OnDisconnected();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:OnDisconnected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_OnDisconnected'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_SetHost(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_SetHost'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ClientSocketProxy:SetHost"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ClientSocketProxy:SetHost");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SetHost'", nullptr);
            return 0;
        }
        cobj->SetHost(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:SetHost",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_SetHost'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_setCallback(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_setCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        XLambda* arg0;

        ok &= luaval_to_object<XLambda>(tolua_S, 2, "XLambda",&arg0, "ClientSocketProxy:setCallback");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_setCallback'", nullptr);
            return 0;
        }
        cobj->setCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:setCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_setCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_connecting(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_connecting'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_connecting'", nullptr);
            return 0;
        }
        bool ret = cobj->connecting();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:connecting",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_connecting'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_connected(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_connected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_connected'", nullptr);
            return 0;
        }
        bool ret = cobj->connected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:connected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_connected'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_Close(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_Close'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_Close'", nullptr);
            return 0;
        }
        cobj->Close();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:Close",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_Close'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_SetParams(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_SetParams'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ClientSocketProxy:SetParams");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ClientSocketProxy:SetParams");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SetParams'", nullptr);
            return 0;
        }
        cobj->SetParams(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ClientSocketProxy:SetParams");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ClientSocketProxy:SetParams");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ClientSocketProxy:SetParams");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SetParams'", nullptr);
            return 0;
        }
        cobj->SetParams(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4) 
    {
        int arg0;
        int arg1;
        int arg2;
        bool arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ClientSocketProxy:SetParams");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ClientSocketProxy:SetParams");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ClientSocketProxy:SetParams");

        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "ClientSocketProxy:SetParams");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SetParams'", nullptr);
            return 0;
        }
        cobj->SetParams(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:SetParams",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_SetParams'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_SetOSVersion(lua_State* tolua_S)
{
    int argc = 0;
    ClientSocketProxy* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ClientSocketProxy*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_helpers_ClientSocketProxy_SetOSVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ClientSocketProxy:SetOSVersion"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_SetOSVersion'", nullptr);
            return 0;
        }
        cobj->SetOSVersion(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ClientSocketProxy:SetOSVersion",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_SetOSVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_helpers_ClientSocketProxy_ToCS(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        void* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_ToCS'", nullptr);
            return 0;
        }
        ClientSocketProxy* ret = ClientSocketProxy::ToCS(arg0);
        object_to_luaval<ClientSocketProxy>(tolua_S, "ClientSocketProxy",(ClientSocketProxy*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ClientSocketProxy:ToCS",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_ToCS'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ClientSocketProxy_getSocket1(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_GetNetInstance'", nullptr);
            return 0;
        }
        ClientSocketProxy* ret = ClientSocketProxy::getSocket1();
        object_to_luaval<ClientSocketProxy>(tolua_S, "ClientSocketProxy",(ClientSocketProxy*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ClientSocketProxy:GetNetInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_GetNetInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ClientSocketProxy_getSocket2(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ClientSocketProxy", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 0)
	{
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ClientSocketProxy_GetNetInstance'", nullptr);
			return 0;
		}
		ClientSocketProxy* ret = ClientSocketProxy::getSocket2();
		object_to_luaval<ClientSocketProxy>(tolua_S, "ClientSocketProxy", (ClientSocketProxy*)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ClientSocketProxy:GetNetInstance", argc, 0);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ClientSocketProxy_GetNetInstance'.", &tolua_err);
#endif
	return 0;
}
int lua_helpers_ClientSocketProxy_initSocket1(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ClientSocketProxy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        uint16_t arg0;
        const char* arg1;
        const char* arg2;
        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ClientSocketProxy:InitSocket");
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ClientSocketProxy:InitSocket"); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "ClientSocketProxy:InitSocket"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_helpers_ClientSocketProxy_InitSocket'", nullptr);
            return 0;
        }
        int ret = ClientSocketProxy::initSocket1(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ClientSocketProxy:InitSocket",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_helpers_ClientSocketProxy_InitSocket'.",&tolua_err);
#endif
    return 0;
}
int lua_helpers_ClientSocketProxy_initSocket2(lua_State* tolua_S)
{
	int argc = 0;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S, 1, "ClientSocketProxy", 0, &tolua_err)) goto tolua_lerror;
#endif

	argc = lua_gettop(tolua_S) - 1;

	if (argc == 3)
	{
		uint16_t arg0;
		const char* arg1;
		const char* arg2;
		ok &= luaval_to_uint16(tolua_S, 2, &arg0, "ClientSocketProxy:InitSocket");
		std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "ClientSocketProxy:InitSocket"); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "ClientSocketProxy:InitSocket"); arg2 = arg2_tmp.c_str();
		if (!ok)
		{
			tolua_error(tolua_S, "invalid arguments in function 'lua_helpers_ClientSocketProxy_InitSocket'", nullptr);
			return 0;
		}
		int ret = ClientSocketProxy::initSocket2(arg0, arg1, arg2);
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
	luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ClientSocketProxy:InitSocket", argc, 3);
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_helpers_ClientSocketProxy_InitSocket'.", &tolua_err);
#endif
	return 0;
}
static int lua_helpers_ClientSocketProxy_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ClientSocketProxy)");
    return 0;
}

int lua_register_helpers_ClientSocketProxy(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ClientSocketProxy");
    tolua_cclass(tolua_S,"ClientSocketProxy","ClientSocketProxy","",nullptr);

    tolua_beginmodule(tolua_S,"ClientSocketProxy");
        tolua_function(tolua_S,"alloc",lua_helpers_ClientSocketProxy_alloc);
        tolua_function(tolua_S,"GameTick",lua_helpers_ClientSocketProxy_GameTick);
        tolua_function(tolua_S,"SendToSrv",lua_helpers_ClientSocketProxy_SendToSrv);
        tolua_function(tolua_S,"ConnectSrv",lua_helpers_ClientSocketProxy_ConnectSrv);
        tolua_function(tolua_S,"SendCmdToSrv",lua_helpers_ClientSocketProxy_SendCmdToSrv);
        tolua_function(tolua_S,"OnDisconnected",lua_helpers_ClientSocketProxy_OnDisconnected);
        tolua_function(tolua_S,"SetHost",lua_helpers_ClientSocketProxy_SetHost);
        tolua_function(tolua_S,"setCallback",lua_helpers_ClientSocketProxy_setCallback);
        tolua_function(tolua_S,"connecting",lua_helpers_ClientSocketProxy_connecting);
        tolua_function(tolua_S,"connected",lua_helpers_ClientSocketProxy_connected);
        tolua_function(tolua_S,"Close",lua_helpers_ClientSocketProxy_Close);
        tolua_function(tolua_S,"SetParams",lua_helpers_ClientSocketProxy_SetParams);
        tolua_function(tolua_S,"SetOSVersion",lua_helpers_ClientSocketProxy_SetOSVersion);
        tolua_function(tolua_S,"ToCS", lua_helpers_ClientSocketProxy_ToCS);
        tolua_function(tolua_S,"initSocket1", lua_helpers_ClientSocketProxy_initSocket1);
		tolua_function(tolua_S, "getSocket1", lua_helpers_ClientSocketProxy_getSocket1);
		tolua_function(tolua_S, "initSocket2", lua_helpers_ClientSocketProxy_initSocket2);
		tolua_function(tolua_S, "getSocket2", lua_helpers_ClientSocketProxy_getSocket2);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ClientSocketProxy).name();
    g_luaType[typeName] = "ClientSocketProxy";
    g_typeCast["ClientSocketProxy"] = "ClientSocketProxy";
    return 1;
}

int lua_md5string(lua_State * L)
{
	const char * pStr = lua_tostring(L, 1);
	if (pStr)
	{
		char pTmp[33];
		processString(pStr, pTmp);
		tolua_pushstring(L, pTmp);
		return 1;
	}
	return 1;
}
//
//int lua_gb2u8(lua_State * L)
//{
//	const char * pStr = lua_tostring(L, 1);
//	if (pStr)
//	{
//		char * pStr = gb2u8(pStr);
//		tolua_pushstring(L, pStr);
//		delete[] pStr;
//		return 1;
//	}
//	return 1;
//}

int lua_saveKey(lua_State * L)
{
	const char * pKey = lua_tostring(L, 1);
	const char * pValue = lua_tostring(L, 2);
	saveKey(pKey,pValue);
	return 1;
}

int lua_loadKey(lua_State * L)
{
	const char * pKey = lua_tostring(L, 1);
	const char * pValue = loadKey(pKey);
	tolua_pushstring(L, pValue);
	return 1;
}

int lua_getTimeFromSecond(lua_State * L)
{
	unsigned int n = 0;
	if (luaval_to_uint32(L, 1, &n, "lua_getTimeFromSecond"))
	{
		const char * pRes = getTimeFromSecond(n);
		tolua_pushstring(L, pRes);
		return 1;
	}
	return 0;
}

int lua_httpRequest(lua_State * L)
{
	CCLOG("lua_httpRequest");

	int nCount = lua_gettop(L);
	if (2 == nCount)
	{
		bool bOk = true;
		const char * pUrl = lua_tostring(L, 1);
		XLambda* arg0;
		bOk &= luaval_to_object<XLambda>(L, 2, "XLambda", &arg0, "httpRequest");
		if (bOk)
		{
			arg0->retain();
			CLuaHttp::Inst().HttpRequest(pUrl, arg0);
		}
		return 0;
	}
	else if (3 == nCount)	// 第二个就是post的资料
	{
		if (!lua_istable(L, 2))
		{
			// 第二个必须是table，且里面必须是key，value的string
			CCLOG("arg 2 is not a table???????????????????????????????????????????????????????????????????");
			return 1;
		}

		bool bOk = true;
		std::string strUrl = lua_tostring(L, 1);

		XLambda* arg0;
		bOk &= luaval_to_object<XLambda>(L, 3, "XLambda", &arg0, "httpRequest");
		if (bOk)
			arg0->retain();
		else
		{
			CCLOG("param is wrong??????!!!!!!!!!");
			return 1;
		}
		

		int num = 1;
		std::map<std::string, std::string> KVMap;

		while (true)
		{
			lua_pushnumber(L, num);
			lua_gettable(L, 2);

			if (lua_isnil(L, -1))
				break;

			std::string strKey = lua_tostring(L, -1);
			lua_pop(L, 1);

			num++;
			lua_pushnumber(L, num);
			lua_gettable(L, 2);
			if (lua_isnil(L, -1))
				break;
			std::string strValue = lua_tostring(L, -1);
			lua_pop(L, 1);
			num++;

			// 记录起来
			KVMap[strKey] = strValue;
		}

		CLuaHttp::Inst().HttpRequest(strUrl.c_str(), KVMap, arg0);
	}

	CCLOG("lua_httpRequestFinish");
	return 1;
}

int lua_SaveKM(lua_State * L)
{
	CCLOG("lua_SaveKM");

	CNewLoader::Inst().SaveKeyAndMD5();
	return 0;
}
//
int lua_handle2String(lua_State * L)
{
	CCLOG("lua_handle2String");


	int nCount = lua_gettop(L);
	if (1 == nCount)
	{
		if (lua_isnumber(L, 1))
		{
			lua_Number b = lua_tonumber(L, 1);
			static char res[128];
			int64_t t = *(int64_t*)&b;
			sprintf(res, "%I64d", t);
			lua_pushstring(L, res);
			return 1;
		}
	}
	return 0;
}

// 解压函数
int lua_UncompressForPack(lua_State * L)
{
	CCLOG("lua_UncompressForPack");

	int nCount = lua_gettop(L);
	if (1 != nCount)
	{
		CCLOGERROR("UncompressForPack need 1 pack");
		lua_pushboolean(L, false);
		return 1;
	}

	bool bOk = true;
	NetPacket * pSourcePack = 0;
	bOk &= luaval_to_object<NetPacket>(L, 1, "NetPacket", &pSourcePack, "lua_UncompressForPack");

	if (!bOk)
	{
		CCLOGERROR("UncompressForPack need pack");
		lua_pushboolean(L, false);
		return 1;
	}

	if (!pSourcePack || pSourcePack->getLength() < BASE_COMPRESS_LEN + sizeof(unsigned int))	// 上面为空的时候也是true～～
	{
		lua_pushboolean(L, false);
		return 1;
	}

	char* pSource = pSourcePack->getMemoryPtr();
	if ( 0 == pSource || 0 != memcmp(pSource, BASE_COMPRESS_SIGN, BASE_COMPRESS_LEN))
	{
		CCLOGERROR("wrong source in UncompressForPack");
		lua_pushboolean(L, false);
		return 1;
	}

	unsigned int nLenghth = *(unsigned int*)(pSource + BASE_COMPRESS_LEN);
	if (nLenghth > 500 * 1024 * 1024)
	{
		// 会不会太大？
		CCLOGERROR("target is too large!!!!!!!!!!!!");
		lua_pushboolean(L, false);
		return 1;
	}

	char * pTarget = (char *)malloc(nLenghth);
	int nRes = uncompress((Bytef*)pTarget, (uLongf *)&nLenghth, (Bytef*)(pSource + BASE_COMPRESS_LEN + sizeof(unsigned int)), pSourcePack->getLength() - BASE_COMPRESS_LEN - sizeof(unsigned int));
	NetPacket* ret = NetPacket::create();
	ret->writeBuf(pTarget, nLenghth);
	ret->setPosition(0);
	free(pTarget);
	if (Z_OK == nRes)
	{
		object_to_luaval<NetPacket>(L, "NetPacket", (NetPacket*)ret);
		return 1;
	}
	else
	{
		CCLOGERROR("uncompress file wrong %d", nRes);
		lua_pushboolean(L, false);
		return 1;
	}
}

int lua_CompressForPack(lua_State * L)
{
	CCLOG("lua_CompressForPack");

	int nCount = lua_gettop(L);
	if (1 != nCount)
	{
		CCLOGERROR("CompressForPack need pack");
		lua_pushboolean(L, false);
		return 1;
	}

	bool bOk = true;
	NetPacket * pSourcePack = 0;
	bOk &= luaval_to_object<NetPacket>(L, 1, "NetPacket", &pSourcePack, "lua_CompressForPack");

	if (!bOk)
	{
		CCLOGERROR("CompressForPack need pack");
		lua_pushboolean(L, false);
		return 1;
	}

	if (!pSourcePack || pSourcePack->getLength() < BASE_COMPRESS_LEN + sizeof(unsigned int))	// 上面为空的时候也是true～～
	{
		lua_pushboolean(L, false);
		return 1;
	}

	char* pSource = pSourcePack->getMemoryPtr();
	if (0 == pSource)
	{
		CCLOGERROR("wrong source in CompressForPack");
		lua_pushboolean(L, false);
		return 1;
	}

	unsigned int nLength = pSourcePack->getLength();
	char * pTarget = (char *)malloc(nLength);
	int nRes = compress((Bytef*)pTarget, (uLongf *)&nLength, (Bytef*)pSource, pSourcePack->getLength());
	
	NetPacket* ret = NetPacket::create();
	ret->writeBuf(BASE_COMPRESS_SIGN, BASE_COMPRESS_LEN);
	ret->writeUInt(pSourcePack->getLength());
	ret->writeBuf(pTarget, nLength);
	ret->setPosition(0);

	free(pTarget);
	if (Z_OK == nRes)
	{
		object_to_luaval<NetPacket>(L, "NetPacket", (NetPacket*)ret);
		return 1;
	}
	else
	{
		CCLOGERROR("uncompress file wrong %d", nRes);
		lua_pushboolean(L, false);
		return 1;
	}
}

int lua_LoadFile(lua_State * L)
{
	CCLOG("lua_LoadFile");

	int nCount = lua_gettop(L);
	if (1 != nCount)
	{
		CCLOGERROR("LoadFile need correct path!");
		return 0;
	}

	bool bOK = true;
	std::string strPath;
	bOK &= luaval_to_std_string(L, 1, &strPath, "LoadFile");
	FileUtils* utils = FileUtils::getInstance();

	if (!bOK)
	{
		CCLOGERROR("LoadFile need correct path!");
		return 0;
	}

	int nSize = 0;
	unsigned char * pSrc = 0;
	FileIO io;
	if (io.FileOpen((utils->getWritablePath() + strPath).c_str(), false, false))
	{
		// 已经写过，直接读取出来
		nSize = io.GetFileSize();
		pSrc = (unsigned char*)malloc(nSize);
		io.ReadFile(pSrc, 0, nSize);
	}
	else
	{
		// 原来的包，用他的读取
		pSrc = utils->getFileData(strPath.c_str(), "rb", (ssize_t*)&nSize);
	}

	if (!pSrc)
	{
		CCLOG("Failed to load file");
		return 0;
	}

	NetPacket* ret = NetPacket::create();
	ret->writeBuf(pSrc, nSize);
	ret->setPosition(0);
	object_to_luaval<NetPacket>(L, "NetPacket", (NetPacket*)ret);
	return 1;
}

int lua_SaveFile(lua_State * L)
{
	CCLOG("lua_SaveFile");

	struct SWrite
	{
		SWrite()
			:m_pBuff(0)
			, m_nBuffLength(0)
		{
		
		}

		~SWrite()
		{
			if (m_pBuff)
			{
				free(m_pBuff);
				m_pBuff = 0;
			}
		}

		void NewCopyBuff( char* buff, int nLength )
		{
			if (m_pBuff && nLength)
			{
				free(m_pBuff);
				m_pBuff = 0;
			}
			m_pBuff = (char*)malloc(nLength);
			memcpy(m_pBuff, buff, nLength);
			m_nBuffLength = nLength;
		}

		void OnWrite()
		{
			FileIO io;
			FileIO::RemoveFile(strFileName.c_str());
			if (io.FileOpen(strFileName.c_str(), true, true))
			{
				io.WriteFile(m_pBuff, m_nBuffLength);
				io.FileClose();
			}
			delete this;	// 最后删除自己
		}
		char * m_pBuff;
		int m_nBuffLength;
		std::string strFileName;
	};


	int nCount = lua_gettop(L);
	if (3 != nCount)
	{
		CCLOGERROR("SaveFile( filename, NetPack, async )");
		return 0;
	}
	bool bOK = true;
	string strFile;
	NetPacket * pSource = 0;
	bool bNeedAsync = false;
	bOK &= luaval_to_std_string(L, 1, &strFile, "SaveFile");
	bOK &= luaval_to_object<NetPacket>(L, 2, "NetPacket", &pSource, "SaveFile");
	bOK &= luaval_to_boolean(L, 3, &bNeedAsync, "SaveFile");
	if (!bOK)
	{
		CCLOGERROR("wrong param in SaveFile( filename, NetPack, async )");
		return 0;
	}

	if (0 == pSource->getLength())
	{
		CCLOGERROR("no data in SaveFile( filename, NetPack, async )");
		return 0;
	}

	if (bNeedAsync)
	{
		SWrite * pNewWrite = new SWrite;
		pNewWrite->NewCopyBuff(pSource->getMemoryPtr(), pSource->getLength());
		pNewWrite->strFileName = strFile.c_str();

		std::thread th(&SWrite::OnWrite, pNewWrite);		
		th.detach();
		return 0;
	}
	else
	{
		FileIO io;
		FileIO::RemoveFile(strFile.c_str());
		if (io.FileOpen(strFile.c_str(), true, true))
		{
			io.WriteFile(pSource->getMemoryPtr(), pSource->getLength());
			io.FileClose();
			lua_pushboolean(L, true);
			return 1;
		}
		else
		{
			lua_pushboolean(L, false);
			return 0;
		}
	}
}

int lua_LoadTabFile(lua_State * L)
{
	CCLOG("lua_LoadTabFile");

	int nCount = lua_gettop(L);
	if (1 != nCount)
	{
		CCLOGERROR("LoadTabFile need correct path!");
		return 0;
	}

	bool bOK = true;
	std::string strPath;
	bOK &= luaval_to_std_string(L, 1, &strPath, "LoadTabFile");
	FileUtils* utils = FileUtils::getInstance();

	if (!bOK)
	{
		CCLOGERROR("LoadFile need correct path!");
		return 0;
	}

	int nSize = 0;
	unsigned char * pSrc = 0;
	FileIO io;
	if (io.FileOpen((utils->getWritablePath() + strPath).c_str(), false, false))
	{
		// 已经写过，直接读取出来
		nSize = io.GetFileSize();
		pSrc = (unsigned char*)malloc(nSize);
		io.ReadFile(pSrc, 0, nSize);
	}
	else
	{
		// 原来的包，用他的读取
		pSrc = utils->getFileData(strPath.c_str(), "rb", (ssize_t*)&nSize);
	}

	if (!pSrc)
	{
		CCLOG("Failed to load tab file");
		return 0;
	}

	CTableFile tfile;
	if (!tfile.LoadTableBuff((char*)pSrc, nSize))
	{
		free(pSrc);
		return 0;
	}

	// 开始生成table传入lua 
	lua_newtable(L);

	unsigned int height = tfile.GetHeight();
	unsigned int width = tfile.GetWidth();
	for (int j = 0; j < height; j++)
	{
		lua_newtable(L);
		for (int i = 0; i < width; i++)
		{
			lua_pushfstring(L, tfile.GetString(j, i).c_str());
			lua_rawseti(L, -2, i + 1);
		}
		lua_rawseti(L, -2, j + 1);
	}
	return 1;
}

int lua_OnLoadFile(lua_State * L)
{
	CCLOG("lua_OnLoadFile %d", __LINE__);

	int nCount = lua_gettop(L);
	if (2 != nCount)
	{
		CCLOGERROR("OnLoadFile need path, need netpack");
		return 0;
	}

	bool bOK = true;
	std::string strPath;
	NetPacket * pSource = 0;
	bOK &= luaval_to_std_string(L, 1, &strPath, "OnLoadFile");
	bOK &= luaval_to_object<NetPacket>(L, 2, "NetPacket", &pSource, "OnLoadFile");

	if (!bOK || pSource->getMemoryPtr() == 0 )
	{
		CCLOGERROR("OnLoadFile need path, need netpack");
		return 0;
	}

	CCLOG("lua_OnLoadFile %d", __LINE__);
	
	CNewLoader::Inst().OnHttpLoad(strPath, pSource->getMemoryPtr(), pSource->getLength());
	return 0;
}

int lua_DownFile(lua_State * L)
{
	int nCount = lua_gettop(L);
	std::string strUrl;
	XLambda * successCB = 0;
	XLambda * progressCB = 0;
	XLambda * errorCB = 0;
	bool bOk = true;
	if (4 == nCount)
	{
		bOk &= luaval_to_std_string(L, 1, &strUrl, "DownFile");
		bOk &= luaval_to_object<XLambda>(L, 2, "XLambda", &successCB, "DownFile");
		bOk &= luaval_to_object<XLambda>(L, 3, "XLambda", &progressCB, "DownFile");
		bOk &= luaval_to_object<XLambda>(L, 4, "XLambda", &errorCB, "DownFile");
	}
	else if (3 == nCount)
	{
		bOk &= luaval_to_std_string(L, 1, &strUrl, "DownFile");
		bOk &= luaval_to_object<XLambda>(L, 2, "XLambda", &successCB, "DownFile");
		bOk &= luaval_to_object<XLambda>(L, 3, "XLambda", &progressCB, "DownFile");
	}
	else if (2 == nCount)
	{
		bOk &= luaval_to_std_string(L, 1, &strUrl, "DownFile");
		bOk &= luaval_to_object<XLambda>(L, 2, "XLambda", &successCB, "DownFile");
	}
	if (bOk)
		CLuaHttp::Inst().DownRequest(strUrl, successCB, progressCB, errorCB);
	return 0;
}

int lua_ReloadPack(lua_State * L)
{
	CCLOG("lua_ReloadPack");
	
	// 重新读取pack文件，只允许热更的时候调用
	CNewLoader::Inst().ReloadPack();
	return 0;
}

int lua_ClearPack(lua_State * L)
{
	// 重新读取pack文件，只允许热更的时候调用
	CNewLoader::Inst().clearPack();
	return 0;
}

int lua_ClearFolder(lua_State * L)
{
	int nCount = lua_gettop(L);
	if (1 != nCount)
		return 0;
	bool bOk = true;
	if (1 == nCount)
	{
		std::string strFolder;
		bOk &= luaval_to_std_string(L, 1, &strFolder, "DownFile");
		FileIO::ClearFolder(strFolder.c_str());
	}
	return 0;
}

class CLoadInterface
{
public:
	static int RegistFailLoadFun(lua_State * L)
	{
		XLambda* arg0;
		if (!luaval_to_object<XLambda>(L, 1, "XLambda", &arg0, "RegistFailLoadFun"))
		{
			return 0;
		}

		if (s_lambda)
			s_lambda->release();
		s_lambda = arg0;
		s_lambda->retain();

		CNewLoader::Inst().RegistFailLoadCallBack(&CLoadInterface::OnFailLoad);
		return 0;
	}

protected:
	static void OnFailLoad(std::string & str)
	{
		CCLOG("OnFailLoad");

		if (s_lambda)
		{
			s_lambda->begin();
			s_lambda->pushString(str.c_str());
			s_lambda->invoke();
		}
	}
	static XLambda * s_lambda;

};
XLambda * CLoadInterface::s_lambda = 0;

TOLUA_API int register_all_helpers(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"helpers",0);
	tolua_beginmodule(tolua_S,"helpers");

	lua_register_helpers_ActionHelpers(tolua_S);
	lua_register_helpers_NetPacket(tolua_S);
	lua_register_helpers_NodeHelpers(tolua_S);
	lua_register_helpers_XAsyncLoadOption(tolua_S);
	lua_register_helpers_ResourceHelpers(tolua_S);
	lua_register_helpers_ScriptCallbackHelpers(tolua_S);
	lua_register_helpers_XLambdaLua(tolua_S);
	lua_register_helpers_ClientSocketProxy(tolua_S);
	lua_register_helpers_SystemHelpers(tolua_S);

	tolua_endmodule(tolua_S);

	//
	lua_pushcfunction(tolua_S, lua_md5string);
	lua_setglobal(tolua_S, "md5string");

	//lua_pushcfunction(tolua_S, lua_gb2u8);
	//lua_setglobal(tolua_S, "gb2u8");

	lua_pushcfunction(tolua_S, lua_saveKey);
	lua_setglobal(tolua_S, "saveKey");

	lua_pushcfunction(tolua_S, lua_loadKey);
	lua_setglobal(tolua_S, "loadKey");

	lua_pushcfunction(tolua_S, lua_httpRequest);
	lua_setglobal(tolua_S, "httpRequest");

	lua_pushcfunction(tolua_S, lua_SaveKM);
	lua_setglobal(tolua_S, "SaveKeyAndMD5");

	lua_pushcfunction(tolua_S, lua_getTimeFromSecond);
	lua_setglobal(tolua_S, "getTimeFromSecond");

	lua_pushcfunction(tolua_S, lua_handle2String);
	lua_setglobal(tolua_S, "handle2String");

	lua_pushcfunction(tolua_S, lua_UncompressForPack);
	lua_setglobal(tolua_S, "UncompressForPack");

	lua_pushcfunction(tolua_S, lua_CompressForPack);
	lua_setglobal(tolua_S, "CompressForPack");

	lua_pushcfunction(tolua_S, lua_LoadFile);
	lua_setglobal(tolua_S, "LoadFile");

	lua_pushcfunction(tolua_S, lua_SaveFile);
	lua_setglobal(tolua_S, "SaveFile");

	lua_pushcfunction(tolua_S, lua_LoadTabFile);
	lua_setglobal(tolua_S, "LoadTabFile");

	lua_pushcfunction(tolua_S, lua_ReloadPack);
	lua_setglobal(tolua_S, "ReloadPack");

	lua_pushcfunction(tolua_S, lua_ClearPack);
	lua_setglobal(tolua_S, "clearPack");

	lua_pushcfunction(tolua_S, lua_helpers_NetPacket_create);
	lua_setglobal(tolua_S, "CreateNetPacket");

	lua_pushcfunction(tolua_S, lua_OnLoadFile);
	lua_setglobal(tolua_S, "OnLoadFile");

	lua_pushcfunction(tolua_S, CLoadInterface::RegistFailLoadFun);
	lua_setglobal(tolua_S, "RegistFailLoadFun");

	lua_pushcfunction(tolua_S, lua_DownFile);
	lua_setglobal(tolua_S, "DownFile");

	lua_pushcfunction(tolua_S, lua_ClearFolder);
	lua_setglobal(tolua_S, "ClearFolder");

	// 注册一下state
#define REGISTE_ENUM( _enum )	\
	lua_pushnumber(tolua_S, (lua_Number(_enum)));	\
	lua_setglobal(tolua_S, #_enum );

	REGISTE_ENUM(eCheckMFail);
	REGISTE_ENUM(eBeforeCheck);
	REGISTE_ENUM(eCheckCanEnter);
	REGISTE_ENUM(eCheckNeedUpdateOnce);
	REGISTE_ENUM(eCheckNeedUpdateTex);


	return 1;
}

