#include "LuaYIM.h"
#include "json/document.h"
#include <YIMPlatformDefine.h>
#include <YIMCInterface.h>
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/CCLuaStack.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
//C:\testlua\testlua\src\app\views\MainScene.lua
std::string yim_to_string(XUINT64 i)
{
	char out[32];
#if defined(WIN32)
	_ui64toa(i, out, 10);
#else
	sprintf(out, "%llu", (long long unsigned int)i);
#endif
	return out;
}


XUINT64 yim_to_xuint64(const char* s)
{
#if defined(WIN32)
	return _atoi64(s);
#else	
	long long unsigned int out = 0;
	sscanf(s, "%llu", &out);
	return (XUINT64)out;
#endif
}

#ifdef WIN32

std::wstring P_UTF8_to_Unicode(const std::string& in)
{
	int len =in.length();
	wchar_t* pBuf = new wchar_t[len + 1];
	if (NULL == pBuf)
	{
		return __XT("");
	}
	size_t out_len = (len + 1) * sizeof(wchar_t);
	memset(pBuf, 0, (len + 1) * sizeof(wchar_t));
	wchar_t* pResult = pBuf;
	out_len = ::MultiByteToWideChar(CP_UTF8, 0, in.c_str(), len, pBuf, len * sizeof(wchar_t));
	std::wstring out;
	out.assign(pResult, out_len);


	delete[] pResult;
	pResult = NULL;
	return out;
}

std::string P_Unicode_to_UTF8(const std::wstring& in)
{
	std::string out;
	int len = in.length();
	size_t out_len = len * 3 + 1;
	char* pBuf = new char[out_len];
	if (NULL == pBuf)
	{
		return "";
	}
	char* pResult = pBuf;
	memset(pBuf, 0, out_len);


	out_len = ::WideCharToMultiByte(CP_UTF8, 0, in.c_str(), len, pBuf, len * 3, NULL, NULL);
	out.assign(pResult, out_len);
	delete[] pResult;
	pResult = NULL;
	return out;
}
#define  UTF8TOPlatString(str) P_UTF8_to_Unicode(str)
#define  PlatStringToUTF8(str) P_Unicode_to_UTF8(str)
#else
#define  UTF8TOPlatString(str) str 
#define  PlatStringToUTF8(str) str
#endif // WIN32
enum YouMeIMCommand
{
	CMD_UNKNOW = 0,
	CMD_LOGIN = 1,
	CMD_HEARTBEAT = 2,
	CMD_LOGOUT = 3,
	CMD_ENTER_ROOM = 4,
	CMD_LEAVE_ROOM = 5,
	CMD_SND_TEXT_MSG = 6,
	CMD_SND_VOICE_MSG = 7,
	CMD_SND_FILE_MSG = 8,
	CMD_GET_MSG = 9,
	CMD_GET_UPLOAD_TOKEN = 10,
	CMD_KICK_OFF = 11,
	CMD_SND_BIN_MSG = 12,
	CMD_RELOGIN = 13,
	CMD_CHECK_ONLINE = 14,
	CMD_SND_GIFT_MSG = 15,
	CMD_GET_ROOM_HISTORY_MSG = 16,
    CMD_GET_USR_INFO = 17,
    CMD_UPDATE_USER_INFO = 18,
	CMD_SND_TIPOFF_MSG = 19,
	CMD_GET_TIPOFF_MSG = 20,
	CMD_GET_DISTRICT = 21,
	CMD_GET_PEOPLE_NEARBY = 22,
    CMD_QUERY_NOTICE = 23,
    
    CMD_GET_FORBID_RECORD = 31,

	//服务器通知
	NOTIFY_LOGIN = 10001,
	NOTIFY_PRIVATE_MSG,
	NOTIFY_ROOM_MSG,

	//客户端(C接口使用)
	CMD_DOWNLOAD = 20001,
	CMD_SEND_MESSAGE_STATUS,
	CMD_RECV_MESSAGE,
	CMD_STOP_AUDIOSPEECH,
	CMD_QUERY_HISTORY_MESSAGE,
	CMD_GET_RENCENT_CONTACTS,
	CMD_RECEIVE_MESSAGE_NITIFY,
    CMD_QUERY_USER_STATUS,
    CMD_AUDIO_PLAY_COMPLETE,
	CMD_STOP_SEND_AUDIO,
	CMD_TRANSLATE_COMPLETE,
	CMD_DOWNLOAD_URL,
	CMD_GET_MICROPHONE_STATUS,
	CMD_USER_ENTER_ROOM,
	CMD_USER_LEAVE_ROOM,
	CMD_RECV_NOTICE,
	CMD_CANCEL_NOTICE
};

namespace {
	ScriptHandlerMgr::HandlerType EVENT_YIM_Login;
	ScriptHandlerMgr::HandlerType EVENT_YIM_Logout;
	ScriptHandlerMgr::HandlerType EVENT_YIM_Download;
	ScriptHandlerMgr::HandlerType EVENT_YIM_SendMessageStatus;
	ScriptHandlerMgr::HandlerType EVENT_YIM_SendAudioMessageStatus;
	ScriptHandlerMgr::HandlerType EVENT_YIM_RecvMessage;
	ScriptHandlerMgr::HandlerType EVENT_YIM_ChatroomMessage;
	ScriptHandlerMgr::HandlerType EVENT_YIM_SpeechStatus;
	ScriptHandlerMgr::HandlerType EVENT_YIM_QueryHistory;
	ScriptHandlerMgr::HandlerType EVENT_YIM_GetRecentContacts;
	ScriptHandlerMgr::HandlerType EVENT_YIM_RecvMsgNotify;
    ScriptHandlerMgr::HandlerType EVENT_YIM_GetUserInfo;
    ScriptHandlerMgr::HandlerType EVENT_YIM_QueryUserStatus;
    ScriptHandlerMgr::HandlerType EVENT_YIM_PlayComplete;
    ScriptHandlerMgr::HandlerType EVENT_YIM_StartSendAudioMessage;
	ScriptHandlerMgr::HandlerType EVENT_YIM_TranslateText;
	ScriptHandlerMgr::HandlerType EVENT_YIM_GetCurrentLocation;
	ScriptHandlerMgr::HandlerType EVENT_YIM_GetNearbyObjects;
    ScriptHandlerMgr::HandlerType EVENT_YIM_DownloadByUrl;
	ScriptHandlerMgr::HandlerType EVENT_YIM_UserJoinRoom;
	ScriptHandlerMgr::HandlerType EVENT_YIM_UserLeaveRoom;
	ScriptHandlerMgr::HandlerType EVENT_YIM_MicrophoneStatus;
	ScriptHandlerMgr::HandlerType EVENT_YIM_AccusationResultNotify;
	ScriptHandlerMgr::HandlerType EVENT_YIM_RecvNotice;
	ScriptHandlerMgr::HandlerType EVENT_YIM_CancelNotice;
    ScriptHandlerMgr::HandlerType EVENT_YIM_GetForbiddenSpeakInfo;
	
	
	
	
	ScriptHandlerMgr::HandlerType EVENT_YIM_Test; //对应的单独注册函数序号 0
}
struct HistoryMsg
{
	int iChatType;
	int iDuration;
	int iMessageType;
	std::string strParam;
	std::string strReceiveID;
	std::string strSenderID;
	std::string strSerial;
	std::string strText;
	std::string strLocalPath;
	HistoryMsg()
	{
		iDuration = 0;
	}
};

struct NearbyLocation
{
	unsigned int distance;
	double longitude;
	double latitude;
	std::string userID;
	std::string country;
	std::string province;
	std::string city;
	std::string districtCounty;
	std::string street;

	NearbyLocation() : distance(0), longitude(0), latitude(0){}
};

struct InnerForbidInfo{
    std::string channelID;
    bool isForbidRoom;
    int  reasonType;
    std::string endTime;
};

