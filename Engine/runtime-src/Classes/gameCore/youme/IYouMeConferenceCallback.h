/*******************************************************************
 *  Copyright(c) 2015-2020 YOUME All rights reserved.
 *
 *  文件名称:IYouMeConferenceCallback.h
 *  简要描述:游密音频通话引擎会议事件回调接口，需要继承此类并实现接口
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

#ifndef cocos2d_x_sdk_IYouMeConferenceCallback_h
#define cocos2d_x_sdk_IYouMeConferenceCallback_h

#include <string>

class IYouMeConferenceCallback
{
    public:
    virtual void onCallEvent (const YouMeCallEvent_t &event, const YouMeErrorCode_t &errCode) = 0;
    //iStatus 0 关闭  1 打开。
    virtual void onCommonStatusEvent (STATUS_EVENT_TYPE_t eventType, const std::string &strUserID, int iStatus) = 0;
    //房间用户变化通知
    virtual void onMemberChangeEvent (const std::string &strUserIDs) = 0;
    
    
};

#endif
