#ifndef _XCOMMON_H_
#define _XCOMMON_H_
#include <cocos2d.h>
#include "helpers/SystemHelpers.h"

#define XL_TEXTURE_TAG "T@"
#define XL_ANIMATION_TAG "A@"
#define XL_DOWNLOAD_TAG "D@"
#define XL_CSB_TAG "C@"
#define XL_UNZIP_TAG "UZ@"
#define XL_GROUP_TAG "G@"

#define X_EVENT_FROM_SCRIPT "__l2c__"
#define X_EVENT_TO_SCRIPT   "__c2l__"

enum Priority
{
	BACKGROUND_PRELOAD_TASK = 0,
	TEXTUTRE = 126,
	TILE = 127,
	ANIMATION = 128,
	HIGHEST = 255,
};

enum LoadWWRetCode
{
	eLOADWWW_OK,
	eLOADWWW_Progress,
	eLOADWWW_Error
};

//#define FOREGROUND_BLUE      0x0001 // text color contains blue.
//#define FOREGROUND_GREEN     0x0002 // text color contains green.
//#define FOREGROUND_RED       0x0004 // text color contains red.
//#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
//#define BACKGROUND_BLUE      0x0010 // background color contains blue.
//#define BACKGROUND_GREEN     0x0020 // background color contains green.
//#define BACKGROUND_RED       0x0040 // background color contains red.
//#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
//

#define XEVENT_LOADFRAME(...) ""

#ifdef _DEBUG

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		#define XLOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
		#define XLOGINFO(format,...)   SystemHelpers::formatlog(0x0020 | 0x0080,format, ##__VA_ARGS__)
		#define XLOGERROR(format,...)  SystemHelpers::formatlog(0x000C,format, ##__VA_ARGS__)
		#define XLOGWARN(format,...)   SystemHelpers::formatlog(0x0020 | 0x0040 | 0x0080,format, ##__VA_ARGS__)
		#define XAssert(cond,msg)	   if(!(cond)) { XLOGERROR("%s @ %s : %d",msg,__FILE__, __LINE__ ); CCASSERT(cond,msg); }
	#else
		#define XLOG        CCLOG
		#define XLOGINFO    CCLOGINFO
		#define XLOGERROR   CCLOGERROR
		#define XLOGWARN	CCLOGWARN
		#define XAssert     CCASSERT
	#endif
#else
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		#define XLOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
		#define XLOGINFO(format,...)   SystemHelpers::formatlog(0x0020 | 0x0080,format, ##__VA_ARGS__)
		#define XLOGERROR(format,...)  SystemHelpers::formatlog(0x0040 | 0x0080,format, ##__VA_ARGS__)
		#define XLOGWARN(format,...)   SystemHelpers::formatlog(0x0020 | 0x0040 | 0x0080,format, ##__VA_ARGS__)
		#define XAssert(cond,msg)	   if(!(cond)) { XLOGERROR("%s @ %s : %d",msg,__FILE__, __LINE__ ); CCASSERT(cond,msg); }
	#else
		#define XLOG        CCLOG
		#define XLOGINFO    CCLOGINFO
		#define XLOGERROR   CCLOGERROR
		#define XLOGWARN	CCLOGWARN
		#define XAssert     CCASSERT
	#endif
#endif // _DEBUG

template<class _Ty>
void _delete_shared_ref(_Ty* obj)
{
	obj->release();
}

template<class _Ty>
std::shared_ptr<_Ty> shared_ref_ptr(_Ty* obj)
{
	obj->retain();
	return std::shared_ptr<_Ty>(obj, _delete_shared_ref<_Ty>);
}

enum XDefault_Tags
{
	eZeroTag = 0,
	eAnimateSpriteAnimateTag = 1,
	eAnimateSpriteSpeedTag = 2,
	eAnimateSpriteMoveTag = 3,
	eCSBTimelineTag = 4,
	eLogicTagStart = 100,
};

#define SP8D_MOVE_SPEED_BASE			100
#define SP8D_MOVE_PIXEL_PER_SECOND		60

#define RENAME_WEBP ".webp"
#define RENAME_JPG	".jpg"
#endif