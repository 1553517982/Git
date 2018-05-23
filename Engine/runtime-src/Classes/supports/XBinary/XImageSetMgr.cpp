#include "XBinary/XImageSetMgr.h"
#include "cocos2d.h"
#include "cocostudio/DictionaryHelper.h"
#include "XCommon.h"
#include "supports/XResource/XResourceUtils.h"

USING_NS_CC;

static XImageSetMgr* gSharedManager = NULL;

SpriteFrameData::SpriteFrameData()
{

}

SpriteFrameData::~SpriteFrameData()
{
	_texture = NULL;
}

bool SpriteFrameData::initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Point& offset, const Size& originalSize)
{
	_rectInPixels = rect;
	_rect = CC_RECT_PIXELS_TO_POINTS(rect);
	_offsetInPixels = offset;
	_offset = CC_POINT_PIXELS_TO_POINTS(_offsetInPixels);
	_originalSizeInPixels = originalSize;
	_originalSize = CC_SIZE_PIXELS_TO_POINTS(_originalSizeInPixels);
	_rotated = rotated;
	return true;
}

void SpriteFrameData :: clearTexture()
{
	CC_SAFE_RELEASE_NULL(_texture);
}

XImageSetMgr :: XImageSetMgr()
{
}

XImageSetMgr :: ~XImageSetMgr()
{
	clear();
}

//XImageSetMgr* XImageSetMgr :: sharedManager()
//{
//	if(gSharedManager)
//		return gSharedManager;
//	gSharedManager = new XImageSetMgr();
//	return gSharedManager;
//}

//void XImageSetMgr :: purgeManager()
//{
//	CC_SAFE_DELETE(gSharedManager);
//}

//²éÕÒ¾²Ö¡
XImageUnit* XImageSetMgr :: findImageUnit(const char* szName, bool bCreateWhenNotFound)
{
	XImageUnitMapIter iter = m_kImagetUnitMap.find(szName);

	TextureCache* pkCache = Director::getInstance()->getTextureCache();
	if(iter == m_kImagetUnitMap.end())
	{
		iter = m_kTextureMap.find(szName);
		if(iter == m_kTextureMap.end())
		{
			if(bCreateWhenNotFound)
			{
				Texture2D* texture2d = pkCache->addImage(szName);
				if(!texture2d)
					return NULL;

				XImageUnit* pkNewUnit = new XImageUnit();
				Size size = texture2d->getContentSize();
				pkNewUnit->Set(0,0,size.width,size.height,szName,false,0,0,size.width,size.height);
				pkNewUnit->textureName = pkNewUnit->imageName;
				m_kTextureMap.insert(std::make_pair(szName,pkNewUnit));
				return pkNewUnit;
			}
			else
			{
				return NULL;
			}

		}
	}

	return iter->second;
}

SpriteFrame* XImageSetMgr::getSpriteFrame(const char* szName, bool bCreateWhenNotFound)
{
	XImageUnit* pkUnit = findImageUnit(szName,bCreateWhenNotFound);
	if(!pkUnit)
		return NULL;

	TextureCache* pkCache = Director::getInstance()->getTextureCache();
	Texture2D* texture = pkCache->addImage(pkUnit->textureName);
	if (!texture)
	{
		return NULL;
	}

	SpriteFrame* pkFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
	if (pkFrame == nullptr)
	{
		pkFrame->createWithTexture(texture,
								   Rect(pkUnit->x, pkUnit->y, pkUnit->width, pkUnit->height),
								   pkUnit->rotation,
								   Vec2(pkUnit->offsetX, pkUnit->offsetY),
								   Size(pkUnit->sourceSizeX, pkUnit->sourceSizeY));
	}
	return pkFrame;
}

