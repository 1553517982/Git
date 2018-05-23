
/************************************************************************/
/* XSlotAnimationConfig  读取slot配件和主动画之间的关系配置
/************************************************************************/

#ifndef	_XSlotAnimation_CONFIG_H_ 
#define _XSlotAnimation_CONFIG_H_
#include "cocos2d.h"
#include "cocostudio/DictionaryHelper.h"
#include "XSlotFrames.h"
#include <map>

USING_NS_CC;

//一个启动sprite，有n个slot
	//wing
typedef Map<std::string, XSlotFrames*>			tSlotFrameMap;

// 所有的驱动sprite 和 各个slot
typedef std::map<std::string, tSlotFrameMap*>	tAllSlotAnimations;

class XSlotAnimationConfig
{
public:
	XSlotAnimationConfig();
	~XSlotAnimationConfig();
	
	static XSlotAnimationConfig*	sharedManager();

	static void						purgeSharedManager();

	/**
	@brief	   获取一个主动画的Slot配置，如果没有找到就读取
	@param 	   const char * szFilename
	@returns   tSlotFrameMap*
	*/
	tSlotFrameMap*					getSlotFrames(const char* szFilename);

	/**
	@brief	   读取一个主动画的Slot配置，会在szFilename 后面添上.json
	@param 	   const char * szFilename
	@returns   tSlotFrameMap*
	*/
	tSlotFrameMap*					loadSlotFrames(const char* szFilename);

	void							clear();
private:
	//身体对应的slot的帧变换
	tAllSlotAnimations*				m_pkAllSlotAnimationDictionary;

};

#endif