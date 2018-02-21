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
	//Calculate frame time in seconds
	auto dt_sec = us.delta_time.count() / 1000.0;

	//Update global game timer
	AngryWorldVars::total_game_time += dt_sec;




	//Test of trajectory

	AngryWorldVars::pullback_force = 100; //This will be calculated from how far the bird is pulled back by the mouse

	if (angrybirds_sprites.devtest.getBirdState() == AngryBirdStates::HAS_BEEN_FIRED) //Bird has been fired
	{
		AngryWorldVars::bird_flight_time += dt_sec;


		//calculate landing X pos from pullback_force
		//calculate height of path from pullback_angle



		angrybirds_sprites.devtest.spriteComponent()->getSprite()->xPos();
	}

}