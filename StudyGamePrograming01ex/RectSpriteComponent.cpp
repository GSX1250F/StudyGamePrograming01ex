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
	for (auto& rectinfos : mRectInfos)
	{
		
	}
}

void RectSpriteComponent::Draw(SDL_Renderer* renderer)
{

	SDL_SetRenderDrawColor(renderer, mRectColor[0], mRectColor[1], mRectColor[2], mRectColor[3]);

	SDL_Rect r;
	r.x = static_cast<int>(mOwner->GetPosition().x + mRectOffset.x);
	r.y = static_cast<int>(mOwner->GetPosition().x + mRectOffset.x);
	r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
	r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

	//ì¬‚µ‚½’·•ûŒ`‚ğ•`‰æi“h‚è‚Â‚Ô‚µj
	SDL_RenderFillRect(renderer, &r);

}

void RectSpriteComponent::SetRectInfos(int rectcolor[4],Vector2 rectoffset,int texwidth,int texheight)
{
	RectInfo temp;
	for (int i = 0; i < 4; i++) 
	{
		temp.mRectColor[i] = rectcolor[i]; 
		temp.mRectOffset.x = rectoffset.x; 
		temp.mRectOffset.y = rectoffset.y;
		temp.mTexWidth = texwidth;
		temp.mTexHeight = texheight;
	};
	mRectInfos.emplace_back(temp);
}
