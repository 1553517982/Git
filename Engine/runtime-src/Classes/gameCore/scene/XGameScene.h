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
 ����Ŀǰ������android��Ļ�� 800*480 ���� 854*480
 �������ǲ���һ��tile�������256*256
 �������������5*3��һ��15��tile
*/
#define GAME_SCENE_TILE_WIDTH	256		// һ���ؿ�Ŀ����256����
#define GAME_SCENE_TILE_HEIGHT	256		// һ���ؿ�ĸ߶���256����
#define LOGIC_TILE_WIDTH		32		// һ���߼��ؿ�Ŀ����32����
#define LOGIC_TILE_HEIGHT		32		// һ���߼��ؿ�ĸ߶���32����
#define CAMERA_WIDTH_LIMIT		80		// ��������80���أ����ƶ���ͷ
#define CAMERA_HEIGHT_LIMIT		64		// ��������48���أ����ƶ���ͷ

#define SCENE_EFFECT_PAR  0
#define SCENE_EFFECT_ANIM 1
// ���¼�����ʣ����ڼ���
static const float LOGIC_SCENE_WIDTH  = (LOGIC_TILE_WIDTH  / GAME_SCENE_TILE_WIDTH);
static const float LOGIC_SCENE_HEIGHT = (LOGIC_TILE_HEIGHT / GAME_SCENE_TILE_HEIGHT);
static const float SCENE_LOGIC_WIDTH  = (GAME_SCENE_TILE_WIDTH  / LOGIC_TILE_WIDTH);
static const float SCENE_LOGIC_HEIGHT = (GAME_SCENE_TILE_HEIGHT / LOGIC_TILE_HEIGHT);

enum ESMapInfo
{
	eMI_move = 0,		// �ƶ�����
	eMI_shield,			// �ڵ�
	eMI_swim,			

	// ����Ҫ���Զ��������
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

	//�ƶ������ʹ��Map����
	void					cameraMoveInPixels(int mapPosX, int mapPosY);
	// ������Ļ�ľ�����������
	Vec2					mapToScreenAbsolute(int x, int y);
	// ������Ļ����800*480Ϊ����scale����
	// ����800*480Ϊ��������������
	Vec2					mapToScreen(int x, int y);

	Vec2					screenToMap(int x, int y);

	Vec2					screenToGLPosition(int x, int y);

	Vec2					GLPositionToScreen(int x, int y);

	void					mapPosToGLPos(Vec2& mapPos);

	// ��camera�ƶ�����ͼָ��������(���ؼ���)
	void					updateCameraInPixels(int& posX, int& posY);
	// ��ȡcamera����(���ؼ���)
	inline Vec2				getCameraPositionInPixels()
	{
		return camera_center_;
	}

	Vec2					cameraMapPosition();

	// ��ͼ����
	static	XGameScene*		sharedScene();

	void					clearAll();

	void					onPause();

	void					onResume();

	// ��ȡmap�ļ�
	bool					initWithMapFile(const std::string& mmapFilename,const std::string& strMapJson,const std::string& strTileBasePath);

	// ����һ�����򣬻��Զ��������������ܹ���
	bool					loadMapInfo(int nIndex, const std::string& strSwimMMap);

	//�뿪��ͼ
	void					leaveMap();
	/**
	 *	Ѱ·
	 *	@param sx ��ʼx����
	 *	@param sy ��ʼy����
	 *	@param tx Ŀ��x����
	 *	@param ty Ŀ��y����
	 *	@return Ѱ��·���Ľڵ��ַ�������ʽ��"x0,y0:x1,y1:..."
	 */
	container::Vector<int>*	findPath(int sx, int sy, int tx, int ty);
	void*					toPtr() { return (void*)this;}

	// ��ʾ/���ص�ͼ�߼�����
	void					showTiles();
	void					hideTiles();

	void					setIsShowTileProp(bool b);

	// ��ԭ��������ͳһһ���ӿ�
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
	// �����Ӧ��Ļ��tile��ֵ, ���ڳ�ʼ����ʱ����ɼ���
	static int				s_gameSceneTileWidth;
	static int				s_gameSceneTileHeight;
	static int				s_logicTileWidth;
	static int				s_logicTileHeight;

	//  ��Ⱦviewport��С/���ڴ�С
	static float			s_viewPortOverWinWidth;
	static float			s_viewPortOverWinHeight;
	
	static float			s_map_to_camera_offsetY;

	static					std::string _strCheckTextureName;

protected:
	
private:
	Size getViewPortSizeInternal();

	void updateDirty(float dt);

	void updateSceneObjects(void);

	Vec2							camera_center_;		// ����ͷ��������
	Vec2							camera_offset_;		// �ƶ�����
	std::vector<GameMapInfo *>		m_MapInfoVec;		// ��ͼ����ͳһ�ӿ�
	GameMapInfo						mapSwimPool;		// ������Ӿ����
	bool							isDirty_;			// �Ƿ���Ҫ���¼���ر�
	AStar							*paStar_;			// A*Ѱ·��
	container::Vector<int>			path_;				// Ѱ�õ�·��
	bool							isShowTiles_;		// �Ƿ���ʾС����
	bool							isShowTilesProp_;	// �Ƿ���ʾ��������
	bool							isInit;				// �Ƿ��Ѿ���ʼ��
	XSceneObjectGroup*				m_pSceneObjects;	// �������
	Node*							m_pBaseLayer;		// �����㣬����tile,shadow,entity,effect 
	//Node*							m_pOverLayer;
	std::string						m_strTileFilePath;	// tile�ļ�����λ��
	bool							m_bMapBoundCheck;
	DrawNode*						m_pkDebugVisibleRect;
	Size							m_kDebugVisibleSize;
	//DrawNode*						m_pkTileMovable;
	//Map<int, Node*>					m_sceneNodes;
	std::vector<Node*>				m_sceneNodes;
	
};
#endif