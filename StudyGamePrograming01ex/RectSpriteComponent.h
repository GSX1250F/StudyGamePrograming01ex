#pragma once
#include "SpriteComponent.h"
#include <vector>
class RectSpriteComponent : public SpriteComponent
{
public:
	RectSpriteComponent(class Actor* owner, int drawOrder = 100);
	// �t���[�����ƂɃA�j���[�V�������X�V����(component����I�[�o�[���C�h)
	// void Update(float deltaTime) override;
	// �`��ispliteComponent����I�[�o�[���C�h�j
	void Draw(SDL_Renderer* renderer);
	// �F�Ƒ傫���̃Z�b�g
	void SetRectInfo(int color[4],int size[4]);
	// �����̒����`�̍\���̂̐ݒ�
	void SetSomeRects(int color[4], int size[4]);

private:
	// �F�̐ݒ�̂��߂̕ϐ�
	int mColor[4];
	// �����`�ݒ�̂��߂̕ϐ�
	int mSize[4];

	// �����̒����`���J�v�Z��������\����
	struct SomeRects
	{
		int mColor[4];
		int mSize[4];
	};
	std::vector<SomeRects> mSomeRects;
};

