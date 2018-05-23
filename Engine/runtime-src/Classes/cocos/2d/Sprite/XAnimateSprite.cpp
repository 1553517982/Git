#include "XCommon.h"
#include "cocos/2d/Sprite/XAnimateSprite.h"
#include "cocos/2d/Animation/XAnimationCache.h"
#include "cocos/2d/Animation/XAnimate.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/math/Vec2.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "supports/XResource/XAsyncLoaderManager.h"

#define CHECK_DELAY_FRAME 3

XAnimateSprite::XAnimateSprite() : 
	m_nActionID(Action::INVALID_TAG),
	m_nResumeActionID(Action::INVALID_TAG),
	m_pkAnimationConfig(NULL),
	m_nUpdateDelay( 0 ),
	m_nCheck( 0 ),
	m_loadedCount(-1)
{
	m_holder = XRefHolder::create();
	m_holder->retain();
}

XAnimateSprite::~XAnimateSprite()
{
	//CC_SAFE_RELEASE_NULL(m_pkAnimationConfig);
	for (auto it = m_pkLoadCallbacks.begin(); it != m_pkLoadCallbacks.end(); it++)
	{
		(*it)->cancel();
	}
	m_pkLoadCallbacks.clear();		// 虽然不知道为什么，不过保险期间，不要去频繁地清空回调，vector会报越界

	//if (m_skinName.size())
	//	SpriteFrameCache::getInstance()->reduceCacheWithResName(m_skinName);

	m_holder->release();
}

