#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"


class RectSpriteComponent : public SpriteComponent
{
public:
	RectSpriteComponent(class Actor* owner, int drawOrder = 10);
	~RectSpriteComponent();

	// �X�V�͐e����I�[�o�[���C�h����B
	void Update(float deltaTime) override;
	// �`��͐e����I�[�o�[���C�h����B��ʂ̑傫���ɒu�����߁B
	void Draw(SDL_Renderer* renderer) override;
	// Rect�̐F�ƃT�C�Y�̐ݒ�
	void SetRectColor(int rectcolor[4]);
	void SetRectSize(int rectsize[4]);
	
	// ������Rect��z��ɓ����֐�
	void SetRectInfos();

private:
	int mRectColor[4];
	int mRectSize[4];
	// ������Rect�̏����J�v�Z��������z��
	struct RectInfo
	{
		int mRectColor[4];
		int mRectSize[4];
	};
	std::vector<RectInfo> mRectInfos;
};
