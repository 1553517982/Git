#include "XSceneObjectGroup.h"
#include "XSceneTileLayer.h"
#include "XSceneBackgroundLayer.h"
#include "XCommon.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "XGameScene.h"
#include "helpers/XLambda.h"
#include "helpers/XLambda.h"
#include "cocos/studio_ext/XCSBNode.h"

#define _JsonHelper cocostudio::DictionaryHelper::getInstance()

XPosNode::XPosNode() : m_bEnablePosChange(true), m_visibleColor(1.0,0.0,0.0,1.0)
{

}

XPosNode::~XPosNode()
{

}

XPosNode* XPosNode::create(const Rect& rect)
{
	XPosNode* node = new XPosNode();
	node->initial(rect);
	node->autorelease();
	return node;
	
}

void XPosNode::initial(const Rect& rect)
{
	setContentSize(rect.size);
	setPosition(rect.origin);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(XPosNode::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(XPosNode::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(XPosNode::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(XPosNode::onTouchCancelled, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	m_pkDrawNode = DrawNode::create();
	addChild(m_pkDrawNode);
	m_pkDrawNode->drawRect(Vec2(0,0),
						   Vec2(rect.size.width,rect.size.height),
						   m_visibleColor);
}

bool XPosNode::isTouchInside(Touch* touch)
{
	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	Rect bBox = getBoundingBox();
	return bBox.containsPoint(touchLocation);
}

bool XPosNode::onTouchBegan(Touch *touch, Event *event)
{
	if (!m_bEnablePosChange)
		return false;
	if (!isTouchInside(touch))
		return false;
	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	m_touchBeginPoint = convertToNodeSpace(touchLocation);
	return true;
}

void XPosNode::onTouchMoved(Touch *touch, Event *event)
{
	if (!m_bEnablePosChange)
		return;
	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	Vec2 pos = Vec2(touchLocation.x - m_touchBeginPoint.x, touchLocation.y - m_touchBeginPoint.y);
	changePosition(pos.x,pos.y);

}

void XPosNode::onTouchEnded(Touch *touch, Event *event)
{
	if (!m_bEnablePosChange)
		return;
}

void XPosNode::setVisibleName(const char* szName)
{
	setName(szName);
	auto oldlab = getChildByName("label");
	if (oldlab)
		oldlab->removeFromParent();

	auto lab = Label::create();
	lab->setString(szName);
	lab->setTextColor(Color4B::WHITE);
	lab->setSystemFontSize(16);
	lab->setAnchorPoint(Vec2(0, 0));
	lab->setPosition(Vec2(0., 32));
	lab->setName("label");
	addChild(lab);
}

void XPosNode::setDrawColor(const Color4F& color)
{
	m_visibleColor = color;
	if (m_pkDrawNode)
	{
		Size size =getContentSize();
		m_pkDrawNode->clear();
		m_pkDrawNode->drawRect(Vec2(0, 0),Vec2(size.width, size.height),color);
	}
}

void XPosNode::changePosition(int x, int y)
{
	
	if (m_onPosCallback)
	{
		Vec2 ret = m_onPosCallback(Vec2(x, y));
		setPosition(ret.x, ret.y);
	}
	else
	{
		setPosition(x, y);
	}
}

XSizeNode::XSizeNode()
{

}

XSizeNode::~XSizeNode()
{

}

XSizeNode* XSizeNode::create(const Rect& rect, const char* szName)
{
	XSizeNode* node = new XSizeNode();
	node->initial(rect);
	node->setName(szName);
	node->autorelease();
	return node;

}

Vec2 XSizeNode::changeSize(int widht, int height, bool isNotify)
{
	widht = MAX(widht, 32);
	height = MAX(height, 32);

	auto size = Size(widht, height);
	setContentSize(size);
	m_pkDrawNode->clear();
	m_pkDrawNode->drawRect(Vec2(0, 0),
	Vec2(size.width, size.height),
	Color4F(m_visibleColor));
	if (isNotify && m_onRectCallback)
	{
		Size c = getContentSize();
		m_onRectCallback(Rect(_position.x, _position.y, c.width, c.height));
	}
	return Vec2(widht, height);
}

void XSizeNode::changePosition(int x, int y)
{
	setPosition(x, y);
	if (m_onRectCallback)
	{
		Size c = getContentSize();
		m_onRectCallback(Rect(_position.x, _position.y, c.width, c.height));
	}
}

void XSizeNode::initial(const Rect& rect)
{
	XPosNode::initial(rect);
	m_pkPosNode = XPosNode::create(Rect(0, 0, 16, 16));
	addChild(m_pkPosNode);
	m_pkPosNode->setPosition(rect.size.width, rect.size.height);
	m_pkPosNode->setOnPosChange([=](const Vec2& vec)
	{
		return changeSize(vec.x, vec.y,true);
	});
}

void XSizeNode::setSizeChangeLambda(XLambda* pkLambda)
{
	auto ptr = shared_ref_ptr(pkLambda);
	m_onRectCallback = [=](const Rect& rect)
	{
		ptr->begin();
		ptr->pushFloat(rect.origin.x);
		ptr->pushFloat(rect.origin.y);
		ptr->pushFloat(rect.size.width);
		ptr->pushFloat(rect.size.height);
		ptr->invoke();
	};
}

bool XSizeNode::isTouchInside(Touch* touch)
{
	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	Rect bBox = getBoundingBox();
	return bBox.containsPoint(touchLocation);
}

bool XSizeNode::onTouchBegan(Touch *touch, Event *event)
{
	if (!m_bEnablePosChange)
		return false;

	if (!isTouchInside(touch))
		return false;

	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	m_touchBeginPoint = convertToNodeSpace(touchLocation);
	if (m_onRectCallback)
	{
		Size c = getContentSize();
		m_onRectCallback(Rect(_position.x, _position.y, c.width, c.height));
	}
	return true;
}

void XSizeNode::onTouchMoved(Touch *touch, Event *event)
{
	if (!m_bEnablePosChange)
		return;

	Vec2 touchLocation = touch->getLocation(); // Get the touch position
	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
	setPosition(Vec2(touchLocation.x - m_touchBeginPoint.x, touchLocation.y - m_touchBeginPoint.y));
	if (m_onRectCallback)
	{
		Size c = getContentSize();
		m_onRectCallback(Rect(_position.x, _position.y, c.width, c.height));
	}
}

void XSizeNode::onTouchEnded(Touch *touch, Event *event)
{
}

XSceneObjectGroup::XSceneObjectGroup() : 
	m_maxID(0), 
	m_fFixSceneViewPow2(0), 
	m_pDebugNode(NULL), 
	m_pVisibleRadiusNode(NULL),
	m_bCameraDirty(true),
	m_iMainLayer(0),
	m_pkParallaxRoot(nullptr),
	m_nUpdateFlag(XSceneLayer::eOpTiles | XSceneLayer::eOpObjects)
{
	XSceneTileLayer::setTilePool(&m_tilesPool);
	m_kWindowSize = CCDirector::getInstance()->getWinSize();
	m_kWindowCenter = Vec2(m_kWindowSize.width * 0.5, m_kWindowSize.height * 0.5);
}

XSceneObjectGroup :: ~XSceneObjectGroup() 
{
	m_pkParallaxRoot = nullptr;
	if (m_pVisibleRadiusNode)
	{
		Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(XSceneObjectGroup::tickDebugVisible), this);
	}
}

XSceneObjectGroup* XSceneObjectGroup::create()
{
	auto obj = new XSceneObjectGroup();
	obj->autorelease();
	return obj;
}

void XSceneObjectGroup::clearall(int flag)
{
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
	{
		it->second->clearall(flag);
	}
}

void XSceneObjectGroup::onPause()
{
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
	{
		it->second->onPause();
	}
}

void XSceneObjectGroup::onResume()
{
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
	{
		it->second->onResume();
	}
}

void XSceneObjectGroup::setLookAt(Vec2& cameraLookAt)
{
	if (m_kCameraLookAt.equals(cameraLookAt))
	{
		m_bCameraDirty = false;
		return;
	}
	m_kCameraLookAt = cameraLookAt;
	m_bCameraDirty = true;
}

void XSceneObjectGroup::setFixViewRadius(float sceneViewPow2)
{
	m_fFixSceneViewPow2 = sceneViewPow2;
	m_fSceneViewRadius = sceneViewPow2;
}

void XSceneObjectGroup::setViewRadius(float sceneViewPow2)
{
	if (m_fFixSceneViewPow2)
	{
		m_fSceneViewRadius = m_fFixSceneViewPow2;
	}
	else
	{
		m_fSceneViewRadius = sceneViewPow2;
	}
}

float XSceneObjectGroup::getViewRadius()
{
	return m_fSceneViewRadius;
}

void XSceneObjectGroup::updateCamera(bool force)
{
	if (m_bCameraDirty || force)
	{
		//统一计算每个layer的摄像机中心
		for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
		{
			auto layer = it->second;
			layer->updateCamera(m_kWindowCenter);
		}
		m_bCameraDirty = false;
	}
}

void XSceneObjectGroup::updateLayers(const Size& size, const Vec2& offset)
{
	
	//刷新所有的图层
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
	{
		auto layer = it->second;
		layer->visibleCheck(size, offset, m_fSceneViewRadius, m_nUpdateFlag);
	}
}

void XSceneObjectGroup::setLayerWithID(int id, XSceneLayer* layer)
{
	XAssert(m_NodeLayers.at(id) == nullptr, "XSceneObjectGroup::setLayerWithID [dup id]");
	m_NodeLayers.insert(id, layer);
}

XSceneLayer* XSceneObjectGroup::getLayer(int id)
{
	return m_NodeLayers.at(id);
}

ValueVector	XSceneObjectGroup::getLayerIDs()
{
	ValueVector IDS;
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
	{
		IDS.push_back(Value(it->first));
	}
	return IDS;
}

void XSceneObjectGroup::addToLayer(int id, XSceneObject* child, bool updateObjectMap)
{
	XSceneLayer* layer = m_NodeLayers.at(id);
	if (!layer)
	{
		XLOGERROR("XSceneObjectGroup::addToLayer %d", id);
		return;
	}
	switch (layer->getLayerType())
	{
		case eNode:
		case eTileLayer:
		case eBackground:
			layer->attach(child, child->getLayerZOrder(), child->getTag(), updateObjectMap);
		break;

		case eSortYNode:
			layer->attach(child, -(child->getPositionY() - child->getLayerZOrder()), child->getTag(), updateObjectMap);
			break;
	}
}

void XSceneObjectGroup::setDebugNode(Node* node)
{
	m_pDebugNode = node;
	if (m_pVisibleRadiusNode == NULL)
	{
		m_pVisibleRadiusNode = DrawNode::create();
		auto p = dynamic_cast<ParallaxNode*>(node);
		if (p)
			p->addChild(m_pVisibleRadiusNode, 0xffff, Vec2::ONE, Vec2::ZERO);
		else
			m_pDebugNode->addChild(m_pVisibleRadiusNode, 0xffff);
		Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(XSceneObjectGroup::tickDebugVisible), this,0.0,false);
	}
}

void XSceneObjectGroup::tickDebugVisible(float dt)
{
	if (m_pVisibleRadiusNode)
	{
		m_pVisibleRadiusNode->clear();
		auto layer = m_NodeLayers.at(m_iMainLayer);
		m_pVisibleRadiusNode->drawCircle(layer->cameraCenter(), m_fSceneViewRadius, 360, 32, false, Color4F(1, 1, 1, 1));
		auto _ct = layer->cameraCenter();
		auto _size = Director::getInstance()->getWinSize() * 0.5;
		m_pVisibleRadiusNode->drawRect(Vec2(_ct.x - _size.width, _ct.y - _size.height), Vec2(_ct.x + _size.width, _ct.y + _size.height), Color4F(1, 1, 0.5, 1));
	}
}

cocos2d::ValueVector& XSceneObjectGroup::getObjectKeys()
{
	static cocos2d::ValueVector s_objects;
	s_objects.clear();
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); it++)
	{
		auto layer = it->second;
		layer->getObjectKeys(s_objects);
	}
	return s_objects;
}


