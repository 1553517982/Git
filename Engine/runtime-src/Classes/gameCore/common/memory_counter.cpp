#include "cocos2d.h"
#include "memory_counter.h"
#include "XCommon.h"

USING_NS_CC;
#ifdef _MEMORY_TRACE_

void MemoryCounter::regist(AllocatorCounterItem* item)
{
	allocator_list.add(item);
}

void MemoryCounter::unregist(AllocatorCounterItem* item)
{
	for (int i = allocator_list.count() - 1; i >= 0; --i)
	{
		if (item == allocator_list[i])
		{
			allocator_list.remove(i);
			break;
		}
	}
}


void MemoryCounter::logToFile()
{
	size_t total = 0, used = 0;
	char buf[1024];
	for (int i = 0; i < allocator_list.count(); i++)
	{
		allocator_list[i]->Log(buf, sizeof(buf) - 1);
		//记录到文件中
		XLOG("%s\n", buf);

		total += allocator_list[i]->alloc_total_;
		used += allocator_list[i]->used_count_;
	}
	const char* fmt = "all: alloc total:%u, used:%u";
	commonFunction::XSNPRINTFA(buf, sizeof(buf) - 1, fmt, total, used);
	XLOG("%s\n", buf);
}

#endif

