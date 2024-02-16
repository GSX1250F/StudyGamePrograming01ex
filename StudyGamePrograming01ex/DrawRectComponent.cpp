#include "DrawRectComponent.h"
#include "Actor.h"
#include "SDL.h"

DrawRectComponent::DrawRectComponent(class Actor* owner, int drawOrder) :Component(owner, drawOrder)
{}

void DrawRectComponent::Update(float deltaTime)
{
}

void DrawRectComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& rc : mRects)
	{
		//長方形の色を設定
		SDL_SetRenderDrawColor(renderer, rc.mColor2[0], rc.mColor2[1], rc.mColor2[2], rc.mColor2[3]);
		
		
		SDL_Rect r;
		r.x = rc.mSize2[0];
		r.y = rc.mSize2[1];
		r.w = rc.mSize2[2];
		r.h = rc.mSize2[3];

		//作成した長方形を描画（塗りつぶし）
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

std::vector<int> DrawRectComponent::GetRectsColor(struct Rects rects)
{
	return std::vector<int>(rects.mColor2);
}

std::vector<int> DrawRectComponent::GetRectsSize(struct Rects rects)
{
	return std::vector<int>();
}
