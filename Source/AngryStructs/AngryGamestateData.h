#pragma once
#include "../AngryEnums/AngryGamestate.h"
#include "../AngryEnums/AngryMenuScreens.h"

struct GamestateData
{
	/* GAMESTATE DATA */
	static Gamestate current_gamestate; //The current gamestate (in-game, in menu, etc)
	static Gamestate win_state; //Won or lost?

	/* GAME DATA */
	static int lives; //Number of lives the player has (number of birds on screen)
	static int current_level; //This cannot be higher than GameVars::NUMBER_OF_LEVELS!
	static float current_score; //The current score the player has for this level
	static int awarded_stars; //The number of stars given to the player for their performance in a level

	/* MENU DATA */
	static MenuScreen menu_screen; //The current menu screen
	static int main_menu_index; //Menu selected index
	static int level_select_menu_index; //Level select menu index
	static int pause_menu_index; //Pause menu selection index
	static int game_over_menu_index; //Game over option select index

	/* LEVEL EDITOR DATA */
	static bool debug_place_block; //Used for level editor mode
	static float debug_block_scale; //Used for level editor mode
};