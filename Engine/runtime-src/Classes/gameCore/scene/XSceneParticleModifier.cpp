#include "XSceneParticleModifier.h"
#include "XCommon.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define _JsonHelper cocostudio::DictionaryHelper::getInstance();

XSceneParticleModifier::XSceneParticleModifier() : m_pkParticle(NULL) //m_fSpeedRate(1.0f)
{

}

XSceneParticleModifier::~XSceneParticleModifier()
{

}

bool XSceneParticleModifier::readValues(rapidjson::Value & json)
{
	auto jsonHelper = _JsonHelper;
	m_fSpeedRate = jsonHelper->getFloatValue_json(json, "speed", 1.0f);
	return true;
}


void XSceneParticleModifier::write(rapidjson::Value& json, rapidjson::Document::AllocatorType& _allocator)
{
	json.AddMember("speed", m_fSpeedRate, _allocator);
}

void XSceneParticleModifier::apply()
{

}