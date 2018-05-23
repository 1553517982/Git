/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ui/UIRichText.h"

#include <vector>
#include <locale>

#include "tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"
#include "platform/CCApplication.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "base/ccUTF8.h"
#include "ui/UIHelper.h"

NS_CC_BEGIN

namespace ui {
bool RichElement::init(int tag, const Color3B &color, GLubyte opacity)
{
    _tag = tag;
    _color = color;
    _opacity = opacity;
    return true;
}
    
    
RichElementText* RichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize, uint32_t flags, const std::string& url)
{
    RichElementText* element = new (std::nothrow) RichElementText();
    if (element && element->init(tag, color, opacity, text, fontName, fontSize, flags, url))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize, uint32_t flags, const std::string& url)
{
    if (RichElement::init(tag, color, opacity))
    {
        _text = text;
        _fontName = fontName;
        _fontSize = fontSize;
        _flags = flags;
        _url = url;
        return true;
    }
    return false;
}

RichElementImage* RichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    RichElementImage* element = new (std::nothrow) RichElementImage();
    if (element && element->init(tag, color, opacity, filePath))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    if (RichElement::init(tag, color, opacity))
    {
        _filePath = filePath;
        _width = -1;
        _height = -1;
        return true;
    }
    return false;
}
void RichElementImage::setWidth(int width)
{
    _width = width;
}

void RichElementImage::setHeight(int height)
{
    _height = height;
}

RichElementCustomNode* RichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    RichElementCustomNode* element = new (std::nothrow) RichElementCustomNode();
    if (element && element->init(tag, color, opacity, customNode))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    if (RichElement::init(tag, color, opacity))
    {
        _customNode = customNode;
        _customNode->retain();
        return true;
    }
    return false;
}
    
RichElementNewLine* RichElementNewLine::create(int tag, const Color3B& color, GLubyte opacity)
{
    RichElementNewLine* element = new (std::nothrow) RichElementNewLine();
    if (element && element->init(tag, color, opacity))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
RichText::RichText()
    : _formatTextDirty(true)
    , _leftSpaceWidth(0.0f)
    , _verticalSpace(0.0f)
    , _wrapMode(WRAP_PER_WORD)
	, _richTextDimensions(Size::ZERO)
{
}
    
RichText::~RichText()
{
    _richElements.clear();
}
    
RichText* RichText::create()
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

RichText* RichText::createWithXML(const std::string& xml)
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->initWithXML(xml))
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool RichText::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

class MyXMLVisitor: public tinyxml2::XMLVisitor
{
    struct Attributes
    {
        std::string face;
        std::string url;
        float fontSize;
        Color3B color;
        bool hasColor;
        bool bold;
        bool italics;
        bool underline;
        bool strikethrough;

        void setColor(const Color3B& acolor)
        {
            color = acolor;
            hasColor = true;
        }
        Attributes()
        : bold(false)
        , italics(false)
        , underline(false)
        , strikethrough(false)
        , hasColor(false)
        , fontSize(-1)
        {
        }
    };

    std::vector<Attributes> _fontElements;

    RichText* _richText;

    Color3B getColor() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->hasColor)
                return i->color;
        }
        return Color3B::WHITE;
    }

    float getFontSize() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->fontSize != -1)
                return i->fontSize;
        }
        return 12;
    }

    std::string getFace() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->face.size() != 0)
                return i->face;
        }
        return "fonts/Marker Felt.ttf";
    }

    std::string getURL() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->url.size() != 0)
                return i->url;
        }
        return "";
    }

    bool getBold() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->bold)
                return true;
        }
        return false;
    }

    bool getItalics() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->italics)
                return true;
        }
        return false;
    }

    bool getUnderline() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->underline)
                return true;
        }
        return false;
    }

    bool getStrikethrough() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->strikethrough)
                return true;
        }
        return false;
    }

