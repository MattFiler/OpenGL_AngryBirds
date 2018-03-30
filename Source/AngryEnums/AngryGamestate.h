#pragma once

/*
	Define all gamestates.
*/
enum class Gamestate : int
{
	IN_MENU, //In main menu
	IS_PLAYING, //In-game
	GAME_OVER, //Game over
	HAS_WON, //Game over - won
	HAS_LOST, //Game over - lost

	REQUESTED_QUIT //User wants to quit
};