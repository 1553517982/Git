//
//  IYouMeCInterface.hpp
//  youme_voice_engine
//
//  Created by YouMe.im on 15/12/10.
//  Copyright © 2015年 tencent. All rights reserved.
//

#ifndef IYouMeCInterface_hpp
#define IYouMeCInterface_hpp


//这个文件对内封装的C 接口，不需要给外部。C# 只能调用C接口的函数
//为了简单只提供单实例的封装
#include <YIMPlatformDefine.h>
#include <YIM.h>

extern "C"
{
#ifndef NO_C_Interface
	 //初始化和反初始化
	YOUMEDLL_API int IM_Init(const XCHAR* appKey, const XCHAR* appSecurity);
	YOUMEDLL_API void IM_Uninit();
    
	//登陆，登出
	YOUMEDLL_API int IM_Login(const XCHAR* userID, const XCHAR* password, const XCHAR* token);
	YOUMEDLL_API int IM_Logout();
 
    //消息接口
	YOUMEDLL_API int IM_SendTextMessage(const XCHAR* receiverID, YIMChatType chatType, const XCHAR* text, XUINT64* requestID);
	YOUMEDLL_API int IM_SendCustomMessage(const XCHAR* receiverID, YIMChatType chatType, const char* content, unsigned int size, XUINT64* requestID);
    
	//发送文件接口
	YOUMEDLL_API int IM_SendFile(const XCHAR* receiverID, YIMChatType chatType, const XCHAR* filePath, const XCHAR* extraParam, YIMFileType fileType, XUINT64* requestID);


	YOUMEDLL_API int IM_SendAudioMessage(const XCHAR* receiverID, YIMChatType chatType, XUINT64* requestID);
    //不会转文字，直接发送的音频
	YOUMEDLL_API int IM_SendOnlyAudioMessage(const XCHAR* receiverID, YIMChatType chatType, XUINT64* requestID);
	YOUMEDLL_API int IM_StopAudioMessage(const XCHAR* extraParam);
    YOUMEDLL_API int IM_CancleAudioMessage();
	YOUMEDLL_API int IM_DownloadFile(XUINT64 serial, const XCHAR* savePath);
	YOUMEDLL_API int IM_DownloadFileByURL(const XCHAR* downloadURL, const XCHAR* savePath);
	YOUMEDLL_API int IM_SendGift(const XCHAR* anchorID, const XCHAR* channel, int giftId, int giftCount, const char* extraParam, XUINT64* requestID);
	YOUMEDLL_API int IM_MultiSendTextMessage(const char* receivers, const XCHAR* text);
	
	//是否自动接收消息(true:自动接收(默认)	false:不自动接收消息，有新消息达到时会收到CMD_RECEIVE_MESSAGE_NITIFY消息，调用方需要调用IM_GetNewMessage获取新消息)
	//targets:房间ID JSON数组 "["xx","xx","xx"]"
	YOUMEDLL_API int IM_SetReceiveMessageSwitch(const XCHAR* targets, bool receive);
	//获取新消息（只有IM_SetReceiveMessageSwitch设置为不自动接收消息，才需要在收到CMD_RECEIVE_MESSAGE_NITIFY消息时，调用该函数）
	//targets:房间ID JSON数组 "["xx","xx","xx"]"
	YOUMEDLL_API int IM_GetNewMessage(const XCHAR* targets);
	// 是否保存房间消息（默认不保存）
	YOUMEDLL_API int IM_SetRoomHistoryMessageSwitch(const XCHAR* roomIDs, bool save);

	YOUMEDLL_API int IM_DownloadAudioFileSync(XUINT64 serial, const XCHAR* savePath);
    //聊天室接口
	YOUMEDLL_API int IM_JoinChatRoom(const XCHAR* chatRoomID);
	YOUMEDLL_API int IM_LeaveChatRoom(const XCHAR* chatRoomID);

	//获取最近联系人(最大100条)
	YOUMEDLL_API int IM_GetRecentContacts();
	//设置用户信息 格式为json {"nickname":"","server_area":"","location":"","level":"","vip_level":""} (以上五个必填，可以添加其他字段)
	YOUMEDLL_API int IM_SetUserInfo(const XCHAR* userInfo);
	//查询用户信息
	YOUMEDLL_API int IM_GetUserInfo(const XCHAR* userID);
	//查询用户在线状态
	YOUMEDLL_API int IM_QueryUserStatus(const XCHAR* userID);
    
	//提供一个get 接口，用来读取数据,如果没有数据会阻塞，调用登出的话，函数会返回
    YOUMEDLL_API const XCHAR* IM_GetMessage();
	YOUMEDLL_API const XCHAR* IM_GetMessage2();
	YOUMEDLL_API void IM_PopMessage(const XCHAR*pszBuffer);
    
    YOUMEDLL_API int IM_GetSDKVer();
	YOUMEDLL_API void IM_SetServerZone(ServerZone zone);
	YOUMEDLL_API void IM_SetAudioCacheDir(const XCHAR* audioCacheDir);


	//设置模式0 正式环境 1开发环境 2 测试环境 3 商务环境。 默认正式环境。所以客户不需要调用这个接口
	YOUMEDLL_API void IM_SetMode(int mode);
    YOUMEDLL_API void IM_SetLogLevel(int iLogLevel);

    
    
	YOUMEDLL_API XCHAR* IM_GetFilterText(const XCHAR* text, int* level);
	YOUMEDLL_API void  IM_DestroyFilterText(XCHAR* text);

	YOUMEDLL_API int IM_StartAudioSpeech(XUINT64* requestID, bool translate);
	YOUMEDLL_API int IM_StopAudioSpeech();
	//查询历史消息
	YOUMEDLL_API int IM_QueryHistoryMessage(const XCHAR* targetID, int chatType, XUINT64 startMessageID , int count, int direction );
	//删除历史消息
	YOUMEDLL_API int IM_DeleteHistoryMessage(YIMChatType chatType, XUINT64 time = 0);
	//删除指定messageID对应消息
	YOUMEDLL_API int IM_DeleteHistoryMessageByID(XUINT64 messageID);
	//查询房间消息
	YOUMEDLL_API int IM_QueryRoomHistoryMessageFromServer(const XCHAR* chatRoomID);
	//wav 转换
	YOUMEDLL_API  int IM_ConvertAMRToWav(const XCHAR* amrFilePath, const XCHAR* wavFielPath);

	//程序切到后台运行
	YOUMEDLL_API void IM_OnPause();
	//程序切到前台运行
	YOUMEDLL_API void IM_OnResume();

	//获取语音缓存目录
	YOUMEDLL_API XCHAR* IM_GetAudioCachePath();
	YOUMEDLL_API void IM_DestroyAudioCachePath(XCHAR* path);
	//清理语音缓存目录(注意清空语音缓存目录后历史记录中会无法读取到音频文件，调用清理历史记录接口也会自动删除对应的音频缓存文件)
	YOUMEDLL_API bool IM_ClearAudioCachePath();

	//设置播放语音音量(volume:0.0-1.0)
	YOUMEDLL_API void IM_SetVolume(float volume);
	//播放语音
	YOUMEDLL_API int IM_StartPlayAudio(const XCHAR* path);
	//停止语音播放
	YOUMEDLL_API int IM_StopPlayAudio();
	//查询播放状态
	YOUMEDLL_API bool IM_IsPlaying();
	//获取麦克风状态
	YOUMEDLL_API void GetMicrophoneStatus();

	//语音结束后是否保持原Category(IOS)
	YOUMEDLL_API void IM_SetKeepRecordModel(bool keep);

	//文本翻译
	YOUMEDLL_API int IM_TranslateText(unsigned int* requestID, const XCHAR* text, LanguageCode destLangCode, LanguageCode srcLangCode = LANG_AUTO);

	// 获取当前地理位置
	YOUMEDLL_API int IM_GetCurrentLocation();
	// 获取附近的目标
	YOUMEDLL_API int IM_GetNearbyObjects(int count, const XCHAR* serverAreaID, DistrictLevel districtlevel = DISTRICT_UNKNOW, bool resetStartDistance = false);
	// 设置位置更新间隔(单位：分钟)
	YOUMEDLL_API void IM_SetUpdateInterval(unsigned int interval);

	YOUMEDLL_API int IM_SetSpeechRecognizeParam(int accent, int language);

	YOUMEDLL_API int IM_GetMicrophoneStatus();

	YOUMEDLL_API int IM_Accusation(const XCHAR* userID, YIMChatType source, int reason, const XCHAR* description, const XCHAR* extraParam);

	YOUMEDLL_API int IM_QueryNotice();
    
    YOUMEDLL_API int IM_GetForbiddenSpeakInfo();
#endif
}
#endif /* IYouMeCInterface_hpp */
