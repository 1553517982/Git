#ifndef XBinary_Common_H
#define XBinary_Common_H
#include "platform/CCPlatformMacros.h"

	#define XBINARY_FILENAME_MAX_SIZE 72				//名字的最大长度72个char
	#define XBINARY_RESERZE_MAX_SIZE  72				//预留字段最大长度，各种文件不一样

	enum XBinaryFileType
	{
		X_FILE_UNKNOWN,						// 未知
		X_FILE_IMAGESET,					// 界面 
		X_FILE_FRAME						// 动画帧
	};
	
	typedef struct _XBinaryHeader
	{
		unsigned short				unFileType;
		unsigned short				unFileVersion;
		unsigned int				unItemCount;
		char						szReserze[XBINARY_RESERZE_MAX_SIZE];
	}XBinaryHeader;

	#define XBINARY_FILE_POSTFIX		0xdeba

	#define COCOS2D						1


#endif