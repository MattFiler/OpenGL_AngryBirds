#include "AngryInput.h"

AngryInput::AngryInput() {

}
AngryInput::~AngryInput() {

}


/*
	GAMESTATE_IN_MENU
*/
void AngryInput::gstateInMenu(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	switch (gamestate.menu_screen) {
		//Splashscreen
		case MenuScreens::SPLASHSCREEN: {
			if (key->key == ASGE::KEYS::KEY_ENTER)
			{
				gamestate.menu_screen = MenuScreens::MAIN_MENU;
			}
			break;
		}
		//Main Menu
		case MenuScreens::MAIN_MENU: {
			if (key->key == ASGE::KEYS::KEY_SPACE)
			{
				gamestate.current_gamestate = Gamestate::IS_PLAYING; //DEBUG: Quickly get into game and skip menu
			}
			break;
		}
	}
}

/*
	GAMESTATE_IS_PLAYING
*/
void AngryInput::gstatePlaying(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Pause the game when ESC is pressed
	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		gamestate.current_gamestate = Gamestate::IN_MENU;
		gamestate.menu_screen = MenuScreens::PAUSE_MENU;
	}
}