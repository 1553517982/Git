/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "2d/CCSpriteFrameCache.h"

#include <vector>


#include "2d/CCSprite.h"
#include "platform/CCFileUtils.h"
#include "base/CCNS.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCTexture2D.h"
#include "renderer/CCTextureCache.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "extention/XBinary/XImageSet.h"

#include "deprecated/CCString.h"

using namespace std;

NS_CC_BEGIN

static SpriteFrameCache *_sharedSpriteFrameCache = nullptr;

SpriteFrameCache* SpriteFrameCache::getInstance()
{
    if (! _sharedSpriteFrameCache)
    {
        _sharedSpriteFrameCache = new (std::nothrow) SpriteFrameCache();
        _sharedSpriteFrameCache->init();
    }

    return _sharedSpriteFrameCache;
}

void SpriteFrameCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedSpriteFrameCache);
}

bool SpriteFrameCache::init()
{
    _spriteFrames.reserve(20);
    _spriteFramesAliases.reserve(20);
    _loadedFileNames = new std::set<std::string>();
    return true;
}

SpriteFrameCache::~SpriteFrameCache()
{
    CC_SAFE_DELETE(_loadedFileNames);
}

void SpriteFrameCache::reduceCacheWithResName(const std::string & name)
{
	auto iter = _spriteFramesCount.find(name);
	if (iter != _spriteFramesCount.end())
	{
		iter->second -= 1;
		if (iter->second < 0)
			iter->second = 0;
	}
}


bool SpriteFrameCache::addSpriteFramesWithResName(const std::string & name, StringMap * texStringMap)
{
	char key[128] = { 0 };

	// 如果第一帧有，也就是已经有了，所以就不再去尝试加载
	auto iter = _spriteFramesCount.find(name);
	if ( iter != _spriteFramesCount.end())
	{
		iter->second += 1;
		return true;
	}

	std::list<std::string> * list = CNewLoader::Inst().LoadResDepenence(name.c_str());
	if (!list)
	{
		CCLOG("XImageSetMgr :: getFrameList getDependency failed %s", name.c_str());
		return false;
	}

	_spriteFramesCount[name] = 1;

	int nResID = 0;
	for (auto it = list->begin(); it != list->end(); it++)
	{
		const char* iuname = (*it).c_str();

		std::string strFilename = iuname;
		// 把plist改为pl
		int nPos = strFilename.find(".plist");
		strFilename.replace(nPos, 6, ".pl");

		// 然后读取
		char * pFileContent;
		unsigned int nSize;
		if (!CNewLoader::Inst().SyncLoadFile(strFilename.c_str(), &pFileContent, &nSize))
			continue;

		// 创建读取
		XImageSet imageSet;

		if (!imageSet.Read(pFileContent, nSize))
			continue;

		XImageUnitList * pList = imageSet.GetImageUnitList();

		for (int nIndex = 0; nIndex < pList->size(); nIndex++)
		{
			XImageUnit* pUnit = &pList->at(nIndex);

			std::string textureName = pUnit->textureName;

			SpriteFrame * spriteFrame = SpriteFrame::create(textureName,
				Rect(pUnit->x, pUnit->y, pUnit->width, pUnit->height),
				pUnit->rotation,
				Vec2(pUnit->offsetX, pUnit->offsetY),
				Size(pUnit->sourceSizeX, pUnit->sourceSizeY));

			sprintf(key, "%s_%d", name.c_str(), nResID);

			addSpriteFrame(spriteFrame, std::string(key));
			nResID++;

			if (texStringMap)
			{
				StringMap & m = *texStringMap;
				m[textureName] = 0;
				spriteFrame->getTexture();
			}
		}
	}
	//CCLOG("load res %d", nResID);
	return true;
}

