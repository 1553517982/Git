LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

Classes = $(LOCAL_PATH)/../../../Classes/

LOCAL_MODULE := youme_voice_engine
LOCAL_SRC_FILES := $(Classes)../proj.android/youmelibs/$(TARGET_ARCH_ABI)/libyoume_voice_engine.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
Classes = $(LOCAL_PATH)/../../../Classes/
LOCAL_MODULE := YIM
LOCAL_SRC_FILES := $(Classes)../proj.android/youmelibs/$(TARGET_ARCH_ABI)/libyim.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
Classes = $(LOCAL_PATH)/../../../Classes/
LOCAL_MODULE := YIMM
LOCAL_SRC_FILES := $(Classes)../proj.android/youmelibs/$(TARGET_ARCH_ABI)/libmsc.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
Classes = $(LOCAL_PATH)/../../../Classes/

LOCAL_MODULE := game_core_shared

LOCAL_MODULE_FILENAME := libGameCore
#APP_OPTIM := release
LOCAL_CFLAGS := -DSTRICT
LOCAL_CFLAGS += -D_CRT_SECURE_NO_WARNINGS
LOCAL_CFLAGS += -D_SCL_SECURE_NO_WARNINGS_DEBUG
LOCAL_CFLAGS += -DRAYMOND_PACK_DEBUG
LOCAL_CFLAGS += -DCOCOS2D_DEBUG=1
LOCAL_CFLAGS += -O2



EngineRoot = $(LOCAL_PATH)/../../../../cocos2d-x/



LOCAL_SRC_FILES := \
main.cpp\
$(Classes)cocos/2d/Animation/XActionProtocol.cpp\
$(Classes)cocos/2d/Animation/XAnimate.cpp\
$(Classes)cocos/2d/Animation/XAnimationCache.cpp\
$(Classes)cocos/2d/Animation/XAnimationConfig.cpp\
$(Classes)cocos/2d/Animation/XAnimationFrame.cpp\
$(Classes)cocos/2d/Animation/XSpriteFrame.cpp\
$(Classes)cocos/2d/SizeTo.cpp\
$(Classes)cocos/2d/SlotAnimation/XFrameModifier.cpp\
$(Classes)cocos/2d/SlotAnimation/XFrameTransform.cpp\
$(Classes)cocos/2d/SlotAnimation/XSlotAnimateSprite.cpp\
$(Classes)cocos/2d/SlotAnimation/XSlotFrames.cpp\
$(Classes)cocos/2d/SlotAnimation/XSlotHolderSprite.cpp\
$(Classes)cocos/2d/SlotAnimation/XSlotProtocol.cpp\
$(Classes)cocos/2d/SlotAnimation/XSlotSprite.cpp\
$(Classes)cocos/2d/Sprite/XAnimateSprite.cpp\
$(Classes)cocos/2d/Sprite/XAnimateSprite8D.cpp\
$(Classes)cocos/2d/Sprite/XSprite.cpp\
$(Classes)cocos/2d/XSpriteHelpers.cpp\
$(Classes)cocos/studio_ext/XActionTimelineCache.cpp\
$(Classes)cocos/studio_ext/XCSBLoaderInfo.cpp\
$(Classes)cocos/studio_ext/XCSBNode.cpp\
$(Classes)cocos/studio_ext/XCSLoader.cpp\
$(Classes)cocos/studio_ext/XCSLoaderRet.cpp\
$(Classes)gameCore/common/CommonFun.cpp\
$(Classes)gameCore/common/memory_counter.cpp\
$(Classes)gameCore/common/utils.cpp\
$(Classes)gameCore/common/wrand.cpp\
$(Classes)gameCore/entity/XActionNode.cpp\
$(Classes)gameCore/network/base_socket.cpp\
$(Classes)gameCore/network/CCNetworkLoop.cpp\
$(Classes)gameCore/network/ClientSocketNormalProxy.cpp\
$(Classes)gameCore/network/ClientSocketProxy.cpp\
$(Classes)gameCore/network/client_socket.cpp\
$(Classes)gameCore/network/net_buf.cpp\
$(Classes)gameCore/network/net_packet.cpp\
$(Classes)gameCore/network/net_packet_pool.cpp\
$(Classes)gameCore/network/SocketDelegateProtocol.cpp\
$(Classes)gameCore/scene/game_map.cpp\
$(Classes)gameCore/scene/pathfinding/astar.cpp\
$(Classes)gameCore/scene/pathfinding/BresenhamLine.cpp\
$(Classes)gameCore/scene/XGameScene.cpp\
$(Classes)gameCore/scene/XGameTile.cpp\
$(Classes)gameCore/scene/XLogicScene.cpp\
$(Classes)gameCore/scene/XSceneBackgroundLayer.cpp\
$(Classes)gameCore/scene/XSceneLayer.cpp\
$(Classes)gameCore/scene/XSceneObject.cpp\
$(Classes)gameCore/scene/XSceneObjectGroup.cpp\
$(Classes)gameCore/scene/XSceneObjectModifier.cpp\
$(Classes)gameCore/scene/XSceneParticleModifier.cpp\
$(Classes)gameCore/scene/XSceneTileLayer.cpp\
$(Classes)GUI/BreadthWidget.cpp\
$(Classes)GUI/DrawNodeEx.cpp\
$(Classes)GUI/EventRichText.cpp\
$(Classes)GUI/RichTextCreator.cpp\
$(Classes)helpers/ActionHelpers.cpp\
$(Classes)helpers/NodeHelpers.cpp\
$(Classes)helpers/ResourceHelpers.cpp\
$(Classes)helpers/SceneHelper.cpp\
$(Classes)helpers/ScriptCallbackHelpers.cpp\
$(Classes)helpers/SystemHelper.cpp\
$(Classes)helpers/XLambda.cpp\
$(Classes)lua_export/auto/lua_gamecore_ccsext_auto.cpp\
$(Classes)lua_export/auto/lua_gamecore_helpers_auto.cpp\
$(Classes)lua_export/auto/lua_gamecore_scene_auto.cpp\
$(Classes)lua_export/auto/lua_gui_common_auto.cpp\
$(Classes)lua_export/plugins/filesystem.c\
$(Classes)supports/download/XDownloader.cpp\
$(Classes)supports/download/XDownloaderUnit.cpp\
$(Classes)supports/utils/stream/base_stream.cpp\
$(Classes)supports/utils/encrypt/CRC.cpp\
$(Classes)supports/utils/encrypt/Encrypt.cpp\
$(Classes)supports/utils/encrypt/encryptBuffer.cpp\
$(Classes)supports/utils/md5/md5/md5.cpp\
$(Classes)supports/utils/md5/md5/md5_t.cpp\
$(Classes)supports/utils/md5/XMD5Utils.cpp\
$(Classes)supports/utils/XSystemUtils.cpp\
$(Classes)supports/utils/stream/memory_stream.cpp\
$(Classes)supports/utils/stream/file_stream.cpp\
$(Classes)supports/utils/unzip/XUnzipUtils.cpp\
$(Classes)supports/utils/stream/zcmprs_stream.cpp\
$(Classes)supports/utils/stream/zdecmprs_stream.cpp\
$(Classes)supports/utils/stream/zstream.cpp\
$(Classes)supports/XBinary/XFrameSet.cpp\
$(Classes)supports/XBinary/XImageSet.cpp\
$(Classes)supports/XBinary/XImageSetMgr.cpp\
$(Classes)supports/XResource/XAsyncLoaderManager.cpp\
$(Classes)supports/XResource/XResourceDataBase.cpp\
$(Classes)supports/XResource/XResourceUtils.cpp\
$(Classes)supports/XResource/XAsyncLoader.cpp\
$(Classes)supports/XResource/XAsyncLoaderCallbacks.cpp\
$(Classes)supports/XResource/XCSBAsyncLoader.cpp\
$(Classes)supports/XResource/XFrameAsyncLoader.cpp\
$(Classes)supports/XResource/XGroupAsyncLoader.cpp\
$(Classes)supports/XResource/XTextureAsyncLoader.cpp\
$(Classes)supports/XResource/XUnzipLoader.cpp\
$(Classes)supports/XResource/XWebLoader.cpp\
$(Classes)gameCore/youme/LuaYIM.cpp\
$(Classes)gameCore/youme/LuaYTalk.cpp\