public:
    explicit MyXMLVisitor(RichText* richText)
    : _richText(richText)
    , _fontElements(20)
    {}
    virtual ~MyXMLVisitor() {}

    /// Visit an element.
    virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute )
    {
        auto elementName = element.Value();

        if (strcmp(elementName, "font") == 0)
        {
            // supported attributes:
            // size, color, align, face
            auto size = element.Attribute("size");
            auto color = element.Attribute("color");
            auto face = element.Attribute("face");

            Attributes attribs;
            if (size)
                attribs.fontSize = atof(size);
            if (color)
            {
                if (strlen(color) == 7)
                {
                    int r,g,b;
                    sscanf(color, "%*c%2x%2x%2x", &r, &g, &b);
                    attribs.setColor(Color3B(r,g,b));
                }
                else
                    attribs.setColor(Color3B::WHITE);
            }
            if (face)
                attribs.face = face;

            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "b") == 0)
        {
            // no supported attributes
            Attributes attribs;
            attribs.bold = 1;
            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "i") == 0)
        {
            // no supported attributes
            Attributes attribs;
            attribs.italics = 1;
            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "del") == 0)
        {
            // no supported attributes
            Attributes attribs;
            attribs.strikethrough = true;
            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "u") == 0)
        {
            // no supported attributes
            Attributes attribs;
            attribs.underline = true;
            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "small") == 0)
        {
            Attributes attribs;
            attribs.fontSize = getFontSize() * 0.8;
            _fontElements.push_back(attribs);
        }

        else if (strcmp(elementName, "big") == 0)
        {
            Attributes attribs;
            attribs.fontSize = getFontSize() * 1.25;
            _fontElements.push_back(attribs);
        }

        else if (strcmp(elementName, "img") == 0)
        {
            // supported attributes:
            // src, height, width
            auto src = element.Attribute("src");
            auto height = element.Attribute("height");
            auto width = element.Attribute("width");

            if (src) {
                auto elementNL = RichElementImage::create(0, getColor(), 255, src);

                if (height)
                    elementNL->setHeight(atoi(height));
                if (width)
                    elementNL->setWidth(atoi(width));
                
                _richText->pushBackElement(elementNL);
            }
        }
        else if (strcmp(elementName, "a") ==  0)
        {
            // supported attributes:
            Attributes attribs;
            auto href = element.Attribute("href");
            attribs.setColor(Color3B::BLUE);
            attribs.underline = true;
            attribs.url = href;
            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "br") == 0)
        {
            auto color = getColor();
            auto elementNL = RichElementNewLine::create(0, color, 255);
            _richText->pushBackElement(elementNL);
        }
        return true;
    }
    /// Visit an element.
    virtual bool VisitExit( const tinyxml2::XMLElement& element )
    {
        auto elementName = element.Value();
        if ((strcmp(elementName, "font") == 0) ||
            (strcmp(elementName, "i") == 0) ||
            (strcmp(elementName, "b") == 0) ||
            (strcmp(elementName, "del") == 0) ||
            (strcmp(elementName, "u") == 0) ||
            (strcmp(elementName, "small") == 0) ||
            (strcmp(elementName, "big") == 0) ||
            (strcmp(elementName, "a") == 0))
        {
            _fontElements.pop_back();
        }
        return true;
    }

    /// Visit a text node.
    virtual bool Visit(const tinyxml2::XMLText& text)
    {
        auto color = getColor();
        auto face = getFace();
        auto fontSize = getFontSize();
        auto italics = getItalics();
        auto underline = getUnderline();
        auto strikethrough = getStrikethrough();
        auto bold = getBold();
        auto url = getURL();

        uint32_t flags = 0;
        if (italics)
            flags |= RichElementText::ITALICS_FLAG;
        if (bold)
            flags |= RichElementText::BOLD_FLAG;
        if (underline)
            flags |= RichElementText::UNDERLINE_FLAG;
        if (strikethrough)
            flags |= RichElementText::STRIKETHROUGH_FLAG;
        if (url.size() > 0)
            flags |= RichElementText::URL_FLAG;

        auto element = RichElementText::create(0, color, 255, text.Value(), face, fontSize, flags, url);
        _richText->pushBackElement(element);
        return true;
    }
};