void XSceneObjectGroup::cleanup()
{
	XSceneTileLayer::setTilePool(nullptr);
	m_pkParallaxRoot = nullptr;
	m_NodeLayers.clear();
	//m_Triggers.clear();
}

void XSceneObjectGroup::setLayerVisible(int layerID, bool isVisible)
{
	auto layer = m_NodeLayers.at(layerID);
	layer->setVisible(isVisible);
}

bool XSceneObjectGroup::loadTiles(rapidjson::Value& _tiles,
								  const std::string& strTileBasePath,
								  const cocos2d::Size& sceneSize,
								  bool bDebug)
{
	bool ret = false;
	//m_maxID = 0;
	do {
		ret = true;
		char buf[256] = { 0 };
		std::string prefix = "";
		prefix = strTileBasePath +"/";

		for (rapidjson::Value::MemberIterator itr = _tiles.MemberBegin(); itr != _tiles.MemberEnd(); ++itr)
		{
			int layer_id = atoi(itr->name.GetString());
			rapidjson::Value &entry = itr->value;
			int type = _JsonHelper->getIntValue_json(entry, "type", 0);

			switch (type)
			{
				case eTileLayer:
				{
					//如果已经有了，就不重复创建了，比如基础layer
					XSceneTileLayer* layer = dynamic_cast<XSceneTileLayer*>(m_NodeLayers.at(layer_id));
					if (layer == nullptr)
					{
						layer = XSceneTileLayer::create();
						layer->setLayerType(XSceneObjectGroup::SceneLayerTypes::eTileLayer);
						setLayerWithID(layer_id, layer);
						layer->readLayer(entry, layer_id, m_pkParallaxRoot, prefix.c_str());
					}
					else
					{
						layer->readLayer(entry, layer_id, nullptr, prefix.c_str());
					}	
					layer->setup(strTileBasePath, sceneSize);
				}
				break;

				case eBackground:
				{
					XSceneBackgroundLayer* layer = dynamic_cast<XSceneBackgroundLayer*>(m_NodeLayers.at(layer_id));
					if (layer == nullptr)
					{
						//snprintf(buf, 255, "%s/%d/%s", imagePath.c_str(), layer_id, skyTex.c_str());
						layer = XSceneBackgroundLayer::create();
						layer->setLayerType(XSceneObjectGroup::SceneLayerTypes::eBackground);
						layer->readLayer(entry, layer_id, m_pkParallaxRoot, prefix.c_str());
						setLayerWithID(layer_id, layer);
					}
					else
					{
						XLOGERROR("there is only one background");
					}
				}
				break;
			default:
				break;
			}
		}
	} while (0);

	return ret;
}

