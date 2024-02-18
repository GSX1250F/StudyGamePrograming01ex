#pragma once
#include "Actor.h"
#include "Math.h"
class Ball : public Actor
{
public:
	Ball(class Game* game);
	~Ball() {};

	void UpdateActor(float deltaTime) override;

private:
	const int thickness = 15;
	int mColor[4] = { 255,255,255,255 };
	Vector2 mOffset;
	float mBallSpeed = 200.0f;
	Vector2 mBallVel;
};

