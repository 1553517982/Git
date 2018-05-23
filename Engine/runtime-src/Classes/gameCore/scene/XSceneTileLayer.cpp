#include "XSceneTileLayer.h"
#include "supports/XResource/XAsyncLoaderManager.h"
#include "supports/XResource/XResourceUtils.h"
#include <set>
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define _JsonHelper cocostudio::DictionaryHelper::getInstance()
#define MainLayerID 0

cocos2d::Vector<XGameTile*>* XSceneTileLayer::m_pkTilesPool = nullptr;

XSceneTileLayerBase::XSceneTileLayerBase()
{

}

XSceneTileLayerBase::~XSceneTileLayerBase()
{

}



XSceneTileLayer::XSceneTileLayer() 
	: m_retryCount(0)
	, m_bReady(true)
	, m_pkGroupLoadCallback(nullptr)
{

}

XSceneTileLayer::~XSceneTileLayer()
{
	clearConfig();

	if (m_pkGroupLoadCallback)
	{
		m_pkGroupLoadCallback->cancel();
		m_pkGroupLoadCallback->release();
	}
}

XSceneTileLayer * XSceneTileLayer::create()
{
	XSceneTileLayer * ret = new (std::nothrow) XSceneTileLayer();
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

void XSceneTileLayer::updateTiles(const cocos2d::Vec2& center,
								  const cocos2d::Size& screenSize,
								  const cocos2d::Vec2& movement)
{
	m_saved_center = center;
	m_saved_screenSize = screenSize;
	m_saved_movement = movement;
	if (!m_bReady)
		return;

	int		LeftOffset = movement.x < 0 ? -1 : 0;
	int		RightOffset = movement.x > 0 ? 1 : 0;

	int		TopOffset = movement.y > 0 ? 1 : 0;
	int		BottomOffset = movement.y < 0 ? -1 : 0;

	int		visibleWidth = screenSize.width * 1.5;		// edited by aXing on 2017-9-5 
	int		visibleHeight = screenSize.height * 1.5;	// 原本是 1.0， 但是当非正常设置比例的屏幕出现时，就会显示出比例多出部分的黑边

	int		camera_center_x = center.x;
	int		camera_center_y = center.y;

	int		halfWinWidth = (int)(visibleWidth / 2);
	int		halfWinHeight = (int)(visibleHeight / 2);

	int		tileWidth = 256;
	int		tileHeight = 256;

	int viewLeft = int(camera_center_x - halfWinWidth);
	int viewTop = int(camera_center_y + halfWinHeight);
	int viewRight = int(camera_center_x + halfWinWidth);
	int viewBottom = int(camera_center_y - halfWinHeight);


	int left = viewLeft + int((-1 + LeftOffset) * tileWidth);// GAME_SCENE_TILE_WIDTH);
	int top = viewTop + int((1 + TopOffset) * tileHeight);//GAME_SCENE_TILE_HEIGHT);

	left = left < 0 ? 0 : left;			// 这里做一下非负限制
	top = top  < 0 ? 0 : top;

	int right = viewRight + int((1 + RightOffset) * tileWidth); // GAME_SCENE_TILE_WIDTH);
	int bottom = viewBottom + int((-1 + BottomOffset) * tileHeight); // GAME_SCENE_TILE_HEIGHT);

	bottom = bottom < 0 ? 0 : bottom;
	right = right < 0 ? 0 : right;
	


	// 计算出视口左上角tile坐标
	int left_index = MAX( 0, (int)floor((float)left / float(tileWidth) - 1) );// GAME_SCENE_TILE_WIDTH);
	int top_index = (int)ceil((float)top / float(tileHeight));//GAME_SCENE_TILE_HEIGHT);
	////
	int right_index = (int)ceil((float)right / float(tileWidth) + 1);//GAME_SCENE_TILE_WIDTH));
	int bottom_index = (int)floor((float)bottom / float(tileHeight));//GAME_SCENE_TILE_HEIGHT));
	cocos2d::Map<int, XGameTile*> showed;
	
	std::set<int> visibleSet;
	int col = (int)ceil(m_LayerSize.width / tileWidth);
	right_index = MIN(col, right_index);
	
	//找出可视tiles
	int nMaxSize = m_tileVec.size();
	for (int y = bottom_index; y < top_index; y++)
	{
		int y_col = y * col;
		for (int x = left_index; x < right_index; x++)
		{
			//if(y_col + x >= nMaxSize)
			//	continue;
			//XGameTile * pTile = m_tileVec[y_col + x];
			//pTile->OnCreate();

			visibleSet.insert(y_col + x);
			//printf("tiles %d %d\n", x * 256, y * 256);
		}
	}

	////删除不可见tiles
	for (auto tIter = m_visibleTiles.begin(); tIter != m_visibleTiles.end(); /*空*/)
	{
		if (visibleSet.find(tIter->first) == visibleSet.end())
		{
			recycleTile(tIter->second);
			m_visibleTiles.erase(tIter++);
		}
		else
		{
			//如果已经可见的，从临时visibleSet删除
			visibleSet.erase(tIter->first);
			tIter++;
		}
	}

	char filename[256] = { 0 };
	auto* config = &m_tileInfoMap;
	//填充可见
	for (auto vIter = visibleSet.begin(); vIter != visibleSet.end(); vIter++)
	{
		//没有没配置的跳过
		int index = *vIter;
		//if (index >= m_tileInfoVec.size())
		//	continue;
		//XSceneTileInfo & info = m_tileInfoVec[index];
		//if (m_visibleTiles.find(index) != m_visibleTiles.end())
		//	continue;

		//没有没配置的跳过
		auto iter = config->find(index);
		if (iter == config->end())
		{
			continue;
		}
		if (m_visibleTiles.find(index) != m_visibleTiles.end())
		{
			continue;
		}
		auto tileInfo = iter->second;

		//构建tile
		auto newTile = createTile(index, this, m_visibleTiles);
		newTile->setVisible(false);
		newTile->loadAsync(tileInfo->m_filename.c_str());
		newTile->setAnchorPoint(Vec2(0, 0));
		newTile->setPosition(tileInfo->m_position.x, tileInfo->m_position.y);

		//newTile->setColor(m_tileColor);
	}
}
void XSceneTileLayer::visibleCheck(const cocos2d::Size& screenSize, 
								   const cocos2d::Vec2& movement,
								   float screenRadius,
								   int flags)
{
	//更新地表
	if (!m_tileInfoMap.empty() && (flags & eOpTiles))
	{
		updateTiles(m_kCameraCenterParallex, screenSize, movement);
	}

	if (flags & eOpObjects)
	{
		//更新物件
		updateObjects(screenRadius);
	}
}

XGameTile* XSceneTileLayer::createTile(int index, Node* parent, cocos2d::Map<int, XGameTile*>& tilemap)
{
	XGameTile* pTile = NULL;
	if (m_pkTilesPool->empty())
	{
		pTile = XGameTile::create();
		pTile->setTag(index);
		tilemap.insert(index, pTile);
	}
	else
	{
		pTile = m_pkTilesPool->back();
		pTile->setTag(index);
		tilemap.insert(index, pTile);
		m_pkTilesPool->popBack();
	}
	parent->addChild(pTile);
	return pTile;
}

void XSceneTileLayer::recycleTile(XGameTile* pTile)
{
	pTile->setTag(INVALID_TAG);
	pTile->setTexture(NULL);
	m_pkTilesPool->pushBack(pTile);
	pTile->removeFromParent();
}

void XSceneTileLayer::clearall(int flag)
{
	if (flag & eOpTiles)
	{
		for (auto iter = m_visibleTiles.begin(); iter != m_visibleTiles.end(); iter++)
		{
			iter->second->removeFromParent();
		}
		m_visibleTiles.clear();
	}
	XSceneLayer::clearall(flag);
	//for (int i = 0; i < m_tileVec.size(); i++)
	//{
	//	XGameTile * t = m_tileVec[i];
	//	t->removeFromParent();
	//}
	//m_tileVec.clear();
}


void XSceneTileLayer::onPause()
{
	XSceneLayer::onPause();
	removeAllChildren();
	m_visibleTiles.clear();
}

void XSceneTileLayer::onResume()
{
	//if (m_pkConfig && !m_pkConfig->m_strGroup.empty())
	//{
	//	m_bReady = false;
	//	m_retryCount = 0;
	//	loadGroup();
	//}
	//else
	//{
	//	m_bReady = true;
	//}
}

void XSceneTileLayer::setTilePool(cocos2d::Vector<XGameTile*>* pool)
{
	m_pkTilesPool = pool;
}


void XSceneTileLayer::cleanup()
{
	if (m_pkGroupLoadCallback)
	{
		m_pkGroupLoadCallback->cancel();
		m_pkGroupLoadCallback->release();
		m_pkGroupLoadCallback = nullptr;
	}

	//for (int i = 0; i < m_tileVec.size(); i++)
	//{
	//	XGameTile * t = m_tileVec[i];
	//	t->removeFromParent();
	//}
	//m_tileVec.clear();
	XSceneTileLayerBase::cleanup();
}

void XSceneTileLayer::loadGroup()
{
	XAssert(!m_strGroup.empty(), "");
	if (m_strGroup.empty())
	{
		return;
	}
	auto& filename = m_strGroup;
	XAsyncLoaderFunction onloaded = [=](const XAsyncLoaderRet* ret)
	{
		if (ret->ret() == XAsyncLoaderCode::eOK)
		{
			this->onLoadGroup();
		}
		else if (m_retryCount <= 1)
		{
			this->loadGroup();
			m_retryCount++;
		}
	};
	if (m_pkGroupLoadCallback == nullptr)
	{
		m_pkGroupLoadCallback = XAsyncLoaderCallback::create();
		m_pkGroupLoadCallback->retain();
	}
	m_pkGroupLoadCallback->init(onloaded);
	auto loader = XAsyncLoaderManager::sharedManager()->loadGroup(filename, filename, Priority::TILE, m_pkGroupLoadCallback);
}

void XSceneTileLayer::onLoadGroup()
{
	m_bReady = true;
	auto group = XResourceUtils::getResourceDataBase()->getResourceGroup(m_strGroup);
	if (group)
	{
		tResourceDataVector* data = group->getResource();

		for (auto it = data->begin(); it != data->end(); it++)
		{
			if ((*it)->m_nType == eResTypePlist)
			{
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile((*it)->m_strFilename);
			}
		}
	}
	updateTiles(m_saved_center, m_saved_screenSize, m_saved_movement);
	XLOG("XSceneTileLayer::onLoadGroup");
}

//void XSceneTileLayer::readLayer(const char * pData, unsigned int nDataSize, ParallaxNode* parent, const char* prefix)
//{
//	m_LayerSize.width = *(unsigned short*)(pData);
//	m_LayerSize.height = *(unsigned short*)(pData+sizeof(unsigned short) );
//
//	int nHeadSize = 2 * sizeof(unsigned short);
//
//	m_nLayerID = 0;
//	
//	if (nDataSize % 2 * sizeof(unsigned short) != 0)
//		return;
//
//	m_tileVec.clear();
//	char buf[256] = { 0 };
//	int nCount = ( nDataSize - nHeadSize ) / (2 * sizeof( unsigned short ) );
//
//	m_tileVec.resize(nCount);
//
//	bool bRes = true;
//	for (int i = 0; i < nCount; i++)
//	{
//		m_tileVec[i] = XGameTile::create();
//		XGameTile & tile = *m_tileVec[i];
//		tile.m_nId = i;
//		tile.m_position = *(SVec2*)( pData + i * sizeof( SVec2 ) + nHeadSize );
//
//		tile.setAnchorPoint(Vec2(0, 0));
//		tile.setPosition(tile.m_position.x, tile.m_position.y);
//
//		snprintf(buf, 255, "%s%d/%d_%d.png", prefix, 0, (int)tile.m_position.x, (int)tile.m_position.y);
//		tile.m_strTextureName = buf;
//
//		addChild(&tile);
//	}
//
//	//if (parent)
//	//	parent->addChild(this, 0, m_ParallaxRatio, m_ParallaxOffset);
//}

void XSceneTileLayer::readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix)
{
	m_bReady = false;

	clearConfig();

	XSceneLayer::readLayer(entry, layerID, parent, prefix);
	m_camera_height = _JsonHelper->getIntValue_json(entry, "cameraHeight", 0);

	char buf[256] = { 0 };
	bool ret = false;
	rapidjson::Value& _tiles = entry["tiles"];
	do
	{
		CC_BREAK_IF(!_tiles.IsArray());
		int size = _tiles.Size();
		for (int i = 0; i < size; i++)
		{
			rapidjson::Value& item = _tiles[i];
			CC_BREAK_IF(item.IsNull());
			XSceneTileInfo* data = new XSceneTileInfo();
			data->m_id = _JsonHelper->getIntValue_json(item, "i", 0);
			data->m_position.x = _JsonHelper->getIntValue_json(item, "x", 0);
			data->m_position.y = _JsonHelper->getIntValue_json(item, "y", 0);

			//modify by xianguiquan
			//add json attribute "res"
			std::string resPath = _JsonHelper->getStringValue_json(item, "res", "");
			
			if (resPath == "")
			{
				snprintf(buf, 255, "%s%d/%d_%d.%s", m_strResPath.c_str(), layerID, (int)data->m_position.x, (int)data->m_position.y, m_strFileType.c_str());
			}
			else
			{
				int index = m_strResPath.find("/");
				std::string path = m_strResPath.substr(0, index);				
				snprintf(buf, 255, "%s/%s", path.c_str(), resPath.c_str());
			}
			//end

			data->m_filename = buf;
			m_tileInfoMap.insert(std::make_pair(data->m_id, data));
		}
		ret = true;
	} while (0);
	if (!ret)
	{
		XLOGERROR("failed to load tiles layer %d", layerID);
	}
	else
	{
		m_bReady = true;
	}

}

void XSceneTileLayer::writeLayer(rapidjson::Value& item, rapidjson::Document& doc, rapidjson::Document::AllocatorType& alloc)
{
	XSceneLayer::writeLayer(item, doc, alloc);
	if (m_nLayerID == MainLayerID)
	{
		item.RemoveMember("cameraHeight");
		item.AddMember("cameraHeight", int(m_camera_height), alloc);
	}
}

void XSceneTileLayer::clearConfig()
{
	for (auto it = m_tileInfoMap.begin(); it != m_tileInfoMap.end(); it++)
	{
		delete it->second;
	}
	m_tileInfoMap.clear();
}

