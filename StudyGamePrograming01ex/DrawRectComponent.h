#pragma once
#include <vector>
#include "SpriteComponent.h"
#include "Math.h"

class DrawRectComponent : public SpriteComponent
{
public:
	//長方形を描くコンポーネントのコンストラクタ
	DrawRectComponent(class Actor* owner, int drawOrder = 10);
	// 更新オーバーライド
	void Update(float deltaTime) override;
	/// 描画 オーバーライド
	void Draw(SDL_Renderer* renderer) override;
	// 長方形の色とサイズの設定
	void SetRects(const std::vector<int>& color, const std::vector<int>& size);
	

private:
	std::vector<int> mColor;
	std::vector<int> mSize;
	//複数の長方形の情報を収める構造体
	struct Rects
	{
		std::vector<int>mColor2;
		std::vector<int>mSize2;
	};
	std::vector<Rects> mRects;
};

