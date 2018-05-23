#include "cocos/2d/Animation/XAnimationConfig.h"
#include "cocos/2d/Animation/XAnimationCache.h"
#include "cocos/2d/Animation/XAnimationFrame.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "base/TableFile//CTableFile.h"
#include "XCommon.h"

USING_NS_CC;

XActionConfig::XActionConfig()
{

}

XActionConfig::~XActionConfig()
{
}

void XActionConfig::Set(bool bRestoreOriginalFrame, int loop, float delay, int nStartFrame, int nEndFrame, int nZOrder)
{
	m_restoreOriginalFrame = bRestoreOriginalFrame;
	m_loop = loop;
	m_delayUnits = delay;
	m_nZorder = nZOrder;
	int size = nEndFrame - nStartFrame + 1;
	m_frames.resize(size);
	for (int i = nStartFrame; i <= nEndFrame; i++)
	{
		XFrameConfig & frame = m_frames[i-nStartFrame];
		frame.m_delayUnits = delay;
		//	pkFrame->m_delayUnits = 1; 为什么之前是1？？？？？？？！！！！！！！！
		frame.m_frameID = i;
	}
}


XAnimationConfig::XAnimationConfig()
{

}


XAnimationConfig::~XAnimationConfig()
{
}

bool XAnimationConfig::load(const char* filename)
{
#if 0
	std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(filename);
	if (jsonpath.empty())
		return false;
#endif

	char * pData = 0;
	unsigned int nDataLength;
	CNewLoader::Inst().SyncLoadFile(filename, &pData, &nDataLength);

	bool ret = false;
	if (!pData)
		return ret;
	CTableFile tFile;
	if (tFile.LoadTableBuff(pData, nDataLength))
	{
		static const int nRestoreOriginalFrame = 0;
		static const int nLoop = 1;
		static const int nDelay = 2;
		static const int nFrameStart = 3;
		static const int nFrameEnd = 4;
		static const int nZOrder = 5;

		int nHeight = tFile.GetHeight();
		m_actions.resize(nHeight-1);
		for (int id = 1; id < nHeight; id++)
		{
			XActionConfig & con = m_actions[id - 1];
			con.m_animationConfig = this;
			con.Set(!!tFile.GetInteger(id, nRestoreOriginalFrame), tFile.GetInteger(id, nLoop), tFile.GetReal(id, nDelay), tFile.GetInteger(id, nFrameStart), tFile.GetInteger(id, nFrameEnd), tFile.GetInteger(id, nZOrder));
		}
		ret = true;
	}
	return ret;
}

Animation* XAnimationConfig::createAnimation(const char* szSkinname, int actionID, StringMap * texStringMap)
{
	Animation* pkAnimation;

	char key[512] = { 0 };
	sprintf(key, "%s_%d", szSkinname, actionID);

	pkAnimation = XAnimationCache::getInstance()->findAnimation(key);
	if( pkAnimation )
		return pkAnimation;
	
	XActionConfig* pkActionConfig = findAction(actionID);
	if (!pkActionConfig)
	{
		XLOGERROR("XAnimationConfig::createAnimation %s not action = %d", szSkinname, actionID);
		return 0;
	}

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	//if (!pCache->addSpriteFramesWithResName(szSkinname, texStringMap))
	//{
	//	XLOGERROR("no file with name %s", szSkinname);
	//	return 0;
	//}

	const std::vector<XFrameConfig> & frames = pkActionConfig->m_frames;

	size_t frame_size = frames.size();
	Vector<AnimationFrame*> array(frame_size);
	
	for (size_t i = 0; i < frame_size; i++)
	{
		const XFrameConfig* fc = &frames[i];
		char tmpKey[128] = { 0 };
		sprintf(tmpKey, "%s/%05d.png", szSkinname, fc->m_frameID);
		SpriteFrame *spriteFrame = pCache->getSpriteFrameByName(std::string(tmpKey));
		if ( !spriteFrame)
		{
			XLOGERROR("XAnimationConfig::createAnimation not found in %s, %d", tmpKey);
			return 0;
		}

		//if (fc->m_frameID >= image_size)
		//{
		//	XLOGERROR("failed to create animation from %s %d", szSkinname, actionID);
		//	return NULL;
		//}
		//XImageUnit* pkUnit = &pkImageUnits->at(fc->m_frameID);
		//SpriteFrame *spriteFrame = pkCache->getSpriteFrameByName(pkUnit->imageName);
		//if (spriteFrame == nullptr)
		//{
		//	const std::string textureName = pkUnit->textureName;
		//	spriteFrame = SpriteFrame::create( textureName,
		//									   Rect(pkUnit->x, pkUnit->y, pkUnit->width, pkUnit->height),
		//									   pkUnit->rotation,
		//									   Vec2(pkUnit->offsetX, pkUnit->offsetY),
		//									   Size(pkUnit->sourceSizeX, pkUnit->sourceSizeY) );
		//	pkCache->addSpriteFrame(spriteFrame, pkUnit->imageName);
		//}

		XAnimationFrame *animFrame = NULL;

		//监听每一帧
		if (fc->m_event.empty())
		{
			animFrame = XAnimationFrame::create(spriteFrame, fc->m_delayUnits, ValueMapNull);
		}
		else
		{
			ValueMap _event;


			_event["i"] = Value(fc->m_frameID);
			_event["e"] = Value(fc->m_event);

			animFrame = XAnimationFrame::create(spriteFrame, fc->m_delayUnits, _event);
		}
		animFrame->setFrameID(fc->m_frameID);
		array.pushBack(animFrame);
	}
	
	int loop = 1;
	if (pkActionConfig->m_loop > 0)
	{
		loop = pkActionConfig->m_loop;
	}
	pkAnimation = Animation::create(array, pkActionConfig->m_delayUnits, loop);
	pkAnimation->setRestoreOriginalFrame(pkActionConfig->m_restoreOriginalFrame);

	XAnimationCache::getInstance()->addAnimation(pkAnimation, key);
	return pkAnimation;
}

XActionConfig* XAnimationConfig::findAction(int actionID)
{
	if (actionID >= m_actions.size())
		return 0;
	return &m_actions[actionID];
}