std::string  getArrayJsonString( lua_State* tolua_S , int index ){
    int iCount = luaL_getn(tolua_S, index );
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value root(rapidjson::kArrayType);
    for (int i = 1; i <= iCount;i++)
    {
        lua_rawgeti(tolua_S, index, i);
        const char* pszItem = lua_tostring(tolua_S, -1);
        rapidjson::Value item;
        item.SetString(pszItem, allocator);
        root.PushBack(item, allocator);
        
        lua_pop(tolua_S, 1);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    root.Accept(writer);
    std::string reststring = buffer.GetString();
    
    return reststring;
}


void ParseJsonMsgThead()
{
	while (true)
	{
		const XCHAR* pszJsonMsg = IM_GetMessage();
		if(CustomClass::getInstance()->m_bUninit)
		{
			break;
		}
		if (pszJsonMsg == NULL)
		{
			continue;
		}
		rapidjson::Document readdoc;
#ifdef WIN32
		readdoc.Parse<0>(P_Unicode_to_UTF8(pszJsonMsg).c_str());
#else
		readdoc.Parse<0>(pszJsonMsg);
#endif
		YouMeIMCommand command = (YouMeIMCommand)readdoc["Command"].GetInt();
		YIMErrorcode errorcode = (YIMErrorcode)readdoc["Errorcode"].GetInt();
		switch (command) {
		case CMD_RECEIVE_MESSAGE_NITIFY:
		{
            int chatType = readdoc["ChatType"].GetInt();
            std::string strTargetID = readdoc["TargetID"].GetString();
            
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_RecvMsgNotify);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(chatType);
                    pStack->pushString(strTargetID.c_str());
					pStack->executeFunctionByHandler(handler, 2);
					pStack->clean();
				}
			});
		}
		break;
		case CMD_GET_RENCENT_CONTACTS:
		{
			rapidjson::Value &contactList = readdoc["contacts"];
			std::vector<std::string> strContactLists;
			for (int i = 0; i < contactList.Size(); i++)
			{
				strContactLists.push_back(contactList[i].GetString());
			}
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_GetRecentContacts);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					
					cocos2d::LuaValueArray luaMsgLists;
					for (int i = 0; i < strContactLists.size(); i++)
					{						
						luaMsgLists.push_back(cocos2d::LuaValue::stringValue(strContactLists[i]));
					}

					pStack->pushLuaValueArray(luaMsgLists);


					pStack->executeFunctionByHandler(handler, 1);
					pStack->clean();
				}
			});
		}
		break;
		case CMD_QUERY_HISTORY_MESSAGE:
		{
			int iRemainCount = readdoc["Remain"].GetInt();
			std::string strTargetID = readdoc["TargetID"].GetString();
			rapidjson::Value &msgList = readdoc["messageList"];
			std::vector<std::shared_ptr<HistoryMsg> >hisoryLists;
			for (int i = 0; i < msgList.Size(); i++)
			{
				std::shared_ptr<HistoryMsg> pMsg(new HistoryMsg);
				const rapidjson::Value& msg = msgList[i];
				pMsg->iMessageType = msg["MessageType"].GetInt();
				pMsg->iChatType = msg["ChatType"].GetInt();
				pMsg->strReceiveID = msg["ReceiveID"].GetString();
				pMsg->strSenderID = msg["SenderID"].GetString();
				pMsg->strSerial = msg["Serial"].GetString();
				if (pMsg->iMessageType == MessageBodyType_TXT)
				{
					pMsg->strText = msg["Content"].GetString();
				}
				else if (pMsg->iMessageType == MessageBodyType_CustomMesssage)
				{
					//base4 编码的数据
					pMsg->strText = msg["Content"].GetString();
				}
				else if (pMsg->iMessageType == MessageBodyType_Voice)
				{
					pMsg->iDuration = msg["Duration"].GetInt();
					pMsg->strParam = msg["Param"].GetString();
					pMsg->strText = msg["Text"].GetString();
					pMsg->strLocalPath = msg["LocalPath"].GetString();
				}

				hisoryLists.push_back(pMsg);
			}
			
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_QueryHistory);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(errorcode);
					pStack->pushString(strTargetID.c_str());
					pStack->pushInt(iRemainCount);
					
					cocos2d::LuaValueArray luaMsgLists;
					for (int i = 0; i < hisoryLists.size(); i++)
					{
						cocos2d::LuaValueDict luaMsg;
						luaMsg["ChatType"] = cocos2d::LuaValue::intValue(hisoryLists[i]->iChatType);
						luaMsg["Duration"] = cocos2d::LuaValue::intValue(hisoryLists[i]->iDuration);
						luaMsg["Param"] = cocos2d::LuaValue::stringValue(hisoryLists[i]->strParam);
						luaMsg["ReceiveID"] = cocos2d::LuaValue::stringValue(hisoryLists[i]->strReceiveID);
						luaMsg["SenderID"] = cocos2d::LuaValue::stringValue(hisoryLists[i]->strSenderID);
						luaMsg["Serial"] = cocos2d::LuaValue::stringValue(hisoryLists[i]->strSerial);
						luaMsg["Text"] = cocos2d::LuaValue::stringValue(hisoryLists[i]->strText);
						luaMsg["MessageType"] = cocos2d::LuaValue::intValue(hisoryLists[i]->iMessageType);
						luaMsg["LocalPath"] = cocos2d::LuaValue::stringValue(hisoryLists[i]->strLocalPath);


						luaMsgLists.push_back(cocos2d::LuaValue::dictValue(luaMsg));
					}

					pStack->pushLuaValueArray(luaMsgLists);


					pStack->executeFunctionByHandler(handler, 4);
					pStack->clean();
				}
			});
		}
		break;
		case CMD_STOP_AUDIOSPEECH:
		{
			std::string strDownloadURL = readdoc["DownloadURL"].GetString();
			int iDuration = readdoc["Duration"].GetInt();
			int iFileSize = readdoc["FileSize"].GetInt();
			std::string strLocalPath = readdoc["LocalPath"].GetString();
			std::string strRequestID = readdoc["RequestID"].GetString();
			std::string strText = readdoc["Text"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_SpeechStatus);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(errorcode);
					pStack->pushString(strRequestID.c_str());
					pStack->pushString(strDownloadURL.c_str());
					pStack->pushInt(iDuration);
					pStack->pushInt(iFileSize);
					pStack->pushString(strLocalPath.c_str());
					pStack->pushString(strText.c_str());


					pStack->executeFunctionByHandler(handler, 7);
					pStack->clean();
				}
			});
		}
		break;
		case CMD_DOWNLOAD:
		{
			std::string strSavePath = readdoc["SavePath"].GetString();
            YIMMessageBodyType bodyType = (YIMMessageBodyType)readdoc["MessageType"].GetInt();
            YIMChatType ChatType = (YIMChatType)readdoc["ChatType"].GetInt();
            std::string strSerial = readdoc["Serial"].GetString();
            int iCreateTime = readdoc["CreateTime"].GetInt();
            std::string RecvID = readdoc["ReceiveID"].GetString();
            std::string SenderID = readdoc["SenderID"].GetString();
            std::string Content;
            std::string Param;
            
            int iDuration = 0;
            if (bodyType == MessageBodyType_Voice)
            {
                Content = readdoc["Text"].GetString();
                Param = readdoc["Param"].GetString();
                iDuration = readdoc["Duration"].GetInt();
            }
            
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_Download);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                    
                    lua_State *tolua_s = pStack->getLuaState();
                    if (NULL == tolua_s) {
                        return;
                    }
                    
                    pStack->pushInt(errorcode);
                    pStack->pushString(strSavePath.c_str());
                    
                    pStack->pushInt(bodyType);
                    pStack->pushInt(ChatType);
                    pStack->pushString(strSerial.c_str());
                    pStack->pushString(RecvID.c_str());
                    pStack->pushString(SenderID.c_str());
                    pStack->pushString(Content.c_str());
                    pStack->pushString(Param.c_str());
                    pStack->pushInt(iDuration);
                    pStack->pushInt( iCreateTime );

                    pStack->executeFunctionByHandler(handler, 11);
                    pStack->clean();
                }
            });
		}
		break;
        case CMD_DOWNLOAD_URL:
        {
            std::string strFromUrl = readdoc["FromUrl"].GetString();
            std::string strSavePath = readdoc["SavePath"].GetString();

            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_DownloadByUrl);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                    
                    lua_State *tolua_s = pStack->getLuaState();
                    if (NULL == tolua_s) {
                        return;
                    }
                    
                    pStack->pushInt(errorcode);
                    pStack->pushString(strFromUrl.c_str());
                    pStack->pushString(strSavePath.c_str());
                    pStack->executeFunctionByHandler(handler, 3);
                    pStack->clean();
                }
            });
        }
        break;
		case CMD_LOGIN:
		{
			std::string	YouMeID = readdoc["UserID"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_Login);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(errorcode);
					pStack->pushString(YouMeID.c_str());
					pStack->executeFunctionByHandler(handler, 2);
					pStack->clean();
				}
			});
		}
		break;
		case CMD_LOGOUT:
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_Logout);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}					
					pStack->executeFunctionByHandler(handler,0);
					pStack->clean();
				}
			});
		}
		break;
		
	
		case CMD_SEND_MESSAGE_STATUS:
		{
			std::string strSerial = readdoc["RequestID"].GetString();
            bool isForbidRoom = readdoc["IsForbidRoom"].GetInt() == 0 ? false:true ;
            int reasonType = readdoc["reasonType"].GetInt();
            std::string strEndTime = readdoc["forbidEndTime"].GetString();
            
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_SendMessageStatus);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushString(strSerial.c_str());
					pStack->pushInt(errorcode);
                    pStack->pushBoolean(isForbidRoom);
                    pStack->pushInt( reasonType );
                    pStack->pushString( strEndTime.c_str() );

					pStack->executeFunctionByHandler(handler, 5);
					pStack->clean();
				} 
			});
		}
		break;
		case CMD_SND_VOICE_MSG:
		{
			std::string strSerial = readdoc["RequestID"].GetString();
			std::string strText = readdoc["Text"].GetString();
			std::string strLocalPath = readdoc["LocalPath"].GetString();
			int iDuration = readdoc["Duration"].GetInt();
            bool isForbidRoom = readdoc["IsForbidRoom"].GetInt() == 0 ? false:true ;
            int reasonType = readdoc["reasonType"].GetInt();
            std::string strEndTime = readdoc["forbidEndTime"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_SendAudioMessageStatus);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushString(strSerial.c_str());
					pStack->pushInt(errorcode);
					pStack->pushString(strText.c_str());
					pStack->pushString(strLocalPath.c_str());
					pStack->pushInt(iDuration);
                    pStack->pushBoolean(isForbidRoom);
                    pStack->pushInt( reasonType );
                    pStack->pushString( strEndTime.c_str() );
                    
					pStack->executeFunctionByHandler(handler, 8);
					pStack->clean();
				}				
			});
		}
		break;
		case CMD_RECV_MESSAGE:
		{
			YIMMessageBodyType bodyType = (YIMMessageBodyType)readdoc["MessageType"].GetInt();
			YIMChatType ChatType = (YIMChatType)readdoc["ChatType"].GetInt();
			std::string strSerial = readdoc["Serial"].GetString();
            int iCreateTime = readdoc["CreateTime"].GetInt();
			std::string RecvID = readdoc["ReceiveID"].GetString();
			std::string SenderID = readdoc["SenderID"].GetString();
			std::string Content;
			std::string Param;
            
            int GiftID =0;
            int GiftCount =0;
            std::string strAnchor;

            int iDuration = 0;
			if ((bodyType == MessageBodyType_TXT) || (bodyType == MessageBodyType_CustomMesssage))
			{
				Content = readdoc["Content"].GetString();
			}
			else if (bodyType == MessageBodyType_Voice)
			{
				Content = readdoc["Text"].GetString();
				Param = readdoc["Param"].GetString();
				iDuration = readdoc["Duration"].GetInt();
			}
            else if (bodyType == MessageBodyType_Gift)
            {
                Param = readdoc["Param"].GetString();
                GiftID = readdoc["GiftID"].GetInt();
                GiftCount = readdoc["GiftCount"].GetInt();
                strAnchor = readdoc["Anchor"].GetString();
            }
            
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_RecvMessage);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(bodyType);
					pStack->pushInt(ChatType);
					pStack->pushString(strSerial.c_str());
					pStack->pushString(RecvID.c_str());
					pStack->pushString(SenderID.c_str());
					pStack->pushString(Content.c_str());
					pStack->pushString(Param.c_str());
					pStack->pushInt(iDuration);
                    pStack->pushInt( iCreateTime );
                    pStack->pushInt( GiftID );
                    pStack->pushInt( GiftCount );
                    pStack->pushString( strAnchor.c_str() );
					pStack->executeFunctionByHandler(handler, 12);
					pStack->clean();
				}
			});
		}
		break;
		case CMD_ENTER_ROOM:
		{
			std::string strGroupID = readdoc["GroupID"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_ChatroomMessage);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushString(strGroupID.c_str());
					pStack->pushInt(errorcode);
					pStack->executeFunctionByHandler(handler, 2);
					pStack->clean();
				}
			});
		}
		break;
        case CMD_GET_USR_INFO:
        {
			std::string strUserID = readdoc["UserID"].GetString();
            std::string strUserInfo = readdoc["UserInfo"].GetString();
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                //获得一个userinfo的json串，包含nickname,server_area,location,level,vip_level,extra字段
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_GetUserInfo);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                    
                    lua_State *tolua_s = pStack->getLuaState();
                    if (NULL == tolua_s) {
                        return;
                    }
                    pStack->pushInt(errorcode);
					pStack->pushString(strUserID.c_str());
                    pStack->pushString(strUserInfo.c_str());
                    pStack->executeFunctionByHandler(handler, 2);
                    pStack->clean();
                }
            });
        }
        break;
        case CMD_QUERY_USER_STATUS:
        {
            std::string strUserID = readdoc["UserID"].GetString();
            int status = readdoc["Status"].GetInt();
                
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_QueryUserStatus);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                        
                    lua_State *tolua_s = pStack->getLuaState();
                    if (NULL == tolua_s) {
                        return;
                    }
                    pStack->pushInt(errorcode);
                    pStack->pushString(strUserID.c_str());
                    pStack->pushInt(status);
                        
                    pStack->executeFunctionByHandler(handler, 3);
                    pStack->clean();
                }
            });
        }
            break;
        case CMD_AUDIO_PLAY_COMPLETE:
        {
            std::string strPath = readdoc["Path"].GetString();
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_PlayComplete);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                    pStack->pushInt(errorcode);
                    pStack->pushString(strPath.c_str());
                    pStack->executeFunctionByHandler(handler,2);
                    pStack->clean();
                }
            });
        }
            break;
        case CMD_STOP_SEND_AUDIO:
        {
            std::string strSerial = readdoc["RequestID"].GetString();
            std::string strText = readdoc["Text"].GetString();
            std::string strLocalPath = readdoc["LocalPath"].GetString();
            int iDuration = readdoc["Duration"].GetInt();
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_StartSendAudioMessage);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                        
                    lua_State *tolua_s = pStack->getLuaState();
                    if (NULL == tolua_s) {
                        return;
                    }
                    pStack->pushString(strSerial.c_str());
                    pStack->pushInt(errorcode);
                    pStack->pushString(strText.c_str());
                    pStack->pushString(strLocalPath.c_str());
                    pStack->pushInt(iDuration);
                    pStack->executeFunctionByHandler(handler, 5);
                    pStack->clean();
                }				
            });
        }
		break;
		case CMD_TRANSLATE_COMPLETE:
		{
			unsigned int iRequestID = readdoc["RequestID"].GetUint();
			std::string strText = readdoc["Text"].GetString();
			LanguageCode  srcLangCode = (LanguageCode) readdoc["SrcLangCode"].GetInt();
			LanguageCode destLangCode = (LanguageCode) readdoc["DestLangCode"].GetInt();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_TranslateText);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(errorcode);
					pStack->pushInt(iRequestID);
					pStack->pushString(strText.c_str());
					pStack->pushInt(srcLangCode);
					pStack->pushInt(destLangCode);
					pStack->executeFunctionByHandler(handler, 5);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_GET_DISTRICT:
		{
			DistrictLevel districtCode = (DistrictLevel) readdoc["DistrictCode"].GetInt();
			std::string strCountry = readdoc["Country"].GetString();
			std::string strProvince = readdoc["Province"].GetString();
			std::string strCity = readdoc["City"].GetString();
			std::string strDistrictCounty = readdoc["DistrictCounty"].GetString();
			std::string strStreet = readdoc["Street"].GetString();
			double fLongitude = readdoc["Longitude"].GetDouble();
			double fLatitude = readdoc["Latitude"].GetDouble();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_GetCurrentLocation);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(errorcode);
					pStack->pushInt(districtCode);
					pStack->pushString(strCountry.c_str());
					pStack->pushString(strProvince.c_str());
					pStack->pushString(strCity.c_str());
					pStack->pushString(strDistrictCounty.c_str());
					pStack->pushString(strStreet.c_str());
					pStack->pushFloat(fLongitude);
					pStack->pushFloat(fLatitude);
					pStack->executeFunctionByHandler(handler, 9);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_GET_PEOPLE_NEARBY:
		{
			unsigned int iStartDistance = readdoc["StartDistance"].GetUint();
			unsigned int iEndDistance = readdoc["EndDistance"].GetUint();
			rapidjson::Value &neighbourList = readdoc["NeighbourList"];
			std::vector<std::shared_ptr<NearbyLocation> > nearbyPeopleList;
			for (int i = 0; i < neighbourList.Size(); i++)
			{
				std::shared_ptr<NearbyLocation> pNearbyLocation(new NearbyLocation);
				const rapidjson::Value& msg = neighbourList[i];
				pNearbyLocation->userID = msg["UserID"].GetString();
				pNearbyLocation->distance = msg["Distance"].GetUint();
				pNearbyLocation->longitude = msg["Longitude"].GetDouble();
				pNearbyLocation->latitude = msg["Latitude"].GetDouble();
				pNearbyLocation->country = msg["Country"].GetString();
				pNearbyLocation->province = msg["Province"].GetString();
				pNearbyLocation->city = msg["City"].GetString();
				pNearbyLocation->districtCounty = msg["DistrictCounty"].GetString();
				pNearbyLocation->street = msg["Street"].GetString();
				nearbyPeopleList.push_back(pNearbyLocation);
			}
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_GetNearbyObjects);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}
					pStack->pushInt(errorcode);
					pStack->pushInt(iStartDistance);
					pStack->pushInt(iEndDistance);

					cocos2d::LuaValueArray nearbyList;
					for (std::vector<std::shared_ptr<NearbyLocation> >::const_iterator itr = nearbyPeopleList.begin(); itr != nearbyPeopleList.end(); ++itr)
					{
						cocos2d::LuaValueDict luaLocation;
						luaLocation["UserID"] = cocos2d::LuaValue::stringValue((*itr)->userID);
						luaLocation["Distance"] = cocos2d::LuaValue::intValue((*itr)->distance);
						luaLocation["Longitude"] = cocos2d::LuaValue::floatValue((*itr)->longitude);
						luaLocation["Latitude"] = cocos2d::LuaValue::floatValue((*itr)->latitude);
						luaLocation["Country"] = cocos2d::LuaValue::stringValue((*itr)->country);
						luaLocation["Province"] = cocos2d::LuaValue::stringValue((*itr)->province);
						luaLocation["City"] = cocos2d::LuaValue::stringValue((*itr)->city);
						luaLocation["DistrictCounty"] = cocos2d::LuaValue::stringValue((*itr)->districtCounty);
						luaLocation["Street"] = cocos2d::LuaValue::stringValue((*itr)->street);

						nearbyList.push_back(cocos2d::LuaValue::dictValue(luaLocation));
					}
					pStack->pushLuaValueArray(nearbyList);

					pStack->executeFunctionByHandler(handler, 4);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_USER_ENTER_ROOM:
		{
			std::string strChannelID = readdoc["ChannelID"].GetString();
			std::string strUserID = readdoc["UserID"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_UserJoinRoom);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}

					pStack->pushString(strChannelID.c_str());
					pStack->pushString(strUserID.c_str());
					pStack->executeFunctionByHandler(handler, 2);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_USER_LEAVE_ROOM:
		{
			std::string strChannelID = readdoc["ChannelID"].GetString();
			std::string strUserID = readdoc["UserID"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_UserLeaveRoom);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}

					pStack->pushString(strChannelID.c_str());
					pStack->pushString(strUserID.c_str());
					pStack->executeFunctionByHandler(handler, 2);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_GET_MICROPHONE_STATUS:
		{
			int status = readdoc["Status"].GetInt();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_MicrophoneStatus);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}

					pStack->pushInt(status);
					pStack->executeFunctionByHandler(handler, 1);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_GET_TIPOFF_MSG:
		{
			int result = readdoc["Result"].GetInt();
			std::string userID = readdoc["UserID"].GetString();
			unsigned int status = readdoc["AccusationTime"].GetUint();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_AccusationResultNotify);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}

					pStack->pushInt(result);
					pStack->pushString(userID.c_str());
					pStack->pushInt(status);
					pStack->executeFunctionByHandler(handler, 3);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_RECV_NOTICE:
		{
			std::string noticeID = readdoc["NoticeID"].GetString();
			std::string channelID = readdoc["ChannelID"].GetString();
			int noticeType = readdoc["NoticeType"].GetInt();
			std::string noticeContent = readdoc["NoticeContent"].GetString();
			std::string linkText = readdoc["LinkText"].GetString();
			std::string linkAddress = readdoc["LinkAddress"].GetString();
			unsigned int beginTime = readdoc["BeginTime"].GetUint();
			unsigned int endTime = readdoc["EndTime"].GetUint();

			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_RecvNotice);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}

					cocos2d::LuaValueDict luaNoticeInfo;
					luaNoticeInfo["NoticeID"] = cocos2d::LuaValue::stringValue(noticeID);
					luaNoticeInfo["ChannelID"] = cocos2d::LuaValue::stringValue(channelID);
					luaNoticeInfo["NoticeType"] = cocos2d::LuaValue::intValue(noticeType);
					luaNoticeInfo["NoticeContent"] = cocos2d::LuaValue::stringValue(noticeContent);
					luaNoticeInfo["LinkText"] = cocos2d::LuaValue::stringValue(linkText);
					luaNoticeInfo["LinkAddress"] = cocos2d::LuaValue::stringValue(linkAddress);
					luaNoticeInfo["BeginTime"] = cocos2d::LuaValue::intValue(beginTime);
					luaNoticeInfo["EndTime"] = cocos2d::LuaValue::intValue(endTime);

					pStack->pushLuaValueDict(luaNoticeInfo);
					pStack->executeFunctionByHandler(handler, 1);
					pStack->clean();
				}
			});
		}
			break;
		case CMD_CANCEL_NOTICE:
		{
			std::string noticeID = readdoc["NoticeID"].GetString();
			std::string channelID = readdoc["ChannelID"].GetString();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_AccusationResultNotify);
				if (0 != handler) {
					LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
					if (NULL == pStack) {
						return;
					}

					lua_State *tolua_s = pStack->getLuaState();
					if (NULL == tolua_s) {
						return;
					}

					pStack->pushString(noticeID.c_str());
					pStack->pushString(channelID.c_str());
					pStack->executeFunctionByHandler(handler, 2);
					pStack->clean();
				}
			});
		}
			break;
        case CMD_GET_FORBID_RECORD:
        {
            rapidjson::Value &forbidList = readdoc["ForbiddenSpeakList"];
            std::vector<std::shared_ptr<InnerForbidInfo> > forbidInfoList;
            for (int i = 0; i < forbidList.Size(); i++)
            {
                std::shared_ptr<InnerForbidInfo> pInfo(new InnerForbidInfo);
                const rapidjson::Value& msg = forbidList[i];
                pInfo->channelID = msg["ChannelID"].GetString();
                pInfo->isForbidRoom = msg["IsForbidRoom"].GetInt() ==0 ? false : true ;
                pInfo->reasonType = msg["reasonType"].GetInt();
                pInfo->endTime = msg["forbidEndTime"].GetString();

                forbidInfoList.push_back(pInfo);
            }
            
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
                int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)CustomClass::getInstance(), EVENT_YIM_GetForbiddenSpeakInfo);
                if (0 != handler) {
                    LuaStack *pStack = LuaEngine::getInstance()->getLuaStack();
                    if (NULL == pStack) {
                        return;
                    }
                    
                    lua_State *tolua_s = pStack->getLuaState();
                    if (NULL == tolua_s) {
                        return;
                    }
                    pStack->pushInt(errorcode);
                    
                    cocos2d::LuaValueArray arr;
                    for (std::vector<std::shared_ptr<InnerForbidInfo> >::const_iterator itr = forbidInfoList.begin(); itr != forbidInfoList.end(); ++itr)
                    {
                        cocos2d::LuaValueDict luaforbid;
                        luaforbid["channelID"] = cocos2d::LuaValue::stringValue((*itr)->channelID);
                        luaforbid["isForbidRoom"] = cocos2d::LuaValue::booleanValue((*itr)->isForbidRoom);
                        luaforbid["reasonType"] = cocos2d::LuaValue::intValue((*itr)->reasonType);
                        luaforbid["endTime"] = cocos2d::LuaValue::stringValue((*itr)->endTime );
                        
                        arr.push_back(cocos2d::LuaValue::dictValue(luaforbid));
                    }
                    pStack->pushLuaValueArray(arr);
                    
                    pStack->executeFunctionByHandler(handler, 2);
                    pStack->clean();
                }
            });
        }
            break;
		default:
			break;
		}

		IM_PopMessage(pszJsonMsg);
	}
}

