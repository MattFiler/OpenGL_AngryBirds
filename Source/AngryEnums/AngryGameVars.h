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
	MAX_FLIGHT_MARKER_DOTS = 100, //The "engine limit" - actual rendered dots are based on bird speed, path and distance.

	//Bird count (lives)
	NUMBER_OF_STARTING_BIRDS = 6,

	//Block counts
	MAX_NUMBER_OF_THIS_BLOCK_TYPE = 5, //The "engine limit" - actual block count is level specific.
	BLOCK_VARIATIONS = 3, //This is hard-coded. Do not modify!
	BLOCK_DESTRUCTION_COUNT = (int)DestructionStates::DESTRUCTION_COUNT,

	//Pig counts
	MAX_NUMBER_OF_PIGS = 10, //Again, this is the "engine limit" - actual pig count is level specific.

	//Total character counts
	TOTAL_MAX_CHARACTERS = NUMBER_OF_STARTING_BIRDS + MAX_NUMBER_OF_PIGS,

	//Menu Options
	MAIN_MENU_OPTION_COUNT = 2,

	//Number of levels and components
	LEVELS = 3,
	MAX_LEVEL_COMPONENTS = 10,

	//Number of cursors
	MAX_CURSOR_STATES = 2 //Only change this if more cursors are added to the resource directory.
};