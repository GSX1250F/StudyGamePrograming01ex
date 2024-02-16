#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class RectSpriteComponent : public SpriteComponent
{
public:
	// 背景のコンストラクタ。指定されない場合の描画順序の初期値は10とする(早く描画されることで背景となる)
	RectSpriteComponent(class Actor* owner, int drawOrder = 10);
	// 更新は親からオーバーライドする。スクロールを設定するため
	void Update(float deltaTime) override;
	// 描画は親からオーバーライドする。画面の大きさに置くため。
	void Draw(SDL_Renderer* renderer) override;
	// Rectの色とサイズの設定
	void SetRectColor(const std::vector<int>& rectcolor);
	void SetRectSize(const std::vector<int>& rectsize);


private:
	std::vector<int> mColor;
	std::vector<int> mSize;
};
