#include "Court.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	thickness = 15;
	mColor[0] = 200;	//R
	mColor[1] = 200;	//G
	mColor[2] = 200;	//B
	mColor[3] = 255;	//A
	
	//�E��
	SetPosition(Vector2(1024.0f - thickness / 2.0f, 768.0f / 2.0f));
	mWH[0] = thickness;
	mWH[1] = 768.0f;

	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mWH);

}

