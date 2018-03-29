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

	switch (angrybirds_gamestate.menu_screen) {
		//Splashscreen
		case AngryMenuScreens::SPLASHSCREEN: {
			if (key->key == ASGE::KEYS::KEY_ENTER)
			{
				angrybirds_gamestate.menu_screen = AngryMenuScreens::MAIN_MENU;
			}
			break;
		}
		//Main Menu
		case AngryMenuScreens::MAIN_MENU: {
			if (key->key == ASGE::KEYS::KEY_SPACE)
			{
				angrybirds_gamestate.current_gamestate = AngryGamestate::IS_PLAYING; //DEBUG: Quickly get into game and skip menu
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
		angrybirds_gamestate.current_gamestate = AngryGamestate::IN_MENU;
		angrybirds_gamestate.menu_screen = AngryMenuScreens::PAUSE_MENU;
	}
}