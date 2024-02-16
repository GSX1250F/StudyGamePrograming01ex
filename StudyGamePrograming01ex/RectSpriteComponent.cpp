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
	// 画面サイズのサイズを想定
	// 所有者の位置を中心に長方形を配置します
	//r.x = static_cast<int>();
	//r.y = static_cast<int>();
	//r.w = static_cast<int>();
	//r.h = static_cast<int>();

	// 描画
}

void RectSpriteComponent::SetRectColor(const std::vector<int>& rectcolor)
{
	mColor = rectcolor;
}

void RectSpriteComponent::SetRectSize(const std::vector<int>& rectsize)
{
	mSize = rectsize;
}
