#include "Court.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	SetPosition(Vector2(1024 / 2, 768 / 2));	//位置は中心

	// Actorの中心位置から壁ごとの中心のオフセットをx,y方向それぞれに設定。
	//右壁
	mOffset.x = static_cast<int>(1024 / 2 - thickness);
	mOffset.y = static_cast<int>( - 768 / 2);
	mWallWidth = thickness;
	mWallHeight = 1024;
	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);
	
	//上壁
	mOffset.x = static_cast<int>(-1024 / 2);
	mOffset.y = static_cast<int>(-768 / 2 );
	mWallWidth = 1024;
	mWallHeight = thickness;
	rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);


	//下壁
	mOffset.x = static_cast<int>(-1024 / 2);
	mOffset.y = static_cast<int>(768 / 2 - thickness);
	mWallWidth = 1024;
	mWallHeight = thickness;
	rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);

	//左壁（テスト用）
	mOffset.x = static_cast<int>(-1024 / 2 );
	mOffset.y = static_cast<int>(-768 / 2);;
	mWallWidth = thickness;
	mWallHeight = 1024;
	rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);



}

