#include "RectSpriteComponent.h"
#include "Actor.h"

RectSpriteComponent::RectSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder)
{
	for (int i = 0; i < 4; i++) {mRectColor[i] = 0; }
	mRectOffset.x = 0;
	mRectOffset.y = 0;
	mRectWidth = 0;
	mRectHeight = 0;
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
	SDL_SetRenderDrawColor(renderer, mRectColor[0], mRectColor[1], mRectColor[2], mRectColor[3]);

	SDL_Rect r;
	r.x = static_cast<int>(mOwner->GetPosition().x + mRectOffset.x);
	r.y = static_cast<int>(mOwner->GetPosition().y + mRectOffset.y);
	r.w = static_cast<int>(mRectWidth);
	r.h = static_cast<int>(mRectHeight);

	//ì¬‚µ‚½’·•ûŒ`‚ğ•`‰æi“h‚è‚Â‚Ô‚µj
	SDL_RenderFillRect(renderer, &r);

}

void RectSpriteComponent::SetRectColor(int rectcolor[4])
{
	for (int i = 0; i < 4; i++) { mRectColor[i] = rectcolor[i]; }
}

void RectSpriteComponent::SetRectSize(Vector2 rectoffset, int rectwidth, int rectheight)
{
	mRectOffset.x = rectoffset.x;
	mRectOffset.y = rectoffset.y;
	mRectWidth = rectwidth;
	mRectHeight = rectheight;
}
