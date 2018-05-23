#include <stdio.h>
#include <stdlib.h>
#include "stream.h"
#include <memory.h>

using namespace stream;

MemoryStream::MemoryStream()
{
	mem_ = ptr_ = mem_end_ = NULL;
}

MemoryStream::~MemoryStream()
{
//	SafeFree(mem_);

	if (mem_) { free(mem_); mem_ = NULL; }
}

char* MemoryStream::AllocStream(char* ptr, const int size)
{
	if (size == 0 && ptr)
	{
		free(ptr);
		return NULL;
	}

	return (char*)realloc(ptr, (int)size);
}

bool MemoryStream::setSize(int tSize)
{
	size_t nOldPos = ptr_ - mem_;

	mem_ = AllocStream(mem_, tSize + sizeof(size_t));
	end_ptr_ = mem_end_ = mem_ + tSize;
	*(int*)end_ptr_ = 0;//在流末尾写入字符0，以便将流内容当做字符串使用
	ptr_ = mem_ + nOldPos;

	if (ptr_ > end_ptr_)
		ptr_ = end_ptr_;

	return true;
}

int MemoryStream::seek(const int tOffset, const int Origin)
{
	if (Origin == SEEK_SET)
		ptr_ = mem_ + tOffset;
	else if (Origin == SEEK_CUR)
		ptr_ += tOffset;
	else if (Origin == SEEK_END)
		ptr_ = end_ptr_ + tOffset;

	return (int)(ptr_ - mem_);
}

int MemoryStream::read(void* lpBuffer, const int tSizeToRead)
{
	size_t nRemain = end_ptr_ - ptr_;
	size_t tReadBytes = tSizeToRead;

	if (nRemain <= 0 || !tReadBytes)
		return 0;

	if (tReadBytes > nRemain)
		tReadBytes = nRemain;

	memcpy(lpBuffer, ptr_, (int)tReadBytes);
	ptr_ += tReadBytes;
	return (int)tReadBytes;
}

int MemoryStream::write(const void* lpBuffer, const size_t tSizeToWrite)
{
	char* pStreamEnd = ptr_ + tSizeToWrite;

	if (pStreamEnd > mem_end_)
	{
		setSize((int)(pStreamEnd - mem_));
	}

	memcpy(ptr_, lpBuffer, (int)tSizeToWrite);
	ptr_ += tSizeToWrite;
	return (int)tSizeToWrite;
}

int MemoryStream::loadFromFile(const char* lpFileName)
{
	/*int nFileSize;
	FileStream stm(lpFileName, FileStream::faRead | FileStream::faShareRead);

	nFileSize = stm.getSize();

	if (nFileSize > 0)
	{
		setSize(nFileSize);
		stm.read(mem_, nFileSize);
	}

	return nFileSize;*/
	return 0;
}

int MemoryStream::saveToFile(const char* lpFileName)
{
	/*FileStream stm(lpFileName, FileStream::faCreate);

	return stm.write(mem_, getSize());*/
	return 0;
}

int MemoryStream::copyFromChar(char* buffer, const unsigned long size)
{
	mem_ = (char*)malloc(size);
	memcpy(mem_, buffer, size);
	setSize(size);
	return size;
}
