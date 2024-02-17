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

private:
	int thickness;
	int mColor[4];
	int mSize[4];
	int PaddleH;
	int PaddleSpeed;
	int PaddleDir;
	// ������Paddle�̏����J�v�Z��������z��
	struct PaddleInfo
	{
		Vector2 mPosition;
	};
	std::vector<PaddleInfo> mPaddles;
};

