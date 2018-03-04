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

	//Handle movement of the currently active bird
	handleBirdMovement(dt_sec, angrybirds_sprites.devtest);
}


/*
Handle movement of the currently active bird
*/
void AngryUpdate::handleBirdMovement(double dt_sec, GameObject &bird)
{
	switch (bird.getBirdState())
	{
		/* Bird is in cannon and ready to be fired... */
		case (AngryBirdStates::IN_CANNON):
		{
			//Reset vars
			AngryFlightVars::bird_flight_time = 0;
			AngryFlightVars::pullback_angle = 0;
			AngryFlightVars::pullback_force = 0;

			//Set position of bird to mouse position
			bird.setY(angrybirds_mousedata.mouse_y);
			bird.setX(angrybirds_mousedata.mouse_x);

			break;
		}
		/* Bird has been fired from cannon... */
		case (AngryBirdStates::HAS_BEEN_FIRED):
		{
			//Calculate the time our bird has been in flight - this will act as our gravity
			AngryFlightVars::bird_flight_time += dt_sec;

			//Move bird dependant on user input
			bird.subtractFromY((AngryFlightVars::pullback_angle * 10 * dt_sec) - (AngryFlightVars::bird_flight_time / 2));
			bird.addToX(AngryFlightVars::pullback_force * 10 * dt_sec);

			//Off window
			if (bird.getY() > (int)AngryGameVars::GAME_HEIGHT ||
				//bird.getY() < -bird.spriteComponent()->getSprite()->height() ||
				bird.getX() > (int)AngryGameVars::GAME_WIDTH ||
				bird.getX() < -bird.spriteComponent()->getSprite()->width())
			{
				bird.setBirdState(AngryBirdStates::SHOULD_DESPAWN);
			}

			break;
		}
		/* Bird is off window and should despawn... */
		case (AngryBirdStates::SHOULD_DESPAWN):
		{
			//Reset bird position (will want to actually "despawn" here eventually.
			bird.setX(0);
			bird.setY(0);

			break;
		}
	}
}