void SpriteFrameCache::addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D* texture)
{
	/*
	ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
		ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
		ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
		ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
		*/


	ValueMap& framesDict = dictionary["frames"].asValueMap();
	int format = 0;

	// get the format
	if (dictionary.find("metadata") != dictionary.end())
	{
		ValueMap& metadataDict = dictionary["metadata"].asValueMap();
		format = metadataDict["format"].asInt();
	}

	// check the format
	CCASSERT(format >= 0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

	for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
	{
		ValueMap& frameDict = iter->second.asValueMap();
		std::string spriteFrameName = iter->first;
		SpriteFrame* spriteFrame = _spriteFrames.at(spriteFrameName);
		if (spriteFrame)
		{
			continue;
		}

		if (format == 0)
		{
			float x = frameDict["x"].asFloat();
			float y = frameDict["y"].asFloat();
			float w = frameDict["width"].asFloat();
			float h = frameDict["height"].asFloat();
			float ox = frameDict["offsetX"].asFloat();
			float oy = frameDict["offsetY"].asFloat();
			int ow = frameDict["originalWidth"].asInt();
			int oh = frameDict["originalHeight"].asInt();
			// check ow/oh
			if (!ow || !oh)
			{
				CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
			}
			// abs ow/oh
			ow = abs(ow);
			oh = abs(oh);
			// create frame
			spriteFrame = SpriteFrame::createWithTexture(texture,
				Rect(x, y, w, h),
				false,
				Vec2(ox, oy),
				Size((float)ow, (float)oh)
				);
		}
		else if (format == 1 || format == 2)
		{
			Rect frame = RectFromString(frameDict["frame"].asString());
			bool rotated = false;

			// rotation
			if (format == 2)
			{
				rotated = frameDict["rotated"].asBool();
			}

			Vec2 offset = PointFromString(frameDict["offset"].asString());
			Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());

			// create frame
			spriteFrame = SpriteFrame::createWithTexture(texture,
				frame,
				rotated,
				offset,
				sourceSize
				);
		}
		else if (format == 3)
		{
			// get values
			Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
			Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
			Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
			Rect textureRect = RectFromString(frameDict["textureRect"].asString());
			bool textureRotated = frameDict["textureRotated"].asBool();

			// get aliases
			ValueVector& aliases = frameDict["aliases"].asValueVector();

			for (const auto &value : aliases) {
				std::string oneAlias = value.asString();
				if (_spriteFramesAliases.find(oneAlias) != _spriteFramesAliases.end())
				{
					CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
				}

				_spriteFramesAliases[oneAlias] = Value(spriteFrameName);
			}

			// create frame
			spriteFrame = SpriteFrame::createWithTexture(texture,
				Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
				textureRotated,
				spriteOffset,
				spriteSourceSize);
		}

		// add sprite frame
		_spriteFrames.insert(spriteFrameName, spriteFrame);
	}
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist, Texture2D *texture)
{
    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        return; // We already added it
    }
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

    addSpriteFramesWithDictionary(dict, texture);
    _loadedFileNames->insert(plist);
}

void SpriteFrameCache::addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture)
{
    ValueMap dict = FileUtils::getInstance()->getValueMapFromData(plist_content.c_str(), static_cast<int>(plist_content.size()));
    addSpriteFramesWithDictionary(dict, texture);
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName)
{
    CCASSERT(textureFileName.size()>0, "texture name should not be null");
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(textureFileName);

    if (texture)
    {
        addSpriteFramesWithFile(plist, texture);
    }
    else
    {
        CCLOG("cocos2d: SpriteFrameCache: couldn't load texture file. File not found %s", textureFileName.c_str());
    }
}

