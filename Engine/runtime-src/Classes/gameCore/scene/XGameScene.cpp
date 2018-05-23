
#include "XGameScene.h"
#include "cocos2d.h"
#include <math.h>
#include "pathfinding/astar.h"
#include "pathfinding/BresenhamLine.h"
#include "XGameTile.h"
#include "XLogicScene.h"
#include "gameCore/common/CommonFun.h"
#include "scene/XSceneTileLayer.h"
#include "XCommon.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"

using namespace cocos2d;
using namespace bresenhamline;


#define CAMERA_OFFSET_Y 48

int XGameScene::s_gameSceneTileWidth	= GAME_SCENE_TILE_WIDTH;
int XGameScene::s_gameSceneTileHeight	= GAME_SCENE_TILE_HEIGHT;
int XGameScene::s_logicTileWidth		= LOGIC_TILE_WIDTH;
int XGameScene::s_logicTileHeight		= LOGIC_TILE_HEIGHT;
float XGameScene::s_viewPortOverWinWidth = 1.0;
float XGameScene::s_viewPortOverWinHeight = 1.0;

#if(WEBP_SUPPORT == 1)
std::string XGameScene::_strCheckTextureName = "nopack/check.png";
#else
std::string XGameScene::_strCheckTextureName = "nopack/check.png";
#endif

//map_pos ����,���������׼��������������ǽ��¡�
float XGameScene::s_map_to_camera_offsetY = 0;

static float s_viewWinWidthPow2 = 1.0;

// LP TODO 
static Node* g_pkEntityRoot = NULL;

//static Texture2D*   g_CheckTexture = NULL;

static Texture2D*	  g_pMinimapTexture = NULL;

XGameScene::XGameScene()
:isDirty_(false)
, isShowTiles_(false)
, isShowTilesProp_(false)
, m_pSceneObjects(NULL)
, m_bMapBoundCheck(true)
//, m_pkTileMovable(nullptr)
, m_pBaseLayer(nullptr)
//, m_pOverLayer(nullptr)
	//,m_pkDebugVisibleRect(NULL)
{
	//Size viewSize = XLogicScene::sharedScene()->getViewPortSize();
	//float  halfViewWidth = viewSize.width / 2;
	//camera_center_ = Vec2(viewSize.width / 2, viewSize.height / 2);
	//camera_offset_ = Vec2(0,0);
	paStar_ = new AStar();
	isInit = false;
	//g_pkEntityRoot = XLogicScene::sharedScene()->getEntityNode();
	//g_pkEntityRoot->retain();
	//g_CheckTexture = Director::getInstance()->getTextureCache()->addImage(_strCheckTextureName.c_str());
	//Texture2D::TexParams texParams = { GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT };
	//g_CheckTexture->setTexParameters(texParams);
	//g_CheckTexture->retain();
	m_pSceneObjects = XSceneObjectGroup::create();
	m_pSceneObjects->retain();
}

