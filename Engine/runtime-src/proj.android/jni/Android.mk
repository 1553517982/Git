LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d-x)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d-x/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d-x/external)

subdirs := $(addprefix $(LOCAL_PATH)/../../../,$(addsuffix /Android.mk, \
			cocos2d-x/cocos/scripting/lua-bindings/proj.android \
			cocos2d-x/tools/simulator/libsimulator/proj.android \
	))

subdirs +=$(LOCAL_PATH)/../../Classes/Android.mk $(LOCAL_PATH)/hellolua/Android.mk

include $(subdirs)
