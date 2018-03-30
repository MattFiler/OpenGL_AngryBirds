#pragma once

/*
Define all menu screens.
*/
enum class MenuScreen : int
{
	SPLASHSCREEN, //Landing - the splashscreen
	MAIN_MENU, //Main menu - after the splashscreen
	LEVEL_SELECT, //Level select screen
	PAUSE_MENU //Pause menu - accessed in-game by using ESC
};