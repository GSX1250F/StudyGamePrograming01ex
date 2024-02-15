#include "Court.h"
#include "DrawRectComponent.h"
#include "Game.h"

Court::Court(Game* game) : Actor(game)		//Actorの子クラス
{
	// 壁の情報を設定
	std::vector<int> color = { 255, 255, 255, 255 };
	

	DrawRectComponent* dc = new DrawRectComponent(this, 10);
	dc->SetRects(color, { 0,0,1024,thickness });	//上側の壁
	dc->SetRects(color, { 0,768-thickness,1024,thickness });	//下側の壁
	dc->SetRects(color, { 1024-thickness,0,thickness,1024 });	//右側の壁
}