LOCAL_C_INCLUDES := \
$(Classes) \
$(Classes)/lua_export\
$(Classes)supports\
$(Classes)supports/download\
$(Classes)supports/utils\
$(Classes)supports/XBinary\
$(Classes)supports/XResource\
$(Classes)gameCore/scene\
$(Classes)gameCore/network\
$(Classes)gameCore/common\
$(Classes)gameCore/youme\
$(Classes)gameCore\
$(Classes)runtime\
$(Classes)protobuf-lite\
$(EngineRoot)external/win32-specific/zlib/include\
$(EngineRoot)cocos/scripting/lua-bindings/auto\
$(EngineRoot)cocos/scripting/lua-bindings/manual\
$(EngineRoot)cocos/audio/include\
$(EngineRoot)cocos/editor-support\
$(EngineRoot)cocos/platform\
$(EngineRoot)cocos\
$(EngineRoot)external\
$(EngineRoot)external/lua/lua\
$(EngineRoot)external/lua/tolua\
$(EngineRoot)external/chipmunk/include/chipmunk\
$(EngineRoot)external/curl/include/win32\
$(EngineRoot)extensions\
$(EngineRoot)tools/simulator/libsimulator/lib\
$(EngineRoot)tools/simulator/libsimulator/lib/protobuf-lite\
$(EngineRoot)\


LOCAL_WHOLE_STATIC_LIBRARIES := engine_extension_static
LOCAL_STATIC_LIBRARIES := cocos2d_simulator_static
LOCAL_STATIC_LIBRARIES += cocos2d_lua_android_static
LOCAL_SHARED_LIBRARIES := YIM youme_voice_engine


include $(BUILD_SHARED_LIBRARY)