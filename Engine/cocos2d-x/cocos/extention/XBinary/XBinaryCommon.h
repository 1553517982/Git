#ifndef XBinary_Common_H
#define XBinary_Common_H
#include "platform/CCPlatformMacros.h"

	#define XBINARY_FILENAME_MAX_SIZE 72				//���ֵ���󳤶�72��char
	#define XBINARY_RESERZE_MAX_SIZE  72				//Ԥ���ֶ���󳤶ȣ������ļ���һ��

	enum XBinaryFileType
	{
		X_FILE_UNKNOWN,						// δ֪
		X_FILE_IMAGESET,					// ���� 
		X_FILE_FRAME						// ����֡
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