#include "RectSpriteComponent.h"
#include "Actor.h"

RectSpriteComponent::RectSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder)
{

}

RectSpriteComponent::~RectSpriteComponent()
{
}

void RectSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
}

void RectSpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, RectColor[0], RectColor[1], RectColor[2], RectColor[3]);

	SDL_Rect r;
	r.x = static_cast<int>(mOwner->GetPosition().x - mTexWidth / 2 );
	r.y = static_cast<int>(mOwner->GetPosition().y - mTexHeight / 2 );
	r.w = mTexWidth;
	r.h = mTexHeight;

	//çÏê¨ÇµÇΩí∑ï˚å`Çï`âÊÅiìhÇËÇ¬Ç‘ÇµÅj
	SDL_RenderFillRect(renderer, &r);

}



void RectSpriteComponent::SetRectColor(int rectcolor[4])
{
	for (int i = 0; i < 4; i++) { RectColor[i] = rectcolor[i]; }
}

void RectSpriteComponent::SetRectSize(int rectWH[2])
{
	mTexWidth = rectWH[0];
	mTexHeight = rectWH[1];
}
