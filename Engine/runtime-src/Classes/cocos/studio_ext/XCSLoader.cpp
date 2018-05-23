#include "XCSLoader.h"

#include "base/ObjectFactory.h"
#include "XCommon.h"
//#include "../../cocos/ui/CocosGUI.h"
//#include "CCActionTimelineCache.h"
//#include "CCActionTimeline.h"
//#include "CCActionTimelineNode.h"
//#include "../CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CSParseBinary_generated.h"

#include "cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "cocostudio/WidgetReader/NodeReaderDefine.h"

#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"

#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "cocostudio/WidgetReader/TextReader/TextReader.h"
#include "cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"
#include "cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "cocostudio/WidgetReader/SliderReader/SliderReader.h"
#include "cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "cocostudio/WidgetReader/PageViewReader/PageViewReader.h"
#include "cocostudio/WidgetReader/ListViewReader/ListViewReader.h"
#include "cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"
#include "cocostudio/WidgetReader/Node3DReader/Node3DReader.h"
//#include "cocostudio/WidgetReader/Sprite3DReader/Sprite3DReader.h"
#include "cocostudio/WidgetReader/UserCameraReader/UserCameraReader.h"
//#include "cocostudio/WidgetReader/Particle3DReader/Particle3DReader.h"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"

#include "cocostudio/FlatBuffersSerialize.h"

#include "cocostudio/WidgetCallBackHandlerProtocol.h"

#include "supports/XResource/XResourceUtils.h"
#include <fstream>

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
/* peterson */
using namespace flatbuffers;
/**/


#include "XActionTimelineCache.h"
//#include "XCSAnimtedRoot.h"

// CSLoader
static XCSLoader* _sharedCSLoader = nullptr;
unsigned char XCSLoader::m_uLoadingType = LOAD_NULL;

XRefHolder* XRefHolder::create()
{
	XRefHolder *sp = new (std::nothrow) XRefHolder();
	sp->autorelease();
	return sp;
}

XCSLoader* XCSLoader::getInstance()
{
	if (!_sharedCSLoader)
	{
		_sharedCSLoader = new XCSLoader();
		_sharedCSLoader->init();
	}

	return _sharedCSLoader;
}

void XCSLoader::destroyInstance()
{
	CC_SAFE_DELETE(_sharedCSLoader);
	XActionTimelineCache::destroyInstance();
}

XCSLoader::XCSLoader()
{
}

XCSLoader::~XCSLoader()
{
}

XCSBLoaderInfo* XCSLoader::loadCSBInfo(const std::string& filename,bool bCache)
{
	XCSBLoaderInfo* pkRet = m_csbFiles.at(filename);
	if (pkRet)
		return pkRet;
	else
	{
		pkRet = XCSBLoaderInfo::create();
		unsigned char* buf = 0;
#ifdef RAYMOND_PACK_DEBUG
		char * pBuff = 0;
		unsigned int chunkSize = 0;
		if (!CNewLoader::Inst().SyncLoadFile(filename.c_str(), &pBuff, &chunkSize))
			return NULL;

//		std::string temp = std::string((const char*)pBuff, chunkSize);
		buf = (unsigned char*)pBuff;
#else
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);

		if (fullPath.empty())
		{
			XLOGERROR("loadCSBInfo failed %s", filename.c_str());
			return NULL;
		}

		ssize_t size = 0;
		buf = FileUtils::getInstance()->getFileData(fullPath, "rb", &size);
#endif
		pkRet->setFileName(filename);
		pkRet->setData(_csBuildID,buf);
		if (bCache)
			m_csbFiles.insert(filename, pkRet);
		return pkRet;
	}
}

void XCSLoader::removeUnusedInfo()
{
	for (auto it = m_csbFiles.begin(); it != m_csbFiles.end(); /**/ )
	{
		if (it->second->getReferenceCount() == 1)
		{
			m_csbFiles.erase(it++);
		}
		else
		{
			it++;
		}
	}
}

