#ifndef __RICHTEXTCREATOR_H__
#define __RICHTEXTCREATOR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RichTextCreator
{
public:
	//文字内容回调
	~RichTextCreator();

	/**
	@brief 获取富文本创建器单例
	@param void
	@return RichTextCreator*
	*/
	static RichTextCreator* getInstance();

	/*
	@brief 对属性符内的字符串中出现的特殊字符添加转义字符
	*/
	static std::string convertAttrStr(std::string& orgStr);

	/*
	@brief 对普通字符串出现的属性符“{”“}”前添加转义字符
	*/
	static std::string convertNormalStr(std::string& orgStr);

	/**
	@brief 销毁单例
	@param void
	@return void
	*/
	static void destroyInstance();

	/**
	@brief 解析字符串,创建富文本对象，
	@param strBuffer*	将要解析的字符串
	@return RichText*	指向新创建的富文本对象
	*/
	cocos2d::ui::RichText* Parser(std::string strBuffer);

	/**
	@brief 解析字符串，创建富文本对象
	@param strBuffer 将要解析的字符串
		   contextSize	控件大小，使用指定的大小，若contentSize.height==0，则默认自动匹配高度
	@return RichText* 
	*/
	cocos2d::ui::RichText* ParserWithSize(std::string strBuffer, cocos2d::Size contextSize);

	/*
	@brief 加载对应字体英文字母的宽度比例配置文件
	*/
	bool LoadFontWidthConfig(const std::string &fileName, bool bReload = false);
	bool createFontWidthConfigFile(const std::string &fontPath, const std::string &fontName, const std::string &savePath, const std::string &saveFileName);
	/*
	@brief 设置字体默认颜色
	*/
	void setDefaultFontColor(cocos2d::Color3B color)	{ _defaultFontColor = color; }
	cocos2d::Color3B getDefaultFontColor()			{ return _defaultFontColor; }
	
	void setDefaultFontOpacity(int opacity)				{ _defaultFontOpacity = opacity; }
	int getDefaultFontOpacity()							{ return _defaultFontOpacity; }

	void setDefaultFontName(std::string fontName)		{ _defaultFontName = fontName; }
	std::string getDefaultFontName()					{ return _defaultFontName; }

	void setDefaultFontSize(float size) { _defaultFontSize = size; }
	float getDefaultFontSize()			{ return _defaultFontSize; }
private:
	typedef std::map<std::string, std::string> tAttrMap;
	RichTextCreator();
	bool init();
	/**
	@brief 解析默认参数
	@param attrMap	参数表map<paraKey,paraValue>
	@return 
	*/
	void parseParameter(tAttrMap attrMap);

	/**
	@brief 创建文本元素
	@param attrMap 参数映射表
	@return 
	*/
	cocos2d::ui::RichElementText* createTextElement(tAttrMap attrMap, cocos2d::ui::RichText*  pRichText);
	cocos2d::ui::RichElementImage* createImageElement(tAttrMap attrMap);
	cocos2d::ui::RichElementCustomNode* createButton(tAttrMap attrMap);
	cocos2d::ui::RichElementCustomNode* createFrameAnimation(tAttrMap attrMap);

	void parseAndCreateText(cocos2d::ui::RichText*  pRichText,cocos2d::Color3B &color, int iOpacity, std::string strText, std::string strFontName, int fontSize);
	cocos2d::Color3B transformColor(std::string strColor);
	void ResetParameter();

#define OPEN_TOKEN			'{'				// 打开的token
#define CLOSE_TOKEN			'}'				// 关闭的token
#define DISCARD_TOKEN		'$'				// 取消token 
	// ${ output }
	// $} output {
	// $= output =
	// $, output ,
	// $$ output $

#define ELEMENT_DELIM_TOKEN ','				// attr分割token
#define ATTR_KV_TOKEN		'='				// attr key value 分割token
	void parseKeyValue(const char* buffer, unsigned int size, tAttrMap& attrMap, cocos2d::ui::RichText*  pRichText);
	void parseAttribute(const char* buffer, unsigned int size, tAttrMap& attrMap, cocos2d::ui::RichText*  pRichText);
	void parseBuffer(const char* buffer, unsigned int size, cocos2d::ui::RichText*  pRichText);

	/**
	@brief 使用默认属性创建label子节点
	@param	text		文本内容
			pRichText	富文本控件
	@return void
	*/
	void TextCallBack(const std::string text, cocos2d::ui::RichText*  pRichText);

	/**
	@brief 解析字符串，属性定义{}回调
	规则：
	1.定义key:type，子节点类型
	a.存在这样的节点类型，解析出来相应的RichElement
	label	字符串
	image	图片
	button	按钮
	ccsanim cocostudio定义的animature
	frame	自定义的帧动画
	b.不存在定义的子节点类型，以字符串的形式输出类型名
	2.未定义key:type, 属性字段当做解析为默认属性
	@param
	attrMap		解析出来的属性map
	pRichText	当前正在创建的富文本对象
	@return
	*/
	void ElementCallBack(tAttrMap attrMap, cocos2d::ui::RichText*  pRichText);

	/**
	@brief 解析失败，输出失败信息为label到控件
	@param	msg			错误代码
			pRichText	控件
	@return void
	*/
	void ErrorCallBack(const std::string msg, cocos2d::ui::RichText*  pRichText);
protected:
	static RichTextCreator* s_Instance;

	float					_defaultFontSize;
	cocos2d::Color3B		_defaultFontColor;
	int						_defaultFontOpacity;
	std::string				_defaultFontName;

	//字体使用的当前参数，对所有的文字输出时，没有新设置值，则使用当前值
	float				_curFontSize;			//默认字体大小
	cocos2d::Color3B	_curFontColor;			//默认颜色
	int					_curFontOpacity;		//默认透明度
	std::string			_curFontName;			//默认字体类型

	std::string			_curAnimationSkinName;	//当前动画使用的纹理
	std::string			_curAnimationActionName;//当前动画使用的动作
	float				_curAnimWidth;			//当前动画的宽度
	float				_curAnimHeight;			//当前动画的长度
};

#endif