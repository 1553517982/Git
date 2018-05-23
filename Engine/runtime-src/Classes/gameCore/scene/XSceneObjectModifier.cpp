#include "XSceneObjectModifier.h"
#include "XCommon.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define _JsonHelper cocostudio::DictionaryHelper::getInstance();

XSceneObjectModifier::XSceneObjectModifier() : m_pkTarget(NULL)
{

}

XSceneObjectModifier::~XSceneObjectModifier()
{

}


bool XSceneObjectModifier::parse(const char* contentStr)
{
	bool ret = false;
	do {
		rapidjson::Document doc;
		doc.Parse<0>(contentStr);
		if (doc.HasParseError())
		{
			XLOGERROR("%s", doc.GetParseError());
			break;
		}
		ret = read(doc);
	} while (0);
	return ret;
}

bool XSceneObjectModifier::read(rapidjson::Value & json)
{
	if (!json.IsObject())
	{
		XLOGERROR("XSceneObject::read is no object");
		return false;
	}
	
	bool ret = false;
	do {
		if (!readValues(json))
			break;
	} while (0);
	return ret;
}

const char* XSceneObjectModifier::serialize(void)
{
	static std::string output;
	//write json
	rapidjson::Document document;
	document.SetObject();
	write(document, document.GetAllocator());
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	const char* ch = buffer.GetString();
	if (ch != NULL)
		output = ch;
	return output.c_str();
}
