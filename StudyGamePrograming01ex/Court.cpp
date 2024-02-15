#include "Court.h"
#include "Game.h"
#include "RectSpriteComponent.h"

Court::Court(Game* game) : Actor(game)
{
	thickness = 15;
	
	// �����`�̕`��R���|�[�l���g���쐬
	RectSpriteComponent* rsc = new RectSpriteComponent(this);
	
	int color[4] = { 200, 200, 200, 255};
	
	// ���
	int size[4] = { 0, 0, 1024, thickness};
	rsc->SetSomeRects(color, size);
	// ����
	size[1] = 768 - thickness;
	rsc->SetSomeRects(color, size);
	// �E��
	size[0] = 1024 - thickness;
	size[1] = 0;
	size[2] = thickness;
	size[3] = 1024;
	rsc->SetSomeRects(color, size);
}
