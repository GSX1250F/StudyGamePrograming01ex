//main.cpp����邱�Ƃ́@1.Game�N���X�̃C���X�^���X�@2.Game.Initialize�@3.Game.RunLoop�@4.Game.Shutdown


#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}