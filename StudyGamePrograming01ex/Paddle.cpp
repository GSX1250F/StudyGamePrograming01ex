#include "Paddle.h"
#include "DrawRectComponent.h"
#include "Game.h"

Paddle::Paddle(Game* game) : Actor(game)		//Actorの子クラス
{
	mSpeed = 300.0f;
	mPaddleDir = 0;

	// パドルの初期情報を設定
	std::vector<int> color = { 255, 255, 255, 255 };

	DrawRectComponent* dc = new DrawRectComponent(this, 50);
	dc->SetRects(color, { static_cast<int>(GetPosition().x) , static_cast<int>(GetPosition().y - paddleH / 2),thickness,paddleH});
}

void Paddle::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 速度とデルタタイムに基づいて位置を更新する
	Vector2 pos = GetPosition();
	pos.y += mPaddleDir * mSpeed * deltaTime;
	// 位置をスクリーン内に制限する。
	if (pos.y < (paddleH / 2.0f + thickness))
	{
		pos.y = paddleH / 2.0f + thickness;
	}
	else if (pos.y > (768.0f - paddleH / 2.0f - thickness))
	{
		pos.y = 768.0f - paddleH / 2.0f - thickness;
	}
	SetPosition(pos);
}

void Paddle::ProcessKeyboard(const uint8_t* state)
{
	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

