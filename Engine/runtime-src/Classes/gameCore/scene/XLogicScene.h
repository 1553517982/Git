#ifndef __ZX_LOGIC_SCENE_H_
#define __ZX_LOGIC_SCENE_H_

#include "cocos2d.h"

class XParallaxNode;

USING_NS_CC;

/*
 由于我们需要创建一个属于自己的游戏场景进行管理，
 包括分层管理，消息管理等。所以构建属于自己的一个场景管理类。
 它具有以下特点：
 -- 他将会分三层，场景层，实体层，UI层
 -- 每一层都是一个ZXMainPanel，用于规定好的消息派发机制
 -- 场景层用于存放地图
 -- 实体层用于存放所有的游戏实体
 -- UI层用于存放游戏UI
 -- 在初始化的时候，对实体层儿子节点预设一个1秒钟1次的基于y坐标的排序
 -- 通知脚本退出，然后需要对retain的CC.Object做回收操作
*/

class XGameScene;

class XLogicScene : public Scene
{
protected:
	XLogicScene();
public:
	virtual ~XLogicScene();

	enum XLogicLayers
	{
		eSceneLayer = 1,
		eUILayer,
		eGuild,
		eTouch,
	};

	bool					init();
	// 获取单例
	static	XLogicScene*	sharedScene();
	
	// 获取场景节点
	XGameScene*				getSceneNode();
	
	Node*					getNode( int nIndex );

	// 阴影根节点
	//SpriteBatchNode*		ShadowNode() const { return m_pkShadowNode; }

	// 实时对实体y坐标进行深度排序
	//void					sort_entity_by_y_position(float dt);
	// 移动镜头(地图坐标)
	void					moveCamera(int posX, int posY);


	void					moveCameraMap(int posX, int posY);

	Vec2					cameraMapPosition();

	//void					createShadowNode(const char* szName);
	// added by aXing on 2013-5-4
	// 为了自适应屏幕，添加期望视口大小设置
	void					setViewPortSize(int width, int height, float scale);

	void					_setViewPortSize(int width, int height, float scale);

	inline Size				getViewPortSize() { return m_default_camera_view_port; };

	inline Size				getViewPortVisibleSize() { return _camera_view_port; };

	float					getViewPortScale() const { return m_fViewPortScale; }

	//Node*					getSceneLayer(int layer);

	void					zoom(float fZoom){}// todo  编译不通过。先加个函数体。lyl 2015/04/14

	void					setCameraOffset(int x, int y);

	void					resetViewPortSize(int width, int height, float scale);

	virtual void			cleanup() override;

protected:
	// 结构，有移动的需求
	// this
	//   m_pkSceneRoot
		//   m_pkGameScene
		//	 m_uiNode


	//Node*					m_sceneNode;			//地面层
	//Node*					m_pkSceneUINode;		//跟随地表移动的层
	//Node*					m_pkShadowRoot;			//阴影层的真正根
	//Node*					m_entityNode;			//实体层
	//Node*					m_pkEffectRoot;			//特效层

	//XGameScene*			m_pkMapBase;			//地表的真正渲染体
	//SpriteBatchNode*		m_pkShadowNode;			//阴影层的真正渲染体

	//场景根
	//Node*					m_pkSceneRoot;			//场景根节点

	//场景结点
	XGameScene*				m_pkSceneNode;
	//界面结点
	Node*					m_pkUINode;
	Node*					m_pGuildNode;
	Node*					m_pTouchNode;

private:
	// 添加定时检查实体遮挡的方法
	//void					_check_shield(float dt);
	// 添加一个定时对实体节点的儿子排序的算法
	//void					_init_entity_node_sort();

	//Node*					_createLayer(ParallaxNode* root, int flag,const Vec2& rate, const Vec2& offset);

	Size					_camera_view_port;
	float					m_fViewPortScale;
	Size					m_default_camera_view_port;
	Vec2					m_cameraOffset;
	Map<int, Node*>			m_sceneLayers;
};

#endif