XGameScene* XGameScene::create()
{
	XGameScene * ret = new (std::nothrow) XGameScene();
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

bool XGameScene::init()
{
	if (!Node::init())
		return false;

	schedule(schedule_selector(XGameScene::updateDirty));
	camera_center_ = Vec2(0,0);
	camera_offset_ = Vec2(0, 0);
	s_viewWinWidthPow2 = 1.0;

	m_pBaseLayer = Node::create();
	
	//������
	auto tileNode	= XSceneTileLayer::create();
	auto entityNode = XSceneLayer::create();
	//m_pOverLayer = Node::create();

	m_sceneNodes.resize(eLayerCount);
	m_sceneNodes[eTileLayerID] = tileNode;
	m_sceneNodes[eEntityLayerID] = entityNode;

	for (int i = 0; i < eLayerCount; i++)
		m_pBaseLayer->addChild(m_sceneNodes[i], i, i);

	//m_pBaseLayer->addChild(tileNode, eMainLayerZOrders::eZOrderTiles, eLayerSceneObjectGroupID::eTileLayerID);
	//m_pBaseLayer->addChild(entityNode, eMainLayerZOrders::eZOrderEntity, eLayerSceneObjectGroupID::eEntityLayerID);

	//m_sceneNodes.insert(eLayerSceneObjectGroupID::eTileLayerID, tileNode);
	//m_sceneNodes.insert(eLayerSceneObjectGroupID::eEntityLayerID, entityNode);
	//m_sceneNodes.insert(eLayerSceneObjectGroupID::eOverLayerID, m_pOverLayer);
	
	//���û���tile layer
	tileNode->setLayerType(XSceneObjectGroup::SceneLayerTypes::eTileLayer);
	entityNode->setLayerType(XSceneObjectGroup::SceneLayerTypes::eSortYNode);


	m_pSceneObjects->setLayerWithID(eLayerSceneObjectGroupID::eTileLayerID, tileNode);
	m_pSceneObjects->setLayerWithID(eLayerSceneObjectGroupID::eEntityLayerID, entityNode);

	m_pSceneObjects->setPreservedLayerID(eLayerSceneObjectGroupID::eTileLayerID);
	m_pSceneObjects->setPreservedLayerID(eLayerSceneObjectGroupID::eEntityLayerID);

	//����Ĭ�ϵĸ��ڵ�
	m_pSceneObjects->setParallaxRoot(this);
	this->addChild(m_pBaseLayer, 0, Vec2::ONE, Vec2::ZERO);
	//this->addChild(m_pOverLayer, eLayerSceneObjectGroupID::eOverLayerID, Vec2::ONE, Vec2::ZERO);

	//m_pSceneObjects->setLayerParallax(eLayerSceneObjectGroupID::eTileLafyerID, Vec2::ONE, Vec2::ZERO);
		
	m_MapInfoVec.resize(3);	// ����3����

	return true;
}

XGameScene::~XGameScene()
{
	for (int i = 0; i < eLayerCount; i++)
	{
		m_sceneNodes[i]->removeFromParent();
	}

	m_pSceneObjects->release();
	if(paStar_)
		delete paStar_;
}

void XGameScene::clearAll()
{
}

XGameScene* XGameScene::sharedScene()
{
	return XLogicScene::sharedScene()->getSceneNode();
}

void XGameScene::cleanSceneObjects()
{
	m_pSceneObjects->clearall(XSceneLayer::eOpObjects);
}

bool XGameScene::initWithMapFile(const std::string& mmapFilename,
								 const std::string& strMapJson,
								 const std::string& strTileBasePath)
{
	isInit = true;
	
	int size = m_MapInfoVec.size();
	for (int i = 0; i < size; i++)	// eMI_moveΪ0
	{
		if (m_MapInfoVec[i])
		{
			delete m_MapInfoVec[i];
			m_MapInfoVec[i] = 0;
		}
	}
	
	bool bDirty = loadMapInfo( eMI_move, mmapFilename );		// �����ȡ�ɹ������ʾ�´�draw��Ҫ����
	if (!bDirty)
	{
		XLOGERROR("mapInfo_.LoadFromFile %s [failed]", mmapFilename.c_str());
		return bDirty;
	}
	
	std::string mapName = mmapFilename;

	//��ʼ��AStar
	paStar_->initGrid(m_MapInfoVec[eMI_move]);
	
	leaveMap();
	
	Size screenSize = getViewPortSizeInternal();
	
	m_pSceneObjects->load(strMapJson, strTileBasePath, screenSize, false);
	
	//�����ͼ����
	setIsDirty(bDirty);

	// added by aXing on 2017-6-14
	// �������Ҫ����ȥ��һ�±�������صİ汾��
	cocos2d::CNewLoader::Inst().SaveKeyAndMD5();
	
	return bDirty;
}

bool XGameScene::loadMapInfo(int nIndex, const std::string& strSwimMMap)
{
	if (nIndex >= m_MapInfoVec.size())
	{
		// ������ʹ�м����Ҳ����
		std::vector<GameMapInfo *> newVec;
		newVec.resize(nIndex + 1);
		memset(&newVec[0], 0, sizeof(GameMapInfo *)*nIndex);
		if (m_MapInfoVec.size() > 0 )
			memcpy(&newVec[0], &m_MapInfoVec[0], sizeof(GameMapInfo *)*m_MapInfoVec.size());
		newVec[nIndex] = new GameMapInfo;

		m_MapInfoVec.resize(nIndex + 1);
		memcpy(&m_MapInfoVec[0], &newVec[0], sizeof(GameMapInfo *)*m_MapInfoVec.size());
	}
	else if (!m_MapInfoVec[nIndex])
	{
		m_MapInfoVec[nIndex] = new GameMapInfo;
	}

	return m_MapInfoVec[nIndex]->LoadFromFile(strSwimMMap.c_str());
}

void XGameScene::leaveMap()
{
	//if (m_pkTileMovable)
	//	m_pkTileMovable = nullptr;

	clearAll();
	//m_pOverLayer->removeAllChildren();
	m_pSceneObjects->leaveMap();
}

void XGameScene :: updateCameraInPixels(int& posX, int& posY)
{
	// ����һ�����ƣ����ܳ�����Ļ
	Size winSize			= XLogicScene::sharedScene()->getViewPortSize();
	int		halfWinWidth	= (int)(winSize.width  / 2);
	int		halfWinHeight	= (int)(winSize.height / 2);

	if (!m_MapInfoVec[eMI_move])
		return;

	if (m_bMapBoundCheck)
	{

		if (posX < halfWinWidth)
		{
			posX = halfWinWidth;
		}

		if (posY < halfWinHeight)
		{
			posY = halfWinHeight;
		}

		int top = (int)m_MapInfoVec[eMI_move]->getHeightInPixel() - halfWinHeight;
		int right = (int)m_MapInfoVec[eMI_move]->getWidthInPixel() - halfWinWidth;
		if (posX > right)
		{
			posX = right;
		}

		if (posY > top)
		{
			posY = top;
		}
	}

	if (camera_center_.x == posX && camera_center_.y == posY)
	{
		return;
	}
	camera_offset_.x = posX - camera_center_.x;
	camera_offset_.y = posY - camera_center_.y;

	camera_center_.x = (float)posX;
	camera_center_.y = (float)posY;

	m_pSceneObjects->setLookAt(camera_center_);
	setIsDirty(true);
}

void XGameScene::cameraMoveInPixels(int mapPosX, int mapPosY)
{
	XLogicScene::sharedScene()->moveCameraMap(mapPosX,mapPosY);
}

Vec2	XGameScene :: mapToScreen(int MapX, int MapY )
{
	Vec2 wp = convertToWorldSpace(Vec2(MapX,MapY));
	return wp;
}

Vec2	XGameScene :: mapToScreenAbsolute(int MapX, int MapY )
{
	Vec2 wp = convertToWorldSpace(Vec2(MapX,MapY));
	return wp;
}

Vec2	XGameScene :: GLPositionToScreen(int glX, int glY)
{
	Size winSize			= XLogicScene::sharedScene()->getViewPortSize();
	int		halfWinWidth	= (int)(winSize.width  / 2);
	int		halfWinHeight	= (int)(winSize.height / 2);

	float px = glX - ( camera_center_.x - halfWinWidth);
	float py = glY - ( camera_center_.y - halfWinHeight);

	return Vec2(px / s_viewPortOverWinWidth, py / s_viewPortOverWinHeight);
}

Vec2	XGameScene :: screenToGLPosition(int ScreenX, int ScreenY)
{
	return screenToMap(ScreenX, ScreenY);
}

Vec2	XGameScene :: screenToMap(int ScreenX, int ScreenY)
{
	if(!isInit)
		return Vec2(0,0);
	return convertToNodeSpace(Vec2(ScreenX, ScreenY));
}

void XGameScene::mapPosToGLPos( Vec2& mapPos )
{
	//mapPos.y =  mapPos.y;
}

container::Vector<int>* XGameScene::findPath(int sx, int sy, int tx, int ty)
{
	float x1, y1, x2, y2;
	int fx, fy;
	int i, j, b, pathingError;
	int *throughResult;
	container::Vector<int> rawPath;
	GameMapInfo *mapInfo = m_MapInfoVec[eMI_move];

	// ���·��
	path_.clear();

	// ����·����Ҫ����ת������
	x1 = (float)(sx) / s_logicTileWidth; // LOGIC_TILE_WIDTH;
	y1 = (float)(sy) / s_logicTileHeight; // LOGIC_TILE_HEIGHT;
	x2 = (float)(tx) / s_logicTileWidth; // LOGIC_TILE_WIDTH;
	y2 = (float)(ty) / s_logicTileHeight; // LOGIC_TILE_HEIGHT;

	//���ȼ���Ƿ����ֱ��ͨ����������ԣ���ֱ���˳���������ʹ��A*Ѱ·��
	throughResult = BresenhamLine::isAbleToThrough(x1, y1, x2, y2, mapInfo);
	if (*throughResult)
	{
		path_.add(tx);
		path_.add(ty);
	}
	else if (!m_MapInfoVec[eMI_move]->canMove((unsigned int)x2, (unsigned int)y2))	// �ж�Ŀ�������Ƿ�Ϸ�
	{
		// ������Ϸ����������������ߵ���Զ���ƶ�������
		path_.add((int)((throughResult[2] + 0.5f) * s_logicTileWidth));// LOGIC_TILE_WIDTH));
		path_.add((int)((throughResult[3] + 0.5f) * s_logicTileHeight));//LOGIC_TILE_HEIGHT));
	}
	else
	{
		// ���ֻ��һ�������ʹ��A*�㷨
		// ������ֱ���ߵ�������Ŀ����ӺϷ����Ż�ʹ��A*���߶�·��·��
		pathingError = paStar_->findPath(&rawPath, (int)x1, (int)y1, (int)x2, (int)y2);
		if (pathingError == AStar::PATHFINDING_ERROR_NONE)
		{
			b = rawPath.count() >> 1;
			for (i = b; i > 0; i--)
			{
				if (i != b)
				{
					x1 = rawPath[i * 2] + 0.5f;
					y1 = rawPath[i * 2 + 1] + 0.5f;
				}

				// Ѱ�ҿ��Ժϲ��Ľڵ�
				for (j = 0; j < i; j++)
				{
					if (j != 0)
					{
						x2 = rawPath[j * 2] + 0.5f;
						y2 = rawPath[j * 2 + 1] + 0.5f;
					}
					else
					{
						x2 = (float)(tx) / s_logicTileWidth; // LOGIC_TILE_WIDTH;
						y2 = (float)(ty) / s_logicTileWidth; // LOGIC_TILE_HEIGHT;
					}
					throughResult = BresenhamLine::isAbleToThrough(x1, y1, x2, y2, mapInfo);
					if (*throughResult)
					{
						path_.add((int)(x2 * s_logicTileWidth));// LOGIC_TILE_WIDTH));
						path_.add((int)(y2 * s_logicTileHeight));//LOGIC_TILE_HEIGHT));
						i = j + 1;
						break;
					}// end if
				}// end for
				
				//������ֻ���ڵ�һ���ڵ�����һ���ڵ�ſ����Ҳ���
				//����������BresenhamLine::isAbleToThrough��������bug��
				//���������ڸ��Ӷ���ʱ�����ҹ���ö����4�����Ӵ��ڲ����ƶ�������»����bug
				//����������Ҫ�������Ľڵ�Ѻ�������б�
				if (j == i)
				{
					if (i == b || i == 1)
					{
						//���������ڵ��������������������
						if (x1 < x2)
						{
							if (mapInfo->canMove((int)(x1 + 1), (int)(y1)))
								fx = 1, fy = 0;
							else fx = 0, fy = y1 < y2 ? 1 : -1;
						}
						else
						{
							if (mapInfo->canMove((int)(x1 - 1), (int)(y1)))
								fx = -1, fy = 0;
							else fx = 0, fy = y1 < y2 ? 1 : -1;
						}

						//���㽫ǰ���ĸ��Ӷ�������
						if (x1 < x2) x1++;
						if (y1 < y2) y1++;

						//���㲢���������ڵ�
						//ע�⣺��������ȶԵ�ͼ����ȡ�����ټ����Ӧ����������
						//path_.add((int)(x1) * LOGIC_TILE_WIDTH + fx);
						//path_.add((int)(y1) * LOGIC_TILE_HEIGHT + fy);
						path_.add((int)(x1) * s_logicTileWidth + fx);
						path_.add((int)(y1) * s_logicTileHeight + fy);

						//����Ѽ�������нڵ㣬��Ѻ���յ�
						//���򣬼���������ڵ�ĸ������꣬ͬʱ����Ҫ������ǰ�ڵ�����ֵ
						if (i == 1)
						{
							path_.add(tx);
							path_.add(ty);
						}
						else
						{
							x1 = (float)(path_[path_.count() - 2] / s_logicTileWidth);// LOGIC_TILE_WIDTH);
							y1 = (float)(path_[path_.count() - 1] / s_logicTileHeight);//LOGIC_TILE_HEIGHT);
							i++;
						}
					}
					else
					{
						path_.add((int)(x2 * s_logicTileWidth));//LOGIC_TILE_WIDTH));
						path_.add((int)(y2 * s_logicTileHeight));//LOGIC_TILE_HEIGHT));
					}// end if
				}// end if
			}// end for
		}
		/* �����־̫����
		else if (pathingError == AStar::PATHFINDING_ERROR_START_POINT)
		{
			XLOG("AStar::PATHFINDING_ERROR_START_POINT");
		}
		else if (pathingError == AStar::PATHFINDING_ERROR_TARGET_POINT)
		{
			XLOG("AStar::PATHFINDING_ERROR_TARGET_POINT");
		}
		else
		{
			XLOG("AStar::PATHFINDING_ERROR_NOT_FOUND %d %d - %d %d", sx, sy, tx, ty);
		}
		*/
	}// end if

	// TODO:��·�����ݸ��ű���path_����Ϊ��
	if (path_.count() != 0)
	{
		// test start
		/*int numPts = path_.count() >> 1;
		unsigned int mapX, mapY;
		for (i = 0; i < numPts; i++)
		{
			mapX = path_.get(i * 2) / LOGIC_TILE_WIDTH;
			mapY = path_.get(i * 2 + 1) / LOGIC_TILE_HEIGHT;
			XLOG(
				"%d,%d(%d,%d) movable:%d",
				path_.get(i * 2), path_.get(i * 2 + 1),
				mapX, mapY,
				mapInfo->canMove(mapX, mapY) ? 1 : 0
			);
		}*/
		// test end
		return &path_;
	}
	return NULL;
}

void XGameScene::setIsShowTileProp(bool b)
{
	isShowTilesProp_ = b;
	isDirty_ = true;
}

void XGameScene::showTiles()
{
	if (!isShowTiles_)
	{
		isShowTiles_	= true;
		isDirty_		= true;
	}
}

void XGameScene::hideTiles()
{
	if (isShowTiles_)
	{
		isShowTiles_	= false;
		isDirty_		= true;
	}
}

bool XGameScene::canMove(int index, unsigned int target_tile_x, unsigned int target_tile_y)
{
	if (index >= m_MapInfoVec.size())
		return false;
	if (!m_MapInfoVec[index])
		return false;
	return m_MapInfoVec[index]->canMove(target_tile_x, target_tile_y);
}

void XGameScene :: setIsDirty(bool b)
{
	isDirty_ = b;
}

void XGameScene :: updateDirty(float dt)
{
	//// ������ǳ�����camera�ƶ��ˣ�����Ҫ���¼���tiles
	if(!isDirty_)
	{
		return;
	}

	_updatePositions();

	Size screenSize = getViewPortSizeInternal();
	m_pSceneObjects->updateCamera(true);
	m_pSceneObjects->updateLayers(screenSize, camera_offset_);

	//if (isShowTiles_ || isShowTilesProp_)
	//{
	//	//if (m_pkTileMovable == nullptr)
	//	//{
	//	//	m_pkTileMovable = DrawNode::create();
	//	//	m_pOverLayer->addChild(m_pkTileMovable, -1);
	//	//}

	//	//m_pkTileMovable->clear();
	//	for (int x = 0; x < mapInfo_.getWidth(); x++)
	//	{
	//		for (int y = 0; y < mapInfo_.getHeight(); y++)
	//		{
	//			MAPGrid* grid = mapInfo_.getGridInfo(x, y);
	//			if (grid)
	//			{
	//				//Vec2 org = Vec2(x * 32, y * 32);
	//				//if (isShowTiles_)
	//				//	m_pkTileMovable->drawRect(org, Vec2(org.x + 32, org.y + 32), cocos2d::Color4F(0.0f, 1.0f, 0.0, 0.2f));
	//				//if (isShowTilesProp_)
	//				//{
	//				//	if (grid->flag_ & MAPFLAG_MOVEABLE)
	//				//	{
	//				//		m_pkTileMovable->drawSolidRect(org, Vec2(org.x + 32, org.y + 32), cocos2d::Color4F(1.0f, 1.0f, 0.0, 0.25f));
	//				//	}
	//				//}
	//			}
	//		}
	//	}
	//	//m_pkTileMovable->drawLine(Vec2(0, 0), Vec2(0xffff, 0), cocos2d::Color4F(1.0f, 0.0f, 0.0, 1.0f));
	//	//m_pkTileMovable->drawLine(Vec2(0, 0), Vec2(0, 0xffff),cocos2d::Color4F(0.0f, 1.0f, 0.0, 1.0f));
	//}
	//else
	//{
	//	//if (m_pkTileMovable)
	//	//	m_pkTileMovable->clear();
	//}
	// ������
	isDirty_ = false;
}

void XGameScene::updateSceneObjects(void)
{
	m_pSceneObjects->updateCamera(true);
}

void XGameScene :: onPause()
{
	m_pSceneObjects->onPause();
}

void XGameScene :: onResume()
{
	m_pSceneObjects->onResume();
	setIsDirty(true);
}

Vec2	XGameScene::cameraMapPosition()
{
	return Vec2(camera_center_.x, camera_center_.y);
}

void XGameScene::setViewPortSize(int width, int height, float scale)
{
	XGameScene::s_viewPortOverWinHeight = 1.0 / scale;
	XGameScene::s_viewPortOverWinWidth = 1.0 / scale;
	Size viewSize = XLogicScene::sharedScene()->getViewPortSize();
	float  halfViewWidth = viewSize.width / 2;
	s_viewWinWidthPow2 = halfViewWidth;
	m_pSceneObjects->setViewRadius(s_viewWinWidthPow2);
}
void XGameScene::debugVisibleRect(int w, int h)
{
	m_kDebugVisibleSize.width = w;
	m_kDebugVisibleSize.height = h;
}

Size XGameScene::getViewPortSizeInternal()
{
	if (m_kDebugVisibleSize.width)
	{
		return m_kDebugVisibleSize;
	}
	return  XLogicScene::sharedScene()->getViewPortVisibleSize();
}

void XGameScene::cleanup()
{
	if (m_pSceneObjects)
	{
		m_pSceneObjects->cleanup();
	}
	Node::cleanup();
}

Node* XGameScene::getSceneNode(int id)
{
	return m_sceneNodes[id];
}