#include "XResource/XAsyncLoaderCallbacks.h"
#include "XResource/XAsyncLoader.h"
static unsigned int s_callback_ID = 0;

XAsyncLoadOption::XAsyncLoadOption() : m_callback(nullptr), m_priority(0)
{

}

XAsyncLoadOption::~XAsyncLoadOption()
{

}

void XAsyncLoadOption::init(const char* filename, const char* customID, unsigned char priority, XAsyncLoaderFunction callback)
{
	m_filename = filename;
	m_customID = customID;
	m_callback = callback;
}

XAsyncLoaderCallback::XAsyncLoaderCallback() : m_pkUserdata(nullptr)
{

}

XAsyncLoaderCallback::~XAsyncLoaderCallback()
{
	if (m_callback)
	{
		XLOGERROR("XAsyncLoaderCallback has not been canceled");
	}
}

void XAsyncLoaderCallback::setOwner(std::shared_ptr<XAsyncLoader> owner)
{
	m_owner = owner;
}

void XAsyncLoaderCallback::reset()
{
	m_owner.reset();
	m_callback = nullptr;
}

void XAsyncLoaderCallback::cancel()
{
	if (m_callback == nullptr)
		return;

	retain();

	if (!m_owner.expired())
	{
		XAsyncLoaderPtr owner = m_owner.lock();
		owner->removeCallback(this);
	}
	else
	{
		XLOGINFO("XAsyncLoaderCallback::cancel m_owner.expired()");
	}

	reset();

	release();
}

void XAsyncLoaderCallback::init(XAsyncLoaderFunction callback)
{
	cancel();
	m_callback = callback;
}


void XAsyncLoaderCallback::onAsyncLoad(const XAsyncLoaderRet* ret)
{
	if (m_callback)
	{
		m_callback(ret);
	}
	reset();
}


XAsyncLoaderCallback* XAsyncLoaderCallback::create()
{
	XAsyncLoaderCallback* pkCallback = new XAsyncLoaderCallback();
	pkCallback->autorelease();
	return pkCallback;
}

