#ifndef _XSceneLayer_H_
#define _XSceneLayer_H_
#include "cocos2d.h"
#include "scene/XSceneObject.h"
#include "cocostudio/DictionaryHelper.h"
USING_NS_CC;

class XSceneLayer : public Node
{
protected:
	XSceneLayer();
public:
	enum eSceneLayerOperationFlag
	{
		eOpTiles = 0x1,
		eOpObjects = 0x2
	};
	virtual ~XSceneLayer();

	static XSceneLayer* create();
	void updateCamera(const Vec2& center);
	void updateObjects(float radius);
	
	virtual void visibleCheck(const cocos2d::Size& screenSize,
							  const cocos2d::Vec2& movement,
							  float screenRadius,
							  int flags);

	virtual void clearall(int flag);

	virtual void onPause();

	virtual void onResume();


//	virtual void readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix);

	virtual void readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix);

	virtual void writeLayer(rapidjson::Value& jarray, rapidjson::Document& doc, rapidjson::Document::AllocatorType& alloc);

	virtual void writeObjects(rapidjson::Value& jarray, rapidjson::Document& doc, rapidjson::Document::AllocatorType& alloc, int& oid);

	/**
	* Stops all running actions and schedulers
	*/
	virtual void cleanup() override;

	void getObjectKeys(cocos2d::ValueVector& objects);

	void removeSceneObjectByType(int type);

	void removeSceneObjectByID(int id);

	void attach(XSceneObject* pkNode, int zOrder, int tag, bool updateObjectMap);
	void detach(XSceneObject* pkNode);
	void detach(int id);
	XSceneObject* getSceneObject(int id);

	//add by xianguiquan
	ValueVector	getObjectIDs();
	void detach(XSceneObject* pkNode, bool isCleanUp);

	const cocos2d::Vec2& cameraCenter() const { return m_kCameraCenter; }

	void setLayerType(int type)		{ m_nLayerType = type; }

	int	 getLayerType()				{ return m_nLayerType; }

	virtual bool setParallax(const Vec2& ratio, const Vec2& offset);

	Vec2 getParallaxOffset()
	{
		return m_ParallaxOffset;
	}

	Vec2 getParallaxRatio()
	{
		return m_ParallaxRatio;
	}

	std::string getFileType() const { return m_strFileType; }

	void setFileType(std::string val) { m_strFileType = val; }


	std::string getResPath() const { return m_strResPath; }
	void setResPath(std::string val) { m_strResPath = val; }

	Size getLayerSize() const { return m_LayerSize;  }

protected:
	int							m_nLayerType;
	Map<int, XSceneObject*>		m_kObjectMap;
	Vec2						m_kCameraCenter;
	Vec2						m_kCameraCenterParallex;
	bool						m_bDebug;
	int							m_nLayerID;

	Vec2						m_ParallaxOffset;
	Vec2						m_ParallaxRatio;
	Size						m_LayerSize;
	std::string					m_strResPath;
	std::string					m_strFileType;

};
#endif