CustomClass::CustomClass(){

}

CustomClass::~CustomClass(){
}

CustomClass* cocos2d::CustomClass::getInstance()
{
	static CustomClass* s_instance = NULL;
	if (NULL == s_instance)
	{
		s_instance = new CustomClass;
	}
	return s_instance;
}

void cocos2d::CustomClass::Uninit()
{
	m_bUninit = true;
	IM_Uninit();
	if(m_parseJsonThread.joinable())
	{
		m_parseJsonThread.join();
	}
}
static int tolua_Cocos2d_YIM_create(lua_State* tolua_S)
{
	CustomClass *wSocket = CustomClass::getInstance();
	tolua_pushusertype(tolua_S, (void*)wSocket, "cc.YIM");
	tolua_register_gc(tolua_S, lua_gettop(tolua_S));
	return 1;
}
static int tolua_Cocos2d_YIM_downloadAudioFile(lua_State* tolua_S)
{
	CustomClass *wSocket = CustomClass::getInstance();
	const char *pszSerial = ((const char*)tolua_tostring(tolua_S, 2, 0));
	const char *pszSavePath = ((const char*)tolua_tostring(tolua_S, 3, 0));
    int iErrorcode =  IM_DownloadFile(yim_to_xuint64(pszSerial), UTF8TOPlatString(std::string(pszSavePath)).c_str());
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_downloadFileByUrl(lua_State* tolua_S)
{
    CustomClass *wSocket = CustomClass::getInstance();
    const char *pszUrl = ((const char*)tolua_tostring(tolua_S, 2, 0));
    const char *pszSavePath = ((const char*)tolua_tostring(tolua_S, 3, 0));
    int iErrorcode =  IM_DownloadFileByURL(UTF8TOPlatString(std::string(pszUrl)).c_str(), UTF8TOPlatString(std::string(pszSavePath)).c_str());
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}


static int tolua_Cocos2d_YIM_leaveChatRoom(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszChatroom = ((const char*)tolua_tostring(tolua_S, 2, 0));
	int iErrorcode = IM_LeaveChatRoom(UTF8TOPlatString(std::string(pszChatroom)).c_str());
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_joinChatRoom(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszChatroom = ((const char*)tolua_tostring(tolua_S, 2, 0));
	int iErrorcode = IM_JoinChatRoom(UTF8TOPlatString(std::string(pszChatroom)).c_str());
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_cancleAudioMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iErrorcode = IM_CancleAudioMessage();
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}



static int tolua_Cocos2d_YIM_stopAudioMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszParam = ((const char*)tolua_tostring(tolua_S, 2, 0));
	int iErrorcode = IM_StopAudioMessage(UTF8TOPlatString(std::string(pszParam)).c_str());
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}


static int tolua_Cocos2d_YIM_sendOnlyAudioMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszRecvID = ((const char*)tolua_tostring(tolua_S, 2, 0));
	int iChatType = lua_tointeger(tolua_S, 3);
	XUINT64 iRequestID = -1;
	IM_SendOnlyAudioMessage(UTF8TOPlatString(std::string(pszRecvID)).c_str(), (YIMChatType)iChatType, &iRequestID);
	lua_pushstring(tolua_S, yim_to_string(iRequestID).c_str());
	return 1;
}

