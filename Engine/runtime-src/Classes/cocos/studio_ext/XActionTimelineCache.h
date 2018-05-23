

#ifndef __X_CCTIMELINE_ACTION_CACHE_H__
#define __X_CCTIMELINE_ACTION_CACHE_H__
#include "cocostudio/ActionTimeline/CCActionTimelineCache.h"

class XActionTimelineCache : public cocostudio::timeline::ActionTimelineCache
{
public:    
    
    /** Gets the singleton */
	static XActionTimelineCache* getInstance();

    /** Destroys the singleton */
    static void destroyInstance();

	cocostudio::timeline::ActionTimeline* loadAnimationActionWithData(const std::string &fileName, void* csparsebinary);
};

#endif /*__CCTIMELINE_ACTION_CACHE_H__*/
