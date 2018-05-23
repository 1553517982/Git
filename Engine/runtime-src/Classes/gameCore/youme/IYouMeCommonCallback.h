/*******************************************************************
 *  Copyright(c) 2015-2020 YOUME All rights reserved.
 *
 *  文件名称:IYouMeCommonCallback.h
 *  简要描述:游密音频通话引擎通用事件回调接口，需要继承此类并实现接口
 *
 *  当前版本:1.0
 *  作者:brucewang
 *  日期:2015.9.30
 *  说明:对外发布接口
 *
 *  取代版本:0.9
 *  作者:brucewang
 *  日期:2015.9.15
 *  说明:内部测试接口
 ******************************************************************/

#ifndef cocos2d_x_sdk_IYouMeVoiceEngineCallback_h
#define cocos2d_x_sdk_IYouMeVoiceEngineCallback_h

#include "YouMeConstDefine.h"


class IYouMeCommonCallback
{
    public:
    virtual void onEvent (const YouMeEvent_t &eventType, const YouMeErrorCode &iErrorCode) = 0;
};

#endif
