#pragma once
#include <vector>
#include "Component.h"
#include "SDL.h"

class DrawRectComponent : public Component
{
public:
	//長方形を描くコンポーネントのコンストラクタ
	DrawRectComponent(class Actor* owner, int drawOrder);
	// 更新
	virtual void Update(float deltaTime);
	/// 描画
	virtual void Draw(SDL_Renderer* renderer);
	// 長方形の色とサイズの設定/取得
	void SetRects(const std::vector<int>& color, const std::vector<int>& size);
	std::vector<int> GetRectsColor(std::vector<Rects>& rects);
	std::vector<int> GetRectsSize(std::vector<Rects>& rects);
	


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