void XSceneObjectGroup::leaveMap()
{
	//if (m_pkDebugDrawTriggersNode)
	//{
	//	m_pkDebugDrawTriggersNode->removeAllChildren();;
	//}
	//m_Triggers.clear();
	for (auto it = m_NodeLayers.begin(); it != m_NodeLayers.end(); /**/)
	{
		auto layer = it->second;
		//移除所有非固定Layer
		if (m_PreservedLayerIDs.find(it->first) == m_PreservedLayerIDs.end())
		{
			layer->removeFromParent();
			m_NodeLayers.erase(it++);
		}
		//清空所有固定layer的内容
		else
		{
			layer->clearall(XSceneLayer::eOpObjects | XSceneLayer::eOpTiles);
			//退出的时候，应该没有任何孩子还挂在上面，特效是有可能
			if (layer->getChildrenCount() > 0)
				XLOG("XSceneObjectGroup::leaveMap layer %d with %d child", it->first, layer->getChildrenCount());
			it++;
		}
	}
}

bool XSceneObjectGroup::load(const std::string& strMapJson,
	const std::string& strTileBasePath,
	const cocos2d::Size& sceneSize,
	bool bDebug)
{
	char * pData = 0;
	unsigned int nSize = 0;

	std::string strTmp = strMapJson;

	//int nPos = strMapJson.find(".json");
	//if (-1 == nPos)
	//	return false;
//	XLOG("SB!!1111 /n %s /n", strMapJson.c_str());
	//strTmp.replace(nPos, 5, ".jo");
	if (!CNewLoader::Inst().SyncLoadFile(strTmp.c_str(), &pData, &nSize))
		return false;
//	XLOG("SB!222 /n %s /n", strMapJson.c_str());
	std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(strMapJson);
//	XLOG("SB!333 /n %s /n", jsonpath.c_str());
	std::string contentStr;
	if (!jsonpath.empty())
		contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
	else if (pData == 0)
		return false;
	
	leaveMap();

//	XLOG("SB!4444 /n %s /n", contentStr.c_str());
	bool ret = false;
	m_maxID = 0;
	rapidjson::Document doc;
	if (pData != 0)
	{ 
//		XLOG("SB!!555 /n %s /n", pData);
		std::string temp = std::string((const char*)pData, nSize);
//		XLOG("WTF %s", temp.c_str());
		//doc.Parse<0>(pData);   xj 2017-4-10 这个错误百度了刚好有人一模一样，就是用 buffer来构造字符串时，必须把长度参数加上  http://blog.csdn.net/u012632851/article/details/51505522
		doc.Parse<0>(temp.c_str());
	}
	else
		doc.Parse<0>(contentStr.c_str());

	if (doc.HasParseError())
	{
		XLOGERROR("XSceneObjectGroup::load\n%s\n[error] %d", strMapJson.c_str(), doc.GetParseError());
		return false;
	}

	if (doc.HasMember("tiles"))
	{
		rapidjson::Value& _tiles = doc["tiles"];
		if (_tiles.IsObject())
		{
			loadTiles(_tiles, strTileBasePath, sceneSize, bDebug);
		}
	}

	/*rapidjson::Value& _objects = doc["objects"];
	CC_BREAK_IF(!_objects.IsArray());
	*/
	//if (doc.HasMember("objects"))
	//{
	//	rapidjson::Value& _objects = doc["objects"];
	//	if (_objects.IsArray())
	//	{
	//		loadObject(_objects, bDebug);
	//	}
	//}

	// 地图只做一层
	//XSceneTileLayer* layer = dynamic_cast<XSceneTileLayer*>( m_NodeLayers.at( 0 ) );
	//if (layer == nullptr)
	//{
	//	layer = XSceneTileLayer::create();
	//	layer->setLayerType(XSceneObjectGroup::SceneLayerTypes::eTileLayer);
	//	setLayerWithID(0, layer);
	//}
	//layer->setup(strTileBasePath, sceneSize);
	//layer->readLayer(pData, nSize, m_pkParallaxRoot, (strTileBasePath + "/").c_str());
	return true;
}
