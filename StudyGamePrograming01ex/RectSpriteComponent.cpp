#include "RectSpriteComponent.h"
#include "Actor.h"

RectSpriteComponent::RectSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder)
{
	for (int i = 0; i < 4; i++) 
	{
		mRectColor[i] = 0; 
		mRectSize[i] = 0;
	}
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
	r.x = static_cast<int>(mRectSize[0]);
	r.y = static_cast<int>(mRectSize[1]);
	r.w = static_cast<int>(mRectSize[2]);
	r.h = static_cast<int>(mRectSize[3]);

	//ì¬‚µ‚½’·•ûŒ`‚ğ•`‰æi“h‚è‚Â‚Ô‚µj
	SDL_RenderFillRect(renderer, &r);

}



void RectSpriteComponent::SetRectColor(int rectcolor[4])
{
	for (int i = 0; i < 4; i++) { mRectColor[i] = rectcolor[i]; }
}

void RectSpriteComponent::SetRectSize(int rectsize[4])
{
	for (int i = 0; i < 4; i++) { mRectSize[i] = rectsize[i]; }
}

void RectSpriteComponent::SetRectInfos()
{
	RectInfo temp;
	for (int i = 0; i < 4; i++) 
	{
		temp.mRectColor[i] = mRectColor[i]; 
		temp.mRectSize[i] = mRectSize[i]; 
	};
	mRectInfos.emplace_back(temp);
}