bool RichText::initWithXML(const std::string& origxml)
{
    if (Widget::init())
    {
        tinyxml2::XMLDocument document;

        // solves to issues:
        //  - creates defaults values
        //  - makes sure that the xml well formed and starts with an element
        auto xml = "<font face=\"Verdana\" size=\"12\" color=\"#ffffff\">" + origxml + "</font>";

        auto error = document.Parse(xml.c_str(), xml.length());
        if (error == tinyxml2::XML_SUCCESS)
        {
            MyXMLVisitor visitor(this);
            document.Accept(&visitor);
            return true;
        }
        CCLOG("cocos2d: UI::RichText: Error parsing xml: %s, %s", document.GetErrorStr1(), document.GetErrorStr2());
    }
    return false;
}
    
void RichText::initRenderer()
{
}

void RichText::insertElement(RichElement *element, int index)
{
    _richElements.insert(index, element);
    _formatTextDirty = true;
}
    
void RichText::pushBackElement(RichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
}
    
void RichText::removeElement(int index)
{
    _richElements.erase(index);
    _formatTextDirty = true;
}
    
void RichText::removeElement(RichElement *element)
{
    _richElements.eraseObject(element);
    _formatTextDirty = true;
}

RichText::WrapMode RichText::getWrapMode() const
{
    return _wrapMode;
}

void RichText::setWrapMode(RichText::WrapMode wrapMode)
{
    if (_wrapMode != wrapMode)
    {
        _wrapMode = wrapMode;
        _formatTextDirty = true;
    }
}

void RichText::formatText()
{
    if (_formatTextDirty)
    {
        this->removeAllProtectedChildren();
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        Label* label;
                        //if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
						if (elmtText->_fontName.length() > 0)	// isFileExist线程不安全，有隐患，有就可以认为有了
                        {
                             label = Label::createWithTTF(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            label = Label::createWithSystemFont(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        elementRenderer = label;
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        elementRenderer = Sprite::create(elmtImage->_filePath);
                        if (elementRenderer && (elmtImage->_height != -1 || elmtImage->_width != -1))
                        {
                            auto currentSize = elementRenderer->getContentSize();
                            if (elmtImage->_width != -1)
                                elementRenderer->setScaleX(elmtImage->_width / currentSize.width);
                            if (elmtImage->_height != -1)
                                elementRenderer->setScaleY(elmtImage->_height / currentSize.height);
                            elementRenderer->setContentSize(Size(currentSize.width * elementRenderer->getScaleX(),
                                                                 currentSize.height * elementRenderer->getScaleY()));
                        }
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        elementRenderer = elmtCustom->_customNode;
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        break;
                    }
                    default:
                        break;
                }

                if (elementRenderer)
                {
                    elementRenderer->setColor(element->_color);
                    elementRenderer->setOpacity(element->_opacity);
                    pushToContainer(elementRenderer);
                }
            }
        }
        else
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = static_cast<RichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
						//auto b = timeGetTime();
						handleTextRenderer(elmtText->_text, elmtText->_fontName, elmtText->_fontSize, elmtText->_color, elmtText->_opacity, elmtText->_flags, elmtText->_url);
						//auto e = timeGetTime();
						//CCLOG("cocos2d: handleTextRenderer cost:[%u]", e - b);
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath, elmtImage->_color, elmtImage->_opacity, elmtImage->_width, elmtImage->_height);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode);
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        formarRenderers();
        _formatTextDirty = false;
    }
}

static int getPrevWord(const std::string& text, int idx)
{
    // start from idx-1
    for (int i=idx-1; i>=0; --i)
    {
		if (!std::isalnum(text[i], std::locale()))
            return i;
    }
    return -1;
}

static bool isWrappable(const std::string& text)
{
    for (int i=0; i<text.length(); ++i)
    {
        if (!std::isalnum(text[i], std::locale()))
            return true;
    }
    return false;
}

