#include "Court.h"
#include "Game.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	thickness = 15;
	
	// 長方形の描画コンポーネントを作成
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	
	int color[4] = { 200, 200, 200, 255};
	
	// 上壁
	int size[4] = { 0, 0, 1024, thickness};
	rsc->SetSomeRects(color, size);
	// 下壁
	size[1] = 768 - thickness;
	rsc->SetSomeRects(color, size);
	// 右壁
	size[0] = 1024 - thickness;
	size[1] = 0;
	size[2] = thickness;
	size[3] = 1024;
	rsc->SetSomeRects(color, size);
}
