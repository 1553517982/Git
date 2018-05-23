#include "RichTextCreator.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CocoStudio.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "GUI/EventRichText.h"
#include "ui/FontWidthHelper.h"
#include "GUI/DrawNodeEx.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace std;

const int cstTag = 100;
RichTextCreator* RichTextCreator::s_Instance = nullptr;

RichTextCreator::RichTextCreator() :
_defaultFontOpacity(255),
_defaultFontSize(20.0f),
_defaultFontName("arial.ttf"),
_defaultFontColor(Color3B::WHITE), 

_curAnimWidth(64),
_curAnimHeight(64)
{
	_curFontColor = _defaultFontColor;
	_curFontOpacity = _defaultFontOpacity;
	_curFontSize = _defaultFontSize;
	_curFontName = _defaultFontName;
}

void RichTextCreator::ResetParameter()
{
	_curFontColor = _defaultFontColor;
	_curFontOpacity = _defaultFontOpacity;
	_curFontSize = _defaultFontSize;
	_curFontName = _defaultFontName;
}

RichTextCreator::~RichTextCreator()
{
}

RichTextCreator* RichTextCreator::getInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new RichTextCreator();
		CC_ASSERT(s_Instance->init());
	}

	return s_Instance;
}

void RichTextCreator::destroyInstance()
{
	if (s_Instance != nullptr)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

string RichTextCreator::convertNormalStr(string& orgStr)
{
	if (orgStr.empty())
	{
		return "";
	}

	int strSize = orgStr.size();
	string strOut;
	for (int i = 0; i < strSize; ++i)
	{
		char curChar = orgStr.at(i);
		if (curChar == OPEN_TOKEN
			|| curChar == CLOSE_TOKEN)
		{
			strOut.push_back(DISCARD_TOKEN);
		}
		strOut.push_back(curChar);
	}
	strOut.push_back('\0');

	return strOut;
}

string RichTextCreator::convertAttrStr(string& orgStr)
{
	if (orgStr.empty())
	{
		return "";
	}

	int strSize = orgStr.size();
	string strOut;
	for (int i = 0; i < strSize; ++i)
	{
		char curChar = orgStr.at(i);
		if (curChar == OPEN_TOKEN
			|| curChar == CLOSE_TOKEN
			|| curChar == DISCARD_TOKEN
			|| curChar == ELEMENT_DELIM_TOKEN
			|| curChar == ATTR_KV_TOKEN)
		{
			strOut.push_back(DISCARD_TOKEN);
		}
		strOut.push_back(curChar);

	}
	strOut.push_back('\0');

	return strOut;
}

bool RichTextCreator::init()
{
	return true;
}

bool RichTextCreator::LoadFontWidthConfig( const std::string &fileName, bool bReload /* = false*/)
{
	return ui::FontWidthHelper::getInstance().LoadConfig(fileName, bReload);
}

bool RichTextCreator::createFontWidthConfigFile(const std::string &fontPath, const std::string &fontName, const std::string &savePath, const std::string &saveFileName)
{
	return ui::FontWidthHelper::getInstance().saveFontWidthConfig(fontPath, fontName, savePath, saveFileName);
}

//type�������͵Ļ���������Ĳ���ֻ�Ե�ǰ����Ч
RichText* RichTextCreator::Parser(std::string strFormat)
{
	ResetParameter();
	RichText* pRichText = RichText::create();
	parseBuffer(strFormat.c_str(), strFormat.size(), pRichText);
	//being add by  zenghaiming on 2015/5/18
	//��ǰ��ʽ�������ı����Ա��ȡ��ʵ�ʴ�С
	pRichText->formatText();
	//end add
	return pRichText;
}

RichText* RichTextCreator::ParserWithSize(string strFormat, Size contentSize)
{
	ResetParameter();
	RichText* pRichText = RichText::create();
	pRichText->ignoreContentAdaptWithSize(false);
	//��һ��ֵ,����label��ǰ����
	pRichText->setContentSize(Size(contentSize.width+0.001f, contentSize.height));
	parseBuffer(strFormat.c_str(), strFormat.size(), pRichText);
	//beging add by zenghaiming on 2015/5/18
	//��ǰ��ʽ�����ı����Ա��ȡʵ�ʴ�С
	pRichText->formatText();
	//end add
	return pRichText;
}

void RichTextCreator::parseAndCreateText(RichText*  pRichText, Color3B &color, int iOpacity, string text, string strFontName, int fontSize)
{
	const char* strContext = text.c_str();
	const char* pCur = &strContext[0];
	char buf[512];
	int outIndex = 0;
	int strSize = text.size() + 1;
	for (int i = 0; i < strSize; ++i)
	{
		if (*pCur == '\n' || *pCur == '\0')
		{
			buf[outIndex] = '\0';
			RichElementText* textElement = RichElementText::create(cstTag, color, iOpacity, buf, strFontName, fontSize);
			pRichText->pushBackElement(textElement);
			outIndex = 0;
			if (*pCur == '\0')
			{
				break;
			}
			else
			{
				Node* node = Node::create();
				node->setContentSize(Size(pRichText->getContentSize().width, 0));
				RichElementCustomNode* eleNode = RichElementCustomNode::create(cstTag, Color3B::BLACK, 255, node);
				pRichText->pushBackElement(eleNode);
			}
		}
		else
		{
			buf[outIndex] = *pCur;
			outIndex++;
		}
		pCur++;
	}
}

void RichTextCreator::TextCallBack(const string text, cocos2d::ui::RichText*  pRichText)
{
	parseAndCreateText(pRichText, _curFontColor, _curFontOpacity, text, _curFontName, _curFontSize);
}

void RichTextCreator::ElementCallBack(tAttrMap attrMap, cocos2d::ui::RichText*  pRichText)
{
	map<string,string>::iterator elementType = attrMap.find("t");
	if (elementType != attrMap.end())
	{
		string strType = elementType->second;
		if (strType.compare("label") == 0)
		{
			createTextElement(attrMap, pRichText);
		}
		else if (strType.compare("image") == 0)
		{
			RichElementImage* reImage = createImageElement(attrMap);
			pRichText->pushBackElement(reImage);
		}
		else if (strType.compare("button") == 0)
		{
			RichElementCustomNode* reCus = createButton(attrMap);
			pRichText->pushBackElement(reCus);
		}
		else if (strType.compare("frame") == 0)
		{
			RichElementCustomNode* reAnimation = createFrameAnimation(attrMap);
			if (reAnimation != nullptr)
			{
				pRichText->pushBackElement(reAnimation);
			}
		}
		else
		{
			//�޷�����������,һ�ζ������Ե�
			CCLOG("Can't find this type:%s", strType.c_str());
			RichElementText* textElement = RichElementText::create(cstTag, _curFontColor, _curFontOpacity, "miss Type:" + strType, _curFontName, 20);
			pRichText->pushBackElement(textElement);
		}
	}
	else
	{
		//û��ָ�����ͣ�����ָ����Ĭ�ϲ���
		parseParameter(attrMap);
	}
}

//
void RichTextCreator::ErrorCallBack(const std::string msg, cocos2d::ui::RichText*  pRichText)
{
	CCLOG(msg.c_str());
	RichElementText* textElement = RichElementText::create(cstTag, Color3B::WHITE, 255, msg, _curFontName, 20);
	pRichText->pushBackElement(textElement);
}

//�����ı�Ĭ�ϲ���
void RichTextCreator::parseParameter(tAttrMap attrMap)
{
	//��ɫ
	map<string, string>::iterator npos = attrMap.find("c");
	if (npos != attrMap.end())
	{
		_curFontColor = transformColor(npos->second);
	}

	//͸����
	npos = attrMap.find("op");
	if (npos != attrMap.end())
	{
		_curFontOpacity = atoi(npos->second.c_str());
	}

	//����
	npos = attrMap.find("ft");
	if (npos != attrMap.end())
	{
		_curFontName = npos->second;
	}

	//�����С
	npos = attrMap.find("fs");
	if (npos != attrMap.end())
	{
		_curFontSize = atof(npos->second.c_str());
	}
}
//////////////////////////////////////////////////////////////////////////
RichElementText* RichTextCreator::createTextElement(tAttrMap attrMap, RichText*  pRichText)
{
	//��ɫ
	Color3B color = _curFontColor;
	map<string, string>::iterator npos = attrMap.find("c");
	if (npos != attrMap.end())
	{
		color = transformColor(npos->second);
	}

	//͸����
	int iOpacity = _curFontOpacity;
	npos = attrMap.find("op");
	if (npos != attrMap.end())
	{
		iOpacity = atoi(npos->second.c_str());
	}
	
	//����
	string strText = "";
	npos = attrMap.find("txt");
	if (npos != attrMap.end())
	{
		strText = npos->second;
	}

	//����
	string strFontName = _curFontName;
	npos = attrMap.find("fn");
	if (npos != attrMap.end())
	{
		strFontName = npos->second;
	}
	
	//�����С
	float fontSize = _curFontSize;
	npos = attrMap.find("fs");
	if (npos != attrMap.end())
	{
		fontSize = atof(npos->second.c_str());
	}

	parseAndCreateText(pRichText, color, iOpacity, strText, strFontName, fontSize);
	return nullptr;
}

RichElementImage* RichTextCreator::createImageElement(tAttrMap attrMap)
{
	//��ɫ
	Color3B color = Color3B::WHITE;
	map<string, string>::iterator npos = attrMap.find("c");
	if (npos != attrMap.end())
	{
		color = transformColor(npos->second);
	}

	//͸����
	int iOpacity = 255;
	npos = attrMap.find("op");
	if (npos != attrMap.end())
	{
		iOpacity = atoi(npos->second.c_str());
	}

	//ͼƬ����
	string strFile = "";
	npos = attrMap.find("file");
	if (npos != attrMap.end())
	{
		strFile = npos->second;
	}

	RichElementImage* reImage = RichElementImage::create(cstTag, color, iOpacity, strFile);
	return reImage;
}

RichElementCustomNode* RichTextCreator::createButton(tAttrMap attrMap)
{
	//��ɫ
	Color3B color = Color3B::WHITE;

	//͸����
	int iButtonOpacity = 255;

	map<string, string>::iterator npos;
	//������ʾʱ��ͼƬ
	string strNormalFile = "";
	npos = attrMap.find("normal");
	if (npos != attrMap.end())
	{
		strNormalFile = npos->second;
	}

	//����ȥ��ʾ��ͼƬ
	string strPressFile = "";
	npos = attrMap.find("press");
	if (npos != attrMap.end())
	{
		strPressFile = npos->second;
	}

	//���͵��¼�����
	string strMsg = "customMsg";
	npos = attrMap.find("event");
	if (npos != attrMap.end())
	{
		strMsg = npos->second;
	}

	//���͵��¼�����
	string strUserData = "userData";
	npos = attrMap.find("data");
	if (npos != attrMap.end())
	{
		strUserData = npos->second;
	}

	//��ť���� 
	string strTitle = "";
	npos = attrMap.find("title");
	if (npos != attrMap.end())
	{
		strTitle = npos->second;
	}

	Button* button = Button::create(strNormalFile, strPressFile);
	if (!strTitle.empty())
	{
		button->setTitleText(strTitle);

		Color3B color = _curFontColor;
		npos = attrMap.find("c");
		if (npos != attrMap.end())
		{
			color = transformColor(npos->second);
		}
		button->setTitleColor(color);

		//����
		string strFontName = _curFontName;
		npos = attrMap.find("fn");
		if (npos != attrMap.end())
		{
			strFontName = npos->second;
		}
		button->setTitleFontName(strFontName);
		
		//�����С
		float fontSize = _curFontSize;
		npos = attrMap.find("fs");
		if (npos != attrMap.end())
		{
			fontSize = atof(npos->second.c_str());
		}
		button->setTitleFontSize(fontSize);
		
	}

	//�Ƿ����»���
	npos = attrMap.find("ulw"); 
	if (npos != attrMap.end())
	{	
		float lineWidth = atof(npos->second.c_str());
		npos = attrMap.find("ulc");
		Color4F	 color = Color4F::WHITE;
		if (npos != attrMap.end())
		{
			Color3B c3b = this->transformColor(npos->second);
			color.r = c3b.r / 255.0f;
			color.g = c3b.g / 255.0f;
			color.b = c3b.b / 255.0f;
			color.a = 1.0f;
		}

		auto bntSize = button->getCustomSize();
		DrawNodeEx* pDotLine = DrawNodeEx::create();
		pDotLine->setLineWidth(lineWidth);
		pDotLine->drawLine(Vec2(0, bntSize.height*0.02f), Vec2(bntSize.width, bntSize.height*0.02f), color);
		button->addChild(pDotLine, -1);
	}

	button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType eventType)
	{
		if (eventType == Widget::TouchEventType::ENDED)
		{
			EventRichText event(strMsg);
			event.setUserStringData(strUserData);
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}

	});

	RichElementCustomNode* recustom = RichElementCustomNode::create(cstTag, color, iButtonOpacity, button);
	return recustom;
}

