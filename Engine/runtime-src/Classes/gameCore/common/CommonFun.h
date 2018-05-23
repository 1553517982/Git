/****************************************************************************
HJH 2014-2-25
类名：无
用途：公共方法集合体

 ****************************************************************************/
#ifndef _COMMONFUN_
#define _COMMONFUN_

#include <string>
#include <list>
#include "cocos2d.h"
#include "os_def.h"

static const int kMaxLogLen = 16 * 1024;

#define CCDeletemap(_maptype , _mapself)										\
	{																				\
		for( _maptype::iterator it = _mapself.begin(); it!=_mapself.end(); )		\
		{																			\
		delete it->second;															\
		_mapself.erase(it++);														\
		}																			\
	}																				

#define CCReleasemap(_maptype , _mapself)										\
	{																				\
		for( _maptype::iterator it = _mapself.begin(); it!=_mapself.end(); )		\
		{																			\
			it->second->release();															\
			_mapself.erase(it++);														\
		}																			\
	}																				


#define CCDeletelist(_listtype, _listself)										\
	{																					\
		for( _listtype::IteratorFunc it = _listself.begin(); it != _listself.end(); )	\
		{																				\
			delete it->second;															\
			_listself.erase(it++);														\
		}																				\
	}																					

#define CCReleaselist(_listtype , _listself)										\
	{																				\
		for( _listtype::iterator it = _listself.begin(); it!=_listself.end(); )		\
		{																			\
			it->second->release();															\
			_listself.erase(it++);														\
		}																			\
	}																				

#ifndef _asncpytA
#define	_asncpytA(dest, src)	{ strncpy(dest, (src) ? (src) : "", sizeof(dest)/sizeof(char)-1); dest[sizeof(dest)/sizeof(char)-1] = 0;}
#define _STRNCPY_A _asncpytA
#endif

namespace commonFunction
{
	/**
	 *
	 *  @brief
	 *  @param const char * data
	 *  @return std::string
	 */
	std::string coverMulitByteToWideChar(const char *data);

	/**
	 *
	 *  @brief 将一个字符转换成Unicode值
	 *  @param const char * data
	 *  @return long
	 */
	long coverToUnicodeIndex(const char *data);

	/**
	 *
	 *  @brief 将一个字符转换成UTF8值
	 *  @param const char * data
	 *  @return long
	 */
	long coverToUTF8Index(const char *data);

	/**
	 *
	 *  @brief
	 *  @param char * dst
	 *  @param int len
	 *  @param const char * format
	 *  @param ...
	 *  @return int
	 */
	int XSNPRINTFA(char *dst, int len, const char *format, ...);

	/**
	 *
	 *  @brief
	 *  @param char * dst
	 *  @param int len
	 *  @param const char * format
	 *  @param va_list args
	 *  @return int
	 */
	int XVSNPRINTFA(char* dst, int len, const char* format, va_list args);

	/**
	 *
	 *  @brief 取得以UTF8码下一个字符所占位
	 *  @param char arg
	 *  @return unsigned short
	 */
	unsigned short getUTF8Len(char arg);

	/**
	 *
	 *  @brief 取得以UTF8码下一个字符所占位
	 *  @param char * arg
	 *  @return unsigned short
	 */
	unsigned short getUTF8Len(char *arg);

	/**
	 *
	 *  @brief
	 *  @param const char * arg
	 *  @param const char * tar
	 *  @param std::list<std::string> & info
	 *  @return void
	 */
	void splitInofByTarget(const char *arg, const char *tar, std::list<std::string> &info);

	UINT64 STRING_TO_UINT64(const char* string);

	const char* UINT64_TO_STRING(UINT64 value);

	INT64 STRING_TO_INT64(const char* string);

	const char* INT64_TO_STRING(INT64 value);
}

#endif