void SpriteFrameCache::addSpriteFramesWithFile(const std::string& plist)
{
    CCASSERT(plist.size()>0, "plist filename should not be nullptr");
    
    //std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    //if (fullPath.size() == 0)
    //{
    //    // return if plist file doesn't exist
    //    CCLOG("cocos2d: SpriteFrameCache: can not find %s", plist.c_str());
    //    return;
    //}

	//int nPos2 = plist.find("icon/");
	//if (nPos2 > -1)
	//{
	//	CCLOGERROR("loading an ICON plist file %s !!!  =============================", plist.c_str(), nPos2);
	//}
	//nPos2 = plist.find("ui/");
	//if (nPos2 > -1)
	//{
	//	CCLOGERROR("loading an UI plist file %s !!!  =============================", plist.c_str(), nPos2);
	//}

    if (_loadedFileNames->find(plist) == _loadedFileNames->end())
    {
		// 把plist转为pl
		std::string strpl = plist;
		int nPos = strpl.find(".plist");
		strpl.replace(nPos, 6, ".pl");

		// 本来在ImageSet中也有
		// 然后读取
#if 1
		

		char * pFileContent;
		unsigned int nSize;
		if (!CNewLoader::Inst().SyncLoadFile(strpl.c_str(), &pFileContent, &nSize))
		{
			CCLOGERROR("load plist file %s fail  =============================", strpl.c_str());
			return;
		}

		// 创建读取
		XImageSet imageSet;

		if (!imageSet.Read(pFileContent, nSize))
		{
			CCLOGERROR("load plist file %s fail ==============================", strpl.c_str());
			return;
		}

		XImageUnitList * pList = imageSet.GetImageUnitList();

		TextureCache * pTexCache = Director::getInstance()->getTextureCache();
		if (!pTexCache)
			return;

		for (int nIndex = 0; nIndex < pList->size(); nIndex++)
		{
			XImageUnit* pUnit = &pList->at(nIndex);

			// Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(pUnit->textureName);
			std::string strFile(pUnit->textureName);
			
			/*
			// removed by aXing on 2017-3-24
			// 这里是不需要的，为什么读取配置的时候，就开始要加载贴图？
			// 应该按需加载
			Texture2D * texture = nullptr;
			if (pTexCache->HasImage(strFile) || CNewLoader::Inst().IsHasFile(strFile))
				texture = pTexCache->addImage(strFile);
			else
				pTexCache->addImageInAsync(strFile);
			*/

			//SpriteFrame * spriteFrame = SpriteFrame::create(pUnit->textureName,
			//	Rect(pUnit->x, pUnit->y, pUnit->width, pUnit->height));
			
			SpriteFrame * spriteFrame = SpriteFrame::create(pUnit->textureName,
				Rect(pUnit->x, pUnit->y, pUnit->width, pUnit->height),
				pUnit->rotation,
				Vec2(pUnit->offsetX, pUnit->offsetY),
				Size(pUnit->sourceSizeX, pUnit->sourceSizeY));

			std::string str = pUnit->imageName;
			// 关于他里面读取，居然没有考虑UI这个路径
			// 这个函数是读取cocos studio里面的csb文件，指向的贴图地址
			// 因为这个地址的根目录是 res/ui 所以要把ui去掉
			// 而我们plist里面的根目录是 res/ 
			//int nPos = str.find("ui/");
			//if (0 == nPos)
			//{
			//	str.replace(nPos, 3, "");
			//}
			//else 
			//{
			//	nPos = str.find("icon/");
			//	if (0 == nPos)
			//		str.replace(nPos, 5, "");
			//}

			addSpriteFrame(spriteFrame, str);
		}
#else

        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

        string texturePath("");

        if (dict.find("metadata") != dict.end())
        {
            ValueMap& metadataDict = dict["metadata"].asValueMap();
            // try to read  texture file name from meta data
            texturePath = metadataDict["textureFileName"].asString();
        }

        if (!texturePath.empty())
        {
            // build texture path relative to plist file
            texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), plist);
        }
        else
        {
            // build texture path by replacing file extension
            texturePath = plist;

            // remove .xxx
            size_t startPos = texturePath.find_last_of("."); 
            texturePath = texturePath.erase(startPos);

            // append .png
            texturePath = texturePath.append(".png");

            CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
        }

		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath);

        if (texture)
        {
            addSpriteFramesWithDictionary(dict, texture);
            _loadedFileNames->insert(plist);
        }
        else
        {
            CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
        }
#endif
    }
}

bool SpriteFrameCache::isSpriteFramesWithFileLoaded(const std::string& plist) const
{
    bool result = false;

    if (_loadedFileNames->find(plist) != _loadedFileNames->end())
    {
        result = true;
    }

    return result;
}

void SpriteFrameCache::addSpriteFrame(SpriteFrame* frame, const std::string& frameName)
{
    _spriteFrames.insert(frameName, frame);
}

void SpriteFrameCache::removeSpriteFrames()
{
    _spriteFrames.clear();
    _spriteFramesAliases.clear();
    _loadedFileNames->clear();
}

