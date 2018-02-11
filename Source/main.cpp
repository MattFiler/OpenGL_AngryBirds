#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Engine/Platform.h>
#include "Game.h"

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	PSTR pScmdline, int iCmdshow)
{
	AngryBirdsGame* game = new AngryBirdsGame;
	if (game->init())
	{
		game->run();
	}

	delete game;
	game = nullptr;
}