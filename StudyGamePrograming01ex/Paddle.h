#pragma once
#include "Actor.h"
#include "Math.h"
class Paddle : public Actor
{
public:
	Paddle(class Game* game);
	~Paddle() {};

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	int GetThickness() { return thickness; }
	int GetPaddleH() { return PaddleH; }
	int GetPaddleSpeed() { return PaddleSpeed; }
	int GetPaddleDir() { return PaddleDir; }
	

private:
	const int thickness = 15;
	int mColor[4] = {255,255,255,255};
	Vector2 mOffset;
	const int PaddleH = 200;
	const int PaddleSpeed = 400;
	int PaddleDir=0;
};

