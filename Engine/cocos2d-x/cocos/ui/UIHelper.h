/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __UIHELPER_H__
#define __UIHELPER_H__

#include <string>
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */
namespace ui {
    
    class Widget;

/**
 * Helper class for traversing children in widget tree.
 * It also provides some helper functions for layout.
 */
class CC_GUI_DLL Helper
{
public:
    /**
     * Find a widget with a specific tag from root widget.
     * This search will be recursive throught all child widgets.
     * @param root      The be seached root widget.
     * @param tag       The widget tag.
     * @return Widget instance pointer.
     */
    static Widget* seekWidgetByTag(Widget* root, int tag);
    
    /**
     * Find a widget with a specific name from root widget.
     * This search will be recursive throught all child widgets.
     *
     * @param root      The be searched root widget.
     * @param name      The widget name.
     * @return Widget isntance pointer.
     */
    static Widget* seekWidgetByName(Widget* root, const std::string& name);
    
    /**
     * Find a widget with a specific action tag from root widget
     * This search will be recursive throught all child widgets.
     *@param root The be searched root widget.
     *@param tag The widget action's tag.
     *@return Widget instance pointer.
     */
    static Widget* seekActionWidgetByActionTag(Widget* root, int tag);
    
    /**
     * @brief Get a UTF8 substring from a std::string with a given start position and length
     *  Sample:  std::string str = "中国中国中国";  substr = getSubStringOfUTF8String(str,0,2) will = "中国"
     *
     * @param str The source string.
     * @param start The start position of the substring.
     * @param length The length of the substring in UTF8 count
     * @return a UTF8 substring
     * @js NA
     */
    static std::string getSubStringOfUTF8String(const std::string& str,
                                   std::string::size_type start,
                                   std::string::size_type length);

	//add by Hosea.Jiang at 2016/10/13 to help to preprocess the infomation of utf8 string
	/**
	*  @brief get the characters index in the UTF8 string.
	*  @param utf8 An UTF-8 encoded string.
	*  @param indexes of the characters,for output.
	*/
	static void getCharacterIndexInUTF8String(const std::string& utf8, std::vector<size_t>& indexes);

	//add by Hosea.Jiang at 2016/10/13 to help to preprocess the infomation of utf8 string
	/**
	*  @brief get the characters index in the UTF8 string.
	*  @param indexes of the characters.
	*  @param begin width pos of the character,for out.
	*  @param fontWidth font width
	*  @param hasHalfWidth whether or not use half width
	*/
	static void getBeginWidthByUTF8CharacterIndexes(const std::vector<size_t>& indexes, std::vector<float>& beginWidths, unsigned int fontWidth, bool hasHalfWidth);
    
    /**
     * Refresh object and it's children layout state
     *
     *@param rootNode   A Node* or Node* descendant instance pointer.
     *
     */
    static void doLayout(Node *rootNode);

    /**
     *  Change the active property of Layout's @see `LayoutComponent`
     *@param active A boolean value.
     */
    static void changeLayoutSystemActiveState(bool active);
    
    /**
     *@brief  restrict capInsetSize, when the capInsets's width is larger than the textureSize, it will restrict to 0,
     *        the height goes the same way as width.
     *@param  capInsets A user defined capInsets.
     *@param  textureSize  The size of a scale9enabled texture
     *@return a restricted capInset.
     */
    static Rect restrictCapInsetRect(const Rect& capInsets, const Size& textureSize);
};
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__CocoGUI__UISystem__) */