RichElementCustomNode* RichTextCreator::createFrameAnimation(tAttrMap attrMap)
{
	tAttrMap::iterator npos;
	npos = attrMap.find("skin");	//ʹ�õ�����
	if (npos != attrMap.end())
	{
		_curAnimationSkinName = npos->second;
	}

	npos = attrMap.find("actjson"); //�����б�
	if (npos != attrMap.end())
	{
		_curAnimationActionName = npos->second;
	}

	int actionID = -1;
	npos = attrMap.find("actID");	//����ID
	if (npos != attrMap.end())
	{
		actionID = atoi(npos->second.c_str());
	}
	
	bool loop = true;
	npos = attrMap.find("loop");	//����֡ѭ��
	if (npos != attrMap.end())
	{
		loop = atoi(npos->second.c_str());
	}

	npos = attrMap.find("w");	//����֡�Ŀ�
	if (npos != attrMap.end())
	{
		_curAnimWidth = atof(npos->second.c_str());
	}

	npos = attrMap.find("h");	//����֡�ĸ�
	if (npos != attrMap.end())
	{
		_curAnimHeight = atof(npos->second.c_str());
	}

	XAnimateSprite* sprite = XAnimateSprite::create();
	sprite->setContentSize(Size(_curAnimWidth, _curAnimHeight));
	sprite->initWithActionFile(_curAnimationSkinName, _curAnimationActionName);
	sprite->playAction(actionID, loop);
	RichElementCustomNode* reNode = RichElementCustomNode::create(cstTag, Color3B::WHITE, 255, sprite);
	return reNode;
}


