#include "AngryInput.h"

InputStates::InputStates() {

}
InputStates::~InputStates() {

}


/*
	GAMESTATE_IN_MENU
*/
void InputStates::gstateInMenu(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	switch (gamestate.menu_screen) {
		//Splashscreen
		case MenuScreens::SPLASHSCREEN: {
			if (key->key == ASGE::KEYS::KEY_SPACE)
			{
				gamestate.menu_screen = MenuScreens::MAIN_MENU;
			}
			break;
		}
		//Main Menu
		case MenuScreens::MAIN_MENU: {
			//User has selected to start game
			if (gamestate.main_menu_index == 0 &&
				key->key == ASGE::KEYS::KEY_ENTER &&
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.menu_screen = MenuScreens::LEVEL_SELECT;
				//gamestate.current_gamestate = Gamestate::IS_PLAYING;
			}

			//User has selected to exit game
			else if (gamestate.main_menu_index == 1 &&
				key->key == ASGE::KEYS::KEY_ENTER &&
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.current_gamestate = Gamestate::REQUESTED_QUIT;
			}

			//Handle up/down on main menu
			else if (gamestate.main_menu_index != 0 && 
				key->key == ASGE::KEYS::KEY_UP && 
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.main_menu_index -= 1;
			}
			else if (gamestate.main_menu_index != ((int)GameVars::MAIN_MENU_OPTION_COUNT - 1) &&
				key->key == ASGE::KEYS::KEY_DOWN &&
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.main_menu_index += 1;
			}

			break;
		}
		//Level Select
		case MenuScreens::LEVEL_SELECT: {
			//User has selected a level
			if (key->key == ASGE::KEYS::KEY_ENTER &&
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.current_level = gamestate.level_select_menu_index + 1;
				gamestate.current_gamestate = Gamestate::IS_PLAYING;
			}

			//Handle up/down
			else if (gamestate.level_select_menu_index != 0 &&
				key->key == ASGE::KEYS::KEY_UP &&
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.level_select_menu_index -= 1;
			}
			else if (gamestate.level_select_menu_index != (LevelSetups::count - 1) &&
				key->key == ASGE::KEYS::KEY_DOWN &&
				key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.level_select_menu_index += 1;
			}

			break;
		}
	}
}

/*
	GAMESTATE_IS_PLAYING
*/
void InputStates::gstatePlaying(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Pause the game when ESC is pressed
	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		gamestate.current_gamestate = Gamestate::IN_MENU;
		gamestate.menu_screen = MenuScreens::PAUSE_MENU;
	}
}