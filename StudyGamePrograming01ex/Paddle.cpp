#include "Paddle.h"
#include "RectSpriteComponent.h"

Paddle::Paddle(Game* game) : Actor(game)
{
	PaddleH = 200;
	PaddleSpeed = 300;
	PaddleDir = 0;

	thickness = 15;		//厚さ
	//色
	mColor[0] = 200;	//R
	mColor[1] = 200;	//G
	mColor[2] = 200;	//B
	mColor[3] = 255;	//A

	//左パドル
	mSize[0] = thickness + 10;	//x
	mSize[1] = static_cast<int>(384 + PaddleH/2);	//y
	mSize[2] = thickness;		//width
	mSize[3] = PaddleH;			//height

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	RectSpriteComponent* rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mSize);
	rsc->SetRectInfos();

	SetPosition(Vector2(thickness + 10 , 384 ));

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
	mSize[1] = static_cast<int>(pos.y - PaddleH / 2);

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

