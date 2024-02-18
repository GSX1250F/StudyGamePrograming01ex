#include "Ball.h"
#include "RectSpriteComponent.h"
#include "Game.h"
#include <random>
#include "Paddle.h"
#include "Court.h"

Ball::Ball(Game* game) : Actor(game)
{
	Init();
	SetRectSpriteComponent();
}

void Ball::Init(){

	SetPosition(Vector2(1024 / 2, 768 / 2));	//初期位置は中心
	
	// ランダム方向に開始
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distra(15, 75);
	std::uniform_int_distribution<int> distrx(0, 1);
	std::uniform_int_distribution<int> distry(0, 1);
	
	float inia = distra(eng);		// 角度ランダム（0～90度範囲）
	int inidx = 2 * distrx(eng) - 1;	// x方向ランダム（+ or -）
	int inidy = 2 * distry(eng) - 1;	// y方向ランダム（+ or -）
	mBallVel.x = (float)inidx * (float)cos(inia / 90.0 * M_PI /2 );
	mBallVel.y = (float)inidy * (float)sin((inia / 90.0 ) * M_PI /2 );

	mOffset.x = - thickness / 2.0f;
	mOffset.y = - thickness / 2.0f;
	

}

void Ball::SetRectSpriteComponent()
{
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

	auto game = GetGame();
	// 上壁での跳ね返り
	if (y2 <= game->mCourt->GetThickness() && mBallVel.y < 0.0f)
	{
		y2 = game->mCourt->GetThickness() - (y2 - game->mCourt->GetThickness());
		mBallVel.y *= -1;
	}
	// 下壁での跳ね返り
	else if (y2 >= (768 - game->mCourt->GetThickness()) &&
		mBallVel.y > 0.0f)
	{
		y2 = 768 - game->mCourt->GetThickness() - (y2 - (768 - game->mCourt->GetThickness()));
		mBallVel.y *= -1;
	}

	// 右壁での跳ね返り
	else if (x2 >= (1024 - game->mCourt->GetThickness()) &&
		mBallVel.x > 0.0f)
	{
		x2 = 1024 - game->mCourt->GetThickness() - (x2 - (1024 - game->mCourt->GetThickness()));
		mBallVel.x *= -1;
	}
	/*
	// 左壁での跳ね返り（テスト）
	else if (x2 <= (game->mCourt->GetThickness()) &&
		mBallVel.x < 0.0f)
	{
		x2 = game->mCourt->GetThickness() - (x2 - (game->mCourt->GetThickness()));
		mBallVel.x *= -1;
	}
	*/
	// パドルでの跳ね返り
	InterceptPoint point{ 0,0,0 };
	//接触判定
	if (mBallVel.x > 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, 1);
	else if (this->mBallVel.x < 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, 2);
	if (point.side == 0) {
		if (this->mBallVel.y > 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, 3);
		else if (this->mBallVel.y < 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, 4);
	}
	//接触位置によって跳ね返り
	if (point.side != 0) {
		switch (point.side) {
		case 1:
		case 2:
			pos.x = point.x;
			mBallVel.x *= -1.0f;
			mBallVel.x *= 1.1f;
			break;
		case 3:
		case 4:
			pos.y = point.y;
			mBallVel.y *= -1.0f;
			break;
		}
	}
	// 跳ねない場合
	else
	{
		pos.x = x2;
		pos.y = y2;
	}
	
	// はみ出したときゲームオーバー　　　・・・できな～い
	if (pos.x < 0.0f || pos.x > 1024.0f){
		
	}

	SetPosition(pos);
}

void Ball::ProcessKeyboard(const uint8_t* state)
{
	// Rキーでリセット
	if (state[SDL_SCANCODE_R])
	{
		Init();
	}
	// PAGEUPでスピードアップ
	else if (state[SDL_SCANCODE_PAGEUP])
	{
		mBallSpeed *= 1.02f;
	}
	// PAGEDOWNでスピードダウン
	else if (state[SDL_SCANCODE_PAGEDOWN])
	{
		mBallSpeed *= 0.98f;
	}
}

InterceptPoint Ball::intercept(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int side)
{
	//ベクトルの外積を使用した当たり判定
	float denom = ((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1));
	if (denom != 0) {
		float ua = (((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / denom;
		if ((ua >= 0) && (ua <= 1)) {
			float ub = (((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / denom;
			if ((ub >= 0) && (ub <= 1)) {
				float x = x1 + (ua * (x2 - x1));
				float y = y1 + (ua * (y2 - y1));
				return { x,y,side };
			}
		}
	}
	return { 0,0,0 };
}
