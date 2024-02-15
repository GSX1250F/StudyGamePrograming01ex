#pragma once
#include "SpriteComponent.h"
#include <vector>
class RectSpriteComponent : public SpriteComponent
{
public:
	RectSpriteComponent(class Actor* owner, int drawOrder = 100);
	// フレームごとにアニメーションを更新する(componentからオーバーライド)
	// void Update(float deltaTime) override;
	// 描画（spliteComponentからオーバーライド）
	void Draw(SDL_Renderer* renderer);
	// 色と大きさのセット
	void SetRectInfo(int color[4],int size[4]);
	// 複数の長方形の構造体の設定
	void SetSomeRects(int color[4], int size[4]);

private:
	// 色の設定のための変数
	int mColor[4];
	// 長方形設定のための変数
	int mSize[4];

	// 複数の長方形をカプセル化する構造体
	struct SomeRects
	{
		int mColor[4];
		int mSize[4];
	};
	std::vector<SomeRects> mSomeRects;
};

