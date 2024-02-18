#include "Court.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	thickness = 15;		//����
	//�F
	mColor[0] = 200;	//R
	mColor[1] = 200;	//G
	mColor[2] = 200;	//B
	mColor[3] = 255;	//A

	SetPosition(Vector2(1024/2 , 768/2));	//�ʒu�͒��S

	// Actor�̒��S�ʒu����ǂ��Ƃ̒��S�̃I�t�Z�b�g��x,y�������ꂼ��ɐݒ�B
	//�E��
	mOffset.x = 1024 / 2 - thickness;
	mOffset.y = 0;

	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	RectSpriteComponent* rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();

	//���
	mOffset.x = 0;
	mOffset.y = -768/2 + thickness;
	

	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();

	//����
	mOffset.x = 0;
	mOffset.y = 768 / 2 + thickness;

	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();

	//���ǁi�e�X�g�p�j
	mOffset.x = -1024/2+thickness;
	mOffset.y = 0;

	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectOffset(mOffset);
	rsc->SetRectInfos();


}

