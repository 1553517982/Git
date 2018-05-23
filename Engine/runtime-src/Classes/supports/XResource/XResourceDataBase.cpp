#include "XResourceDataBase.h"
#include "cocostudio/DictionaryHelper.h"
#include "XCommon.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"

USING_NS_CC;
#define _JsonHelper cocostudio::DictionaryHelper::getInstance()
XResouceGroup::XResouceGroup()
{

}

XResouceGroup::~XResouceGroup()
{
	for (auto it = m_resources.begin(); it != m_resources.end(); it++)
	{
		delete *it;
	}
}

tResourceDataVector* XResouceGroup::getResource()
{
	return &m_resources;
}

XResourceDataBase::XResourceDataBase()
{

}

XResourceDataBase::~XResourceDataBase()
{
}

bool XResourceDataBase::loadDependency(const std::string& filename)
{
	return loadConfig(filename);
}

bool XResourceDataBase::loadConfig(const std::string& filename)
{
	// 先清空列表
	m_dependencyGroups.clear();

	std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(filename);
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);

#ifdef RAYMOND_PACK_DEBUG
	// 弱智补充，json都被打包成一个文件了，所以真机版本要去拿那个文件
	CCLOG(" XResourceDataBase::loadConfig come here: %s %s", jsonpath.c_str(), contentStr.c_str());
	if (jsonpath.length() == 0 && contentStr.length() == 0)
	{
		char * pBuff = 0;
		unsigned int chunkSize = 0;
		if (!CNewLoader::Inst().SyncLoadFile(filename.c_str(), &pBuff, &chunkSize))
			return false;
		
		contentStr = std::string((const char*)pBuff, chunkSize);
	}
#endif

	bool ret = false;
	do {
		rapidjson::Document doc;
		doc.Parse<0>(contentStr.c_str());
		if (doc.HasParseError())
		{
			XLOGERROR("XResourceDataBase::loadConfig %s [error] %d", doc.GetParseError());
			break;
		}
		ret = true;
		rapidjson::Value& _root = doc;
		CC_BREAK_IF(!_root.IsObject());

		for (rapidjson::Value::MemberIterator itr = _root.MemberBegin(); itr != _root.MemberEnd(); ++itr)
		{
			const rapidjson::Value &_entry = itr->value;
			const char* name = itr->name.GetString();
			XResouceGroup* config = new XResouceGroup();

			if (_entry.IsArray())
			{
				int size = _entry.Size();
				for (int i = 0; i < size; i++)
				{
					const rapidjson::Value& item = _entry[i];
					XResouceData* data = new XResouceData();

					data->m_strFilename = _JsonHelper->getStringValue_json(item, "file", "");
					data->m_nType = _JsonHelper->getIntValue_json(item, "type", 0);
#ifdef _DEBUG
					XAssert(data->m_nType != 0, "XResourceData should not be type 0");
					if (data->m_nType == eResTypeImage)
					{
						XAssert(data->m_strFilename.find(".png") || 
								data->m_strFilename.find(".jpg") ||
								data->m_strFilename.find(".webp"),
								"XResourceData wrong type eResTypeImage");
					}
					else if (data->m_nType == eResTypePlist)
					{
						XAssert(data->m_strFilename.find(".plist"),"XResourceData wrong plist");
					}
					else if (data->m_nType == eResTypeZip)
					{
						//TODO
						XAssert(data->m_strFilename.find(".zip"), "XResourceData wrong zip");
					}
#endif // _DEBUG
					config->getResource()->push_back(data);
				}
			}
			setResourceGroup(name, config);
		}

	} while (0);
	return ret;
}

//tNameList* XResourceDataBase::getDependency(const std::string& filename)
//{
//	auto iter = m_dependencyMap.find(filename);
//	if (iter != m_dependencyMap.end())
//	{
//		return iter->second;
//	}
//	return NULL;
//}

XResouceGroup* XResourceDataBase::getResourceGroup(const std::string& filename)
{
	auto iter = m_dependencyGroups.find(filename);
	if (iter != m_dependencyGroups.end())
	{
		return iter->second;
	}
	return NULL;
}

void XResourceDataBase::setResourceGroup(const std::string& name, XResouceGroup* config)
{
	m_dependencyGroups.insert(std::make_pair(name, config));
}