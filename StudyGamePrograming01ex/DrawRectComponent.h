#pragma once
#include <vector>
#include "SpriteComponent.h"
class DrawRectComponent : public SpriteComponent
{
public:
	//�����`��`���R���|�[�l���g�̃R���X�g���N�^
	DrawRectComponent(class Actor* owner, int drawOrder);
	/// �X�V�͐e����I�[�o�[���C�h���Ȃ��BDraw������͍X�V���Ȃ��B
	//void Update(float deltaTime) override;
	/// �`��͐e����I�[�o�[���C�h����
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

