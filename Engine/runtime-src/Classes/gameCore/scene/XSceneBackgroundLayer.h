#ifndef _XSceneBackgroundLayer_H_
#define _XSceneBackgroundLayer_H_
#include "cocos2d.h"
#include "scene/XSceneLayer.h"
#include "cocostudio/DictionaryHelper.h"
#include "scene/XGameTile.h"
USING_NS_CC;

class XSceneBackgroundLayer : public XSceneLayer
{
protected:
	XSceneBackgroundLayer();
public:


	virtual ~XSceneBackgroundLayer();
	static XSceneBackgroundLayer* create();

	virtual void onPause() override;

	virtual void onResume() override;

	void setBackground(const std::string& strBackground);

	void transfomUV(float dt);



	cocos2d::CCSprite * Background() const { return m_pkBackground; }
	void Background(cocos2d::CCSprite * val) { m_pkBackground = val; }

	void setShadername(const std::string& name);

	virtual void readLayer(rapidjson::Value& entry, int layerID, ParallaxNode* parent, const char* prefix);

	cocos2d::Vec2 getBasePos() const { return m_basePos; }
	void setBasePos(cocos2d::Vec2 val);

	cocos2d::Vec2 getBaseScale() const { return m_baseScale; }
	void setBaseScale(cocos2d::Vec2 val);

	cocos2d::Vec2 getUVTranslate() const { return m_UVTranslate; }
	void setUVTranslate(cocos2d::Vec2 val);

protected:
	void initUVTranslate(float x, float y);

	cocos2d::CCSprite *		m_pkBackground;
	std::string		m_strBackground;
	std::string		m_strShadername;
	Vec2			m_UVTranslate;

	Vec2			m_basePos;
	Vec2			m_baseScale;
};
#endif