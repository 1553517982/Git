#ifndef _XSceneObject_H_
#define _XSceneObject_H_

#include "cocostudio/DictionaryHelper.h"
#include "cocos2d.h"
USING_NS_CC;

enum XSceneObjectTypes
{
	eSceneObjectInvisible = 0,
	//eSceneObjectParticle = 1,
	eSceneObjectCSB = 1
};

class XSceneObjectGroup;
class XSceneLayer;

class XSceneObject : public Node
{
	friend XSceneObjectGroup;
	friend XSceneLayer;
protected:
	XSceneObject();
public:
	
		
	virtual ~XSceneObject();

	static XSceneObject* create();

	/*!
	* \brief 解析一段json创建自己
	* \param const char * contentStr
	* \return bool
	*/
	bool parse(const char* contentStr);

	/*!
	* \brief 序列化成json
	* \return const char*
	*/
	const char* serialize();

	/*!
	* \brief 从rapidjson加载自己
	* \param rapidjson::Value & json
	* \return bool
	*/
	bool read(rapidjson::Value & json);

	/*!
	* \brief 写入json
	* \param rapidjson::Value & json
	* \param rapidjson::Document & document
	* \param int & id
	* \return void
	*/
	void write(rapidjson::Value& json, rapidjson::Document& document, int& id);

	/*!
	* \brief 可视化检测
	* \param const Vec2 & center
	* \param float radius
	* \return bool
	*/
	bool visibilityCheck(const Vec2& center, float radius);

	unsigned char getType() const { return m_uType; }
	void setType(unsigned char val) { m_uType = val; }

	int getLayerID() const { return m_iLayerID; }
	void setLayerID(int val);

	bool getAnimated() const { return m_bAnimated; }
	void setAnimated(bool val) { m_bAnimated = val; }

	const char* getFilename() const { return m_strFilename.c_str(); }
	void setFilename(const std::string& val) { m_strFilename = val; }

	float getBoundRadius() const { return m_fBoundRadius; }

	void setBoundRadius(float val) { m_fBoundRadius = val; }

	//void setRadiusBound(float val);

	cocos2d::Vec2 getBoundOffset() const { return m_kBoundOffset; }

	void setBoundOffset(cocos2d::Vec2 val) { m_kBoundOffset = val; }

	void setBoundOffsetX(float x) { m_kBoundOffset.x = x; }

	void setBoundOffsetY(float y) { m_kBoundOffset.y = y; }

	float getBoundOffsetX(void) { return m_kBoundOffset.x; }

	float getBoundOffsetY(void) { return m_kBoundOffset.y; }

	void wake();
	void sleep();

	int getObjectID() const { return m_nObjectID; }
	void setObjectID(int val) { m_nObjectID = val; }

	XSceneObjectGroup* getOwner() const { return m_pkOwner; }

	void setOwner(XSceneObjectGroup* val) { m_pkOwner = val; }

	cocos2d::Color4F getRadiusColor() const { return m_radiusColor; }
	void setRadiusColor(cocos2d::Color4F val) { m_radiusColor = val; }

	int getLayerZOrder() const { return m_nlayerZOrder; }

	void setLayerZOrder(int val);

	virtual void setScaleX(float scaleX) override;

	virtual void setScaleY(float scaleY) override;

	virtual void setRotation(float rotation) override;
	Node* updateDebug();
	void updateBoundRadius();
protected:
	bool leaveWorld(bool removeSelf = false);
	void resetFromConfig();
	bool enterWorld();
	
	void createParticle();
	void createCSB();

	Vec2					m_kBoundOffset;		//可视球偏移
	float					m_fBoundRadius;		//可视球半径
	float					m_fBoundRadiusWorld;//可视球半径
	unsigned char			m_uType;			//类型
	int						m_iLayerID;			//层次ID
	bool					m_bAnimated;		//是否支持动画
	Node*					m_pNode;			//节点
	std::string				m_strFilename;		//输入文件
	Color4F					m_radiusColor;

	DrawNode*				m_pRadiusNode;
	DrawNode*				m_pRectNode;
	int						m_nObjectID;
	int						m_nlayerZOrder;

	bool					m_bIsSleep;
	Node*					m_pkClickAble;
	XSceneObjectGroup*		m_pkOwner;


};

class XSceneTrigger : public Ref
{
protected:
	XSceneTrigger() :m_nTag(-1)				{		};
public:
	virtual ~XSceneTrigger()				{		};
	const Rect& getBoundingBox() const { return m_kBoundingBox; }
	void setBoundingBox(const Rect& val) { m_kBoundingBox = val; }

	const std::string& getData() const { return m_strData; }
	void setData(const std::string& val) { m_strData = val; }

	const int getTag() const { return m_nTag; }
	void setTag(int val) { m_nTag = val; }

	int getID() const { return m_nTID; }
	void setID(int val) { m_nTID = val; }

	const char* getName() const { return m_strName.c_str(); }
	void setName(const std::string& val) { m_strName = val; }

	bool read(rapidjson::Value & json);

	void write(rapidjson::Value& json, rapidjson::Document& document);

	static XSceneTrigger* create();
protected:
	Rect				m_kBoundingBox;
	std::string			m_strData;
	std::string			m_strName;

	int					m_nTag;
	int					m_nTID;
};
#endif