void SpriteFrameCache::removeUnusedSpriteFrames()
{
    bool removed = false;
    std::vector<std::string> toRemoveFrames;
	std::vector<std::string> toRemoveName;

	char key[128] = {};
	
	for (auto it = _spriteFramesCount.begin(); it != _spriteFramesCount.end(); it++)
	{
		if (it->second == 0)
		{
			toRemoveName.push_back(it->first);
			//CCLOG("SpriteFrameCache :: removeUnusedSpriteFrames %s", it->first.c_str());
			int i = 0;
			while ( true )
			{
				sprintf(key, "%s_%d", it->first.c_str(), i);
				auto iter = _spriteFrames.find(key);
				if (iter != _spriteFrames.end())
				{
					i++;
					if (iter->second->getReferenceCount() <= 2)	// 如果不是1，也就是其他地方用到，接口不统一的问题
					{
						TextureCache::getInstance()->removeTextureForKey(iter->second->GetTextureName());
						toRemoveFrames.push_back(iter->first);
					}
					else
					{
						CCLOG("can remove %s", it->first.c_str());
						toRemoveName.pop_back();
						break;
					}
				}
				else					
				{ 
					break;
				}
			}
		}
	}

	for (auto it = toRemoveName.begin(); it != toRemoveName.end(); it++)
		_spriteFramesCount.erase(*it);

    //for (auto iter = _spriteFrames.begin(); iter != _spriteFrames.end(); ++iter)
    //{
    //    SpriteFrame* spriteFrame = iter->second;
    //    if( spriteFrame->getReferenceCount() == 1 )
    //    {
    //        toRemoveFrames.push_back(iter->first);
    //        CCLOG("cocos2d: SpriteFrameCache: removing unused frame: %s", iter->first.c_str());
    //        removed = true;
    //    }
    //}

    _spriteFrames.erase(toRemoveFrames);
    
    // FIXME:. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    if( removed )
    {
        _loadedFileNames->clear();
    }
}


void SpriteFrameCache::removeSpriteFrameByName(const std::string& name)
{
    // explicit nil handling
    if( !(name.size()>0) )
        return;

    // Is this an alias ?
    std::string key = _spriteFramesAliases[name].asString();

    if (!key.empty())
    {
        _spriteFrames.erase(key);
        _spriteFramesAliases.erase(key);
    }
    else
    {
        _spriteFrames.erase(name);
    }

    // FIXME:. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    _loadedFileNames->clear();
}

void SpriteFrameCache::removeSpriteFramesFromFile(const std::string& plist)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFile: create dict by %s fail.",plist.c_str());
        return;
    }
    removeSpriteFramesFromDictionary(dict);

    // remove it from the cache
    set<string>::iterator ret = _loadedFileNames->find(plist);
    if (ret != _loadedFileNames->end())
    {
        _loadedFileNames->erase(ret);
    }
}

void SpriteFrameCache::removeSpriteFramesFromFileContent(const std::string& plist_content)
{
    ValueMap dict = FileUtils::getInstance()->getValueMapFromData(plist_content.data(), static_cast<int>(plist_content.size()));
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFileContent: create dict by fail.");
        return;
    }
    removeSpriteFramesFromDictionary(dict);
}

void SpriteFrameCache::removeSpriteFramesFromDictionary(ValueMap& dictionary)
{
    ValueMap framesDict = dictionary["frames"].asValueMap();
    std::vector<std::string> keysToRemove;

    for (auto iter = framesDict.cbegin(); iter != framesDict.cend(); ++iter)
    {
        if (_spriteFrames.at(iter->first))
        {
            keysToRemove.push_back(iter->first);
        }
    }

    _spriteFrames.erase(keysToRemove);
}

void SpriteFrameCache::removeSpriteFramesFromTexture(Texture2D* texture)
{
    std::vector<std::string> keysToRemove;

    for (auto iter = _spriteFrames.cbegin(); iter != _spriteFrames.cend(); ++iter)
    {
        std::string key = iter->first;
        SpriteFrame* frame = _spriteFrames.at(key);
        if (frame && (frame->getTexture() == texture))
        {
            keysToRemove.push_back(key);
        }
    }

    _spriteFrames.erase(keysToRemove);
}

