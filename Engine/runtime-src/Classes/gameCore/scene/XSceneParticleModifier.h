#ifndef _XSceneParticleModifier_H_
#define _XSceneParticleModifier_H_
#include "XSceneObjectModifier.h"
#include "cocos2d.h"
USING_NS_CC;

class XSceneParticleModifier : public XSceneObjectModifier
{
protected:
	XSceneParticleModifier();
public:

	virtual ~XSceneParticleModifier();

	virtual void write(rapidjson::Value& json, rapidjson::Document::AllocatorType& _allocator) override;

protected:
	virtual bool readValues(rapidjson::Value & json) override;
	virtual void apply() override;

	float	m_fSpeedRate;
	int		m_nPositionMode;
	ParticleSystem*	m_pkParticle;
};
#endif