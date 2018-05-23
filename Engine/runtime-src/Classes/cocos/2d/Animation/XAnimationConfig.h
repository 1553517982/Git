#include "cocos2d.h"
#include <map>
#include <list>
#include <string>
#include "extention/XBinary/XImageSet.h"
//#include "cocostudio/DictionaryHelper.h"

#ifndef __XAnimationConfig__
#define __XAnimationConfig__
USING_NS_CC;

/*! \class XAnimationConfig
*  \brief 带多动作动画的精灵的配置类

@section XAnimateSprite 动作配置定义

	actions 里面记录的每个动作的定义
	"restoreOriginalFrame" : false,    默认false，当动画播放完毕时，是否恢复到初始帧
	"loop" : 1,   循环次数默认 1</br>
	"delay" : -1, 播放速度，如果是正数就是每帧间隔，如果是负数就是指动画时长
	比如说一个动画有5帧，希望1秒播完，[delay] 可以填写-1,或者1/5 = 0.2
	"frames" 有几种定义方法</br>

	1. "frames" : { "start": 28, "end": 35 }
	从第28帧播放到35帧
	2. "frames": [ [11,1.5,""], [12,0.5,"123"] ]
	依次播放11,12帧，他们的[每帧间隔乘数],分别是1.5, 0.5, 第12帧有帧事件"1,2,3"
	3. "frames" : [ 1,2,3,4,5 ]
	依次播放1,2,3,4,5  [每帧间隔乘数] 1.0,

	解释 [每帧间隔乘数] 比如说上面[delay]是0.2也就是说每一帧播放时长是0.2秒
	最终帧的速度 = [每帧间隔乘数] X [delay]
*/
class XAnimationConfig;

struct XFrameConfig
{
	XFrameConfig() : m_delayUnits(1.0f), m_frameID(0)
	{
	}

	//bool load(rapidjson::Value & json);
	int					m_frameID;
	float				m_delayUnits;
	std::string			m_event;
};

struct XActionConfig
{
	XActionConfig();
	~XActionConfig();
	//bool load(rapidjson::Value & json);
	void Set(bool bRestoreOriginalFrame, int loop, float delay, int nStartFrame, int nEndFrame, int nZOrder);
	std::vector<XFrameConfig>		m_frames;
	XAnimationConfig*				m_animationConfig;
	float							m_delayUnits;
	bool							m_restoreOriginalFrame;
	int								m_loop;
	int								m_nZorder;
};

class XAnimationConfig
{
public:
	XAnimationConfig();
	virtual ~XAnimationConfig();
	bool load(const char* filename);

	/**
	@brief 根据Config创建动画
	@param szSkinname 皮肤名字
	@param actionID   动作ID
	@return Animation*
	*/
	Animation* createAnimation(const char* szSkinname, int actionID, StringMap * texStringMap);

	/**
	@brief 查找动画config
	@param actionID
	@return XActionConfig*
	*/
	XActionConfig* findAction(int actionID);

	std::list<std::string>						m_plists;
	std::vector<XActionConfig>					m_actions;
};
#endif