XAnimateSprite* XAnimateSprite::create()
{
	XAnimateSprite *sprite = new (std::nothrow) XAnimateSprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void XAnimateSprite::setDefaultFrame(int index)
{
	if (m_skinName.empty())
	{
		XLOGERROR("XAnimateSprite::setDefaultFrame error");
		return;
	}
	setDefaultFrame(m_skinName.c_str(), index);
}
void XAnimateSprite::Jump( float sec, float height )
{
	cocos2d::Vec2 vec( 0, 0 );
	ActionInterval* pkAction = JumpBy::create(sec, vec, height, 1);
	auto event = [=]
	{
		
	};
	pkAction = Sequence::createWithTwoActions(pkAction, CallFunc::create(event));
	pkAction->setTag(XDefault_Tags::eAnimateSpriteAnimateTag);
	runAction(pkAction);
}

void XAnimateSprite::KnockDown(float duration, float xspeed, float yspeed)
{
	ActionInterval* pkAction = KnockDown::create(duration, xspeed, yspeed);
	auto event = [=]
	{
		// 由于lua上面记着了，所以只能告诉lua搞定了
	};
	pkAction = Sequence::createWithTwoActions(pkAction, CallFunc::create(event));
	pkAction->setTag(XDefault_Tags::eAnimateSpriteAnimateTag);
	runAction(pkAction);
}

void XAnimateSprite::setDefaultFrame(const char* filename, int index)
{
	//设置当前帧
	//XImageUnitList* pkList = XImageSetMgr::Inst().getFrameList(filename);
	//if (!pkList)
	//	return;

	//XImageUnit* pkUnit = &pkList->at(index);
	//const std::string textureName = pkUnit->textureName;

	//SpriteFrame *spriteFrame = SpriteFrame::create(textureName,
	//	Rect(pkUnit->x, pkUnit->y, pkUnit->width, pkUnit->height),
	//	pkUnit->rotation,
	//	Vec2(pkUnit->offsetX, pkUnit->offsetY),
	//	Size(pkUnit->sourceSizeX, pkUnit->sourceSizeY));
	//this->setSpriteFrame(spriteFrame);
}

void XAnimateSprite::setActionConfig(const char* actionConfig)
{
	//设置actionConfig
	//CC_SAFE_RELEASE_NULL(m_pkAnimationConfig);
	m_pkAnimationConfig = XAnimationCache::getInstance()->getAnimationConfig(actionConfig);
	//CC_SAFE_RETAIN(m_pkAnimationConfig);
}

bool XAnimateSprite::hasActionConfig(int id)
{
	if (m_pkAnimationConfig == NULL)
		return false;

	return m_pkAnimationConfig->findAction(id) != NULL;
}

bool XAnimateSprite::playAnimation(const char* name, float delayUnits, bool restoreOriginalFrame, int loops)
{
	//if (!name)
		return false;
}

FiniteTimeAction* XAnimateSprite::prepareAction(int actionID, bool repeatforever, StringMap * texStringMap)
{
	if (actionID == Action::INVALID_TAG)
	{
		if (m_nActionID != Action::INVALID_TAG)
		{
			this->stopActionByTag(m_nActionID);
			m_nActionID = actionID;
		}
		return nullptr;
	}
	
	if (m_nActionID != Action::INVALID_TAG)
	{
		this->stopActionByTag(m_nActionID);
	}

	m_nActionID = actionID;
	m_bRepeatforever = repeatforever;

	if (m_skinName.empty() || actionID == Action::INVALID_TAG)
	{
		return NULL;
	}

	if (m_pkAnimationConfig == NULL)
	{
		setDefaultFrame(m_skinName.c_str(), 0);
		return NULL;
	}

	Animation* pkAnimation = m_pkAnimationConfig->createAnimation(m_skinName.c_str(), m_nActionID, texStringMap);
	if (!pkAnimation)
		return NULL;

	if (texStringMap)
		return NULL;

	XActionConfig * pConfig = m_pkAnimationConfig->findAction(m_nActionID);

	ActionInterval* pkAction = XAnimate::create(pkAnimation);
	setLocalZOrder(pConfig->m_nZorder);

	((XAnimate*)pkAction)->setListenEvent(m_pkAnimationEventCallback != nullptr);

	((XAnimate*)pkAction)->setListenFrame(m_pkFrameCallback != nullptr);

	if (m_bRepeatforever)
	{
		pkAction = RepeatForever::create(pkAction);
	}

	pkAction->setTag(actionID);
	return pkAction;
}
bool XAnimateSprite::playAction(int actionID, bool repeatforever)
{
	if (m_loadedCount != 0)
	{
		m_nResumeActionID		= actionID;
		m_bResumeRepeatforever	= repeatforever;
		return false;
	}
	auto pkAction = prepareAction(actionID, repeatforever, 0);
	if (!pkAction)
	{
		return false;
	}
	
	this->runAction(pkAction);
	return true;
}

bool XAnimateSprite::setSkinName(const char* filename)
{
	m_skinName = filename;
	return true;
}  

bool XAnimateSprite::initWithActionFile(std::string & skinName, std::string & actionFile)
{
	
	if (!skinName.length() || !actionFile.length())
	{
		XLOGERROR("initWithActionFile failed to load actionFile %s %s", skinName.c_str(), actionFile.c_str());
		return false;
	}
	// 如果加载的是同一个皮肤
	if (m_skinName == skinName)
	{
		return true;
	}
	// 加载不同的皮肤的时候，需要把以前的皮肤回调都cancel掉
	for (auto it = m_pkLoadCallbacks.begin(); it != m_pkLoadCallbacks.end(); it++)
	{
		(*it)->cancel();
	}

	// 从这里开始正式进入动画加载
	setActionConfig(actionFile.c_str());

	// 这里需要去释放sprintFrame吗？ 需要思考
	// 但一定不会用皮肤名字去释放
	//SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	//pCache->reduceCacheWithResName(m_skinName);
	m_skinName.clear();

	// 释放以前的皮肤贴图
	cocos2d::Vector<Ref*>* refs = m_holder->getRefs();
	refs->clear();
	
	setSkinName(skinName.c_str());
	// 令到动画不能播放，直到下载完贴图，依赖完成才播放
	// removed by aXing on 2017-4-18
	// 不能这么做，因为逻辑上有可能需要setVisible，这样的话就和这个逻辑冲突了
//	this->setVisible(false);	
	// added by aXing on 2017-4-9
	// 因为已经读取依赖的时候已经按绝对路径去读取了，所以不需要再分析皮肤文件了
	// 不过需要去获取皮肤依赖贴图列表
	std::list<std::string> * textureList = CNewLoader::Inst().LoadResDepenence(m_skinName.c_str());
	if (textureList)
	{
		m_loadedCount = textureList->size();
		if (m_loadedCount == 0)
		{
			XLOGERROR("XAnimateSprite skin %s error! no texture list", m_skinName.c_str());
		}
		
		// 然后进行加载
		for (auto it = textureList->begin(); it != textureList->end(); it++)
		{
			this->loadAsync(*it);
		}
	}
	else
	{
		XLOGERROR("XAnimateSprite skin %s can`t be found", m_skinName.c_str());
		return false;
	}
	
	return true;
}

void XAnimateSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if ( m_loadedCount == 0)
	{
		CCSprite::draw(renderer, transform, flags);
	}
}

