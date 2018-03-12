#pragma once

/*
	Define some game vars.
*/
enum class AngryGameVars : int
{
	//Game window sizes
	GAME_WIDTH = 1920,
	GAME_HEIGHT = 1080,

	//Slingshot position
	SLINGSHOT_X_ORIGIN = 250,
	SLINGSHOT_Y_ORIGIN = 850,

	//Flight curvature modifiers
	FLIGHT_ANGLE_MODIFIER = 10,
	FLIGHT_FORCE_MODIFIER = 10,
	FLIGHT_TIME_MODIFIER = 2,

	//Despawn sprite holding location
	DESPAWN_X_POS = 0,
	DESPAWN_Y_POS = 0
};