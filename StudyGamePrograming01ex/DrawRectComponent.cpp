#include "DrawRectComponent.h"
#include "Actor.h"

DrawRectComponent::DrawRectComponent(class Actor* owner, int drawOrder) :SpriteComponent(owner, drawOrder)
{}

void DrawRectComponent::Draw(SDL_Renderer* renderer)
{
	// �e�w�i�e�N�X�`����`�悵�܂�
	for (auto& rc : mRects)
	{
		//�����`�̐F��ݒ�
		SDL_SetRenderDrawColor(renderer, rc.mColor2[0], rc.mColor2[1], rc.mColor2[2], rc.mColor2[3]);
		
		
		SDL_Rect r;
		r.x = rc.mSize2[0];
		r.y = rc.mSize2[1];
		r.w = rc.mSize2[2];
		r.h = rc.mSize2[3];

		//�쐬���������`��`��i�h��Ԃ��j
		SDL_RenderFillRect(renderer, &r);	
	}
}

void DrawRectComponent::SetRects(const std::vector<int>& color, const std::vector<int>& size)
{
	Rects temp;
	temp.mColor2 = color;
	temp.mSize2 = size;
	mRects.emplace_back(temp);
}