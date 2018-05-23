#include "EventRichText.h"


EventRichText::EventRichText(const std::string& eventName) :EventCustom(eventName)
{
}


EventRichText::~EventRichText()
{
}

const std::string& EventRichText::getUserStringData()
{ 
	return _strData;
}

void EventRichText::setUserStringData(const std::string& strVal) 
{ 
	_strData = strVal;
}