SpriteFrame* SpriteFrameCache::getSpriteFrameByName(const std::string& name)
{
	SpriteFrame* frame = _spriteFrames.at(name);
	if (!frame)
	{
#ifdef COCOS2D_STUDIO_SB_PATH_FIX
		// added by aXing on 2017-4-10
		// 因为sb的cocos studio路径和res开发路径不一样，所以要再次搜索
		// 不然的话Android版本会找不到路径
		int nPos = name.find("ui/");
		if (nPos != 0)
		{
			std::string storge_name = "ui/" + name;
			frame = _spriteFrames.at(storge_name);
			if (frame)
				return frame;
		}
#endif

		CCLOGERROR("cocos2d: SpriteFrameCache: Frame '%s' not found", name.c_str());
		// try alias dictionary
		std::string key = _spriteFramesAliases[name].asString();
		if (!key.empty())
		{
			frame = _spriteFrames.at(key);
			if (!frame)
			{
				CCLOG("cocos2d: SpriteFrameCache: Frame '%s' not found", name.c_str());
			}
		}
	}
	//else
	//	frame->retain();

#ifdef COCOS2D_CUSTOM_FIX
	// added by aXing on 2017-4-17
	// 适应项目，添加一个错误纹理的sprite frame，防止程序崩溃
	if (!frame)
	{
		std::string textureName = "error.png";
		frame = _spriteFrames.at(textureName);
		if (!frame)
		{
			frame = SpriteFrame::create(textureName,
				Rect(0, 0, 4, 4), false, Vec2(0, 0), Size(4, 4));
			this->addSpriteFrame(frame, "error.png");
		}
	}
#endif
    return frame;
}

void SpriteFrameCache::addSpriteFramesWithFileEX(const std::string& plist, cocos2d::Vector<Ref*>* refs)
{
	CCASSERT(plist.size() > 0, "plist filename should not be nullptr");

	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
	if (fullPath.size() == 0)
	{
		// return if plist file doesn't exist
		CCLOG("cocos2d: SpriteFrameCache: can not find %s", plist.c_str());
		return;
	}

	if (_loadedFileNames->find(plist) == _loadedFileNames->end())
	{

		ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);

		string texturePath("");

		if (dict.find("metadata") != dict.end())
		{
			ValueMap& metadataDict = dict["metadata"].asValueMap();
			// try to read  texture file name from meta data
			texturePath = metadataDict["textureFileName"].asString();
		}

		if (!texturePath.empty())
		{
			// build texture path relative to plist file
			texturePath = FileUtils::getInstance()->fullPathFromRelativeFile(texturePath.c_str(), plist);
		}
		else
		{
			// build texture path by replacing file extension
			texturePath = plist;

			// remove .xxx
			size_t startPos = texturePath.find_last_of(".");
			texturePath = texturePath.erase(startPos);

			// append .png
			texturePath = texturePath.append(".png");

			CCLOG("cocos2d: SpriteFrameCache: Trying to use file %s as texture", texturePath.c_str());
		}

		Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath.c_str());

		if (texture)
		{
			addSpriteFramesWithDictionaryEX(dict, plist, texturePath, texture, refs);
			_loadedFileNames->insert(plist);
		}
		else
		{
			CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
		}
	}
	else
	{
#ifdef COCOS2D_CUSTOM_FIX
		//从m_plistMapOfSpriteName 搜集引用对象
		if (refs)
		{
			auto sid = m_plistMapOfSpriteName.find(plist);
			if (sid != m_plistMapOfSpriteName.end())
			{
				auto entry = sid->second;
				for (auto it = entry->begin(); it != entry->end(); it++)
				{
					auto sp = getSpriteFrameByName(*it);
					if (sp)
					{
						refs->pushBack(sp);
					}
				}
			}
		}
#endif
	}
}

