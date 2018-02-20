#include "AngryUpdate.h"

AngryUpdate::AngryUpdate() {

}
AngryUpdate::~AngryUpdate() {

}


/*
GAMESTATE_IN_MENU
*/
void AngryUpdate::gstateInMenu(const ASGE::GameTime & us) {

}

/*
GAMESTATE_IS_PLAYING
*/
void AngryUpdate::gstatePlaying(const ASGE::GameTime & us) {

	//Test of trajectory
	if (angrybirds_sprites.devtest.getPigState() == AngryPigStates::HAS_BEEN_FIRED) 
	{
		angrybirds_sprites.devtest.spriteComponent()->getSprite()->xPos();
	}

}