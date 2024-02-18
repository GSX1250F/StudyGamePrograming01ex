#pragma once
#include "Actor.h"
#include "Math.h"

class Court : public Actor
{
public:
	Court(class Game* game);
	~Court() {};
	int GetThickness() { return thickness; }

private:
	const int thickness = 15;
	int mColor[4] = {200,200,200,255};
	Vector2 mOffset;
	int mWallWidth;
	int mWallHeight;

};

