#include "RectSpriteComponent.h"
#include "Actor.h"

{
{
}
}

//void RectSpriteComponent::Update(float deltaTime){}

void RectSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& sr : mSomeRects)
	{
		SDL_SetRenderDrawColor(renderer, sr.mColor[0], sr.mColor[1], sr.mColor[2], sr.mColor[3]);

	SDL_Rect r;

	// •`‰æ
}

{
}

{
}
