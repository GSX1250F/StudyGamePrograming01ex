#include "Court.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	SetPosition(Vector2(1024 / 2, 768 / 2));	//�ʒu�͒��S

	// Actor�̒��S�ʒu����ǂ��Ƃ̒��S�̃I�t�Z�b�g��x,y�������ꂼ��ɐݒ�B
	//�E��
	mOffset.x = static_cast<int>(1024 / 2 - thickness);
	mOffset.y = static_cast<int>( - 768 / 2);
	mWallWidth = thickness;
	mWallHeight = 1024;
	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);
	
	//���
	mOffset.x = static_cast<int>(-1024 / 2);
	mOffset.y = static_cast<int>(-768 / 2 );
	mWallWidth = 1024;
	mWallHeight = thickness;
	rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);


	//����
	mOffset.x = static_cast<int>(-1024 / 2);
	mOffset.y = static_cast<int>(768 / 2 - thickness);
	mWallWidth = 1024;
	mWallHeight = thickness;
	rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);

	//���ǁi�e�X�g�p�j
	mOffset.x = static_cast<int>(-1024 / 2 );
	mOffset.y = static_cast<int>(-768 / 2);;
	mWallWidth = thickness;
	mWallHeight = 1024;
	rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, mWallWidth, mWallHeight);



}

