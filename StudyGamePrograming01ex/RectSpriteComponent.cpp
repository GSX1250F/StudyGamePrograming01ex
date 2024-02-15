#include "RectSpriteComponent.h"

RectSpriteComponent::RectSpriteComponent(Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder)
{
	for (int i = 0; i < 4; i++) 
	{
		mColor[i] = 0;
		mSize[i] = 0; 
	}
}

//void RectSpriteComponent::Update(float deltaTime){}

void RectSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& sr : mSomeRects)
	{
		SDL_SetRenderDrawColor(renderer, sr.mColor[0], sr.mColor[1], sr.mColor[2], sr.mColor[3]);

		SDL_Rect r;
		r.x = sr.mSize[0];
		r.y = sr.mSize[1];
		r.w = sr.mSize[2];
		r.h = sr.mSize[3];

		SDL_RenderFillRect(renderer, &r);	//ì¬‚µ‚½’·•ûŒ`‚ð•`‰æi“h‚è‚Â‚Ô‚µj
	}
	
}

void RectSpriteComponent::SetRectInfo(int color[4],int size[4])
{
	for (int i = 0; i < 4; i++) 
	{ 
		mColor[i] = color[i];
		mSize[i] = size[i]; 
	}
}

void RectSpriteComponent::SetSomeRects(int color[4], int size[4])
{
	SomeRects temp;
	for (int i = 0; i < 4; i++)
	{
		temp.mColor[i] = color[i];
		temp.mSize[i] = size[i];
	}
	mSomeRects.emplace_back(temp);
}
