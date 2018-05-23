#include "XLogicScene.h"
#include "XGameScene.h"
USING_NS_CC;

static XLogicScene*	_instance;
const unsigned int		uShadowNumber = 64;



XLogicScene::XLogicScene() : 
	  m_pkSceneNode(NULL)
	, m_pkUINode(NULL)
	, _camera_view_port(Size(1280, 720))
	, m_cameraOffset(0,0)
	, m_fViewPortScale(1.0)

{

	//auto pkSceneRoot = ParallaxNode::create();

	/*
	//m_pkSceneUINode = Node::create();
	/*
	// Top Layer, a simple image
	auto cocosImage = Sprite::create("Hello.png");
	// scale the image (optional)
	//cocosImage->setScale(2.5f);
	// change the transform anchor point to 0,0 (optional)
	cocosImage->setAnchorPoint(Vec2(0, 0));
	pkSceneRoot->addChild(cocosImage, eSkyLevel, Vec2(0.4f, 0.5f), Vec2::ZERO);
	*/
	//m_pkSceneRoot = pkSceneRoot;

	//地表
	//m_uiNode = Node::create();
	//this->addChild(m_pkSceneRoot);
	m_pGuildNode = Node::create();
	m_pkUINode = Node::create();
	m_pkSceneNode = XGameScene::create();
	m_pTouchNode = Node::create();
	m_pkSceneNode->retain();
	//场景层
	this->addChild(m_pkSceneNode, eSceneLayer);
	//界面层
	this->addChild(m_pkUINode,eUILayer);

	this->addChild(m_pGuildNode, eGuild);
	this->addChild(m_pTouchNode, eTouch);	
}

XLogicScene::~XLogicScene()
{
	//m_sceneNode->release();
	//m_entityNode->release();
}

bool XLogicScene::init()
{
	bool bRet = false;
	do 
	{
		Director * pDirector = Director::getInstance();
		CC_BREAK_IF( ! (pDirector) );
		this->setContentSize(pDirector->getWinSize());
		// 然后添加一个定时排序算法
		//this->_init_entity_node_sort();
		// success
		bRet = true;
		/*
		auto sceneObjGroup = m_pkMapBase->getSceneObjects();

		//sceneObjGroup->setLayers(eUndergroundID,	m_undergroundNode, XSceneObjectGroup::eNode);
		sceneObjGroup->setLayers(eTileLayerID,		m_sceneNode, XSceneObjectGroup::eNode);
		sceneObjGroup->setLayers(eEntityLayerID,	m_entityNode, XSceneObjectGroup::eSortYNode);
		sceneObjGroup->setLayers(eEffectLayerID,	m_pkEffectRoot, XSceneObjectGroup::eNode);
		//sceneObjGroup->setLayers(eSkyLayerID,		m_pkSkyNode, XSceneObjectGroup::eNode);
		*/

	} while (0);
	return bRet;
}

XLogicScene* XLogicScene::sharedScene()
{
	if(!_instance)
	{
		int tmp1 = sizeof(Scene);
		int tmp2 = sizeof(XLogicScene);
		int tmp3 = sizeof(Node);
		_instance = new XLogicScene();
		//_instance->retain();
	//	auto test = &_instance->_navMesh;
		_instance->init();
		_instance->autorelease();
	}
	return _instance;
}



XGameScene* XLogicScene::getSceneNode()
{
	return m_pkSceneNode;
}

Node* XLogicScene::getNode( int nIndex )
{
	switch (nIndex)
	{
	case eSceneLayer:
		return m_pkSceneNode;
	case eUILayer:
		return m_pkUINode;
	case eGuild:
		return m_pGuildNode;
	case eTouch:
		return m_pTouchNode;
	default:
		return m_pkUINode;
	}
}

void XLogicScene::moveCameraMap(int posX, int posY)
{
	//posY += XGameScene::s_map_to_camera_offsetY;
	Vec2 p = Vec2(posX,posY);
	m_pkSceneNode->mapPosToGLPos(p);
	moveCamera(p.x,p.y);
}

