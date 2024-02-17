#include "Paddle.h"
#include "RectSpriteComponent.h"

Paddle::Paddle(Game* game) : Actor(game)
{
	PaddleH = 200;
	PaddleSpeed = 300;
	PaddleDir = 0;

	thickness = 15;		//����
	//�F
	mColor[0] = 200;	//R
	mColor[1] = 200;	//G
	mColor[2] = 200;	//B
	mColor[3] = 255;	//A

	//���p�h��
	mSize[0] = thickness + 10;	//x
	mSize[1] = static_cast<int>(384 + PaddleH/2);	//y
	mSize[2] = thickness;		//width
	mSize[3] = PaddleH;			//height

	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	RectSpriteComponent* rsc = new RectSpriteComponent(this);

	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mSize);
	rsc->SetRectInfos();

	SetPosition(Vector2(thickness + 10 , 384 ));

}

void Paddle::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// ���x�ƃf���^�^�C���Ɋ�Â��Ĉʒu���X�V����
	Vector2 pos = GetPosition();
	
	pos.y += PaddleDir * PaddleSpeed * deltaTime;
	
	// �ʒu��ǂɓ�����܂łɐ���
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
	// ���͂Ɋ�Â��ĕ�����ύX
	// ��U�X�s�[�h�� 0 �Ƀ��Z�b�g���邱�ƂŁA�L�[�����������Ă��Ă��������Ȃ��B
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

