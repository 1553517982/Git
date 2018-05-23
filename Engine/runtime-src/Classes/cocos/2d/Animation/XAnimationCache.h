#include "cocos2d.h"
#include <map>
#include <list>
#include <string>
#include "cocos/2D/Animation/XAnimationConfig.h"

#ifndef __XAnimationCache__
#define __XAnimationCache__
USING_NS_CC;

/*! \class XAnimationCache
*  \brief XAnimation 动画缓存
*
*
*/
class XAnimationCache : public Ref
{
	XAnimationCache();
	virtual ~XAnimationCache();
public:

	/** Returns the shared instance of the Animation cache */
	static XAnimationCache* getInstance();

	bool init(void);

	bool loadAnimationConfig(const std::string& name);

	XAnimationConfig* getAnimationConfig(const std::string& filename);

	Animation* findAnimation(const std::string& name);

	Animation* createAnimation(const std::string& name, float delayUnits, bool restoreOriginalFrame, int loops);

	bool getSpriteFrame(const std::string& name, Vector<SpriteFrame*>* frameArray);

	bool getSpriteFrameMap(const std::string& name, Map<unsigned int, SpriteFrame*>* frameArray);

	void addAnimation(Animation *animation, const std::string& name);

	void removeAnimation(const std::string& name);

	void removeUnusedAnimations();

	void clearAnimations();

private:
	std::map<std::string, XAnimationConfig>	_animationConfigs;
	std::map<std::string, Animation*>		_animations;
	static XAnimationCache*				s_sharedAnimationCache;
};
#endif