//modify by Hosea.Jiang at 2016/10/13 for performance
//int RichText::findSplitPositionForWord(cocos2d::Label* label, const std::string& text)
//{
//	auto originalLeftSpaceWidth = _leftSpaceWidth + label->getContentSize().width;
//
//	bool startingNewLine = (_richTextDimensions.width == originalLeftSpaceWidth);
//	if (!isWrappable(text))
//	{
//		if (startingNewLine)
//			return (int)text.length();
//		return 0;
//	}
//
//	for (int idx = (int)text.size() - 1; idx >= 0;)
//	{
//		int newidx = getPrevWord(text, idx);
//		if (newidx >= 0)
//		{
//			idx = newidx;
//			auto leftStr = Helper::getSubStringOfUTF8String(text, 0, idx);
//			label->setString(leftStr);
//			if (label->getContentSize().width <= originalLeftSpaceWidth)
//				return idx;
//		}
//		else
//		{
//			if (startingNewLine)
//				return idx;
//			return 0;
//		}
//	}
//
//	// no spaces... return the original label + size
//	label->setString(text);
//	return (int)text.size();
//}
//
//
//int RichText::findSplitPositionForChar(cocos2d::Label* label, const std::string& text)
//{
//	float textRendererWidth = label->getContentSize().width;
//
//	float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
//	std::string curText = text;
//	size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);
//
//	// rough estimate
//	int leftLength = stringLength * (1.0f - overstepPercent);
//
//	// The adjustment of the new line position
//	auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;
//	auto leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
//	label->setString(leftStr);
//	auto leftWidth = label->getContentSize().width;
//	if (originalLeftSpaceWidth < leftWidth) {
//		// Have protruding
//		for (;;) {
//			leftLength--;
//			leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
//			label->setString(leftStr);
//			leftWidth = label->getContentSize().width;
//			if (leftWidth <= originalLeftSpaceWidth) {
//				break;
//			}
//			else if (leftLength <= 0) {
//				break;
//			}
//		}
//	}
//	else if (leftWidth < originalLeftSpaceWidth) {
//		// A wide margin
//		for (;;) {
//			leftLength++;
//			leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
//			label->setString(leftStr);
//			leftWidth = label->getContentSize().width;
//			if (originalLeftSpaceWidth < leftWidth) {
//				leftLength--;
//				break;
//			}
//			else if (stringLength <= leftLength) {
//				break;
//			}
//		}
//	}
//
//	if (leftLength < 0)
//		leftLength = (int)text.size() - 1;
//	return leftLength;
//}
//
//void RichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color, GLubyte opacity, uint32_t flags, const std::string& url)
//{
//	auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
//	Label* textRenderer = nullptr;
//	if (fileExist)
//	{
//		textRenderer = Label::createWithTTF(text, fontName, fontSize);
//	}
//	else
//	{
//		textRenderer = Label::createWithSystemFont(text, fontName, fontSize);
//	}
//
//	float textRendererWidth = textRenderer->getContentSize().width;
//	_leftSpaceWidth -= textRendererWidth;
//	if (_leftSpaceWidth < 0.0f)
//	{
//		int leftLength = 0;
//		if (_wrapMode == WRAP_PER_WORD)
//			leftLength = findSplitPositionForWord(textRenderer, text);
//		else
//			leftLength = findSplitPositionForChar(textRenderer, text);
//
//		//The minimum cut length is 1, otherwise will cause the infinite loop.
//		//        if (0 == leftLength) leftLength = 1;
//		std::string leftWords = Helper::getSubStringOfUTF8String(text, 0, leftLength);
//		int rightStart = leftLength;
//		if (std::isspace(text[rightStart], std::locale()))
//			rightStart++;
//		std::string cutWords = Helper::getSubStringOfUTF8String(text, rightStart, text.length() - leftLength);
//		if (leftLength > 0)
//		{
//			Label* leftRenderer = nullptr;
//			if (fileExist)
//			{
//				leftRenderer = Label::createWithTTF(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
//			}
//			else
//			{
//				leftRenderer = Label::createWithSystemFont(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
//			}
//			if (leftRenderer)
//			{
//				leftRenderer->setColor(color);
//				leftRenderer->setOpacity(opacity);
//				pushToContainer(leftRenderer);
//
//			}
//		}
//
//		addNewLine();
//		handleTextRenderer(cutWords, fontName, fontSize, color, opacity, flags, url);
//	}
//	else
//	{
//		textRenderer->setColor(color);
//		textRenderer->setOpacity(opacity);
//		pushToContainer(textRenderer);
//	}
//}

