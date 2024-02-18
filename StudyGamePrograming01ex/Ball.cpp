#include "Ball.h"
#include "RectSpriteComponent.h"
#include "Game.h"

Ball::Ball(Game* game) : Actor(game)
{
	SetPosition(Vector2(1024 / 2, 768 / 2));	//初期位置は中心
	mBallVel.x = 1.0f;
	mBallVel.y = -1.0f;

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

	float x1 = pos.x;
	float y1 = pos.y;
	//衝突しない場合のdeltaTime後の位置
	float x2 = pos.x + mBallVel.x * deltaTime * mBallSpeed;
	float y2 = pos.y + mBallVel.y * deltaTime * mBallSpeed;

	// 上壁での跳ね返り
	if (y2 <= thickness && this->vel_y < 0.0f)
	{
		y2 = WALL_W - (y2 - WALL_W);
		this->vel_y *= -1;
	}
	// 下壁での跳ね返り
	else if (y2 >= (WIN_H - WALL_W) &&
		this->vel_y > 0.0f)
	{
		y2 = WIN_H - WALL_W - (y2 - (WIN_H - WALL_W));
		this->vel_y *= -1;
	}

	// 右壁での跳ね返り
	else if (PADDLES_NUM == 1 &&
		x2 >= (WIN_W - WALL_W) &&
		this->vel_x > 0.0f)
	{
		x2 = WIN_W - WALL_W - (x2 - (WIN_W - WALL_W));
		this->vel_x *= -1;
	}



	SetPosition(pos);
}