static int tolua_Cocos2d_YIM_sendAudioMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszRecvID = ((const char*)tolua_tostring(tolua_S, 2, 0));
	int iChatType = lua_tointeger(tolua_S, 3);
	XUINT64 iRequestID = -1;
	IM_SendAudioMessage(UTF8TOPlatString(std::string(pszRecvID)).c_str(), (YIMChatType)iChatType, &iRequestID);
	lua_pushstring(tolua_S, yim_to_string(iRequestID).c_str());
	return 1;
}


static int tolua_Cocos2d_YIM_unInit(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	self->Uninit();
	return 0;
}
static int tolua_Cocos2d_YIM_init(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);	
	const char *pszAppKey = ((const char*)tolua_tostring(tolua_S, 2, 0));
	const char *pszAppSec = ((const char*)tolua_tostring(tolua_S, 3, 0));
	int iErrorcode = IM_Init(UTF8TOPlatString(std::string(pszAppKey)).c_str(), UTF8TOPlatString(std::string(pszAppSec)).c_str());
	if (iErrorcode == YIMErrorcode_Success)
	{
		if(!self->m_parseJsonThread.joinable())
		{
			self->m_parseJsonThread = std::thread(ParseJsonMsgThead);
		}
		
	}
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}



static int tolua_Cocos2d_YIM_getFilterText(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszFileText = ((const char*)tolua_tostring(tolua_S, 2, 0));
    int level = 0;
	XCHAR* pszDealText = IM_GetFilterText(UTF8TOPlatString(std::string(pszFileText)).c_str(), &level );
	std::string strUTFText = PlatStringToUTF8(pszDealText);
	IM_DestroyFilterText(pszDealText);
	lua_pushstring(tolua_S, strUTFText.c_str());
    lua_pushinteger(tolua_S,  level );
	return 2;
}

