#ifndef __cocos2d_libs__XCSLoaderRet__
#define __cocos2d_libs__XCSLoaderRet__
#include "cocos2d.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "XCommon.h"
#include "cocos2d.h"

USING_NS_CC;

class XCSLoadRet : Ref
{
protected:
	XCSLoadRet() : m_pkNode(NULL), m_pkTimeline(NULL)
	{

	}
	virtual ~XCSLoadRet()
	{
		CC_SAFE_RELEASE_NULL(m_pkNode);
		CC_SAFE_RELEASE_NULL(m_pkTimeline);
	}
public:
	static XCSLoadRet* create(Node* n);
	Node* getNode() const {
		return m_pkNode;
	}
	void setNode(Node* val)
	{
		CC_SAFE_RETAIN(val);
		CC_SAFE_RELEASE_NULL(m_pkNode);
		m_pkNode = val;
	}
	void setTimeline(cocostudio::timeline::ActionTimeline* val) {
		CC_SAFE_RETAIN(val);
		CC_SAFE_RELEASE_NULL(m_pkTimeline);
		m_pkTimeline = val;
	}
	cocostudio::timeline::ActionTimeline* getTimeline() const { return m_pkTimeline; }
private:
	Node*								  m_pkNode;
	cocostudio::timeline::ActionTimeline* m_pkTimeline;
};
#endif