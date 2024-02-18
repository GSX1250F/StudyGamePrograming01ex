#include "Ball.h"
#include "RectSpriteComponent.h"

Ball::Ball(Game* game) : Actor(game)
{
	SetPosition(Vector2(1024 / 2, 768 / 2));	//初期位置は中心
	mBallDir.x = 1.0f;
	mBallDir.y = 1.0f;
	mBallSpeed.x = 100.0f;
	mBallSpeed.y = -100.0f;

	mOffset.x = static_cast<int>(-thickness / 2);
	mOffset.y = static_cast<int>(-thickness / 2);
	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, thickness, thickness);

}

void Ball::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 速度とデルタタイムに基づいて位置を更新する
	Vector2 pos = GetPosition();

	pos.x += mBallDir.x * mBallSpeed.x * deltaTime;
	pos.y += mBallDir.y * mBallSpeed.y * deltaTime;

	// 反射



	SetPosition(pos);
}