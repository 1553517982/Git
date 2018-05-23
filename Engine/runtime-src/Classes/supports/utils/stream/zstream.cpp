#include "stream.h"
#include "zstream.h"
#include <stdio.h>
#include "memory.h"

using namespace zstream;


BaseZStream::BaseZStream(BaseStream &stream)
:Inherited()
{
	strm_ = &stream;
	strm_pos_ = stream.getPosition();

//	ZeroMemory( &z_strm_, sizeof(z_strm_) );
	memset(&z_strm_, 0, sizeof(z_strm_));

	z_strm_.zalloc = (alloc_func)zlibAllocMem;
	z_strm_.zfree = (free_func)zlibFreeMem;
	z_strm_.opaque = this;

	last_code_ = Z_OK;
}

BaseZStream::~BaseZStream()
{
}

void* BaseZStream::zlibAllocMem(BaseZStream &ZStream, uInt Items, uInt Size)
{
	return ZStream.AllocStream( Items * Size );
}

void BaseZStream::zlibFreeMem(BaseZStream &ZStream, void *lpBlock)
{
	ZStream.Free( lpBlock );
}

void* BaseZStream::AllocStream(int size)
{
	return malloc((int)size);
}

void BaseZStream::Free(void* ptr)
{
	free(ptr);
}

void BaseZStream::DoProgress()
{
}

