#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class RectSpriteComponent : public SpriteComponent
{
public:
	// �w�i�̃R���X�g���N�^�B�w�肳��Ȃ��ꍇ�̕`�揇���̏����l��10�Ƃ���(�����`�悳��邱�ƂŔw�i�ƂȂ�)
	RectSpriteComponent(class Actor* owner, int drawOrder = 10);
	// �X�V�͐e����I�[�o�[���C�h����B�X�N���[����ݒ肷�邽��
	void Update(float deltaTime) override;
	// �`��͐e����I�[�o�[���C�h����B��ʂ̑傫���ɒu�����߁B
	void Draw(SDL_Renderer* renderer) override;
	// Rect�̐F�ƃT�C�Y�̐ݒ�
	void SetRectColor(const std::vector<int>& rectcolor);
	void SetRectSize(const std::vector<int>& rectsize);


private:
	std::vector<int> mColor;
	std::vector<int> mSize;
};
