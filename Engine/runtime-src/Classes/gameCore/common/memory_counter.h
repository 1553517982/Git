#ifndef _MEMORY_COUNTER_H_
#define _MEMORY_COUNTER_H_

/************************************************************************
*                          内存分配统计
* 每个用于内存分配的类最好都继承这个，并实现接口，好方便内存使用量的统计
* 可通过宏定义_MEMORY_TRACE_ 开关
***********************************************************************/
#include "os_def.h"
#include "CommonFun.h"

#define _MEMORY_TRACE_
#ifdef _MEMORY_TRACE_

template <typename T, int ONE_TIME_NUM = 16>
class MemoryItemList
{
protected:
	T*	data_ptr_;
	int	max_size_;
	int	count_;
public:
	MemoryItemList()
	{
		data_ptr_ = NULL;
		max_size_ = 0;
		count_ = 0;
	}

	virtual ~MemoryItemList()
	{
		empty();
	}

	inline int count() const
	{
		return count_;
	}

	int add(const T& data)
	{
		if (count_ >= max_size_)
			reserve((max_size_ > 0) ? max_size_ * 2 : ONE_TIME_NUM);
		memcpy(data_ptr_ + count_, &data, sizeof(data));
		count_++;
		return count_ - 1;
	}

	void remove(const int index)
	{
		assert(index > -1 && index < count_);
		remove(index, 1);
	}
	void remove(const int index, const int count)
	{
		assert(index + count <= count_);

		if (count > 0)
		{
			memcpy(data_ptr_ + index, data_ptr_ + index + count, sizeof(data_ptr_[0]) * (count_ - index - count));
			count_ -= count;
		}
	}
	virtual void empty()
	{
		clear();
		max_size_ = 0;

		if (data_ptr_)
		{
			free(data_ptr_);
			data_ptr_ = NULL;
		}
	}
	inline void clear()
	{
		count_ = 0;
	}
	virtual void reserve(int count)
	{
		if (count > count_ && count != max_size_)
		{
			max_size_ = count;
			data_ptr_ = (T*)realloc(data_ptr_, sizeof(T) * count);
		}
	}	
	inline operator T* () const
	{
		return data_ptr_;
	}
};

class AllocatorCounterItem;
class MemoryCounter
{
public:
	static MemoryCounter& getSingleton()
	{
		static MemoryCounter mgr;
		return mgr;
	}

	~MemoryCounter()
	{
		clear();
	}

	void clear()
	{
		allocator_list.clear();
		allocator_list.empty();
	}

	/*
	* Comments:添加一个统计项
	* @Return void:
	*/
	void regist(AllocatorCounterItem* item);

	/*
	* Comments: 移除一个统计项
	* Param CSingleObjectAllocatorStat * stat:
	* @Return void:
	*/
	void unregist(AllocatorCounterItem* item);

	/*
	* Comments: 统计信息到日志
	* @Return void:
	*/
	void logToFile();

private:
	MemoryItemList<AllocatorCounterItem*, 2048> allocator_list;
};



class AllocatorCounterItem
{
	friend class MemoryCounter;
public:
	enum
	{
	    MAX_NAME_LENGTH = 32,			// 最大描述字符串长度
	};

	AllocatorCounterItem(const char* namestr)
	{
		alloc_total_ = 0;
		free_count_ = 0;
		used_count_ = 0;

		if (!namestr)
		{
			name_[0] = 0;
		}
		else
		{
			strncpy(name_, namestr, sizeof(name_) - 1);
			name_[sizeof(name_) - 1] = 0;
		}

		MemoryCounter::getSingleton().regist(this);
	}

	virtual ~AllocatorCounterItem()
	{
		MemoryCounter::getSingleton().unregist(this);
	}
	const char* GetName()
	{
		return name_;
	}
	virtual int Log(char* buf, int num)
	{
		const char* fmt = "%s, alloc total:%u, used:%u %s";
		const char* tip  = "";
		const size_t largeCount = 100 * 1024 * 1024;
		const size_t midCount = 10 * 1024 * 1024;
		if (alloc_total_ > largeCount || used_count_ > largeCount)
		{
			tip = "*****";
		}
		else if (alloc_total_ > midCount || used_count_ > midCount)
		{
			tip = "**";
		}
		return commonFunction::XSNPRINTFA(buf, num, fmt, name_, alloc_total_, used_count_, tip);
	}
	size_t GetAllocCount ()
	{
		return alloc_total_;
	}

protected:
	size_t				alloc_total_;	//分配的总数
	size_t				free_count_;	//空闲
	size_t				used_count_;	//正在使用的内存量
	char				name_[MAX_NAME_LENGTH];		//
};

#else	//ifdef _MEMORY_TRACE_

class AllocatorCounterItem
{
public:
	AllocatorCounterItem(const char* namestr)
	{

	}
};

#endif	//ifdef _MEMORY_TRACE_

#endif	//end _ONCE_ALLOCATOR_H_