bool XImageSetMgr :: loadImageSet(const char* filename)
{
	if(m_kImageSetMap.find(filename) != m_kImageSetMap.end())
		return true;

	const std::string strFilename = filename;
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(strFilename);
	Data fileData = FileUtils::getInstance()->getDataFromFile(fullpath);
	unsigned int size = fileData.getSize();
	if (size == 0)
	{
		return false;
	}
	unsigned char* pFileContent = fileData.getBytes();

	XImageSet* pkNewImageSet = new XImageSet();
	if(pkNewImageSet->Read(pFileContent,size,&m_kImagetUnitMap))
	{
		m_kImageSetMap.insert(std::make_pair(filename,pkNewImageSet));
		return true;
	}
	else
	{
		delete pkNewImageSet;
		return false;
	}
}


void XImageSetMgr :: clear()
{
	for( XImageSetMapIter iter = m_kImageSetMap.begin();
		iter != m_kImageSetMap.end();
		iter++ )
	{
		delete iter->second;
	}

	for( XImageUnitMapIter iter = m_kTextureMap.begin();
		iter != m_kTextureMap.end();
		iter++ )
	{
		delete iter->second;
	}


	for(XFrameListMap::iterator iter = m_kFrameListMap.begin();
		iter != m_kFrameListMap.end();
		iter++)
	{
		delete iter->second;
	}


	m_kFrameListMap.clear();
	m_kImageSetMap.clear();
	m_kImagetUnitMap.clear();
}

Sprite* XImageSetMgr :: Sprite_createWithImagetUnit(const char* szName)
{
	SpriteFrame* pkFrame = getSpriteFrame(szName,true);
	if(!pkFrame)
		return NULL;

	Sprite* pkNewSprite = Sprite::createWithSpriteFrame(pkFrame);
	return pkNewSprite;
}

SpriteFrame* XImageSetMgr :: SpriteFrame_createWithImagetUnit(const char* szName)
{
	SpriteFrame* pkFrame = getSpriteFrame(szName,true);
	if(!pkFrame)
		return NULL;

	SpriteFrame* pkNewFrame = (SpriteFrame*)pkFrame->clone();
	return pkNewFrame;
}

bool XImageSetMgr :: loadFrameSet(const char* filename)
{
	if(m_kImageSetMap.find(filename) != m_kImageSetMap.end())
		return true;

	const std::string strFilename = filename;
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(strFilename);
	Data fileData = FileUtils::getInstance()->getDataFromFile(fullpath);
	unsigned int size = fileData.getSize();
	if (size == 0)
	{
		return false;
	}
	unsigned char* pFileContent = fileData.getBytes();

	XFrameSet* pkNewImageSet = new XFrameSet();
	if(pkNewImageSet->Read(pFileContent,size,&m_kImagetUnitMap,&m_kFrameListMap))
	{
		m_kImageSetMap.insert(std::make_pair(filename,pkNewImageSet));
		return true;
	}
	else
	{
		delete pkNewImageSet;
		return false;
	}
}

XFrameList*	XImageSetMgr :: getFrameList(const char *szName)
{
	XFrameListMap::iterator iter = m_kFrameListMap.find(szName);
	if (iter == m_kFrameListMap.end())
	{
		XResourceDataBase* pkBase = XResourceUtils::getResourceDataBase();
		auto* list = pkBase->getResourceGroup(szName);
		if (!list)
		{
			XLOGERROR("XImageSetMgr :: getFrameList getDependency failed %s", szName);
			return NULL;
		}

		auto res = list->getResource();
		for (auto it = res->begin(); it != res->end(); it++)
		{
			const char* iuname = (*it)->m_strFilename.c_str();
			if (!loadFrameSet(iuname))
			{
				XLOGERROR("XImageSetMgr :: loadFrameSet failed %s", iuname);
				return NULL;
			}
		}

		iter = m_kFrameListMap.find(szName);
		if (iter == m_kFrameListMap.end())
		{
			XLOGERROR("XImageSetMgr :: find FrameListMap failed %s", szName);
			return NULL;
		}

	}
	return iter->second;
}

void XImageSetMgr::setSprite_withFrameName(Sprite* pkSprite, const char* szName)
{
	if(pkSprite)
		pkSprite->setSpriteFrame(getSpriteFrame(szName, true));
}