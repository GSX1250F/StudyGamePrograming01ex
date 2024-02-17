#pragma once
#include "Actor.h"
#include "Math.h"

class Court : public Actor
{
public:
	Court(class Game* game);
	~Court() {};
private:
	int thickness;
	int mColor[4];
	int mSize[4];
};

