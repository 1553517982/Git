#ifndef _XSceneTileLayer_H_
#define _XSceneTileLayer_H_
#include "XSceneLayer.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocos2d.h"
#include "supports/XResource/XAsyncLoaderCallbacks.h"
#include "XGameTile.h"

USING_NS_CC;

class XSceneTileInfo
{
public:
	unsigned int		m_id;
	cocos2d::Vec2		m_position;
	std::string			m_filename;
};

typedef std::map<int, XSceneTileInfo*>	  XSceneTileInfoMap;

typedef struct _XSceneTileLayerParams
{
	~_XSceneTileLayerParams();

	int					m_nLayerID;
	int					m_nLayerType;
	std::string			m_strImageType;
	std::string			m_strGroup;
	std::string			m_strImagePath;
	Vec2				m_ratio;
	Vec2				m_offset;
	Size				m_size;

}XSceneTileLayerParams;

typedef std::map<int, XSceneTileLayerParams*> XSceneTileInfoGroupMap;

class XSceneTileLayerBase : public XSceneLayer
{
protected:
	XSceneTileLayerBase();
public:
	virtual ~XSceneTileLayerBase();

	void setup(const std::string& strImageBasePath, const cocos2d::Size& sceneSize)
	{
		m_strImageBasePath = strImageBasePath;
		m_sceneSize = sceneSize;
	}

protected:
	std::string						m_strImageBasePath;
	cocos2d::Size					m_sceneSize;
};

class XSceneTileInfoGroup;

class XSceneTileLayer : public XSceneTileLayerBase
{
protected:
	XSceneTileLayer();

public:
	virtual ~XSceneTileLayer();

	static XSceneTileLayer * create();

	/*!
	* \brief 
	* \param const cocos2d::Vec2 & center
	* \param int width
	* \param int height					
	* \param const cocos2d::Vec2 & movement 移动趋向，如果向左跑我们就提早加载左边的tiles
	* \return void
	*/
	virtual void visibleCheck(const cocos2d::Size& screenSize,
							  const cocos2d::Vec2& movement,
							  float screenRadius,
							  int flags) override;
	
	virtual void clearall(int flag) override;

	virtual void onPause() override;

	virtual void onResume() override;

	virtual void cleanup() override;

	//void readLayer(const char * pData, unsigned int nDataSize, ParallaxNode* parent, const char* prefix);

	virtual void readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix) override;

	virtual void writeLayer(rapidjson::Value& item, rapidjson::Document& doc, rapidjson::Document::AllocatorType& alloc) override;

	static void setTilePool(cocos2d::Vector<XGameTile*>* pool);

protected:

	void clearConfig();

	void updateTiles(const cocos2d::Vec2& center,
					 const cocos2d::Size& screenSize,
					 const cocos2d::Vec2& movement);


	void loadGroup();

	void onLoadGroup();

	static XGameTile*	createTile(int index, Node* parent, cocos2d::Map<int, XGameTile*>& tilemap);

	static void recycleTile(XGameTile* pTile);
	bool									m_bReady;
	cocos2d::Map<int, XGameTile*>			m_visibleTiles;			// 地块对应的字典
	XAsyncLoaderCallback*					m_pkGroupLoadCallback;
	int										m_retryCount;
	
	cocos2d::Vec2							m_saved_center;
	cocos2d::Size							m_saved_screenSize;
	cocos2d::Vec2							m_saved_movement;
	std::vector<XGameTile*>					m_tileVec;
	XSceneTileInfoMap						m_tileInfoMap;
	static cocos2d::Vector<XGameTile*>*		m_pkTilesPool;			// 地块池\

	std::string								m_strGroup;

	int m_camera_height;
};
#endif