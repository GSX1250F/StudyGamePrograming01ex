#include "Ball.h"
#include "RectSpriteComponent.h"
#include "Game.h"

Ball::Ball(Game* game) : Actor(game)
{
	SetPosition(Vector2(1024 / 2, 768 / 2));	//�����ʒu�͒��S
	mBallVel.x = 1.0f;
	mBallVel.y = -1.0f;

	mOffset.x = static_cast<int>(-thickness / 2);
	mOffset.y = static_cast<int>(-thickness / 2);
	//SpriteComponent��Draw���I�[�o�[���C�h����`��p�R���|�[�l���g
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	rsc->SetRectColor(mColor);
	rsc->SetRectSize(mOffset, thickness, thickness);

}

void Ball::UpdateActor(float deltaTime)
{
	

	Actor::UpdateActor(deltaTime);
	// ���x�ƃf���^�^�C���Ɋ�Â��Ĉʒu���X�V����
	Vector2 pos = GetPosition();

	float x1 = pos.x;
	float y1 = pos.y;
	//�Փ˂��Ȃ��ꍇ��deltaTime��̈ʒu
	float x2 = pos.x + mBallVel.x * deltaTime * mBallSpeed;
	float y2 = pos.y + mBallVel.y * deltaTime * mBallSpeed;

	// ��ǂł̒��˕Ԃ�
	if (y2 <= thickness && this->vel_y < 0.0f)
	{
		y2 = WALL_W - (y2 - WALL_W);
		this->vel_y *= -1;
	}
	// ���ǂł̒��˕Ԃ�
	else if (y2 >= (WIN_H - WALL_W) &&
		this->vel_y > 0.0f)
	{
		y2 = WIN_H - WALL_W - (y2 - (WIN_H - WALL_W));
		this->vel_y *= -1;
	}

	// �E�ǂł̒��˕Ԃ�
	else if (PADDLES_NUM == 1 &&
		x2 >= (WIN_W - WALL_W) &&
		this->vel_x > 0.0f)
	{
		x2 = WIN_W - WALL_W - (x2 - (WIN_W - WALL_W));
		this->vel_x *= -1;
	}



	SetPosition(pos);
}