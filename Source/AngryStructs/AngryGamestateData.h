#pragma once
#include "../AngryEnums/AngryGamestate.h"
#include "../AngryEnums/AngryMenuScreens.h"

struct GamestateData
{
	static Gamestate current_gamestate; //The current gamestate (in-game, in menu, etc)
	static MenuScreens menu_screen; //The current menu screen
	static Gamestate win_state; //Won or lost?
	static int lives; //Number of lives the player has (number of birds on screen)
	static int current_level; //This cannot be higher than AngryLevels.count!
};