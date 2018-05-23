#ifndef __FONTWIDTHHELPER_H__
#define __FONTWIDTHHELPER_H__

#include "base/CCRef.h"
#include "ui/GUIExport.h"
#include <vector>
#include <map>

NS_CC_BEGIN

namespace ui
{
	class  CC_GUI_DLL FontWidthHelper : public Ref
	{
	public:
		static FontWidthHelper & getInstance();
		bool LoadConfig(const std::string & configFile, bool bReload = false);
		int getSubStringByLength(const std::string &text, const std::string &fontName, int subLength, float fontSize);
		bool saveFontWidthConfig(const std::string fontPath, const std::string &fontName, const std::string &savePath, const std::string &saveFileName);
	protected:
		unsigned short getUTF8Len(char arg);
		std::vector<float>& getFontWidthConfig(const std::string &fontName);
		bool createFontWidthConfig(const std::string &fontPath, const std::string &fontName, std::vector<float> &outVec);

	private:
		FontWidthHelper();
		~FontWidthHelper();

	private:
		std::map<std::string, std::vector<float>> _fontWidthConfig;
		std::vector<float> _defautConfig;
	};
}
NS_CC_END
#endif