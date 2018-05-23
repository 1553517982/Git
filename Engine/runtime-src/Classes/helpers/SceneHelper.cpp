#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "SceneHelper.h"
#include "gameCore/scene/XGameScene.h"

void PushIntListToTable(lua_State* L, int* data, size_t size)
{
	if (size > 0)
	{
		lua_createtable(L, (int)size, 0);

		for (size_t i = 1; i <= size; ++i)
		{
			int ret = data[i - 1];
			lua_pushnumber(L, ret);
			lua_rawseti(L, -2, (int)i);
		}
	}
	else
	{
		lua_pushnil(L);
	}
}

int MapFindPath(lua_State* L)
{
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "XGameScene", 0, &tolua_err)) return 0;

	XGameScene* scene = (XGameScene*)(tolua_tousertype(L, 1, 0));
	int sx = ((int)tolua_tonumber(L, 2, 0));
	int sy = ((int)tolua_tonumber(L, 3, 0));
	int tx = ((int)tolua_tonumber(L, 4, 0));
	int ty = ((int)tolua_tonumber(L, 5, 0));

	container::Vector<int>* path = scene->findPath(sx, sy, tx, ty);
	if (!path) return 0;
	PushIntListToTable(L, *path, path->count());
	return 1;
}
/* function: MapFindPath */
#ifndef tolua_gamecore_helpers_MapFindPath00
static int tolua_gamecore_helpers_MapFindPath00(lua_State* tolua_S)
{
	return MapFindPath(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE


TOLUA_API int register_scene_helper(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	tolua_module(tolua_S, NULL, 0);
	tolua_beginmodule(tolua_S, NULL);
	tolua_module(tolua_S, "helpers", 0);
	tolua_beginmodule(tolua_S, "helpers");
	tolua_module(tolua_S, "SceneHelper", 0);
	tolua_beginmodule(tolua_S, "SceneHelper");
	tolua_function(tolua_S, "MapFindPath", tolua_gamecore_helpers_MapFindPath00);
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);
	return 1;
}
