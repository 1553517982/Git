#include "XCSLoaderRet.h"

XCSLoadRet* XCSLoadRet::create(Node* n)
{
	XCSLoadRet* ret = new (std::nothrow) XCSLoadRet();
	ret->setNode(n);
	ret->autorelease();
	return ret;
}