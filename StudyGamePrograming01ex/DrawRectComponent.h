#pragma once
#include <vector>
#include "Component.h"
#include "SDL.h"

class DrawRectComponent : public Component
{
public:
	//�����`��`���R���|�[�l���g�̃R���X�g���N�^
	DrawRectComponent(class Actor* owner, int drawOrder);
	// �X�V
	virtual void Update(float deltaTime);
	/// �`��
	virtual void Draw(SDL_Renderer* renderer);
	// �����`�̐F�ƃT�C�Y�̐ݒ�/�擾
	void SetRects(const std::vector<int>& color, const std::vector<int>& size);
	std::vector<int> GetRectsColor(std::vector<Rects>& rects);
	std::vector<int> GetRectsSize(std::vector<Rects>& rects);
	


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

