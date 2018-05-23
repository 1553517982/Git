#ifndef __XSpriteHelpers_H__
#define __XSpriteHelpers_H__
#include "cocos2d.h"


USING_NS_CC;

class XSpriteHelpers
{
public:
	class DirFlip
	{
	public:
		DirFlip(int dir, bool flip) : _dir(dir), _filp(flip) {}
		int  _dir;
		bool _filp;
	};

	static int posTo8Dir(const Vec2& src, const Vec2& dst);

	static const DirFlip& posTo8DirFlip(const Vec2& src, const Vec2& dst);

	static const DirFlip& dirToFlip(int direction_id);
};

#endif /* defined(__CocoGUI__UISystem__) */
