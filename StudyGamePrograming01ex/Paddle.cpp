#include "Paddle.h"
#include "RectSpriteComponent.h"

Paddle::Paddle(Game* game) : Actor(game)
{
	SetPosition(Vector2( 3 * thickness , 768 / 2));	//�ʒu�͒��S

	//���p�h��
	mOffset.x = static_cast<int>(-thickness / 2);
	mOffset.y = static_cast<int>(-PaddleH / 2);
	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, thickness, PaddleH);

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