static int tolua_Cocos2d_YIM_GetAudioCachePath(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
  
    XCHAR* pszPath = IM_GetAudioCachePath();
    std::string strPath = PlatStringToUTF8(pszPath);
    IM_DestroyFilterText(pszPath);
    lua_pushstring(tolua_S, strPath.c_str());
    return 1;
}


static int tolua_Cocos2d_YIM_setServerZone(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iServerZone = lua_tointeger(tolua_S, 2);
	IM_SetServerZone((ServerZone)iServerZone);
	return 0;
}



static int tolua_Cocos2d_YIM_startAudioSpeech(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	bool bTrans = lua_toboolean(tolua_S, 2);
	XUINT64 ulSerial = -1;
	IM_StartAudioSpeech(&ulSerial, bTrans);
	lua_pushstring(tolua_S, yim_to_string(ulSerial).c_str());
	return 1;
}

static int tolua_Cocos2d_YIM_stopAudioSpeech(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iErrorCode =IM_StopAudioSpeech();
	lua_pushinteger(tolua_S, iErrorCode);
	return 1;
}

static int tolua_Cocos2d_YIM_convertAMRToWav(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char* pszSrc = lua_tostring(tolua_S, 2);
	const char* pszDest = lua_tostring(tolua_S, 3);
	int iErrorCode = IM_ConvertAMRToWav(UTF8TOPlatString(std::string(pszSrc)).c_str(),UTF8TOPlatString(std::string(pszDest)).c_str());
	lua_pushinteger(tolua_S, iErrorCode);
	return 1;
}


