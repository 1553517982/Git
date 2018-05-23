#include "FontWidthHelper.h"
#include "json/rapidjson.h"
//#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "cocos2d.h"


NS_CC_BEGIN
namespace ui
{
	FontWidthHelper::FontWidthHelper()
	{
		_defautConfig.clear();
		for (int i = 0; i < 128; ++i)
		{
			_defautConfig.push_back(1.0f);
		}
	}

	FontWidthHelper & FontWidthHelper::getInstance()
	{
		static FontWidthHelper inst;
		return inst;
	}

	bool FontWidthHelper::LoadConfig(const std::string & configFile, bool bReload /* = false*/)
	{
		/*
		rapidjson::Document doc;
		//todo 需要修改 fullPathForFilename多线程出现小概率奔溃
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(configFile);
		std::string strJson = FileUtils::getInstance()->getStringFromFile(fullPath);
		//end
		doc.Parse<0>(strJson.c_str());
		if (doc.HasParseError())
		{
			CCLOG("Parser FontWidthConfig Failed!");
			return false;
		}

		rapidjson::Value &fontName = doc["fontname"];
		rapidjson::Value &factorArray = doc["factor"];
		std::map<std::string, std::vector<float>>::iterator npos = _fontWidthConfig.find(fontName.GetString());
		if (npos == _fontWidthConfig.end() || bReload)
		{
			std::vector<float> configFactor;
			for (int i = 0; i < factorArray.Capacity(); ++i)
			{
				rapidjson::Value &factorValue = factorArray[i];
				configFactor.push_back(factorValue.GetDouble());
			}
			_fontWidthConfig[fontName.GetString()] = configFactor;
		}
		*/
		return true;
	}


	int FontWidthHelper::getSubStringByLength(const std::string &text, const std::string &fontName, int subLength, float fontSize)
	{
		int strCharLength = text.length();
		if (strCharLength <= 0)
		{
			return 0;
		}

		std::vector<float>& fontWidthVec = this->getFontWidthConfig(fontName);
		for (int i = 0; i < strCharLength;)
		{
			char ch = text.at(i);
			unsigned short u = this->getUTF8Len(ch);
			if (u >= 2)
			{
				subLength -= fontSize;
			}
			else
			{
				if (ch < 128 && ch >= 0)
				{
					subLength -= fontSize*fontWidthVec.at(ch);
				}
				else{
					subLength -= fontSize;
				}
			}

			if (subLength < 0)
			{
				return i;
			}

			i += u;
		}

		return strCharLength;
	}

	unsigned short FontWidthHelper::getUTF8Len(char arg)
	{
		unsigned short len = 1;
		for (int i = 0; i < 6; i++)
		{
			if (arg & 0x80)
				len++;
			else
			{
				if (i > 1)
					len -= 1;
				break;
			}
			arg <<= 1;
		}
		return len;
	}

	std::vector<float>& FontWidthHelper::getFontWidthConfig(const std::string &fontName)
	{
		std::map<std::string, std::vector<float>>::iterator npos = _fontWidthConfig.find(fontName);
		if (npos == _fontWidthConfig.end())
		{
			CCLOG("find fontwidth config:%s failed!", fontName.c_str());
			return _defautConfig;
		}

		return npos->second;
	}

	bool FontWidthHelper::saveFontWidthConfig(const std::string fontPath, const std::string &fontName, const std::string &savePath, const std::string &saveFileName)
	{
		//std::vector<float> config;
		//this->createFontWidthConfig(fontPath, fontName, config);
		//rapidjson::Document doc;
		//doc.SetObject();
		//rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
		//rapidjson::Value array(rapidjson::kArrayType);
		//for (std::vector<float>::iterator it = config.begin(); it != config.end(); ++it)
		//{
		//	array.PushBack(*it, allocator);
		//}

		//doc.AddMember("fontname", rapidjson::Value(fontName.c_str(), allocator), allocator);
		//doc.AddMember("factor", array, allocator);

		//rapidjson::StringBuffer  buffer;
		//rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		//doc.Accept(writer);
		//std::string path = CCFileUtils::getInstance()->getWritablePath();

		//std::string fullPath = savePath + "/" + saveFileName;
		//const char* out = buffer.GetString();

		//FILE* fp = fopen(fullPath.c_str(), "w+");
		//if (!fp)
		//{
		//	CCLOG("Save FontWidthConfig Failed!");
		//	return false;
		//}

		//fwrite(out, 1, strlen(out) + 1, fp);
		//fclose(fp);

		return false;
	}

	bool FontWidthHelper::createFontWidthConfig(const std::string &fontPath, const std::string &fontName, std::vector<float> &outVec)
	{
		outVec.clear();
		float fontSize = 100.0f;
		std::string resPath = fontPath + "\\" + fontName;
		auto fileExist = FileUtils::getInstance()->isFileExist(resPath);
		Label* textRenderer = nullptr;
		if (fileExist)
		{
			auto fullPath = FileUtils::getInstance()->fullPathForFilename(resPath);
			textRenderer = Label::createWithTTF("", fullPath, fontSize);
		}
		else
		{
			textRenderer = Label::createWithSystemFont("", fontName, fontSize);
		}

		for (int ch = 0; ch < 128; ++ch)
		{
			char buf[64];
			sprintf(buf, "%c%c%c%c%c", ch, ch, ch, ch, ch);
			textRenderer->setString(buf);
			outVec.push_back(textRenderer->getContentSize().width*0.2f / fontSize);
		}

		return true;
	}

	FontWidthHelper::~FontWidthHelper()
	{

	}

}

NS_CC_END