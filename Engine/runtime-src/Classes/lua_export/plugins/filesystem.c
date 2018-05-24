#ifdef ANDROID
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#elif defined (__APPLE__)
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#elif (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#else 
#include "direntWin.h"
#endif

#ifdef WIN32
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
}
#else
#include "lua.h"
#include "lauxlib.h"
#endif

/* forward declaration for the iterator function */
static int dir_iter(lua_State *L);

static int l_dir(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);

	/* create a userdatum to store a DIR address */
	DIR **d = (DIR **)lua_newuserdata(L, sizeof(DIR *));

	/* set its metatable */
	luaL_getmetatable(L, "__lfs_dir");
	lua_setmetatable(L, -2);

	/* try to open the given directory */
//	*d = opendir(path);
//	if (*d == NULL)  /* error opening the directory? */
//		luaL_error(L, "cannot open %s: %s", path,
//		strerror(errno));

	/* creates and returns the iterator function
	(its sole upvalue, the directory userdatum,
	is already on the stack top */
	lua_pushcclosure(L, dir_iter, 1);
	return 1;
}

static int dir_iter(lua_State *L) {
	DIR *d = *(DIR **)lua_touserdata(L, lua_upvalueindex(1));
	struct dirent *entry;
	if ((entry = readdir(d)) != NULL) {
		lua_pushstring(L, entry->d_name);
		lua_pushnumber(L, entry->d_type);
		return 2;
	}
	else return 0;  /* no more values to return */
}

static int dir_gc(lua_State *L) {
	DIR *d = *(DIR **)lua_touserdata(L, 1);
	if (d) closedir(d);
	return 0;
}

#ifdef WIN32
extern "C" int luaopen_lfs_dir(lua_State *L) {
#else	
int luaopen_lfs_dir(lua_State *L) {
#endif
	luaL_newmetatable(L, "__lfs_dir");

	/* set its __gc field */
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, dir_gc);
	lua_settable(L, -3);

	/* register the `dir' function */
	lua_pushcfunction(L, l_dir);
	lua_setglobal(L, "lfs_dir");

	return 0;
}