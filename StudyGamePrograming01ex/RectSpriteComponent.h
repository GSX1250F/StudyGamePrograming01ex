#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"


class RectSpriteComponent : public SpriteComponent
{
public:
	RectSpriteComponent(class Actor* owner, int drawOrder = 10);
	~RectSpriteComponent();

	// 更新は親からオーバーライドする。
	void Update(float deltaTime) override;
	// 描画は親からオーバーライドする。画面の大きさに置くため。
	void Draw(SDL_Renderer* renderer) override;
	
	void SetRectColor(int rectcolor[4]);
	void SetRectSize(Vector2 rectoffset, int rectwidth,int rectheight);

private:
	int mRectColor[4];
	Vector2 mRectOffset;
	int mRectWidth;
	int mRectHeight;
	
};