Vec2 XLogicScene::cameraMapPosition()
{
	return m_pkSceneNode->cameraMapPosition();
}


void XLogicScene::moveCamera(int posX, int posY)
{
	posX += m_cameraOffset.x;
	posY += m_cameraOffset.y;
	Size	winSize			= getViewPortSize();
	float	halfWinWidth	= winSize.width  / 2;
	float	halfWinHeight	= winSize.height / 2;
	m_pkSceneNode->updateCameraInPixels(posX, posY);

	Vec2 UILayerMove = Vec2( (-posX + halfWinWidth),
									   (-posY + halfWinHeight));

	Vec2 LayerMove = Vec2(UILayerMove.x * m_fViewPortScale,
						  UILayerMove.y * m_fViewPortScale);
	
	
	//m_pkSeaNode->setPosition(LayerMove);
	m_pkSceneNode->setPosition(LayerMove);
	//m_pkSkyNode->setPosition(LayerMove);
								//逆操作
	//m_pkSceneUINode->setPosition(-UILayerMove.x,-UILayerMove.y);
}

/*
void XLogicScene::_init_entity_node_sort()
{
	// 尝试0.15秒做一次快速排序
	this->schedule(schedule_selector(XLogicScene::sort_entity_by_y_position), 0.15f);
	// 尝试0.15秒做一次遮挡判断
	this->schedule(schedule_selector(XLogicScene::_check_shield), 0.15f);
}
*/

/*
void XLogicScene::_check_shield(float dt)
{
	Vector<Node*>&	children = m_entityNode->getChildren();
	int				count	 = m_entityNode->getChildrenCount();
	for (int i = 0; i < count; i++)
	{
		Node* pNode = children.at(i);
		// LP TODO
		/*
		if(pNode)
		{
			unsigned int tile_x = (unsigned int)(pNode->m_x / XGameScene::s_logicTileWidth);// LOGIC_TILE_WIDTH);
			unsigned int tile_y = (unsigned int)(pNode->m_y / XGameScene::s_logicTileHeight);//LOGIC_TILE_HEIGHT);
			bool shield = XGameScene::sharedScene()->isShield(tile_x, tile_y);
			pNode->shieldEntity(shield);
		}
	}
}
*/

/*
void XLogicScene::sort_entity_by_y_position(float dt)
{
	if (m_entityNode->getChildrenCount() == 0)
	{
		return;
	}
	
	Vector<Node*>& vec = m_entityNode->getChildren();
	
	std::sort(vec.begin(), vec.end(), compareZOrder);
}

void XLogicScene :: createShadowNode(const char* szName)
{
	if(!m_pkShadowNode)
	{
		m_pkShadowNode = SpriteBatchNode::create(szName, uShadowNumber);
		m_pkShadowRoot->addChild(m_pkShadowNode, 0, 0);
		// LP TODO
		//ZXEntity::SetShadowWidth(pkData->width);
	}
}
*/

///////////////////////////////////////////////////////////
void XLogicScene::setViewPortSize(int width, int height, float scale)
{
	m_default_camera_view_port = Size(width, height);
	_setViewPortSize(width,height,scale);
}

void XLogicScene::_setViewPortSize(int width, int height, float scale)
{
	m_fViewPortScale = scale;
	_camera_view_port = Size(width, height);
	m_pkSceneNode->setScale(scale);
	m_pkSceneNode->setViewPortSize(width, height, scale);
}

void XLogicScene::setCameraOffset(int x, int y)
{
	m_cameraOffset.x = x;
	m_cameraOffset.y = y;
}

void XLogicScene::resetViewPortSize(int width, int height, float scale)
{
	setViewPortSize(width,height,scale);
}



void XLogicScene::cleanup()
{
	m_sceneLayers.clear();
	CC_SAFE_RELEASE_NULL(m_pkSceneNode);
	Scene::cleanup();
}