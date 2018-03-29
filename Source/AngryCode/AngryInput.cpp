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

	//Start the game when ENTER is pressed
	if (key->key == ASGE::KEYS::KEY_ENTER)
	{
		angrybirds_gamestate.current_gamestate = AngryGamestate::IS_PLAYING;
	}
}

/*
	GAMESTATE_IS_PLAYING
*/
void AngryInput::gstatePlaying(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
}