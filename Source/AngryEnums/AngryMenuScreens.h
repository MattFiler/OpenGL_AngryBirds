#pragma once

/*
Define all menu screens.
*/
enum class MenuScreen : int
{
	SPLASHSCREEN, //Landing - the splashscreen
	MAIN_MENU, //Main menu (level select) - after the splashscreen
	PAUSE_MENU //Pause menu - accessed in-game by using ESC
};