void XAnimateSprite::cleanup()
{
	Node::cleanup();
	if (m_pkAnimationEventCallback)
		m_pkAnimationEventCallback = nullptr;

	if (m_pkFrameCallback)
		m_pkFrameCallback = nullptr;
}

void XAnimateSprite::setFrameCallback(std::function<void(int)> val)
{
	m_pkFrameCallback = val;
}

void XAnimateSprite::onXAnimateEvent(XAnimate* who, int stage, const ValueMap* vm)
{
	if (m_pkAnimationEventCallback)
	{
		m_pkAnimationEventCallback(stage, vm);
	}
	else
	{
		who->setListenEvent(false);
	}
}

void XAnimateSprite::onXAnimateFrame(XAnimate* who, int frameID)
{
	if (m_pkFrameCallback)
	{
		m_pkFrameCallback(frameID);
	}
	else
	{
		who->setListenFrame(false);
	}
}

void XAnimateSprite::loadAsync(const std::string&filename)
{
	XAsyncLoaderCallback* callback = XAsyncLoaderCallback::create();
	callback->init(CC_CALLBACK_1(XAnimateSprite::onTextureAsyncLoad, this));
	XAsyncLoaderManager::sharedManager()->loadTexture(filename, filename, Priority::ANIMATION, callback);
	m_pkLoadCallbacks.pushBack(callback);
}

void XAnimateSprite::onTextureAsyncLoad(const XAsyncLoaderRet* retCode)
{
	// 如果成功，提示成功
	XAsyncLoaderCode result = (XAsyncLoaderCode)retCode->ret();
//	XLOG("XAnimateSprite::onTextureAsyncLoad:: %d %d %s", retCode->ret(), m_loadedCount, m_skinName.c_str());
	if (result == XAsyncLoaderCode::eOK)
	{
		m_loadedCount--;

		if (m_loadedCount == 0)
		{
			// removed by aXing on 2017-4-18
			// 不能这么做，因为逻辑上有可能需要setVisible，这样的话就和这个逻辑冲突了
//			this->setVisible(true);
			// 回复
			if (m_nResumeActionID != Action::INVALID_TAG)
			{
				this->playAction(m_nResumeActionID, m_bResumeRepeatforever);
			}

			// 既然做完了，就直接清掉所有的回调
			for (auto it = m_pkLoadCallbacks.begin(); it != m_pkLoadCallbacks.end(); it++)
			{
				(*it)->cancel();
			}
		}
		Texture2D* pkTex2D = (Texture2D*)retCode->data();
		m_holder->addRef(pkTex2D);
		//this->setTexture(pkTex2D);
		//this->setTextureRect(Rect(0, 0, pkTex2D->getPixelsWide(), pkTex2D->getPixelsHigh()));
		//this->setVisible(true);
	}
	else
	{
		XLOGERROR("XAnimateSprite %s load Texture Failed", m_skinName.c_str());
//		this->setTexture(nullptr);
	}
}

void XAnimateSprite::onTextureLoadEnd()
{
	//m_pkLoadCallbacks.clear();
}