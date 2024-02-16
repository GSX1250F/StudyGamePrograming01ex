#include "Court.h"
#include "DrawRectComponent.h"
#include "Game.h"

Court::Court(Game* game) : Actor(game)		//ActorÌqNX
{
	// ÇÌîñðÝè
	std::vector<int> color = { 255, 255, 255, 255 };
	
	DrawRectComponent* dc = new DrawRectComponent(this, 10);
	dc->SetRects(color, { 0,0,1024,thickness });	//ã¤ÌÇ
	dc->SetRects(color, { 0,768-thickness,1024,thickness });	//º¤ÌÇ
	dc->SetRects(color, { 1024-thickness,0,thickness,1024 });	//E¤ÌÇ
}

