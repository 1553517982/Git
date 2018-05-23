#ifndef __ZX_LOGIC_SCENE_H_
#define __ZX_LOGIC_SCENE_H_

#include "cocos2d.h"

class XParallaxNode;

USING_NS_CC;

/*
 ����������Ҫ����һ�������Լ�����Ϸ�������й���
 �����ֲ������Ϣ����ȡ����Թ��������Լ���һ�����������ࡣ
 �����������ص㣺
 -- ����������㣬�����㣬ʵ��㣬UI��
 -- ÿһ�㶼��һ��ZXMainPanel�����ڹ涨�õ���Ϣ�ɷ�����
 -- ���������ڴ�ŵ�ͼ
 -- ʵ������ڴ�����е���Ϸʵ��
 -- UI�����ڴ����ϷUI
 -- �ڳ�ʼ����ʱ�򣬶�ʵ�����ӽڵ�Ԥ��һ��1����1�εĻ���y���������
 -- ֪ͨ�ű��˳���Ȼ����Ҫ��retain��CC.Object�����ղ���
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
	// ��ȡ����
	static	XLogicScene*	sharedScene();
	
	// ��ȡ�����ڵ�
	XGameScene*				getSceneNode();
	
	Node*					getNode( int nIndex );

	// ��Ӱ���ڵ�
	//SpriteBatchNode*		ShadowNode() const { return m_pkShadowNode; }

	// ʵʱ��ʵ��y��������������
	//void					sort_entity_by_y_position(float dt);
	// �ƶ���ͷ(��ͼ����)
	void					moveCamera(int posX, int posY);


	void					moveCameraMap(int posX, int posY);

	Vec2					cameraMapPosition();

	//void					createShadowNode(const char* szName);
	// added by aXing on 2013-5-4
	// Ϊ������Ӧ��Ļ����������ӿڴ�С����
	void					setViewPortSize(int width, int height, float scale);

	void					_setViewPortSize(int width, int height, float scale);

	inline Size				getViewPortSize() { return m_default_camera_view_port; };

	inline Size				getViewPortVisibleSize() { return _camera_view_port; };

	float					getViewPortScale() const { return m_fViewPortScale; }

	//Node*					getSceneLayer(int layer);

	void					zoom(float fZoom){}// todo  ���벻ͨ�����ȼӸ������塣lyl 2015/04/14

	void					setCameraOffset(int x, int y);

	void					resetViewPortSize(int width, int height, float scale);

	virtual void			cleanup() override;

protected:
	// �ṹ�����ƶ�������
	// this
	//   m_pkSceneRoot
		//   m_pkGameScene
		//	 m_uiNode


	//Node*					m_sceneNode;			//�����
	//Node*					m_pkSceneUINode;		//����ر��ƶ��Ĳ�
	//Node*					m_pkShadowRoot;			//��Ӱ���������
	//Node*					m_entityNode;			//ʵ���
	//Node*					m_pkEffectRoot;			//��Ч��

	//XGameScene*			m_pkMapBase;			//�ر��������Ⱦ��
	//SpriteBatchNode*		m_pkShadowNode;			//��Ӱ���������Ⱦ��

	//������
	//Node*					m_pkSceneRoot;			//�������ڵ�

	//�������
	XGameScene*				m_pkSceneNode;
	//������
	Node*					m_pkUINode;
	Node*					m_pGuildNode;
	Node*					m_pTouchNode;

private:
	// ��Ӷ�ʱ���ʵ���ڵ��ķ���
	//void					_check_shield(float dt);
	// ���һ����ʱ��ʵ��ڵ�Ķ���������㷨
	//void					_init_entity_node_sort();

	//Node*					_createLayer(ParallaxNode* root, int flag,const Vec2& rate, const Vec2& offset);

	Size					_camera_view_port;
	float					m_fViewPortScale;
	Size					m_default_camera_view_port;
	Vec2					m_cameraOffset;
	Map<int, Node*>			m_sceneLayers;
};

#endif