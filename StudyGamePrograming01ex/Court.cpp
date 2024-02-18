#include "Court.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	thickness = 15;		//厚さ
	//色
	mColor[0] = 200;	//R
	mColor[1] = 200;	//G
	mColor[2] = 200;	//B
	mColor[3] = 255;	//A

	SetPosition(Vector2(1024/2 , 768/2));	//位置は中心

	// Actorの中心位置から壁ごとの中心のオフセットをx,y方向それぞれに設定。
	//右壁
	mOffset.x = 1024 / 2 - thickness;
	mOffset.y = 0;

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	RectSpriteComponent* rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();

	//上壁
	mOffset.x = 0;
	mOffset.y = -768/2 + thickness;
	

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();

	//下壁
	mOffset.x = 0;
	mOffset.y = 768 / 2 + thickness;

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();

	//左壁（テスト用）
	mOffset.x = -1024/2+thickness;
	mOffset.y = 0;

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();


}

