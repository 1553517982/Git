#ifndef _X_SCENE_EFFECT_H_
#define _X_SCENE_EFFECT_H_

#include "cocostudio/DictionaryHelper.h"
#include "cocos2d.h"
#include "XSceneLayer.h"
#include "XSceneTileLayer.h"
class XLambda;

USING_NS_CC;
class XSceneTileLayerBase;

class XPosNode : public Node
{
	protected:
		XPosNode();
	public:
		
		virtual ~XPosNode();
		static XPosNode* create(const Rect& rect);
		virtual bool onTouchBegan(Touch *touch, Event *event);
		virtual void onTouchMoved(Touch *touch, Event *event);
		virtual void onTouchEnded(Touch *touch, Event *event);
		virtual void onTouchCancelled(Touch *touch, Event *event){};
		virtual bool isTouchInside(Touch * touch);
		virtual void initial(const Rect& rect);

		void setOnPosChange(std::function<Vec2(const Vec2&)> val) { m_onPosCallback = val; }
		
		void setVisibleName(const char* szName);

		virtual void changePosition(int x, int y);

		//void setPosChangeLambda(XLambda* pkLambda);

		bool getEnablePosChange() const { return m_bEnablePosChange; }
		void setEnablePosChange(bool val) { m_bEnablePosChange = val; }

		void setDrawColor(const Color4F& color);
	protected:
		std::function<Vec2(const Vec2&)>	m_onPosCallback;
		bool								m_bEnablePosChange;

protected:
		DrawNode*							m_pkDrawNode;
		Vec2								m_touchBeginPoint;
		Color4F								m_visibleColor;
};

class XSizeNode : public XPosNode
{
protected:
	XSizeNode();
public:
	virtual ~XSizeNode();
	static XSizeNode* create(const Rect& rect, const char* szName);
	virtual bool onTouchBegan(Touch *touch, Event *event)  override;
	virtual void onTouchMoved(Touch *touch, Event *event)  override;
	virtual void onTouchEnded(Touch *touch, Event *event)  override;
	virtual void onTouchCancelled(Touch *touch, Event *event) override {};
	virtual bool isTouchInside(Touch * touch)  override;
	virtual void initial(const Rect& rect) override;
	virtual void changePosition(int x, int y) override;
	void setOnRectChange(std::function<void(const Rect&)> val) { m_onRectCallback = val; }
	Vec2 changeSize(int widht, int height, bool isNotify = false);
	void setSizeChangeLambda(XLambda* pkLambda);
	bool getEnableSizeChange() const { if (m_pkPosNode) { return m_pkPosNode->getEnablePosChange(); } else { return false; }; }
	void setEnableSizeChange(bool val) { if (m_pkPosNode) m_pkPosNode->setEnablePosChange(val); }
	XPosNode* getPosNode() const { return m_pkPosNode; }
protected:
	std::function<void(Rect)>		m_onRectCallback;
	XPosNode*						m_pkPosNode;

	
};
class XSceneObjectGroup : public Ref
{
	protected:
		XSceneObjectGroup();
	public:
		enum SceneLayerTypes
		{
			eTileLayer,
			eBackground,
			eNode,
			eSortYNode
		};

		static XSceneObjectGroup* create();

		virtual ~XSceneObjectGroup();

		bool	load(const std::string& strTileJson, 
					 const std::string& strTileBasePath,
					 const cocos2d::Size& sceneSize,
					 bool bDebug);

		void	leaveMap();

		void	updateLayers(const Size& size, const Vec2& offset);

		void	setViewRadius(float sceneViewPow2);

		float	getViewRadius();

		void	setFixViewRadius(float sceneViewPow2);

		void	setLookAt(Vec2& p);

		void	setLayerWithID(int id, XSceneLayer* layer);

		XSceneLayer*	getLayer(int id);

		ValueVector		getLayerIDs();

		void	addToLayer(int id, XSceneObject* child, bool updateObjectMap);

		void	clearall(int flag);

		void	onPause();

		void	onResume();

		void setLayerVisible(int layerID, bool isVisible);

		void setDebugNode(Node* Node);

		void tickDebugVisible(float dt);

		cocos2d::ValueVector& getObjectKeys();

		//void setLayerParallax(char layerID, const Vec2& rate, const Vec2& offset);

		void cleanup();

		void updateCamera(bool force);

		void setPreservedLayerID(int id)
		{
			m_PreservedLayerIDs.insert(id);
		}

		ParallaxNode* getParallaxRoot() const { return m_pkParallaxRoot; }
		void setParallaxRoot(ParallaxNode* val) { m_pkParallaxRoot = val; }


	private:

		bool	addTriggerToScene(XSceneTrigger* trigger);

		bool	loadObject(rapidjson::Value& _objects, bool bDebug);

		bool	loadTiles(rapidjson::Value& _tiles,
			const std::string& strTileBasePath,
			const cocos2d::Size& sceneSize,
			bool bDebug);
		
		//bool	loadTriggers(rapidjson::Value& _objects, bool bDebug);

		Map<int, XSceneLayer*>				m_NodeLayers;
		//cocos2d::Vector<XSceneTrigger*>	m_Triggers;
		std::set<int>						m_PreservedLayerIDs;
		Vec2								m_kCameraLookAt;
		float								m_fSceneViewRadius;
		int									m_maxID;
		float								m_fFixSceneViewPow2;
		Node*								m_pDebugNode;
		DrawNode*							m_pVisibleRadiusNode;
		Size								m_kWindowSize;
		Vec2								m_kWindowCenter;
		bool								m_bCameraDirty;
		char								m_iMainLayer;
		ParallaxNode*						m_pkParallaxRoot;
		cocos2d::Vector<XGameTile*>			m_tilesPool;			// 地块池
		int									m_nUpdateFlag;
		//Node*								m_pkDebugDrawTriggersNode;

};
#endif