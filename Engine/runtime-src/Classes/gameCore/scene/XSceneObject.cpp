#include "XSceneObject.h"
#include "XSceneObjectGroup.h"
#include "XCommon.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

// LP TODO 
USING_NS_CC;
#define _JsonHelper cocostudio::DictionaryHelper::getInstance();
#define _OBJRADIUS 32
#define _REAL_OBJRADIUS _OBJRADIUS
XSceneObject::XSceneObject() :  m_pNode(NULL), 
								m_fBoundRadius(_REAL_OBJRADIUS),
								m_fBoundRadiusWorld(_REAL_OBJRADIUS),
							    m_uType(eSceneObjectInvisible),
								m_pRadiusNode(NULL),
								m_pRectNode(NULL),
								m_nObjectID(0),
								m_pkOwner(NULL),
								m_bIsSleep(true),
								m_pkClickAble(NULL),
								m_nlayerZOrder(0)
{
}

XSceneObject::~XSceneObject()
{

}

XSceneObject * XSceneObject::create()
{
	XSceneObject * ret = new (std::nothrow) XSceneObject();
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

bool XSceneObject::parse(const char* contentStr)
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

bool XSceneObject::read(rapidjson::Value & json)
{/*
	if (!json.IsObject())
	{
	XLOGERROR("XSceneObject::read is no object");
	return false;
	}
	auto jsonHelper = _JsonHelper;
	bool ret = false;
	do {
	m_nObjectID = jsonHelper->getIntValue_json(json, "id", 0);

	Vec2 p;
	p.x = jsonHelper->getFloatValueFromArray_json(json, "transfrom", 0, 0.0f);
	p.y = jsonHelper->getFloatValueFromArray_json(json, "transfrom", 1, 0.0f);
	setPosition(p);
	m_nlayerZOrder = jsonHelper->getFloatValueFromArray_json(json, "transfrom", 2, 0.0f);
	setScaleX(jsonHelper->getFloatValueFromArray_json(json, "transfrom", 3, 1.0f));
	setScaleY(jsonHelper->getFloatValueFromArray_json(json, "transfrom", 4, 1.0f));
	setRotation(jsonHelper->getFloatValueFromArray_json(json, "transfrom",5, 0.0f));


	m_kBoundOffset.x = jsonHelper->getFloatValueFromArray_json(json, "bound", 0, 0.0f);
	m_kBoundOffset.y = jsonHelper->getFloatValueFromArray_json(json, "bound", 1, 0.0f);
	m_fBoundRadius = jsonHelper->getFloatValueFromArray_json(json, "bound", 2, _REAL_OBJRADIUS);

	m_uType = jsonHelper->getIntValue_json(json, "type", eSceneObjectInvisible);
	m_iLayerID = jsonHelper->getIntValue_json(json, "layer", 0);
	m_bAnimated = jsonHelper->getBooleanValue_json(json, "anim", false);

	const char* file = jsonHelper->getStringValue_json(json, "file");
	if (file)
	{
	m_strFilename = file;
	}
	else
	{
	m_uType = eSceneObjectInvisible;
	}
	updateBoundRadius();
	#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	const char* name = jsonHelper->getStringValue_json(json, "name");
	if (name)
	{
	setName(name);
	}
	#endif
	} while (0);
	return ret;*/
	return false;
}

const char* XSceneObject::serialize(void)
{
	static std::string output;
	//write json
	rapidjson::Document document;
	document.SetObject();
	int oid = 0;
	write(document, document, oid);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	const char* ch =  buffer.GetString();
	if (ch != NULL)
		output = ch;
	return output.c_str();
}

void XSceneObject::write(rapidjson::Value& json, rapidjson::Document& document, int& oid)
{
	//rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	///////////////////////////////
	//m_nObjectID = oid;
	//oid++;
	//////////////////////////////

	//json.AddMember("id", m_nObjectID, allocator);
	//
	///////////////////////////////////////////////
	//{
	//	rapidjson::Value _array(rapidjson::kArrayType);
	//	_array.PushBack(_position.x, allocator);
	//	_array.PushBack(_position.y, allocator);
	//	_array.PushBack(m_nlayerZOrder, allocator);
	//	_array.PushBack(_scaleX, allocator);
	//	_array.PushBack(_scaleY, allocator);
	//	_array.PushBack(getRotation(), allocator);
	//	json.AddMember("transfrom", _array, allocator);

	//}
	///////////////////////////////////////////////


	///////////////////////////////////////////////
	//{
	//	rapidjson::Value _array(rapidjson::kArrayType);
	//	_array.PushBack(m_kBoundOffset.x, allocator);
	//	_array.PushBack(m_kBoundOffset.y, allocator);
	//	_array.PushBack(m_fBoundRadius, allocator);
	//	json.AddMember("bound", _array, allocator);
	//}
	///////////////////////////////////////////////

	//json.AddMember("type", m_uType, allocator);
	//json.AddMember("layer", m_iLayerID, allocator);
	//json.AddMember("anim", m_bAnimated, allocator);
	//json.AddMember("file", rapidjson::Value(m_strFilename.c_str(),allocator), allocator);
	//json.AddMember("name", rapidjson::Value(_name.c_str(),allocator), allocator);

	/////////////////////////////////////////////
	//{
	//	rapidjson::Value _array(rapidjson::kArrayType);
	//	_array.PushBack(m_parallaxRatio.x, allocator);
	//	_array.PushBack(m_parallaxRatio.y, allocator);
	//	_array.PushBack(m_positionOffset.x, allocator);
	//	_array.PushBack(m_positionOffset.y, allocator);
	//	json.AddMember("parallax", _array, allocator);
	//}
	/////////////////////////////////////////////

}

bool XSceneObject::visibilityCheck(const Vec2& center, float radius)
{
	auto realPos = _position + m_kBoundOffset;
	Vec2 dstVec = (realPos - center);
	float dst = dstVec.getLength();
	//float dstsqr = dstVec.getLength();
	bool ret = false;
	if (dst < (radius + m_fBoundRadiusWorld))
	{
		ret = true;
		enterWorld();
	}
	else
	{
		leaveWorld();
	}
	return ret;
}

bool XSceneObject::leaveWorld(bool removeSelf)
{
	//是否已经处于睡眠状态
	if (m_bIsSleep)
		return false;

	// 移除显示节点
	if (m_pNode)
	{
		m_pNode->removeFromParent();
		m_pNode = NULL;
	}

	//如果是编辑模式，仅仅是隐藏自己，无需移除
	if (m_pRadiusNode)
	{
		if (removeSelf)
			removeFromParent();
		// 只是隐藏自己
		//setVisible(false);
		// 切换到睡眠状态
		m_bIsSleep = true;
		return false;
	}
	//如果是运行模式，整个移除自己
	else
	{
		removeFromParent();
		// 切换到睡眠状态
		m_bIsSleep = true;
		//需要加到根节点
		return false;
	}
}

bool XSceneObject::enterWorld()
{
	//是否已经是激活状态
	if (!m_bIsSleep)
		return true;

	//创建渲染体
	switch (m_uType)
	{
		case eSceneObjectInvisible:
			break;

		case eSceneObjectCSB:
			createCSB();
			break;
	}
	
	//处于睡眠状态
	m_bIsSleep = false;

	//如果处于编辑状态
	if (m_pRadiusNode)
	{
		//从跟上面移除自己
		//setVisible(true);
		//无需重新添加到图层
		return true;
	}
	else
	{
		setVisible(true);
		//需要重新添加到图层
		//if (getParent())
		//{
		//	XLOGERROR("visibilityCheck should have no parent");
		//	return true;
		//}
		//m_pkOwner->addToLayer(m_iLayerID, this, false);
		return true;
	}
	
}

void XSceneObject::createParticle()
{
	XLOGERROR("don't need createParticle");
	//XAssert(m_pNode == nullptr, "XSceneObject::createParticle m_pNode != nullptr");
	//ParticleSystemQuad* par = ParticleSystemQuad::create(m_strFilename);
	//par->setPositionType(ParticleSystem::PositionType::RELATIVE);
	//m_pNode = par;
	//addChild(m_pNode);
}

void XSceneObject::createCSB()
{
//	XAssert(m_pNode == nullptr, "XSceneObject::createCSB m_pNode != nullptr");
//	XCSBNode* node = XCSBNode::create();
//	XAsyncLoadOption pkOption;
//	pkOption.m_filename = m_strFilename;
//	pkOption.m_priority = Priority::TEXTUTRE;
//	pkOption.m_callback = [=](const XAsyncLoaderRet* ret)
//	{
//		if (ret->ret() == XAsyncLoaderCode::eOK)
//		{
//			node->setVisible(true);
//			node->load(m_strFilename, m_bAnimated);
//#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
//			if (node)
//			{
//				m_bAnimated = node->getTimeLine() != nullptr;
//				node->gotoFrameAndPlay(0, true);
//			}
//#endif
//		}
//	};
//	node->setVisible(false);
//	node->loadAsync(&pkOption, m_bAnimated);
//	m_pNode = node;
//	addChild(m_pNode);
}

void XSceneObject::wake()
{
	enterWorld();
}

void XSceneObject::sleep()
{
	leaveWorld();
}

Node* XSceneObject::updateDebug()
{
//	m_fBoundRadiusWorld = m_fBoundRadius * MAX(abs(_scaleX), abs(_scaleY));
//	if (m_pRectNode == NULL)
//	{
//		m_pRectNode = DrawNode::create();
//		float rect_size = _OBJRADIUS * 0.5;
//		float rect_full_size = _OBJRADIUS; 
//		//m_pRectNode->setPosition(-rect_size, -rect_size);
//		m_pRectNode->clear();
//		m_pRectNode->drawRect(Vec2(-rect_size, -rect_size), Vec2(rect_size, rect_size), Color4F(1, 1, 0, 1));
//		//m_pRectNode->setContentSize(Size(rect_full_size, rect_full_size));
//		if (m_pkClickAble == NULL)
//		{
//			m_pkClickAble = cocos2d::ui::Widget::create();
//			m_pkClickAble->setContentSize(Size(rect_full_size, rect_full_size));
//			//m_pkClickAble->setAnchorPoint(Vec2(0, 0));
//		}
//		addChild(m_pRectNode, 254);
//		m_pRectNode->addChild(m_pkClickAble);
//	}
//
//	if (m_pRadiusNode == nullptr)
//	{
//		m_pRadiusNode = DrawNode::create();
//		addChild(m_pRadiusNode, 255);
//	}
//	m_pRadiusNode->clear();
//	m_pRadiusNode->drawCircle(m_kBoundOffset, m_fBoundRadiusWorld, 360, 32, false, m_radiusColor);
//
//	Node* child = m_pRectNode->getChildByTag(0xffff);
//	LabelTTF* pkNameLabel = nullptr;
//	if (!child)
//	{
//		pkNameLabel = LabelTTF::create();
//		m_pRectNode->addChild(pkNameLabel, 1, 0xffff);
//	}
//	else
//	{
//		pkNameLabel = dynamic_cast<LabelTTF*>(child);
//	}
//	
//	if (pkNameLabel)
//		pkNameLabel->setString(getName());
//	
//
//	float inverseScaleX = 1.0 / getScaleX();
//	float inverseScaleY = 1.0 / getScaleY();
//	float inverseRotation = -getRotation();
//
//	m_pRadiusNode->setScaleX(inverseScaleX);
//	m_pRadiusNode->setScaleY(inverseScaleY);
//	m_pRadiusNode->setRotation(inverseRotation);
//
//	m_pRectNode->setScaleX(inverseScaleX);
//	m_pRectNode->setScaleY(inverseScaleY);
//	m_pRectNode->setRotation(inverseRotation);
//
//	m_pkClickAble->setRotation(inverseRotation);
//	return m_pkClickAble;
	return 0;
}

void XSceneObject::setLayerID(int val)
{
	if (_parent == NULL)
	{
		m_iLayerID = val;
		m_pkOwner->addToLayer(val, this, true);
	}
	else
	{
		XAssert(_referenceCount > 1,"XSceneObject setLayerID ref count error");
		XSceneLayer* layer = dynamic_cast<XSceneLayer*>(_parent);
		if (layer)
		{
			retain();
			layer->detach(this, false);
			m_iLayerID = val;
			m_pkOwner->addToLayer(val, this, true);
			release();
		}
	}
}


void XSceneObject::setScaleX(float scaleX)
{
	Node::setScaleX(scaleX);
	updateBoundRadius();
}

void XSceneObject::setScaleY(float scaleY)
{
	Node::setScaleY(scaleY);
	updateBoundRadius();
}

void XSceneObject::setRotation(float rotation)
{
	Node::setRotation(rotation);
}

void XSceneObject::updateBoundRadius()
{
	m_fBoundRadiusWorld = m_fBoundRadius * MAX(abs(_scaleX), abs(_scaleY));
}

void XSceneObject::setLayerZOrder(int val)
{ 
	m_nlayerZOrder = val;
	if (_parent)
	{
		_parent->reorderChild(this, m_nlayerZOrder);
	}
}

XSceneTrigger* XSceneTrigger::create()
{
	auto p = new XSceneTrigger();
	p->autorelease();
	return p;
}

bool XSceneTrigger::read(rapidjson::Value & json)
{
	auto jsonHelper = _JsonHelper;

	m_nTID = jsonHelper->getIntValue_json(json, "id", 0);

	m_kBoundingBox.origin.x = jsonHelper->getIntValueFromArray_json(json, "rect", 0, 0.0f);
	m_kBoundingBox.origin.y = jsonHelper->getIntValueFromArray_json(json, "rect", 1, 0.0f);
	m_kBoundingBox.size.width = jsonHelper->getIntValueFromArray_json(json, "rect", 2, 0.0f);
	m_kBoundingBox.size.height = jsonHelper->getIntValueFromArray_json(json, "rect", 3, 0.0f);
	m_strData = jsonHelper->getStringValue_json(json, "data","");
	m_strName = jsonHelper->getStringValue_json(json, "name","");
	m_nTag = jsonHelper->getIntValue_json(json, "tag");

	return true;
}

void XSceneTrigger::write(rapidjson::Value& json, rapidjson::Document& document)
{
	//rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	//json.AddMember("id", m_nTID, allocator);
	///////////////////////////////////////////////
	//{
	//	rapidjson::Value _array(rapidjson::kArrayType);
	//	_array.PushBack(int(m_kBoundingBox.origin.x), allocator);
	//	_array.PushBack(int(m_kBoundingBox.origin.y), allocator);
	//	_array.PushBack(int(m_kBoundingBox.size.width), allocator);
	//	_array.PushBack(int(m_kBoundingBox.size.height), allocator);
	//	json.AddMember("rect", _array, allocator);
	//}
	//json.AddMember("data", rapidjson::Value(m_strData.c_str(), allocator), allocator);
	//json.AddMember("name", rapidjson::Value(m_strName.c_str(), allocator), allocator);
	//json.AddMember("tag", m_nTag, allocator);
	//return;
}