void SpriteFrameCache::addSpriteFramesWithDictionaryEX(ValueMap& dictionary, const std::string& plist, const std::string& textureName, Texture2D* texture, cocos2d::Vector<Ref*>* refs)
{
	/*
	Supported Zwoptex Formats:

	ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
	ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
	ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
	ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
	*/


	ValueMap& framesDict = dictionary["frames"].asValueMap();
	int format = 0;

	// get the format
	if (dictionary.find("metadata") != dictionary.end())
	{
		ValueMap& metadataDict = dictionary["metadata"].asValueMap();
		format = metadataDict["format"].asInt();
	}

	// check the format
	CCASSERT(format >= 0 && format <= 3, "format is not supported for SpriteFrameCache addSpriteFramesWithDictionary:textureFilename:");

	//auto textureFileName = Director::getInstance()->getTextureCache()->getTextureFilePath(texture);
	//auto image = new Image();
	//image->initWithImageFile(textureFileName);
	//NinePatchImageParser parser;
	tStringList* entry = nullptr;
	auto tid = m_plistMapOfSpriteName.find(plist);
	if (tid == m_plistMapOfSpriteName.end())
	{
		entry = new tStringList();
		m_plistMapOfSpriteName.insert(std::make_pair(plist, entry));
	}

	for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
	{
		ValueMap& frameDict = iter->second.asValueMap();
		std::string spriteFrameName = iter->first;
		SpriteFrame* spriteFrame = _spriteFrames.at(spriteFrameName);
		if (spriteFrame)
		{
			continue;
		}

		if (format == 0)
		{
			float x = frameDict["x"].asFloat();
			float y = frameDict["y"].asFloat();
			float w = frameDict["width"].asFloat();
			float h = frameDict["height"].asFloat();
			float ox = frameDict["offsetX"].asFloat();
			float oy = frameDict["offsetY"].asFloat();
			int ow = frameDict["originalWidth"].asInt();
			int oh = frameDict["originalHeight"].asInt();
			// check ow/oh
			if (!ow || !oh)
			{
				CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
			}
			// abs ow/oh
			ow = abs(ow);
			oh = abs(oh);
			// create frame
			spriteFrame = SpriteFrame::createWithTexture(texture,
				Rect(x, y, w, h),
				false,
				Vec2(ox, oy),
				Size((float)ow, (float)oh)
				);
		}
		else if (format == 1 || format == 2)
		{
			Rect frame = RectFromString(frameDict["frame"].asString());
			bool rotated = false;

			// rotation
			if (format == 2)
			{
				rotated = frameDict["rotated"].asBool();
			}

			Vec2 offset = PointFromString(frameDict["offset"].asString());
			Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());

			// create frame
			spriteFrame = SpriteFrame::createWithTexture(texture,
				frame,
				rotated,
				offset,
				sourceSize
				);
		}
		else if (format == 3)
		{
			// get values
			Size spriteSize = SizeFromString(frameDict["spriteSize"].asString());
			Vec2 spriteOffset = PointFromString(frameDict["spriteOffset"].asString());
			Size spriteSourceSize = SizeFromString(frameDict["spriteSourceSize"].asString());
			Rect textureRect = RectFromString(frameDict["textureRect"].asString());
			bool textureRotated = frameDict["textureRotated"].asBool();

			// get aliases
			ValueVector& aliases = frameDict["aliases"].asValueVector();

			for (const auto &value : aliases) {
				std::string oneAlias = value.asString();
				if (_spriteFramesAliases.find(oneAlias) != _spriteFramesAliases.end())
				{
					CCLOGWARN("cocos2d: WARNING: an alias with name %s already exists", oneAlias.c_str());
				}

				_spriteFramesAliases[oneAlias] = Value(spriteFrameName);
			}

			// create frame
			spriteFrame = SpriteFrame::createWithTexture(texture,
				Rect(textureRect.origin.x, textureRect.origin.y, spriteSize.width, spriteSize.height),
				textureRotated,
				spriteOffset,
				spriteSourceSize);
		}

		//bool flag = NinePatchImageParser::isNinePatchImage(spriteFrameName);
		//if (flag)
		//{
		//	parser.setSpriteFrameInfo(image, spriteFrame->getRectInPixels(), spriteFrame->isRotated());
		//	texture->addSpriteFrameCapInset(spriteFrame, parser.parseCapInset());
		//}
#ifdef COCOS2D_CUSTOM_FIX
		if (refs)
			refs->pushBack(spriteFrame);
		if (entry)
			entry->push_back(spriteFrameName);
#endif // COCOS2D_CUSTOM_FIX
		// add sprite frame
		_spriteFrames.insert(spriteFrameName, spriteFrame);
	}
	//CC_SAFE_DELETE(image);
}

NS_CC_END