int RichText::findSplitPositionForWord(const std::string& text, size_t begin, const std::vector<size_t>& indexes, const std::vector<float> beginPositions)
{
	auto startPos = beginPositions[begin];
	float textRendererWidth = beginPositions[beginPositions.size() - 1] - startPos;
	auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;

    bool startingNewLine = (_richTextDimensions.width == originalLeftSpaceWidth);
    if (!isWrappable(text))
    {
        if (startingNewLine)
			return (int)indexes.size() - 1;
        return 0;
    }

	for (int idx = indexes.size() - 1; idx > begin;)
    {
		//int newidx = getPrevWord(text, idx);
		if (indexes[idx] - indexes[idx - 1] == 1 && isalnum(text[indexes[idx - 1]]))
		{
			idx--;
			continue;
		}
		if (beginPositions[idx] - startPos <= originalLeftSpaceWidth)
		{
			return idx - begin;
		}
		else
		{
			idx--;
		}
    }

	return (int)indexes.size() - 1 - begin;
}


int RichText::findSplitPositionForChar(const std::string& text, size_t begin, const std::vector<size_t>& indexes, const std::vector<float> beginPositions)
{
	auto startPos = beginPositions[begin];
	float textRendererWidth = beginPositions[beginPositions.size() - 1] - startPos;

    float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
	size_t stringLength = indexes.size() - 1 - begin;

    // rough estimate
    int leftLength = stringLength * (1.0f - overstepPercent);

    // The adjustment of the new line position
    auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;
	auto leftWidth = beginPositions[begin + leftLength] - startPos;
    if (originalLeftSpaceWidth < leftWidth) {
        // Have protruding
        for (;;) {
            leftLength--;
			leftWidth = beginPositions[begin + leftLength] - startPos;
            if (leftWidth <= originalLeftSpaceWidth) {
                break;
            }
            else if (leftLength <= 0) {
                break;
            }
        }
    }
    else if (leftWidth < originalLeftSpaceWidth) {
        // A wide margin
        for (;;) {
            leftLength++;
			leftWidth = beginPositions[begin + leftLength] - startPos;
            if (originalLeftSpaceWidth < leftWidth) {
                leftLength--;
                break;
            }
            else if (stringLength <= leftLength) {
                break;
            }
        }
    }

	if (leftLength < 0)
		leftLength = (int)indexes.size() - 1 - begin;
    return leftLength;
}

void RichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color, GLubyte opacity, uint32_t flags, const std::string& url)
{
	//modify by Hosea.Jiang at 2016/10/13 for performance
	//first,modify recursive mode to loop mode so I can do the preprocess for once
    // auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
	// isFileExist 线程不安全。且ttf规定是在文件夹下，所以此处只要有就是true
	bool fileExist = (fontName.c_str() != 0);

	//do the preprocess for once get the indexes and the widths for the character in a utf8 string
	std::vector<size_t> indexes;
	std::vector<float> beginPositions;
	//to cal the index of the character in a utf8 string once rather than cal that repeatedly by following steps
	Helper::getCharacterIndexInUTF8String(text, indexes);
	//to cal the width in logic code once rather than draw the text on dc repeatedly too find the properly character length
	Helper::getBeginWidthByUTF8CharacterIndexes(indexes, beginPositions, fontSize, fileExist);

	float textRendererWidth = beginPositions[beginPositions.size() - 1];

	int rightStart = 0;
	do
	{
		_leftSpaceWidth -= textRendererWidth;
		if (_leftSpaceWidth < 0.0f)
		{
			textRendererWidth -= (textRendererWidth + _leftSpaceWidth);
			int leftLength = 0;
			if (_wrapMode == WRAP_PER_WORD)
				leftLength = findSplitPositionForWord(text, rightStart, indexes, beginPositions);
			else
				leftLength = findSplitPositionForChar(text, rightStart, indexes, beginPositions);

			//The minimum cut length is 1, otherwise will cause the infinite loop.
			//        if (0 == leftLength) leftLength = 1
			auto start = indexes[rightStart];
			auto end = indexes[rightStart + leftLength];
			std::string leftWords = text.substr(start, end - start);
			rightStart += leftLength;
			if (leftLength > 0)
			{
				Label* leftRenderer = nullptr;
				if (fileExist)
				{
					leftRenderer = Label::createWithTTF(leftWords, fontName, fontSize);
				}
				else
				{
					leftRenderer = Label::createWithSystemFont(leftWords, fontName, fontSize);
				}
				if (leftRenderer)
				{
					leftRenderer->setColor(color);
					leftRenderer->setOpacity(opacity);
					pushToContainer(leftRenderer);

				}
			}

			addNewLine();
		}
		else
		{
			auto cutWords = text.substr(indexes[rightStart]);
			Label* textRenderer = nullptr;
			if (fileExist)
			{
				textRenderer = Label::createWithTTF(cutWords, fontName, fontSize);
			}
			else
			{
				textRenderer = Label::createWithSystemFont(cutWords, fontName, fontSize);
			}
			textRenderer->setColor(color);
			textRenderer->setOpacity(opacity);
			pushToContainer(textRenderer);
			break;
		}
	} while (true);
    
}
    
