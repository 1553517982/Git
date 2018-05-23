#include "base/ccConfig.h"

#ifndef __SceneHelper_H__
#define __SceneHelper_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif


int register_scene_helper(lua_State* tolua_S);

#endif