void XCSLoader::loadPlistFromCSBInfo(XCSBLoaderInfo* info, XRefHolder* holder)
{
	XResourceDataBase* pkDataBase = XResourceUtils::getResourceDataBase();
	auto resgroup = pkDataBase->getResourceGroup(info->getFileName());
	if (!resgroup)
	{
		XLOGWARN("generating resourceGroup %s",info->getFileName());
		auto csparsebinary = info->getData();
		auto csBuildId = csparsebinary->version();
		if (csBuildId)
		{
			CCASSERT(strcmp(_csBuildID.c_str(), csBuildId->c_str()) == 0,
				StringUtils::format("%s%s%s%s%s%s%s%s%s%s",
				"The reader build id of your Cocos exported file(",
				csBuildId->c_str(),
				") and the reader build id in your Cocos2d-x(",
				_csBuildID.c_str(),
				") are not match.\n",
				"Please get the correct reader(build id ",
				csBuildId->c_str(),
				")from ",
				"http://www.cocos2d-x.org/filedown/cocos-reader",
				" and replace it in your Cocos2d-x").c_str());
		}

		// decode plist
		auto textures = csparsebinary->textures();
		int textureSize = csparsebinary->textures()->size();
		//CCLOG("textureSize = %d", textureSize);
		resgroup = new XResouceGroup();
		std::set<std::string> plists;
		for (int i = 0; i < textureSize; ++i)
		{
			const char* tn = textures->Get(i)->c_str();
			if (plists.find(tn) == plists.end())
			{
				XResouceData* data = new XResouceData();
				data->m_nType = XResouceDataTypes::eResTypePlist;
				data->m_strFilename = tn;
				resgroup->getResource()->push_back(data);
				plists.insert(tn);
			}
		}
		pkDataBase->setResourceGroup(info->getFileName(), resgroup);
	}

	auto res = resgroup->getResource();
	if (holder)
	{
		cocos2d::Vector<Ref*>* pRef = holder->getRefs();

		for (auto it = res->begin(); it != res->end(); it++)
		{
			if ((*it)->m_nType == XResouceDataTypes::eResTypePlist)
			{
				std::string plistName = (*it)->m_strFilename;
#ifdef COCOS2D_STUDIO_SB_PATH_FIX
				// 因为游戏一开始构架不好，使得cocos studio的资源路径和游戏运行路径差一层 
				plistName = "ui/" + plistName;
#endif
				SpriteFrameCache::getInstance()->addSpriteFramesWithFileEX(plistName, pRef);
			}
		}
	}
	else
	{
		for (auto it = res->begin(); it != res->end(); it++)
		{
			if ((*it)->m_nType == XResouceDataTypes::eResTypePlist)
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile((*it)->m_strFilename);
		}
	}
}


void XCSLoader::_loadDependency(const char* szFilename, XRefHolder* holder)
{
	//XResourceDataBase* pkDataBase = XResourceUtils::getResourceDataBase();
	//auto resgroup = pkDataBase->getResourceGroup(szFilename);
	//if (!resgroup)
	//{
	//	return;
	//}

	//auto res = resgroup->getResource();
	
}

Node* XCSLoader::nodeWithCSBInfo(XCSBLoaderInfo* pkInfo, const ccNodeLoadCallback &callback)
{
	auto csparsebinary = pkInfo->getData();
    Node* node = nodeWithFlatBuffers(csparsebinary->nodeTree(), callback);
    
    return node;
}

cocostudio::timeline::ActionTimeline* XCSLoader::timeLineWithCSBInfo(XCSBLoaderInfo* pkInfo)
{
	return XActionTimelineCache::getInstance()->loadAnimationActionWithData(pkInfo->getFileName(), (void*)(pkInfo->getData()));
}

XCSLoadRet* XCSLoader::loadCSB(const std::string& filename, bool bWithTimeline, bool bCache, const ccNodeLoadCallback &callback)
{
	auto info = loadCSBInfo(filename, bCache);
	if (!info)
		return nullptr;

	
	XRefHolder* holder = XRefHolder::create();
	loadPlistFromCSBInfo(info, holder);
	Node* node = nodeWithCSBInfo(info, callback);

	if (node == nullptr)
		return nullptr;

	if (bWithTimeline && !holder->getRefs()->empty())
	{
		node->setUserObject(holder);
	}

	XCSLoadRet* ret = XCSLoadRet::create(node);
	if (bWithTimeline)
	{
		auto timeline = timeLineWithCSBInfo(info);
		if (timeline)
		{
			ret->setTimeline(timeline);
			/*node->runAction(timeline);
			timeline->gotoFrameAndPause(0);*/
		}
	}

	return ret;
}

//bool XCSLoader::loadDependency(const std::string& filename, Node* node)
//{
//	XRefHolder* holder = XRefHolder::create();
//	if (node)
//	{
//		_loadDependency(filename.c_str(), holder);
//		if (!holder->getRefs()->empty())
//		{
//			node->setUserObject(holder);
//			return true;
//		}
//	}
//	return false;
//}
