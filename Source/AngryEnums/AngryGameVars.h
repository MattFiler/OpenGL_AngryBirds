#pragma once
#include "AngryDestructionStates.h"

/*
	Define some game vars.
*/
enum class GameVars : int
{
	//Game window sizes
	GAME_WIDTH = 1920,
	GAME_HEIGHT = 1080,

	//Slingshot position
	SLINGSHOT_X_ORIGIN = 250,
	SLINGSHOT_Y_ORIGIN = 750,

	//Flight curvature modifiers
	FLIGHT_ANGLE_MODIFIER = 10,
	FLIGHT_FORCE_MODIFIER = 10,
	FLIGHT_TIME_MODIFIER = 2,

	//Despawn sprite holding location
	DESPAWN_X_POS = 0,
	DESPAWN_Y_POS = 0,

	//Number of flight path dots
	MAX_FLIGHT_MARKER_DOTS = 100,

	//Bird count (lives)
	NUMBER_OF_STARTING_BIRDS = 6,

	//Block counts
	MAX_NUMBER_OF_THIS_BLOCK_TYPE = 5,
	BLOCK_VARIATIONS = 3, //This is hard-coded
	BLOCK_DESTRUCTION_COUNT = (int)DestructionStates::DESTRUCTION_COUNT,

	//Menu Options
	MAIN_MENU_OPTION_COUNT = 2
};