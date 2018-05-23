#pragma once
#include "base/CCEventCustom.h"

class EventRichText :
	public cocos2d::EventCustom
{
public:
	EventRichText(const std::string& eventName);
	~EventRichText();

	const std::string& getUserStringData();
	void setUserStringData(const std::string& strVal);

protected:
	std::string	_strData;
};

