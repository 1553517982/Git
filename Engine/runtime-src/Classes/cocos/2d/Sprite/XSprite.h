#ifndef _X_XSprite_H_
#define _X_XSprite_H_

#include "cocos2d.h"
#include "supports/XResource/XAsyncLoaderCallbacks.h"

USING_NS_CC;

class XAsyncLoaderCallback;

/*! \class XSprite
*  \brief [lua] 带读取frame文件和异步加载的精灵
*
*
*/

class XSprite : public Sprite
{
public:

	static XSprite* create();

	static XSprite* create(const std::string& filename);

	/**
	@brief	   创建自imageUnit .frame文件
	@param 	   const std::string & filename
	@returns   bool
	*/
	bool initWithImageUnit(const std::string& filename);

	/**
	@brief	   异步加载.frame动画,如果已经有异步加载未完成，如果自身被销毁，自动取消加载
	@param 	   XAsyncLoadOption * option
	@returns   void
	*/
	void loadAnimationAsync(XAsyncLoadOption* option);

	/**
	@brief	   异步加载纹理,如果已经有异步加载未完成，自动取消，如果自身被销毁，自动取消加载
	@param 	   XAsyncLoadOption * option
	@returns   void
	*/
	void loadTextureAsync(XAsyncLoadOption* option);

	/**
	@brief	   取消异步加载
	@returns   void
	*/
	void cancelLoadAsync();

	/**
	@brief	   根据父控件大小设置自己的相对位置
	@param 	   float x  0 - 1.0 为在父控件之内
	@param 	   float y  0 - 1.0 为在父控件之内
	@returns   void
	*/
	void setRelativePosition(float x, float y);

	bool getAutoUpdateBlendFunc() const { return m_bAutoUpdateBlendFunc; }
	void setAutoUpdateBlendFunc(bool val) { m_bAutoUpdateBlendFunc = val; }

	void setXQuad(const V3F_C4B_T2F_Quad& quad);

	virtual void cleanup() override;

	//virtual void update(float dt) override;

protected:
	XSprite();
	virtual ~XSprite();

protected:
	virtual void updateBlendFunc() override;

	XAsyncLoaderCallback*	m_pkCallback;
	bool					m_bAutoUpdateBlendFunc;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(XSprite);
};

#endif