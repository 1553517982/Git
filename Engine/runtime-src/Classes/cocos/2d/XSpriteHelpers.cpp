#include "cocos/2d/XSpriteHelpers.h"
#include "XCommon.h"
#include <math.h>
#define PI 3.1415926535897932385f
#define HALF_PI PI * 0.5
/*
	8 1 2
	7   3
	6 5 4
*/
static XSpriteHelpers::DirFlip FILP_8[9] =
{
	/*0*/ XSpriteHelpers::DirFlip(0, false),
	/*1*/ XSpriteHelpers::DirFlip(1, false),
	/*2*/ XSpriteHelpers::DirFlip(8, false ),
	/*3*/ XSpriteHelpers::DirFlip(7, false ),
	/*4*/ XSpriteHelpers::DirFlip(6, false ),
	/*5*/ XSpriteHelpers::DirFlip(5, true ),
	/*6*/ XSpriteHelpers::DirFlip(6, true ),
	/*7*/ XSpriteHelpers::DirFlip(7, true ),
	/*8*/ XSpriteHelpers::DirFlip(8, true )
};

static XSpriteHelpers::DirFlip s_invailedDir = XSpriteHelpers::DirFlip(-1, false);

int XSpriteHelpers::posTo8Dir(const Vec2& src, const Vec2& dst)
{
	float dx = floor(src.x - dst.x);
	float dy = floor(src.y - dst.y);
	if (dx != 0 && dy != 0)
	{
		float angle = atan2(dx, dy);
		return fmod(((angle + PI) / HALF_PI) * 8, 8) + 1;
	}
	return -1;
}

const XSpriteHelpers::DirFlip& XSpriteHelpers::posTo8DirFlip(const Vec2& src, const Vec2& dst)
{
	XAssert(!(src == dst),"same dir");
	if (src == dst)
	{
		return s_invailedDir;
	}
	int dir = XSpriteHelpers::posTo8Dir(src, dst);
	return XSpriteHelpers::dirToFlip(dir);
}

const XSpriteHelpers::DirFlip& XSpriteHelpers::dirToFlip(int direction_id)
{
	if (direction_id > 0)
	{
		return (FILP_8[direction_id]);
	}
	return (FILP_8[0]);
}