#pragma once
#include "Actor.h"
class Court : public Actor
{
public:
	Court(class Game* game);
	
private:
	int thickness;
};

