#pragma once
#include "Actor.h"
#include "Math.h"

struct InterceptPoint {
	float x;
	float y;
	int side;		//0は交差しない、1は左、2は右、3は上、4は下の交差
};

class Ball : public Actor
{
public:
	Ball(class Game* game);
	~Ball() {};

	void Init();
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	void SetRectSpriteComponent();
	int GetThickness() { return thickness; }
	float GetBallSpeed() { return mBallSpeed; }
	Vector2 GetBallVel() { return mBallVel; }

	InterceptPoint intercept(float, float, float, float, float, float, float, float, int side = 5);

private:
	const int thickness = 15;
	int mColor[4] = { 255,255,255,255 };
	Vector2 mOffset;
	float mBallSpeed = 300.0f;
	Vector2 mBallVel;
};

