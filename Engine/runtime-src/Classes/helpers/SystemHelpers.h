#ifndef __SystemHelpers_H__
#define __SystemHelpers_H__

#include <string>

class SystemHelpers
{
public:
	/*! \class  SystemHelpers
	*  \brief  节点Node的帮助操作类
	*/

	/**
	@brief 弹出一个messageBox
	@param title
	@param content
	@return void
	*/
	static void	messageBox(const char* title, const char* content);

	/**
	@brief 获取时间
	@return float
	*/
	static float   gettime();

	/**
	@brief 打印信息,win32下带有颜色
	@param szText
	@param colorIndex	颜色的枚举，请自行百度 SetConsoleTextAttribute
	@return void
	*/
	static void	log(const char* szText, unsigned short colorIndex = 0x0002);

	static void	formatlog(unsigned short colorIndex, const char * format, ...);

	/*!
	* \brief 添加搜索路径
	* \param const char * path
	* \return void
	*/
	static void	addSearchPath(const char* path);

	/*!
	* \brief 从粘贴板获取内容
	* \return std::string
	*/
	static std::string fromClipboard();

	/*!
	* \brief 打开一个路径Dialog
	* \param const char * title
	* \param const char * defaultPath
	* \return std::string
	*/
	static std::string pathDialog(const char* title, const char* defaultPath);

	static unsigned int low8Word(unsigned int number);

	static unsigned int high8Word(unsigned int number);

	static unsigned int lowByte(unsigned int number);

	static unsigned int highByte(unsigned int number);

	static int rshift(int number, int pos);

	static int lshift(int number, int pos);

	static unsigned int band(unsigned int n1, unsigned int n2);

	static unsigned int bor(unsigned int n1, unsigned int n2);

	static unsigned int binvert(unsigned int n1);

	static unsigned int bclear(unsigned int n1, unsigned int n2);

};

#endif /* defined(__CocoGUI__UISystem__) */
