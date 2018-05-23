#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdarg.h>
#include <stdio.h>

//拷贝MBCS字符串到MBCS字符数组并添加终止字符
#ifndef _asncpytA
#define	_asncpytA(dest, src)	{ strncpy(dest, (src) ? (src) : "", sizeof(dest)/sizeof(char)-1); dest[sizeof(dest)/sizeof(char)-1] = 0;}
#define _STRNCPY_A _asncpytA
#endif

//取64位整数的低32位整数
#ifndef LO_INT64
#define LO_INT64(S)           ((unsigned int)((uint64_t)(S) & 0xffffffff))
#endif
//取64位整数的高32位整数
#ifndef HI_INT64
#define HI_INT64(S)           ((unsigned int)((uint64_t)(S) >> 32))
#endif

//获取数组长度
#ifndef ArrayCount
#define	ArrayCount(a)		(sizeof(a)/sizeof((a)[0]))
#endif


#ifndef TEXTURE_FILE_RENAME
#define TEXTURE_FILE_RENAME
#define RENAME_JPG  ".jd"
#define RENAME_PNG  ".pd"
#define RENAME_WEBP ".wd"
#endif

#endif