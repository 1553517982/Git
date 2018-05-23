#ifndef _XSceneObjectModifier_H_
#define _XSceneObjectModifier_H_
#include "cocostudio/DictionaryHelper.h"
#include "cocos2d.h"
USING_NS_CC;

class XSceneObjectModifier : public Ref
{
protected:
	XSceneObjectModifier();
public:

	virtual ~XSceneObjectModifier();

	bool parse(const char* contentStr);

	const char* serialize();

	bool read(rapidjson::Value & json);
	
	virtual void write(rapidjson::Value& json, rapidjson::Document::AllocatorType& _allocator) = 0;

	Node* getTargetRoot() const { return m_pkTarget; }

	void setTargetRoot(Node* val) { m_pkTarget = val; }

protected:
	virtual bool readValues(rapidjson::Value & json) = 0;
	virtual void apply() = 0;
	Node*		m_pkTarget;

};
#endif