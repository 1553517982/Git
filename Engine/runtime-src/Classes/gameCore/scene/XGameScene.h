#ifndef _X_GAMESCENE_H_
#define _X_GAMESCENE_H_

#include "cocos2d.h"
#include "game_map.h"
#include "XGameTile.h"
#include "../common/vector.h"
#include "scene/XSceneObjectGroup.h"
#include "scene/XSceneTileLayer.h"

#include <list>

USING_NS_CC;

class AStar;

/*
 由于目前主流的android屏幕是 800*480 或者 854*480
 所以我们采用一个tile的面积是256*256
 这样最大的情况是5*3，一共15块tile
*/
#define GAME_SCENE_TILE_WIDTH	256		// 一个地块的宽度是256像素
#define GAME_SCENE_TILE_HEIGHT	256		// 一个地块的高度是256像素
#define LOGIC_TILE_WIDTH		32		// 一个逻辑地块的宽度是32像素
#define LOGIC_TILE_HEIGHT		32		// 一个逻辑地块的高度是32像素
#define CAMERA_WIDTH_LIMIT		80		// 超出左右80像素，则移动镜头
#define CAMERA_HEIGHT_LIMIT		64		// 超出上下48像素，则移动镜头

#define SCENE_EFFECT_PAR  0
#define SCENE_EFFECT_ANIM 1
// 以下计算比率，用于计算
static const float LOGIC_SCENE_WIDTH  = (LOGIC_TILE_WIDTH  / GAME_SCENE_TILE_WIDTH);
static const float LOGIC_SCENE_HEIGHT = (LOGIC_TILE_HEIGHT / GAME_SCENE_TILE_HEIGHT);
static const float SCENE_LOGIC_WIDTH  = (GAME_SCENE_TILE_WIDTH  / LOGIC_TILE_WIDTH);
static const float SCENE_LOGIC_HEIGHT = (GAME_SCENE_TILE_HEIGHT / LOGIC_TILE_HEIGHT);

enum ESMapInfo
{
	eMI_move = 0,		// 移动区域
	eMI_shield,			// 遮挡
	eMI_swim,			

	// 有需要则自动往后面加
};

enum eMainLayerZOrders
{
	eZOrderTiles  = 0,
	eZOrderShadow = 100,
	eZOrderEntity = 200,
	eZOrderEffect = 300
};

enum eLayerSceneObjectGroupID
{
	//eUndergroundID = -1,
	eTileLayerID = 0,
	eEntityLayerID,
	//eOverLayerID = 2000
	//eSkyLayerID = 3,
	eLayerCount,
};

class XLogicScene;

class XGameScene : public ParallaxNode
{
	friend XLogicScene;
protected:
	XGameScene();
	static XGameScene* create();
public:
	
	typedef std::function<void(XGameScene* node, GameMapInfo* map)>	tDebugRenderCallback;

	~XGameScene();

	virtual bool init() override;

	//移动摄像机使用Map坐标
	void					cameraMoveInPixels(int mapPosX, int mapPosY);
	// 返回屏幕的绝对像素坐标
	Vec2					mapToScreenAbsolute(int x, int y);
	// 由于屏幕是以800*480为基数scale而得
	// 返回800*480为基数的像素坐标
	Vec2					mapToScreen(int x, int y);

	Vec2					screenToMap(int x, int y);

	Vec2					screenToGLPosition(int x, int y);

	Vec2					GLPositionToScreen(int x, int y);

	void					mapPosToGLPos(Vec2& mapPos);

	// 把camera移动到地图指定的坐标(像素级别)
	void					updateCameraInPixels(int& posX, int& posY);
	// 获取camera坐标(像素级别)
	inline Vec2				getCameraPositionInPixels()
	{
		return camera_center_;
	}

	Vec2					cameraMapPosition();

	// 地图单例
	static	XGameScene*		sharedScene();

	void					clearAll();

	void					onPause();

	void					onResume();

	// 读取map文件
	bool					initWithMapFile(const std::string& mmapFilename,const std::string& strMapJson,const std::string& strTileBasePath);

	// 增加一个区域，会自动增长索引，不能过大
	bool					loadMapInfo(int nIndex, const std::string& strSwimMMap);

	//离开地图
	void					leaveMap();
	/**
	 *	寻路
	 *	@param sx 起始x坐标
	 *	@param sy 起始y坐标
	 *	@param tx 目标x坐标
	 *	@param ty 目标y坐标
	 *	@return 寻得路径的节点字符串，格式："x0,y0:x1,y1:..."
	 */
	container::Vector<int>*	findPath(int sx, int sy, int tx, int ty);
	void*					toPtr() { return (void*)this;}

	// 显示/隐藏地图逻辑格子
	void					showTiles();
	void					hideTiles();

	void					setIsShowTileProp(bool b);

	// 把原来的区域，统一一个接口
	bool					canMove(int index, unsigned int target_tile_x, unsigned int target_tile_y);
	
	void					cleanSceneObjects();

	void					setIsDirty(bool b);

	bool					getMapBoundCheck() const { return m_bMapBoundCheck; }
	
	void					setMapBoundCheck(bool val) { m_bMapBoundCheck = val; }

	void					setViewPortSize(int width, int height, float scale);

	XSceneObjectGroup*		getSceneObjects() const { return m_pSceneObjects; }

	void					debugVisibleRect(int w, int h);

	Node*					getSceneNode(int id);

	/**
	* Stops all running actions and schedulers
	*/
	virtual void cleanup() override;
public:
	// added by aXing on 2013-5-6
	// 添加适应屏幕的tile的值, 并在初始化的时候完成计算
	static int				s_gameSceneTileWidth;
	static int				s_gameSceneTileHeight;
	static int				s_logicTileWidth;
	static int				s_logicTileHeight;

	//  渲染viewport大小/窗口大小
	static float			s_viewPortOverWinWidth;
	static float			s_viewPortOverWinHeight;
	
	static float			s_map_to_camera_offsetY;

	static					std::string _strCheckTextureName;

protected:
	
private:
	Size getViewPortSizeInternal();

	void updateDirty(float dt);

	void updateSceneObjects(void);

	Vec2							camera_center_;		// 摄像头世界坐标
	Vec2							camera_offset_;		// 移动趋向
	std::vector<GameMapInfo *>		m_MapInfoVec;		// 地图区域统一接口
	GameMapInfo						mapSwimPool;		// 定义游泳区域
	bool							isDirty_;			// 是否需要重新计算地表
	AStar							*paStar_;			// A*寻路器
	container::Vector<int>			path_;				// 寻得的路径
	bool							isShowTiles_;		// 是否显示小格子
	bool							isShowTilesProp_;	// 是否显示可走区域
	bool							isInit;				// 是否已经初始化
	XSceneObjectGroup*				m_pSceneObjects;	// 场景物件
	Node*							m_pBaseLayer;		// 基础层，包括tile,shadow,entity,effect 
	//Node*							m_pOverLayer;
	std::string						m_strTileFilePath;	// tile文件所在位置
	bool							m_bMapBoundCheck;
	DrawNode*						m_pkDebugVisibleRect;
	Size							m_kDebugVisibleSize;
	//DrawNode*						m_pkTileMovable;
	//Map<int, Node*>					m_sceneNodes;
	std::vector<Node*>				m_sceneNodes;
	
};
#endif