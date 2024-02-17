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
	// Rectの色とサイズの設定
	void SetRectColor(int rectcolor[4]);
	void SetRectSize(int rectsize[4]);
	
	// 複数のRectを配列に入れる関数
	void SetRectInfos();

private:
	int mRectColor[4];
	int mRectSize[4];
	// 複数のRectの情報をカプセル化する配列
	struct RectInfo
	{
		int mRectColor[4];
		int mRectSize[4];
	};
	std::vector<RectInfo> mRectInfos;
};
