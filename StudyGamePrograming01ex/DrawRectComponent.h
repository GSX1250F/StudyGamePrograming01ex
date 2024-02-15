#pragma once
#include <vector>
#include "Component.h"
class DrawRectComponent : public Component
{
public:
	//�����`��`���R���|�[�l���g�̃R���X�g���N�^
	DrawRectComponent(class Actor* owner, int drawOrder);
	// �X�V
	void Update(float deltaTime);
	/// �`��
	void Draw(SDL_Renderer* renderer);
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

