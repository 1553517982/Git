#ifndef __XCSBNode__
#define __XCSBNode__

#include "cocos2d.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "supports/XResource/XAsyncLoaderCallbacks.h"
#include "cocos/2d/SlotAnimation/XSlotProtocol.h"
#include "cocos/studio_ext/XCSLoader.h"
#include "helpers/XLambda.h"

USING_NS_CC;

class XCSBNode : public Node, public XSlotProtocol
{
protected:
	XCSBNode();
public:
	virtual ~XCSBNode();
	static XCSBNode* create();

	bool load(const std::string& filename, bool bTimeline);

	void loadAsync(XAsyncLoadOption* option, bool bTimeline);

	bool play(const std::string& name, bool loop);

	bool gotoFrameAndPlay(int start_index, int end_index,  bool loop);

	bool gotoFrameAndPlay(int start_index, bool loop);
	/**
	@brief	   取消异步加载
	@returns   void
	*/
	void cancelLoadAsync();

	Node* getNode();

	virtual void setSpriteFrameByIndex(int index, Sprite* parent);

	cocostudio::timeline::ActionTimeline* getTimeLine();

	void clearCSB();

	void setNodeCallback(XLambda* luaFunction);

protected:

	void onTextureAsyncLoad(const XAsyncLoaderRet* retCode);

	cocostudio::timeline::ActionTimeline* m_pkTimeline;
	Node*								  m_pkNode;
	XAsyncLoaderCallback*				  m_pkCallback;
	std::string							  m_currentAnimationName;
	XAsyncLoadOption*					  m_asyncOption;
	ccNodeLoadCallback					  m_asyncNodeCallback;
};

#endif /* defined(__cocos2d_libs__CSLoader__) */