#pragma region string parse
Color3B RichTextCreator::transformColor(std::string strColor)
{
	Color3B color= Color3B::WHITE;
	size_t length = strColor.size();
	unsigned int intColor;
	if (length == 6)
	{
		sscanf(strColor.c_str(), "%x", &intColor);
		color.r = intColor >> 16 & 0xff;
		color.g = intColor >> 8 & 0xff;
		color.b = intColor & 0xff;
	}
	return color;
}

void RichTextCreator::parseKeyValue(const char* buffer, unsigned int size, tAttrMap& attrMap, RichText*  pRichText)
{
	char errormsg[256] = { 0 };
	std::string element;
	std::string key;
	char* p = (char*)buffer;
	bool bDiscard = false;

	for (int i = 0; i < size; i++)
	{
		switch (*p)
		{
		case DISCARD_TOKEN:
			if (i < size)
			{
				char c = *(p + 1);
				if (c == ATTR_KV_TOKEN)
				{
					element.push_back(c);
					i++; p++;
				}
				else
				{
					element.push_back(*p);
				}

			}
			break;

		case ATTR_KV_TOKEN:
			//HANDLE_DISCARD(bDiscard,element,*p)
			if (!element.empty())
			{
				if (key.empty())
				{
					key = element;
				}
				else
				{
					attrMap.insert(std::make_pair(key, element));
					key.clear();
				}
				element.clear();
			}
			else
			{
				sprintf(errormsg, "[attr] missing key of string \"%s\"", buffer);
				this->ErrorCallBack(errormsg, pRichText);
			}
			break;
		default:
			bDiscard = false;
			element.push_back(*p);
			break;
		}
		p++;
	}

	if (!element.empty())
	{
		if (!key.empty())
		{
			attrMap.insert(std::make_pair(key, element));
		}
		else
		{
			sprintf(errormsg, "[attr] key \"%s\" missing value of string \"%s\"", element.c_str(), buffer);
			this->ErrorCallBack(errormsg, pRichText);
		}
	}
}

