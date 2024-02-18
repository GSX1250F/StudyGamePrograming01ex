#include "Paddle.h"
#include "RectSpriteComponent.h"

Paddle::Paddle(Game* game) : Actor(game)
{
	SetPosition(Vector2( 3 * thickness , 768 / 2));	//位置は中心

	//左パドル
	mOffset.x = static_cast<int>(-thickness / 2);
	mOffset.y = static_cast<int>(-PaddleH / 2);
	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, thickness, PaddleH);

}

void Paddle::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 速度とデルタタイムに基づいて位置を更新する
	Vector2 pos = GetPosition();
	
	pos.y += PaddleDir * PaddleSpeed * deltaTime;
	
	// 位置を壁に当たるまでに制限
	if (pos.y < thickness + PaddleH / 2)
	{
		pos.y = thickness + PaddleH / 2;
	}
	else if (pos.y > 768 - thickness - PaddleH / 2)
	{
		pos.y = 768 - thickness - PaddleH / 2;
	}
	SetPosition(pos);
}

void Paddle::ProcessKeyboard(const uint8_t* state)
{
	// 入力に基づいて方向を変更
	// 一旦スピードを 0 にリセットすることで、キーを押し続けていても加速しない。
	PaddleDir = 0;
	// Up or Down
	if (state[SDL_SCANCODE_Q])
	{
		PaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_A])
	{
		PaddleDir += 1;
	}
}

