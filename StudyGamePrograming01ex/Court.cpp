#include "Court.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	thickness = 15;
	mColor[0] = 200;	//R
	mColor[1] = 200;	//G
	mColor[2] = 200;	//B
	mColor[3] = 255;	//A
	


	//右壁
	mSize[0] = 1024 - thickness;	//x
	mSize[1] = 0;	//y
	mSize[2] = thickness;	//width
	mSize[3] = 768;		//height

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	RectSpriteComponent* rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mSize);
	rsc->SetRectInfos();

	//上壁
	mSize[0] = 0;	//x
	mSize[1] = 0;	//y
	mSize[2] = 1024;	//width
	mSize[3] = thickness;		//height

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mSize);
	rsc->SetRectInfos();

	//下壁
	mSize[0] = 0;	//x
	mSize[1] = 768 - thickness;	//y
	mSize[2] = 1024;	//width
	mSize[3] = thickness;		//height

	//SpriteComponentのDrawをオーバーライドする描画用コンポーネント
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mSize);
	rsc->SetRectInfos();
}