static int tolua_Cocos2d_YIM_queryRoomHistoryMessageFromServer(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char* pszRoomID = lua_tostring(tolua_S, 2);
	int iErrorCode = IM_QueryRoomHistoryMessageFromServer(UTF8TOPlatString(std::string(pszRoomID)).c_str());
	lua_pushinteger(tolua_S, iErrorCode);
	return 1;
}


static int tolua_Cocos2d_YIM_deleteHistoryMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iChatType = lua_tointeger( tolua_S, 2 );
	const char* pszTime = lua_tostring(tolua_S, 3);
	int iErrorCode = IM_DeleteHistoryMessage((YIMChatType)iChatType, yim_to_xuint64(pszTime));
	lua_pushinteger(tolua_S, iErrorCode);
	return 1;
}


static int tolua_Cocos2d_YIM_deleteHistoryMessageByID(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    const char* pszMessageID = lua_tostring(tolua_S, 2);
    int iErrorCode = IM_DeleteHistoryMessageByID(yim_to_xuint64(pszMessageID));
    lua_pushinteger(tolua_S, iErrorCode);
    return 1;
}


static int tolua_Cocos2d_YIM_queryHistoryMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char* pszTarget = lua_tostring(tolua_S, 2);
    int iChatType = lua_tointeger( tolua_S, 3 );
	const char* pszSerial = lua_tostring(tolua_S, 4);
	int iCount = lua_tointeger(tolua_S, 5);
	int iDirect = lua_tointeger(tolua_S, 6);
	int iErrorCode = IM_QueryHistoryMessage(UTF8TOPlatString(std::string(pszTarget)).c_str(),iChatType,  yim_to_xuint64(pszSerial), iCount, iDirect);
	lua_pushinteger(tolua_S, iErrorCode);
	return 1;
}


static int tolua_Cocos2d_YIM_setAudioCacheDir(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszAudioCacheDir = ((const char*)tolua_tostring(tolua_S, 2, 0));
	IM_SetAudioCacheDir(UTF8TOPlatString(std::string(pszAudioCacheDir)).c_str());
	return 0;
}

static int tolua_Cocos2d_YIM_login(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszUserName = ((const char*)tolua_tostring(tolua_S, 2, 0));
	const char *pszPasswd = ((const char*)tolua_tostring(tolua_S, 3, 0));
	const char *pszToken = ((const char*)tolua_tostring(tolua_S, 4, 0));
	int iErrorcode = IM_Login(UTF8TOPlatString(std::string(pszUserName)).c_str(),
                              UTF8TOPlatString(std::string(pszPasswd)).c_str(),
                              UTF8TOPlatString(std::string(pszToken)).c_str());
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

//传一个json字符串，需要包含nickname,server_area,location,level,vip_level,extra字段
static int tolua_Cocos2d_YIM_setUserInfo(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    const char *pszUserInfo = ((const char*)tolua_tostring(tolua_S, 2, 0));
    int iErrorcode = IM_SetUserInfo(UTF8TOPlatString(std::string(pszUserInfo)).c_str());
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}

//获取联系人信息
static int tolua_Cocos2d_YIM_getUserInfo(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    const char *pszUserID = ((const char*)tolua_tostring(tolua_S, 2, 0));
    int iErrorcode = IM_GetUserInfo(UTF8TOPlatString(std::string(pszUserID)).c_str());
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}

//获取用户登录状态
static int tolua_Cocos2d_YIM_QueryUserStatus(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    const char *pszUserID = ((const char*)tolua_tostring(tolua_S, 2, 0));
    int iErrorcode = IM_QueryUserStatus(UTF8TOPlatString(std::string(pszUserID)).c_str());
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}

//播放录音
static int tolua_Cocos2d_YIM_SetVolume(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    float volume = (float)tolua_tonumber( tolua_S, 2, 0 );
    IM_SetVolume(  volume );
    return 0;
}

//播放录音
static int tolua_Cocos2d_YIM_StartPlayAudio(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    const char *pszPath = ((const char*)tolua_tostring(tolua_S, 2, 0));
    int iErrorcode = IM_StartPlayAudio(UTF8TOPlatString(std::string(pszPath)).c_str()  );
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}

static int tolua_Cocos2d_YIM_StopPlayAudio(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    int iErrorcode = IM_StopPlayAudio();
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}

static int tolua_Cocos2d_YIM_IsPlaying(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    bool bPlaying = IM_IsPlaying();
    lua_pushboolean(tolua_S, bPlaying);
    return 1;
}

static int tolua_Cocos2d_YIM_ClearAudioCachePath(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    
    bool bRes  = IM_ClearAudioCachePath();
    lua_pushboolean(tolua_S, bRes);
    return 1;
}

static int tolua_Cocos2d_YIM_SetRoomHistoryMessageSwitch(lua_State* tolua_S)
{

	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    std::string strTargets = getArrayJsonString( tolua_S , 2 );
    
    int iSave = lua_tointeger(tolua_S, 3);
    
    int iErrorcode = IM_SetRoomHistoryMessageSwitch(UTF8TOPlatString(strTargets).c_str(), iSave);
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}

static int tolua_Cocos2d_YIM_sendGift(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszRecvID = ((const char*)tolua_tostring(tolua_S, 2, 0));
	const char *pszChannel = ((const char*)tolua_tostring(tolua_S, 3, 0));
	int iGiftID = lua_tointeger(tolua_S, 4);
	int iGiftCount = lua_tointeger(tolua_S, 5);
	const char *pszExtParam = ((const char*)tolua_tostring(tolua_S, 6, 0));

	XUINT64 iRequestID = -1;
	IM_SendGift(UTF8TOPlatString(std::string(pszRecvID)).c_str(), UTF8TOPlatString(std::string(pszChannel)).c_str(),
                iGiftID, iGiftCount, pszExtParam, &iRequestID);
	lua_pushstring(tolua_S, yim_to_string(iRequestID).c_str());
	return 1;
}

static int tolua_Cocos2d_YIM_getNewMessage(lua_State* tolua_S)
{
    std::string str = getArrayJsonString( tolua_S , 2 );
	int iErrorcode = IM_GetNewMessage( UTF8TOPlatString(str).c_str() );
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}



static int tolua_Cocos2d_YIM_setReceiveMessageSwitch(lua_State* tolua_S)
{
    CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
    std::string strTargets = getArrayJsonString( tolua_S , 2 );
    
    int iAutoRecv = lua_tointeger(tolua_S, 3);
    
	int iErrorcode = IM_SetReceiveMessageSwitch( UTF8TOPlatString(strTargets).c_str(), iAutoRecv);
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_getContact(lua_State* tolua_S)
{
	int iErrorcode = IM_GetRecentContacts();
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}
static int tolua_Cocos2d_YIM_multiSendTextMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);	
	int iCount = luaL_getn(tolua_S, 2);
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value root(rapidjson::kArrayType);
	for (int i = 1; i <= iCount;i++)
	{
		lua_rawgeti(tolua_S, 2, i);
		const char* pszRecvID = lua_tostring(tolua_S, -1);
		rapidjson::Value item;
		item.SetString(pszRecvID, allocator);
		root.PushBack(item, allocator);

		lua_pop(tolua_S, 1);
	}
	const char *pszText = ((const char*)tolua_tostring(tolua_S, 3, 0));
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	root.Accept(writer);
	std::string reststring = buffer.GetString();

	int iErrorCode = IM_MultiSendTextMessage( reststring.c_str(), UTF8TOPlatString(std::string(pszText)).c_str());
	lua_pushinteger(tolua_S, iErrorCode);

	return 1;
}

