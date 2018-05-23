#include "cocos/2D/Animation/XAnimationCache.h"
#include "XAnimationFrame.h"
USING_NS_CC;

#define _JsonHelper cocostudio::DictionaryHelper::getInstance()

XAnimationCache* XAnimationCache::getInstance()
{
	static XAnimationCache inst;
	return &inst;
}

XAnimationCache::XAnimationCache()
{
}

XAnimationCache::~XAnimationCache()
{
	clearAnimations();
}

bool XAnimationCache::loadAnimationConfig(const std::string& name)
{
	return getAnimationConfig(name) != NULL;
}

XAnimationConfig* XAnimationCache::getAnimationConfig(const std::string& name)
{
	std::map<std::string, XAnimationConfig>::iterator iter = _animationConfigs.find(name);
	
	if (iter != _animationConfigs.end())
		return &iter->second;

	XAnimationConfig & con = _animationConfigs[name];
	if (!con.load(name.c_str()))
	{
		_animationConfigs.erase(name);
		return 0;
	}
	return &con;
}

void XAnimationCache::addAnimation(Animation *animation, const std::string& name)
{
	animation->retain();
	_animations[name] = animation;
	//_animations.insert(name, animation);
}

void XAnimationCache::removeAnimation(const std::string& name)
{
	std::map<std::string, Animation*>::iterator it = _animations.find(name);
	if (it != _animations.end())
	{
		it->second->release();
		_animations.erase(it);
	}
}

Animation* XAnimationCache::findAnimation(const std::string& name)
{
	std::map<std::string, Animation*>::iterator it = _animations.find(name);
	if (it == _animations.end())
		return 0;
	return it->second;
}

void XAnimationCache::removeUnusedAnimations()
{
	for (auto it = _animations.cbegin(); it != _animations.cend(); /* nothing */) {
		Animation *animation = it->second;
		if (animation->getReferenceCount() == 1) {
			CCLOG("cocos2d: XAnimationCache: removing unused animation: %s", it->first.c_str());
			_animations.erase(it++);
		}
		else {
			++it;
		}
	}
}

void XAnimationCache::clearAnimations()
{
	for (std::map<std::string, Animation*>::iterator it = _animations.begin(); it != _animations.end(); it++)
		it->second->release();
	_animations.clear();
}

Animation* XAnimationCache::createAnimation(const std::string& name, float delayUnits, bool restoreOriginalFrame, int loops)
{
	return 0;
	//XImageUnitList* pkImageUnits = XImageSetMgr::Inst().getFrameList(name.c_str());
	//if (!pkImageUnits)
	//{
	//	return NULL;
	//}

	//Animation* pkAnimation = nullptr;
	//const char* key = name.c_str();
	///*
	//pkAnimation = findAnimation(key);
	//if (pkAnimation)
	//	return pkAnimation;
	//*/
	//size_t frame_size = pkImageUnits->size();
	//Vector<AnimationFrame*> array(frame_size);
	//SpriteFrameCache* pkCache = SpriteFrameCache::getInstance();

	//for (size_t i = 0; i < frame_size; i++)
	//{
	//	XImageUnit* pkUnit = &pkImageUnits->at(i);
	//	SpriteFrame *spriteFrame = pkCache->getSpriteFrameByName(pkUnit->imageName);
	//	if (spriteFrame == nullptr)
	//	{
	//		const std::string textureName = pkUnit->textureName;
	//		spriteFrame = SpriteFrame::create(textureName,
	//			Rect(pkUnit->x, pkUnit->y, pkUnit->width, pkUnit->height),
	//			pkUnit->rotation,
	//			Vec2(pkUnit->offsetX, pkUnit->offsetY),
	//			Size(pkUnit->sourceSizeX, pkUnit->sourceSizeY));
	//		XAssert(spriteFrame->getTexture(), "spriteFrame != null");
	//		pkCache->addSpriteFrame(spriteFrame, pkUnit->imageName);
	//	}
	//	XAnimationFrame *animFrame = animFrame = XAnimationFrame::create(spriteFrame, 1.0, ValueMapNull);
	//	array.pushBack(animFrame);
	//}

	//pkAnimation = Animation::create(array, delayUnits, loops);
	//pkAnimation->setRestoreOriginalFrame(restoreOriginalFrame);

	//return pkAnimation;
}


bool XAnimationCache::getSpriteFrame(const std::string& name, Vector<SpriteFrame*>* frameArray)
{
	//XImageUnitList* pkImageUnits = XImageSetMgr::Inst().getFrameList(name.c_str());
	//if (!pkImageUnits)
	//{
		return false;
	//}

	//size_t frame_size = pkImageUnits->size();
	//SpriteFrameCache* pkCache = SpriteFrameCache::getInstance();

	//for (size_t i = 0; i < frame_size; i++)
	//{
	//	XImageUnit* pkUnit = &pkImageUnits->at(i);
	//	SpriteFrame *spriteFrame = pkCache->getSpriteFrameByName(pkUnit->imageName);
	//	int frameID = XImageSet::nameToIndex(pkUnit->imageName);
	//	if (spriteFrame == nullptr)
	//	{
	//		const std::string textureName = pkUnit->textureName;
	//		spriteFrame = SpriteFrame::create(textureName,
	//			Rect(pkUnit->x, pkUnit->y, pkUnit->width, pkUnit->height),
	//			pkUnit->rotation,
	//			Vec2(pkUnit->offsetX, pkUnit->offsetY),
	//			Size(pkUnit->sourceSizeX, pkUnit->sourceSizeY));
	//		XAssert(spriteFrame->getTexture(), "spriteFrame != null");
	//		pkCache->addSpriteFrame(spriteFrame, pkUnit->imageName);
	//	}
	//	frameArray->pushBack(spriteFrame);
	//}
	//return true;
}

bool XAnimationCache::getSpriteFrameMap(const std::string& name, Map<unsigned int, SpriteFrame*>* frameMap)
{
	//XImageUnitList* pkImageUnits = XImageSetMgr::Inst().getFrameList(name.c_str());
	//if (!pkImageUnits)
	//{
		return false;
	//}

	//size_t frame_size = pkImageUnits->size();
	//SpriteFrameCache* pkCache = SpriteFrameCache::getInstance();

	//for (size_t i = 0; i < frame_size; i++)
	//{
	//	XImageUnit* pkUnit = &pkImageUnits->at(i);
	//	SpriteFrame *spriteFrame = pkCache->getSpriteFrameByName(pkUnit->imageName);
	//	int frameID = XImageSet::nameToIndex(pkUnit->imageName);
	//	if (spriteFrame == nullptr)
	//	{
	//		const std::string textureName = pkUnit->textureName;
	//		spriteFrame = SpriteFrame::create(textureName,
	//			Rect(pkUnit->x, pkUnit->y, pkUnit->width, pkUnit->height),
	//			pkUnit->rotation,
	//			Vec2(pkUnit->offsetX, pkUnit->offsetY),
	//			Size(pkUnit->sourceSizeX, pkUnit->sourceSizeY));
	//		XAssert(spriteFrame->getTexture(), "spriteFrame != null");
	//		pkCache->addSpriteFrame(spriteFrame, pkUnit->imageName);
	//	}
	//	frameMap->insert(frameID, spriteFrame);
	//}
	//return true;
}