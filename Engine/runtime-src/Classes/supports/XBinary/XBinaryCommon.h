#ifndef XBinary_Common_H
#define XBinary_Common_H
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

	//MOD_FOR_64BIT by Shan Lu 2015-01-10 Begin
	//����ͳһ��ȡ���ȫ�������ټ��ط�ʽ
	#if defined(__LP64__) && __LP64__
	#define XIMAGEUNIT_SLOW__READ
	#else
	#define XIMAGEUNIT_SLOW__READ
	#endif
	//MOD_FOR_64BIT by Shan Lu 2015-01-10 End

#endif