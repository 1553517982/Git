#include "XSceneLayer.h"
#include <set>
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "XCommon.h"
#define _JsonHelper cocostudio::DictionaryHelper::getInstance()

XSceneLayer::XSceneLayer() : m_nLayerType(0), m_bDebug(false)
{
	m_ParallaxOffset.x = 0;
	m_ParallaxOffset.y = 0;
	m_ParallaxRatio.x = 1.0f;
	m_ParallaxRatio.y = 1.0f;
}

XSceneLayer::~XSceneLayer()
{

}

XSceneLayer * XSceneLayer::create()
{
	XSceneLayer * ret = new (std::nothrow) XSceneLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void XSceneLayer::updateCamera(const Vec2& center)
{
	m_kCameraCenterParallex = convertToNodeSpace(center);
	m_kCameraCenter = convertToNodeSpace(center);
}

void XSceneLayer::attach(XSceneObject* pkInput, int zOrder, int tag, bool updateObjectMap)
{
	if (!pkInput)
		return;

	auto pkNode = pkInput;
	if (updateObjectMap)
	{
		//添加到对象Map,如果没有被添加过的话
		auto pkNode = m_kObjectMap.at(pkInput->getObjectID());
		if (pkNode == nullptr)
		{
			pkNode = pkInput;
			m_kObjectMap.insert(pkNode->getObjectID(), pkNode);
		}
		else
		{
			XLOGINFO("XSceneLayer::attach dup %d", pkNode->getObjectID());
		}
	}

	//如果没有parent
	if (pkNode->getParent())
		return;

	addChild(pkNode, zOrder, tag);
}

void XSceneLayer::detach(XSceneObject* pkNode)
{
	removeChild(pkNode, true);
	m_kObjectMap.erase(pkNode->getObjectID());
}

void XSceneLayer::detach(int id)
{
	auto obj = m_kObjectMap.at(id);
	if (obj)
	{
		detach(obj);
	}
	else
	{
		XLOGERROR("try to detach %d from layer no found", id);
	}
}

//add by xianguiquan
void XSceneLayer::detach(XSceneObject* pkNode, bool isCleanUp)
{
	m_kObjectMap.erase(pkNode->getObjectID());
	removeChild(pkNode, isCleanUp);
}

void XSceneLayer::visibleCheck(const cocos2d::Size& screenSize, const cocos2d::Vec2& movement, float screenRadius, int flags)
{
	if (flags & eOpObjects)
	{
		updateObjects(screenRadius);
	}
}

void XSceneLayer::updateObjects(float radius)
{
	//刷新所有的节点
	for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
	{
		auto obj = it->second;
		bool ret = obj->visibilityCheck(m_kCameraCenter, radius);
	}
}

// add by xianguiquan
ValueVector	XSceneLayer::getObjectIDs()
{
	ValueVector IDS;
	for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
	{
		IDS.push_back(Value(it->first));
	}
	return IDS;
}


XSceneObject* XSceneLayer::getSceneObject(int id)
{
	return m_kObjectMap.at(id);
}

void XSceneLayer::clearall(int flag)
{
	if (flag & eOpObjects)
	{
		for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
		{
			it->second->leaveWorld(true);
		}
		m_kObjectMap.clear();
	}
}

void XSceneLayer::onPause()
{
	for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
	{
		it->second->leaveWorld();
	}
}

void XSceneLayer::onResume()
{

}

void XSceneLayer::cleanup()
{
	m_kObjectMap.clear();
	Node::cleanup();
}

void XSceneLayer::removeSceneObjectByType(int type)
{
	XAssert(false, "TODO");
	/*
	for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
	{
	auto obj = it->second;
	if (type == obj->getType())
	{
	obj->leaveWorld();
	}
	}
	*/
}

void XSceneLayer::removeSceneObjectByID(int id)
{
	auto obj = m_kObjectMap.at(id);
	if (obj)
	{
		obj->leaveWorld(true);
		m_kObjectMap.erase(id);
	}
}


//void XSceneLayer::readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix)
//{
//	//m_ParallaxOffset.x = _JsonHelper->getIntValueFromArray_json(entry, "offset", 0, 0);
//	//m_ParallaxOffset.y = _JsonHelper->getIntValueFromArray_json(entry, "offset", 1, 0);
//	//m_ParallaxRatio.x = _JsonHelper->getFloatValueFromArray_json(entry, "ratio", 0, 1.0f);
//	//m_ParallaxRatio.y = _JsonHelper->getFloatValueFromArray_json(entry, "ratio", 1, 1.0f);
//
//	//m_nLayerID = layerID;
//
//	//if (parent)
//	//{
//	//	parent->addChild(this, layerID, m_ParallaxRatio, m_ParallaxOffset);
//	//}
//}

void XSceneLayer::writeObjects(rapidjson::Value& jarray, rapidjson::Document& doc, rapidjson::Document::AllocatorType& alloc, int& oid)
{
	for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
	{
		auto obj = it->second;
		rapidjson::Value object(rapidjson::kObjectType);
		it->second->write(object, doc, oid);
		jarray.PushBack(object, alloc);
	}
}

void XSceneLayer::readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix)
{
	m_ParallaxOffset.x = _JsonHelper->getIntValueFromArray_json(entry, "offset", 0, 0);
	m_ParallaxOffset.y = _JsonHelper->getIntValueFromArray_json(entry, "offset", 1, 0);
	m_ParallaxRatio.x = _JsonHelper->getFloatValueFromArray_json(entry, "ratio", 0, 1.0f);
	m_ParallaxRatio.y = _JsonHelper->getFloatValueFromArray_json(entry, "ratio", 1, 1.0f);
	m_LayerSize.width = _JsonHelper->getIntValue_json(entry, "w", 0);
	m_LayerSize.height = _JsonHelper->getIntValue_json(entry, "h", 0);
	m_strResPath = _JsonHelper->getStringValue_json(entry, "resPath", prefix);
	m_strFileType = _JsonHelper->getStringValue_json(entry, "file", "png");

	m_nLayerID = layerID;

	if (parent)
	{
		parent->addChild(this, layerID, m_ParallaxRatio, m_ParallaxOffset);
	}
}

