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

	SetPosition(Vector2(1024 / 2, 768 / 2));	//�����ʒu�͒��S
	
	// �����_�������ɊJ�n
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distra(15, 75);
	std::uniform_int_distribution<int> distrx(0, 1);
	std::uniform_int_distribution<int> distry(0, 1);
	
	float inia = distra(eng);		// �p�x�����_���i0�`90�x�͈́j
	int inidx = 2 * distrx(eng) - 1;	// x���������_���i+ or -�j
	int inidy = 2 * distry(eng) - 1;	// y���������_���i+ or -�j
	mBallVel.x = (float)inidx * (float)cos(inia / 90.0 * M_PI /2 );
	mBallVel.y = (float)inidy * (float)sin((inia / 90.0 ) * M_PI /2 );

	mOffset.x = - thickness / 2.0f;
	mOffset.y = - thickness / 2.0f;
	

}

void Ball::SetRectSpriteComponent()
{
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

	auto game = GetGame();
	// ��ǂł̒��˕Ԃ�
	if (y2 <= game->mCourt->GetThickness() && mBallVel.y < 0.0f)
	{
		y2 = game->mCourt->GetThickness() - (y2 - game->mCourt->GetThickness());
		mBallVel.y *= -1;
	}
	// ���ǂł̒��˕Ԃ�
	else if (y2 >= (768 - game->mCourt->GetThickness()) &&
		mBallVel.y > 0.0f)
	{
		y2 = 768 - game->mCourt->GetThickness() - (y2 - (768 - game->mCourt->GetThickness()));
		mBallVel.y *= -1;
	}

	// �E�ǂł̒��˕Ԃ�
	else if (x2 >= (1024 - game->mCourt->GetThickness()) &&
		mBallVel.x > 0.0f)
	{
		x2 = 1024 - game->mCourt->GetThickness() - (x2 - (1024 - game->mCourt->GetThickness()));
		mBallVel.x *= -1;
	}
	/*
	// ���ǂł̒��˕Ԃ�i�e�X�g�j
	else if (x2 <= (game->mCourt->GetThickness()) &&
		mBallVel.x < 0.0f)
	{
		x2 = game->mCourt->GetThickness() - (x2 - (game->mCourt->GetThickness()));
		mBallVel.x *= -1;
	}
	*/
	// �p�h���ł̒��˕Ԃ�
	InterceptPoint point{ 0,0,0 };
	//�ڐG����
	if (mBallVel.x > 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, 1);
	else if (this->mBallVel.x < 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, 2);
	if (point.side == 0) {
		if (this->mBallVel.y > 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y - game->mPaddle->GetPaddleH() / 2.0f, 3);
		else if (this->mBallVel.y < 0)point = intercept(x1, y1, x2, y2, game->mPaddle->GetPosition().x - game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, game->mPaddle->GetPosition().x + game->mPaddle->GetThickness() / 2.0f, game->mPaddle->GetPosition().y + game->mPaddle->GetPaddleH() / 2.0f, 4);
	}
	//�ڐG�ʒu�ɂ���Ē��˕Ԃ�
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
	// ���˂Ȃ��ꍇ
	else
	{
		pos.x = x2;
		pos.y = y2;
	}
	
	// �͂ݏo�����Ƃ��Q�[���I�[�o�[�@�@�@�E�E�E�ł��ȁ`��
	if (pos.x < 0.0f || pos.x > 1024.0f){
		
	}

	SetPosition(pos);
}

void Ball::ProcessKeyboard(const uint8_t* state)
{
	// R�L�[�Ń��Z�b�g
	if (state[SDL_SCANCODE_R])
	{
		Init();
	}
	// PAGEUP�ŃX�s�[�h�A�b�v
	else if (state[SDL_SCANCODE_PAGEUP])
	{
		mBallSpeed *= 1.02f;
	}
	// PAGEDOWN�ŃX�s�[�h�_�E��
	else if (state[SDL_SCANCODE_PAGEDOWN])
	{
		mBallSpeed *= 0.98f;
	}
}

InterceptPoint Ball::intercept(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int side)
{
	//�x�N�g���̊O�ς��g�p���������蔻��
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
