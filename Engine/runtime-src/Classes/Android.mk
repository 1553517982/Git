LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -DRAYMOND_PACK_DEBUG

LOCAL_MODULE := engine_extension_static

LOCAL_MODULE_FILENAME := libEngineExtension

#LOCAL_SRC_FILES := $(LOCAL_PATH)/test.cpp
LOCAL_SRC_FILES := ./AppDelegate.cpp\
./ide-support/SimpleConfigParser.cpp\
./ide-support/RuntimeLuaImpl.cpp\
./ide-support/lua_debugger.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos2d_lua_static

EngineRoot = $(LOCAL_PATH)/../../cocos2d-x/
Classes = $(LOCAL_PATH)/

LOCAL_C_INCLUDES := $(Classes)/lua_export\
$(Classes)supports \
$(Classes)supports/download \
$(Classes)supports/utils \
$(Classes)supports/XBinary \
$(Classes)supports/XResource \
$(Classes)supports/XResource/asyncLoader \
$(Classes)gameCore/scene \
$(Classes)gameCore/network \
$(Classes)gameCore/common \
$(Classes)gameCore \
$(Classes)\
$(Classes)runtime\
$(Classes)protobuf-lite\
$(EngineRoot)/external/win32-specific/zlib/include \
$(EngineRoot)/cocos/scripting/lua-bindings/auto \
$(EngineRoot)/cocos/scripting/lua-bindings/manual \
$(EngineRoot)/cocos/audio/include \
$(EngineRoot)/cocos/editor-support \
$(EngineRoot)/cocos \
$(EngineRoot)/cocos/2d \
$(EngineRoot)/cocos/2d/SlotAnimation \
$(EngineRoot)/cocos/2d/Sprite \
$(EngineRoot)/cocos/2d/studio_ext \
$(EngineRoot)/external \
$(EngineRoot)/external/lua/lua \
$(EngineRoot)/external/lua/tolua \
$(EngineRoot)/external/chipmunk/include/chipmunk \
$(EngineRoot)/external/curl/include/win32 \
$(EngineRoot)/extensions \
$(EngineRoot)/tools/simulator/libsimulator/lib \
$(EngineRoot)/tools/simulator/libsimulator/lib/protobuf-lite \
$(EngineRoot)\

include $(BUILD_STATIC_LIBRARY)