void XSceneLayer::writeLayer(rapidjson::Value& item, rapidjson::Document& doc, rapidjson::Document::AllocatorType& alloc)
{
	item.RemoveMember("offset");
	rapidjson::Value _offset(rapidjson::kArrayType);
	_offset.PushBack(int(m_ParallaxOffset.x), alloc);
	_offset.PushBack(int(m_ParallaxOffset.y), alloc);
	item.AddMember("offset", _offset, alloc);

	item.RemoveMember("ratio");
	rapidjson::Value _ratio(rapidjson::kArrayType);
	_ratio.PushBack(m_ParallaxRatio.x, alloc);
	_ratio.PushBack(m_ParallaxRatio.y, alloc);
	item.AddMember("ratio", _ratio, alloc);

	item.RemoveMember("w");
	item.AddMember("w", int(m_LayerSize.width), alloc);

	item.RemoveMember("h");
	item.AddMember("h", int(m_LayerSize.height), alloc);

	item.RemoveMember("resPath");
//	item.AddMember("resPath", rapidjson::Value(m_strResPath.c_str(), alloc), alloc);

	item.RemoveMember("file");
//	item.AddMember("file", rapidjson::Value(m_strFileType.c_str(), alloc), alloc);

	item.RemoveMember("type");
	item.AddMember("type", m_nLayerType, alloc);

}

void XSceneLayer::getObjectKeys(cocos2d::ValueVector& objects)
{
	for (auto it = m_kObjectMap.begin(); it != m_kObjectMap.end(); it++)
	{
		objects.push_back(Value(it->first));
	}
}

bool XSceneLayer::setParallax(const Vec2& ratio, const Vec2& offset)
{
	auto parent = dynamic_cast<ParallaxNode*>(getParent());
	if (!parent)
	{
		XLOGERROR("XSceneLayer::setParallax parrallParent is not ParallaxNode");
		return false;
	}
	m_ParallaxOffset = offset;
	m_ParallaxRatio = ratio;
	int zOrder = getLocalZOrder();
	setPosition(Vec2::ZERO);
	removeFromParentAndCleanup(false);
	parent->addChild(this, zOrder, ratio, offset);
	return true;
}