#pragma once
#include "../AngryEnums/AngryGamestate.h"
#include "../AngryEnums/AngryMenuScreens.h"

struct AngryGamestateData
{
	static AngryGamestate current_gamestate; //The current gamestate (in-game, in menu, etc)
	static AngryMenuScreens menu_screen; //The current menu screen
	static AngryGamestate win_state; //Won or lost?
	static int lives; //Number of lives the player has (number of birds on screen)
};