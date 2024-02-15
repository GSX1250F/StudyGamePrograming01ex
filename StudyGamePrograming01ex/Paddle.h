#pragma once
#include "Actor.h"
class Paddle : public Actor
{
public:
	Paddle(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetSpeed() const { return mSpeed; }

private:
	float mSpeed;
	const int thickness = 15;
	const int paddleH = 200;
	int mPaddleDir;
};