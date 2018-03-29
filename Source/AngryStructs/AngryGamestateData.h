#pragma once
#include "../AngryEnums/AngryGamestate.h"

struct AngryGamestateData
{
	static AngryGamestate current_gamestate; //The current gamestate (in-game, in menu, etc)
	static int lives; //Number of lives the player has (number of birds on screen)
};