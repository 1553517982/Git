#ifndef __RICHTEXTCREATOR_H__
#define __RICHTEXTCREATOR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RichTextCreator
{
public:
	//�������ݻص�
	~RichTextCreator();

	/**
	@brief ��ȡ���ı�����������
	@param void
	@return RichTextCreator*
	*/
	static RichTextCreator* getInstance();

	/*
	@brief �����Է��ڵ��ַ����г��ֵ������ַ����ת���ַ�
	*/
	static std::string convertAttrStr(std::string& orgStr);

	/*
	@brief ����ͨ�ַ������ֵ����Է���{����}��ǰ���ת���ַ�
	*/
	static std::string convertNormalStr(std::string& orgStr);

	/**
	@brief ���ٵ���
	@param void
	@return void
	*/
	static void destroyInstance();

	/**
	@brief �����ַ���,�������ı�����
	@param strBuffer*	��Ҫ�������ַ���
	@return RichText*	ָ���´����ĸ��ı�����
	*/
	cocos2d::ui::RichText* Parser(std::string strBuffer);

	/**
	@brief �����ַ������������ı�����
	@param strBuffer ��Ҫ�������ַ���
		   contextSize	�ؼ���С��ʹ��ָ���Ĵ�С����contentSize.height==0����Ĭ���Զ�ƥ��߶�
	@return RichText* 
	*/
	cocos2d::ui::RichText* ParserWithSize(std::string strBuffer, cocos2d::Size contextSize);

	/*
	@brief ���ض�Ӧ����Ӣ����ĸ�Ŀ�ȱ��������ļ�
	*/
	bool LoadFontWidthConfig(const std::string &fileName, bool bReload = false);
	bool createFontWidthConfigFile(const std::string &fontPath, const std::string &fontName, const std::string &savePath, const std::string &saveFileName);
	/*
	@brief ��������Ĭ����ɫ
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
	@brief ����Ĭ�ϲ���
	@param attrMap	������map<paraKey,paraValue>
	@return 
	*/
	void parseParameter(tAttrMap attrMap);

	/**
	@brief �����ı�Ԫ��
	@param attrMap ����ӳ���
	@return 
	*/
	cocos2d::ui::RichElementText* createTextElement(tAttrMap attrMap, cocos2d::ui::RichText*  pRichText);
	cocos2d::ui::RichElementImage* createImageElement(tAttrMap attrMap);
	cocos2d::ui::RichElementCustomNode* createButton(tAttrMap attrMap);
	cocos2d::ui::RichElementCustomNode* createFrameAnimation(tAttrMap attrMap);

	void parseAndCreateText(cocos2d::ui::RichText*  pRichText,cocos2d::Color3B &color, int iOpacity, std::string strText, std::string strFontName, int fontSize);
	cocos2d::Color3B transformColor(std::string strColor);
	void ResetParameter();

#define OPEN_TOKEN			'{'				// �򿪵�token
#define CLOSE_TOKEN			'}'				// �رյ�token
#define DISCARD_TOKEN		'$'				// ȡ��token 
	// ${ output }
	// $} output {
	// $= output =
	// $, output ,
	// $$ output $

#define ELEMENT_DELIM_TOKEN ','				// attr�ָ�token
#define ATTR_KV_TOKEN		'='				// attr key value �ָ�token
	void parseKeyValue(const char* buffer, unsigned int size, tAttrMap& attrMap, cocos2d::ui::RichText*  pRichText);
	void parseAttribute(const char* buffer, unsigned int size, tAttrMap& attrMap, cocos2d::ui::RichText*  pRichText);
	void parseBuffer(const char* buffer, unsigned int size, cocos2d::ui::RichText*  pRichText);

	/**
	@brief ʹ��Ĭ�����Դ���label�ӽڵ�
	@param	text		�ı�����
			pRichText	���ı��ؼ�
	@return void
	*/
	void TextCallBack(const std::string text, cocos2d::ui::RichText*  pRichText);

	/**
	@brief �����ַ��������Զ���{}�ص�
	����
	1.����key:type���ӽڵ�����
	a.���������Ľڵ����ͣ�����������Ӧ��RichElement
	label	�ַ���
	image	ͼƬ
	button	��ť
	ccsanim cocostudio�����animature
	frame	�Զ����֡����
	b.�����ڶ�����ӽڵ����ͣ����ַ�������ʽ���������
	2.δ����key:type, �����ֶε�������ΪĬ������
	@param
	attrMap		��������������map
	pRichText	��ǰ���ڴ����ĸ��ı�����
	@return
	*/
	void ElementCallBack(tAttrMap attrMap, cocos2d::ui::RichText*  pRichText);

	/**
	@brief ����ʧ�ܣ����ʧ����ϢΪlabel���ؼ�
	@param	msg			�������
			pRichText	�ؼ�
	@return void
	*/
	void ErrorCallBack(const std::string msg, cocos2d::ui::RichText*  pRichText);
protected:
	static RichTextCreator* s_Instance;

	float					_defaultFontSize;
	cocos2d::Color3B		_defaultFontColor;
	int						_defaultFontOpacity;
	std::string				_defaultFontName;

	//����ʹ�õĵ�ǰ�����������е��������ʱ��û��������ֵ����ʹ�õ�ǰֵ
	float				_curFontSize;			//Ĭ�������С
	cocos2d::Color3B	_curFontColor;			//Ĭ����ɫ
	int					_curFontOpacity;		//Ĭ��͸����
	std::string			_curFontName;			//Ĭ����������

	std::string			_curAnimationSkinName;	//��ǰ����ʹ�õ�����
	std::string			_curAnimationActionName;//��ǰ����ʹ�õĶ���
	float				_curAnimWidth;			//��ǰ�����Ŀ��
	float				_curAnimHeight;			//��ǰ�����ĳ���
};

#endif