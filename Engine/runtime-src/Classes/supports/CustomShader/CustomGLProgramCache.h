#ifndef __CUSTOMGLPROGRAMCACHE_H__
#define __CUSTOMGLPROGRAMCACHE_H__


#include <string>
#include <unordered_map>

#include "cocos2d.h"

class CustomGLProgramCache : public cocos2d::Ref
{
public:
	~CustomGLProgramCache();

	static CustomGLProgramCache* getInstance();
	static void destroyInstance();
	cocos2d::GLProgram* getGLProgram(const std::string &key);
	bool addGLProgram(const std::string& key, const std::string& vertString, const std::string& fragString);

	void reloadGLProgram();
protected:
	CustomGLProgramCache();
	bool init();

protected:
	std::unordered_map<std::string, cocos2d::GLProgram*>		_programs;
	std::unordered_map<std::string, std::string>	_vertShader;
	std::unordered_map<std::string, std::string>	_fragShader;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	cocos2d::EventListenerCustom* _backToForegroundlistener;
#endif
};

#endif
