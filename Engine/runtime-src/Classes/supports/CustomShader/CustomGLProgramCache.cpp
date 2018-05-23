#include "CustomGLProgramCache.h"



static CustomGLProgramCache *_sharedCustomGLProgramCache = 0;

USING_NS_CC;
using namespace std;

CustomGLProgramCache::CustomGLProgramCache()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	/** listen the event that renderer was recreated on Android/WP8 */
	CCLOG("create rendererRecreatedListener for GLProgramState");
	_backToForegroundlistener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
		[this](EventCustom*)
	{
		CCLOG("reload CustomGLProgram!!!!!!");
		CustomGLProgramCache::getInstance()->reloadGLProgram();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
#endif
}


CustomGLProgramCache::~CustomGLProgramCache()
{
	for (auto it = _programs.begin(); it != _programs.end(); ++it) {
		(it->second)->release();
	}

}


CustomGLProgramCache* CustomGLProgramCache::getInstance()
{
	if (!_sharedCustomGLProgramCache)
	{
		_sharedCustomGLProgramCache = new (std::nothrow) CustomGLProgramCache();
		if (!_sharedCustomGLProgramCache->init())
		{
			CC_SAFE_DELETE(_sharedCustomGLProgramCache);
		}
	}

	return _sharedCustomGLProgramCache;
}

void CustomGLProgramCache::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(_sharedCustomGLProgramCache);
}

bool CustomGLProgramCache::init()
{

	return true;
}

GLProgram* CustomGLProgramCache::getGLProgram(const std::string &key)
{
	auto it = _programs.find(key);
	if (it != _programs.end())
		return it->second;
	CCLOG("Not customGLProgram:%s", key.c_str());
	return GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
}

bool CustomGLProgramCache::addGLProgram(const std::string& key, const std::string& vertString, const std::string& fragString)
{
	// release old one
	bool bRet = false;

	GLProgram* prev = nullptr;
	auto it = _programs.find(key);
	if (it != _programs.end())
	{
		prev = it->second;
	}

	if (prev != nullptr) //ÓÐÖØ¸´µÄkey
	{
		prev->reset();
		bRet = prev->initWithByteArrays(vertString.c_str(), fragString.c_str());
		if (bRet)
		{
			_vertShader[key] = vertString;
			_fragShader[key] = fragString;
		}
		else
		{
			prev->reset();
			prev->initWithByteArrays(_vertShader[key].c_str(), _fragShader[key].c_str());
		}
		prev->link();
		prev->updateUniforms();
	}
	else
	{
		GLProgram* pGL = new GLProgram();
		bRet = pGL->initWithByteArrays(vertString.c_str(), fragString.c_str());
		if (bRet)
		{
			pGL->link();
			pGL->updateUniforms();
			CHECK_GL_ERROR_DEBUG();
			_vertShader[key] = vertString;
			_fragShader[key] = fragString;
			_programs[key] = pGL;
		}
	}

	return bRet;
}

void CustomGLProgramCache::reloadGLProgram()
{
	for (auto itGL = _programs.begin(); itGL != _programs.end(); ++itGL)
	{
		string keyName = itGL->first;
		GLProgram* pGLProgram = itGL->second;
		string strVert = _vertShader[keyName];
		string strFlag = _fragShader[keyName];

		pGLProgram->reset();
		pGLProgram->initWithByteArrays(strVert.c_str(), strFlag.c_str());
		pGLProgram->link();
		pGLProgram->updateUniforms();
		CHECK_GL_ERROR_DEBUG();
	}
}
