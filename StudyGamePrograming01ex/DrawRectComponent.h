#pragma once
#include <vector>
#include "SpriteComponent.h"
#include "Math.h"

class DrawRectComponent : public SpriteComponent
{
public:
	//�����`��`���R���|�[�l���g�̃R���X�g���N�^
	DrawRectComponent(class Actor* owner, int drawOrder = 10);
	// �X�V�I�[�o�[���C�h
	void Update(float deltaTime) override;
	/// �`�� �I�[�o�[���C�h
	void Draw(SDL_Renderer* renderer) override;
	// �����`�̐F�ƃT�C�Y�̐ݒ�
	void SetRects(const std::vector<int>& color, const std::vector<int>& size);
	

private:
	std::vector<int> mColor;
	std::vector<int> mSize;
	//�����̒����`�̏������߂�\����
	struct Rects
	{
		std::vector<int>mColor2;
		std::vector<int>mSize2;
	};
	std::vector<Rects> mRects;
};

