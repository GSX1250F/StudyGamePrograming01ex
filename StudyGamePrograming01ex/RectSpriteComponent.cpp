#include "RectSpriteComponent.h"
#include "Actor.h"

RectSpriteComponent::RectSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder)
{
}

void RectSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
}

void RectSpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r;
	// ��ʃT�C�Y�̃T�C�Y��z��
	// ���L�҂̈ʒu�𒆐S�ɒ����`��z�u���܂�
	//r.x = static_cast<int>();
	//r.y = static_cast<int>();
	//r.w = static_cast<int>();
	//r.h = static_cast<int>();

	// �`��
}

void RectSpriteComponent::SetRectColor(const std::vector<int>& rectcolor)
{
	mColor = rectcolor;
}

void RectSpriteComponent::SetRectSize(const std::vector<int>& rectsize)
{
	mSize = rectsize;
}
