#include "XActionTimelineCache.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
/* peterson */
using namespace flatbuffers;
/**/

static XActionTimelineCache* _sharedActionCache = nullptr;

XActionTimelineCache* XActionTimelineCache::getInstance()
{
    if (! _sharedActionCache)
    {
		_sharedActionCache = new (std::nothrow) XActionTimelineCache();
        _sharedActionCache->init();
    }

    return _sharedActionCache;
}

void XActionTimelineCache::destroyInstance()
{
    CC_SAFE_DELETE(_sharedActionCache);
}

cocostudio::timeline::ActionTimeline* XActionTimelineCache::loadAnimationActionWithData(const std::string &fileName, void* data)
{
    // if already exists an action with filename, then return this action
	cocostudio::timeline::ActionTimeline* action = _animationActions.at(fileName);
    if (action)
        return action->clone();
    
    //std::string path = fileName;
    //
    //std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
    //
    //CC_ASSERT(FileUtils::getInstance()->isFileExist(fullPath));
    //
    //Data buf = FileUtils::getInstance()->getDataFromFile(fullPath);
    //
    //auto csparsebinary = GetCSParseBinary(buf.getBytes());
    
	CSParseBinary* csparsebinary = ((CSParseBinary*)data);

    auto nodeAction = csparsebinary->action();    
	action = cocostudio::timeline::ActionTimeline::create();
    
    int duration = nodeAction->duration();
    action->setDuration(duration);
    float speed = nodeAction->speed();
    action->setTimeSpeed(speed);
    
    auto animationlist = csparsebinary->animationList();
    int animationcount = animationlist->size();
    for (int i = 0; i < animationcount; i++)
    {
        auto animationdata = animationlist->Get(i);
        cocostudio::timeline::AnimationInfo info;
        info.name = animationdata->name()->c_str();
        info.startIndex = animationdata->startIndex();
        info.endIndex = animationdata->endIndex();
        action->addAnimationInfo(info);
    }

    auto timelines = nodeAction->timeLines();
    int timelineLength = timelines->size();
    for (int i = 0; i < timelineLength; i++)
    {
        auto timelineFlatBuf = timelines->Get(i);
        Timeline* timeline = loadTimelineWithFlatBuffers(timelineFlatBuf);
        
        if (timeline)
            action->addTimeline(timeline);
    }
    
    _animationActions.insert(fileName, action);
    
    return action;
}