void RichText::handleImageRenderer(const std::string& filePath, const Color3B &color, GLubyte opacity, int width, int height)
{
    Sprite* imageRenderer = Sprite::create(filePath);
    if (imageRenderer)
    {
        auto currentSize = imageRenderer->getContentSize();
        if (width != -1)
            imageRenderer->setScaleX(width / currentSize.width);
        if (height != -1)
            imageRenderer->setScaleY(height / currentSize.height);
        imageRenderer->setContentSize(Size(currentSize.width * imageRenderer->getScaleX(),
                                             currentSize.height * imageRenderer->getScaleY()));

        handleCustomRenderer(imageRenderer);
    }
}

void RichText::handleCustomRenderer(cocos2d::Node *renderer)
{
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        pushToContainer(renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(renderer);
    }
}
    
void RichText::addNewLine()
{
    _leftSpaceWidth = _richTextDimensions.width;
    _elementRenders.push_back(new Vector<Node*>());
}
    
void RichText::formarRenderers()
{
    if (_ignoreSize || _richTextDimensions.width == 0)
    {
        float newContentSizeWidth = 0.0f;
        float nextPosY = 0.0f;
        for (auto& element: _elementRenders)
        {
            Vector<Node*>* row = element;
            float nextPosX = 0.0f;
            float maxY = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(l, 1);
                Size iSize = l->getContentSize();
                newContentSizeWidth += iSize.width;
                nextPosX += iSize.width;
                maxY = MAX(maxY, iSize.height);
            }
            nextPosY -= maxY;
        }
        this->setContentSize(Size(newContentSizeWidth, -nextPosY));
    }
    else
    {
        float newContentSizeHeight = 0.0f;
		float newContentSizeWidth = 0.0f;
        float *maxHeights = new (std::nothrow) float[_elementRenders.size()];
        
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float maxHeight = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                maxHeight = MAX(l->getContentSize().height, maxHeight);
            }
            maxHeights[i] = maxHeight;
            newContentSizeHeight += maxHeights[i];
        }

        float nextPosY = _customSize.height;
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float nextPosX = 0.0f;
            nextPosY -= (maxHeights[i] + _verticalSpace);
            
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(l, 1);
                nextPosX += l->getContentSize().width;
            }
			newContentSizeWidth = MAX(newContentSizeWidth, nextPosX);

        }
		_customSize = cocos2d::Size(newContentSizeWidth, newContentSizeHeight);
        delete [] maxHeights;
    }
    
    size_t length = _elementRenders.size();
    for (size_t i = 0; i<length; i++)
	{
        Vector<Node*>* l = _elementRenders[i];
        l->clear();
        delete l;
	}    
    _elementRenders.clear();
    
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
    updateContentSizeWithTextureSize(_contentSize);
}
    
void RichText::adaptRenderers()
{
    this->formatText();
}
    
void RichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}
    
void RichText::setVerticalSpace(float space)
{
    _verticalSpace = space;
}

void RichText::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize != ignore)
    {
        _formatTextDirty = true;
        Widget::ignoreContentAdaptWithSize(ignore);
    }
}
    
std::string RichText::getDescription() const
{
    return "RichText";
}

void RichText::setDimensions(float width, float height)
{
	if (_richTextDimensions.width != width || _richTextDimensions.height != height)
	{
		_richTextDimensions.width = width;
		_richTextDimensions.height = height;
        _formatTextDirty = true;
	}
}

}

NS_CC_END
