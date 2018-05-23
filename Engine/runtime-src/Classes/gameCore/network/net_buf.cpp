#include "XCommon.h"
#include "net_buf.h"

NetBuf::NetBuf() :
	size_(0),
	max_size_(0),
	buf_(NULL)
{

}

NetBuf::~NetBuf()
{
	if (buf_)
		free(buf_);
}

void NetBuf::append(char* buf, int size)
{
	int old_size = size_;
	size_ += size;

	if (max_size_ < size_)
	{
#ifdef X_DEBUG
		XLOG("NetBuf resize %d to %d", max_size_, size);
#endif // _DEBUG
		buf_ = (char*)realloc(buf_, size_);
		max_size_ = size_;
	}
	memcpy(buf_ + old_size, buf, size);
}

void NetBuf::copy(char* buf, int size)
{
	size_ = 0;
	append(buf, size);
}

void NetBuf::clear()
{
	size_ = 0;
	memset(buf_, 0, max_size_);
}
