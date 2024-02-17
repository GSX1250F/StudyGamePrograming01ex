#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"


class RectSpriteComponent : public SpriteComponent
{
public:
	RectSpriteComponent(class Actor* owner, int drawOrder = 10);
	~RectSpriteComponent();

	// �X�V�͐e����I�[�o�[���C�h����B�X�N���[����ݒ肷�邽��
	void Update(float deltaTime) override;
	// �`��͐e����I�[�o�[���C�h����B��ʂ̑傫���ɒu�����߁B
	void Draw(SDL_Renderer* renderer) override;
	// Rect�̐F�ƃT�C�Y�̐ݒ�
	void SetRectColor(int rectcolor[4]);
	void SetRectSize(int rectsize[4]);


private:
	int RectColor[4];

};