static int tolua_Cocos2d_YIM_sendTextMessage(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszRecvID = ((const char*)tolua_tostring(tolua_S, 2, 0));
	int iChatType = lua_tointeger(tolua_S, 3);
	const char *pszContent = ((const char*)tolua_tostring(tolua_S, 4, 0));
	XUINT64 iRequestID = -1;
	IM_SendTextMessage(UTF8TOPlatString(std::string(pszRecvID)).c_str(), (YIMChatType)iChatType, UTF8TOPlatString(std::string(pszContent)).c_str(), &iRequestID);
	lua_pushstring(tolua_S, yim_to_string(iRequestID).c_str());
	return 1;
}



static int tolua_Cocos2d_YIM_onResume(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	IM_OnResume();
	return 0;
}

static int tolua_Cocos2d_YIM_onPause(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	IM_OnPause();
	return 0;
}

static int tolua_Cocos2d_YIM_logout(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iErrorcode = IM_Logout();
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_TranslateText(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszText = ((const char*)tolua_tostring(tolua_S, 2, 0));
	LanguageCode destLanguage = (LanguageCode)lua_tointeger(tolua_S, 3);
	LanguageCode srcLanguage = (LanguageCode)lua_tointeger(tolua_S, 4);
	unsigned int iRequestID = 0;
	IM_TranslateText(&iRequestID, UTF8TOPlatString(std::string(pszText)).c_str(), destLanguage, srcLanguage);
	lua_pushinteger(tolua_S, iRequestID);
	return 1;
}

static int tolua_Cocos2d_YIM_GetCurrentLocation(lua_State* tolua_S)
{
	int iErrorcode = IM_GetCurrentLocation();
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_GetNearbyObjects(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iCount = lua_tointeger(tolua_S, 2);
	const char *pszServerAreaID = ((const char*)tolua_tostring(tolua_S, 3, 0));
	DistrictLevel districtLevel = (DistrictLevel)lua_tointeger(tolua_S, 4);
	bool bResetStartDistance = lua_toboolean(tolua_S, 5);
	int iErrorcode = IM_GetNearbyObjects(iCount, UTF8TOPlatString(std::string(pszServerAreaID)).c_str(), districtLevel, bResetStartDistance);
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_SetUpdateInterval(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iInterval = lua_tointeger(tolua_S, 2);
	IM_SetUpdateInterval(iInterval);
	return 1;
}

// 设置语音识别参数
static int tolua_Cocos2d_YIM_SetSpeechRecognizeParam(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iAccent = lua_tointeger(tolua_S, 2);
	int iLanguage = lua_tointeger(tolua_S, 3);

	int iErrorcode = IM_SetSpeechRecognizeParam(iAccent, iLanguage);
	lua_pushinteger(tolua_S, iErrorcode);

	return 1;
}

// 查询公告
static int tolua_Cocos2d_YIM_GetMicrophoneStatus(lua_State* tolua_S)
{
	int iErrorcode = IM_GetMicrophoneStatus();
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

// 举报
static int tolua_Cocos2d_YIM_Accusation(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	const char *pszUserID = (const char*)tolua_tostring(tolua_S, 2, 0);
	int iChatType = lua_tointeger(tolua_S, 3);
	int iReason = lua_tointeger(tolua_S, 4);
	const char *pszDescription = (const char*)tolua_tostring(tolua_S, 5, 0);
	const char *pszExtraParam = (const char*)tolua_tostring(tolua_S, 6, 0);

	int iErrorcode = IM_Accusation(UTF8TOPlatString(std::string(pszUserID)).c_str(), (YIMChatType)iChatType, iReason,
                                   UTF8TOPlatString(std::string(pszDescription)).c_str(),
                                   UTF8TOPlatString(std::string(pszExtraParam)).c_str());
	lua_pushinteger(tolua_S, iErrorcode);

	return 1;
}

// 查询公告
static int tolua_Cocos2d_YIM_QueryNotice(lua_State* tolua_S)
{
	int iErrorcode = IM_QueryNotice();
	lua_pushinteger(tolua_S, iErrorcode);
	return 1;
}

static int tolua_Cocos2d_YIM_GetForbiddenSpeakInfo(lua_State* tolua_S)
{
    int iErrorcode = IM_GetForbiddenSpeakInfo();
    lua_pushinteger(tolua_S, iErrorcode);
    return 1;
}


static ScriptHandlerMgr::HandlerType _bindLuaFunction(lua_State *tolua_S, int index, void *cobj)
{
	int handler = toluafix_ref_function(tolua_S, index, 0);
	return cocos2d::ScriptHandlerMgr::getInstance()->addCustomHandler(cobj, handler);
}

static int tolua_Cocos2d_YIM_bindScriptHandler(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iEvtType = lua_tointeger(tolua_S, 2);
	switch (iEvtType)
	{
	case 0:
	{
		EVENT_YIM_Test = _bindLuaFunction(tolua_S, 3, self);
		//如果需要回掉先判断 EVENT_YIM_Test ==0 。 如果==0 说明用户并没有注册，就不要回掉了
	}
	break;

	default:
		break;
	}

	return 0;
}


static int tolua_Cocos2d_YIM_registerScriptHandler(lua_State* tolua_S)
{
	CustomClass *self = (CustomClass*)tolua_tousertype(tolua_S, 1, 0);
	int iCallbackCount = lua_gettop(tolua_S) - 1;
	assert(iCallbackCount == 26);
	if (iCallbackCount != 26)
	{
		return 0;
	}

	EVENT_YIM_Login = _bindLuaFunction(tolua_S, 2, self);
	EVENT_YIM_Logout = _bindLuaFunction(tolua_S, 3, self);
	EVENT_YIM_Download = _bindLuaFunction(tolua_S, 4, self);
	EVENT_YIM_SendMessageStatus = _bindLuaFunction(tolua_S, 5, self);
	EVENT_YIM_SendAudioMessageStatus = _bindLuaFunction(tolua_S, 6, self);
	EVENT_YIM_RecvMessage = _bindLuaFunction(tolua_S, 7, self);
	EVENT_YIM_ChatroomMessage = _bindLuaFunction(tolua_S, 8, self);

	EVENT_YIM_SpeechStatus = _bindLuaFunction(tolua_S, 9, self);
	EVENT_YIM_QueryHistory = _bindLuaFunction(tolua_S, 10, self);
	EVENT_YIM_GetRecentContacts = _bindLuaFunction(tolua_S, 11, self);
	EVENT_YIM_RecvMsgNotify = _bindLuaFunction(tolua_S, 12, self);
    EVENT_YIM_GetUserInfo = _bindLuaFunction( tolua_S, 13 , self );
    EVENT_YIM_QueryUserStatus = _bindLuaFunction( tolua_S, 14 , self );
    EVENT_YIM_PlayComplete = _bindLuaFunction( tolua_S, 15 , self );
    EVENT_YIM_StartSendAudioMessage = _bindLuaFunction( tolua_S, 16 , self );
	EVENT_YIM_TranslateText = _bindLuaFunction(tolua_S, 17, self);
	EVENT_YIM_GetCurrentLocation = _bindLuaFunction(tolua_S, 18, self);
	EVENT_YIM_GetNearbyObjects = _bindLuaFunction(tolua_S, 19, self);
    EVENT_YIM_DownloadByUrl = _bindLuaFunction( tolua_S, 20, self);
	EVENT_YIM_UserJoinRoom = _bindLuaFunction(tolua_S, 21, self);
	EVENT_YIM_UserLeaveRoom = _bindLuaFunction(tolua_S, 22, self);
	EVENT_YIM_MicrophoneStatus = _bindLuaFunction(tolua_S, 23, self);
	EVENT_YIM_AccusationResultNotify = _bindLuaFunction(tolua_S, 24, self);
	EVENT_YIM_RecvNotice = _bindLuaFunction(tolua_S, 25, self);
	EVENT_YIM_CancelNotice = _bindLuaFunction(tolua_S, 26, self);
    EVENT_YIM_GetForbiddenSpeakInfo = _bindLuaFunction(tolua_S, 27, self);

	/*
	int handler = toluafix_ref_function(tolua_S, 2, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_Login);
	
	handler = toluafix_ref_function(tolua_S, 3, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_Logout);

	handler = toluafix_ref_function(tolua_S, 4, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_Download);

	handler = toluafix_ref_function(tolua_S, 5, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_SendMessageStatus);

	handler = toluafix_ref_function(tolua_S, 6, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_SendAudioMessageStatus);

	handler = toluafix_ref_function(tolua_S, 7, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_RecvMessage);

	handler = toluafix_ref_function(tolua_S, 8, 0);
	cocos2d::ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, cocos2d::ScriptHandlerMgr::HandlerType::EVENT_YIM_ChatroomMessage);

	*/
	return 0;
}



static int tolua_collect_LuaYouMe(lua_State* tolua_S)
{
	return 0;
}
TOLUA_API int register_youmeim_manual(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	tolua_usertype(tolua_S, "cc.YIM");


	tolua_module(tolua_S, "cc", 0);
	tolua_beginmodule(tolua_S, "cc");
	tolua_cclass(tolua_S, "YIM", "cc.YIM", "", tolua_collect_LuaYouMe);
	tolua_beginmodule(tolua_S, "YIM");
	tolua_function(tolua_S, "create", tolua_Cocos2d_YIM_create);
	tolua_function(tolua_S, "init", tolua_Cocos2d_YIM_init);
	tolua_function(tolua_S, "unInit", tolua_Cocos2d_YIM_unInit);
	tolua_function(tolua_S, "sendTextMessage", tolua_Cocos2d_YIM_sendTextMessage);
	tolua_function(tolua_S, "sendAudioMessage", tolua_Cocos2d_YIM_sendAudioMessage);
	tolua_function(tolua_S, "sendOnlyAudioMessage", tolua_Cocos2d_YIM_sendOnlyAudioMessage);
	tolua_function(tolua_S, "stopAudioMessage", tolua_Cocos2d_YIM_stopAudioMessage);
	tolua_function(tolua_S, "cancleAudioMessage", tolua_Cocos2d_YIM_cancleAudioMessage);
	tolua_function(tolua_S, "joinChatRoom", tolua_Cocos2d_YIM_joinChatRoom);
	tolua_function(tolua_S, "leaveChatRoom", tolua_Cocos2d_YIM_leaveChatRoom);
	tolua_function(tolua_S, "downloadAudioFile", tolua_Cocos2d_YIM_downloadAudioFile);
    tolua_function(tolua_S, "downloadFileByUrl", tolua_Cocos2d_YIM_downloadFileByUrl);
	
	tolua_function(tolua_S, "login", tolua_Cocos2d_YIM_login);
	tolua_function(tolua_S, "logout", tolua_Cocos2d_YIM_logout);
	//一些全局的函数
	tolua_function(tolua_S, "getFilterText", tolua_Cocos2d_YIM_getFilterText);
	tolua_function(tolua_S, "setServerZone", tolua_Cocos2d_YIM_setServerZone);
	tolua_function(tolua_S, "setAudioCacheDir", tolua_Cocos2d_YIM_setAudioCacheDir);
	//新加的
	
	tolua_function(tolua_S, "startAudioSpeech", tolua_Cocos2d_YIM_startAudioSpeech);
	tolua_function(tolua_S, "stopAudioSpeech", tolua_Cocos2d_YIM_stopAudioSpeech);
	tolua_function(tolua_S, "queryHistoryMessage", tolua_Cocos2d_YIM_queryHistoryMessage);
	tolua_function(tolua_S, "deleteHistoryMessage", tolua_Cocos2d_YIM_deleteHistoryMessage);
    tolua_function(tolua_S, "deleteHistoryMessageByID", tolua_Cocos2d_YIM_deleteHistoryMessageByID);
	tolua_function(tolua_S, "queryRoomHistoryMessageFromServer", tolua_Cocos2d_YIM_queryRoomHistoryMessageFromServer);
	tolua_function(tolua_S, "convertAMRToWav", tolua_Cocos2d_YIM_convertAMRToWav);

	tolua_function(tolua_S, "onResume", tolua_Cocos2d_YIM_onResume);
	tolua_function(tolua_S, "onPause", tolua_Cocos2d_YIM_onPause);


	tolua_function(tolua_S, "sendGift", tolua_Cocos2d_YIM_sendGift);
	tolua_function(tolua_S, "multiSendTextMessage", tolua_Cocos2d_YIM_multiSendTextMessage);
	tolua_function(tolua_S, "getContact", tolua_Cocos2d_YIM_getContact);
	tolua_function(tolua_S, "setReceiveMessageSwitch", tolua_Cocos2d_YIM_setReceiveMessageSwitch);
	tolua_function(tolua_S, "getNewMessage", tolua_Cocos2d_YIM_getNewMessage);
    
    tolua_function(tolua_S, "setUserInfo", tolua_Cocos2d_YIM_setUserInfo);
    tolua_function(tolua_S, "getUserInfo", tolua_Cocos2d_YIM_getUserInfo);
    
    tolua_function(tolua_S, "queryUserStatus", tolua_Cocos2d_YIM_QueryUserStatus);
    tolua_function(tolua_S, "setVolume", tolua_Cocos2d_YIM_SetVolume);
    tolua_function(tolua_S, "startPlayAudio", tolua_Cocos2d_YIM_StartPlayAudio);
    tolua_function(tolua_S, "stopPlayAudio", tolua_Cocos2d_YIM_StopPlayAudio);
    tolua_function(tolua_S, "isPlaying", tolua_Cocos2d_YIM_IsPlaying );
    tolua_function(tolua_S, "getAudioCachePath", tolua_Cocos2d_YIM_GetAudioCachePath);
    tolua_function(tolua_S, "clearAudioCachePath", tolua_Cocos2d_YIM_ClearAudioCachePath);
    tolua_function(tolua_S, "setRoomHistoryMessageSwitch", tolua_Cocos2d_YIM_SetRoomHistoryMessageSwitch);

	tolua_function(tolua_S, "translateText", tolua_Cocos2d_YIM_TranslateText);

	tolua_function(tolua_S, "getCurrentLocation", tolua_Cocos2d_YIM_GetCurrentLocation);
	tolua_function(tolua_S, "getNearbyObjects", tolua_Cocos2d_YIM_GetNearbyObjects);
	tolua_function(tolua_S, "setUpdateInterval", tolua_Cocos2d_YIM_SetUpdateInterval);

	tolua_function(tolua_S, "setSpeechRecognizeParam", tolua_Cocos2d_YIM_SetSpeechRecognizeParam);
	tolua_function(tolua_S, "getMicrophoneStatus", tolua_Cocos2d_YIM_GetMicrophoneStatus);
	tolua_function(tolua_S, "accusation", tolua_Cocos2d_YIM_Accusation);
	tolua_function(tolua_S, "queryNotice", tolua_Cocos2d_YIM_QueryNotice);
    
    tolua_function(tolua_S, "getForbiddenSpeakInfo", tolua_Cocos2d_YIM_GetForbiddenSpeakInfo);

    
    
	
	tolua_function(tolua_S, "registerScriptHandler", tolua_Cocos2d_YIM_registerScriptHandler);
	tolua_function(tolua_S, "bindScriptHandler", tolua_Cocos2d_YIM_bindScriptHandler);
	
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);

	return 1;
}