void RichTextCreator::parseAttribute(const char* buffer, unsigned int size, tAttrMap& attrMap, RichText*  pRichText)
{
	std::string element;
	char* p = (char*)buffer;
	bool bDiscard = false;
	for (int i = 0; i < size; i++)
	{
		switch (*p)
		{
		case DISCARD_TOKEN:
			if (i < size)
			{
				char c = *(p + 1);
				if (c == ELEMENT_DELIM_TOKEN)
				{
					element.push_back(c);
					i++; p++;
				}
				else
				{
					element.push_back(*p);
				}

			}
			break;

		case ELEMENT_DELIM_TOKEN:
			if (!element.empty())
			{
				parseKeyValue(element.c_str(), element.length(), attrMap, pRichText);
				element.clear();
			}
			break;
		default:
			bDiscard = false;
			element.push_back(*p);
			break;
		}
		p++;
	}

	if (!element.empty())
	{
		parseKeyValue(element.c_str(), element.length(), attrMap, pRichText);
		element.clear();
	}
}

void RichTextCreator::parseBuffer(const char* buffer, unsigned int size, RichText*  pRichText)
{
	std::string element;
	tAttrMap attrMap;
	char errormsg[256] = { 0 };
	char* p = (char*)buffer;
	bool bIsOpen = false;			//�Ƿ�δ�ر��ַ�
	bool bDiscard = false;			//�Ƿ�ȡ����һ���ַ�

	for (int i = 0; i < size; i++)
	{
		switch (*p)
		{
		case DISCARD_TOKEN:
			if (i < size)
			{
				char c = *(p + 1);
				switch (c)
				{
				case DISCARD_TOKEN:
				case OPEN_TOKEN:
				case CLOSE_TOKEN:
					element.push_back(c);
					i++; p++;
					break;

				default:
					element.push_back(*p);
					break;
				}
			}
			break;

		case OPEN_TOKEN:
			if (!element.empty())
			{
				this->TextCallBack(element, pRichText);
				element.clear();
			}
			bIsOpen = true;
			break;

		case CLOSE_TOKEN:
			if (bIsOpen)
			{
				if (!element.empty())
				{
					parseAttribute(element.c_str(), element.length(), attrMap, pRichText);

					if (!attrMap.empty())
					{
						this->ElementCallBack(attrMap, pRichText);
						attrMap.clear();
					}
					else
					{
						sprintf(errormsg, "[parser] missing token \"%s\"", element.c_str());
						this->ErrorCallBack(errormsg, pRichText);
					}
					element.clear();
				}
				bIsOpen = false;
			}
			else
			{
				sprintf(errormsg, "[parser] missing token %c at %d", OPEN_TOKEN, i);
				this->ErrorCallBack(errormsg, pRichText);
				element.push_back(*p);
			}
			break;

		case ELEMENT_DELIM_TOKEN:
		case ATTR_KV_TOKEN:
			element.push_back(*p);
			break;

		default:
			bDiscard = false;
			element.push_back(*p);
			break;
		}
		p++;
	}

	if (bIsOpen)
	{
		sprintf(errormsg, "[parser] missing token %c ", CLOSE_TOKEN);
		this->ErrorCallBack(errormsg, pRichText);
	}

	if (!element.empty())
	{
		this->TextCallBack(element, pRichText);
	}
}
#pragma endregion


