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
	handleBirdMovement(dt_sec);
}


/*
Handle movement of the currently active bird
*/
void AngryUpdate::handleBirdMovement(double dt_sec)
{
	switch (angrybirds_sprites.devtest.getBirdState())
	{
		/* Bird is in cannon and ready to be fired... */
		case (AngryBirdStates::IN_CANNON):
		{
			//Reset vars
			AngryFlightVars::bird_flight_time = 0;
			AngryFlightVars::pullback_angle = 0;
			AngryFlightVars::pullback_force = 0;

			//Set position of bird to mouse position
			angrybirds_sprites.devtest.spriteComponent()->getSprite()->yPos(angrybirds_mousedata.mouse_y);
			angrybirds_sprites.devtest.spriteComponent()->getSprite()->xPos(angrybirds_mousedata.mouse_x);

			break;
		}
		/* Bird has been fired from cannon... */
		case (AngryBirdStates::HAS_BEEN_FIRED):
		{
			//Calculate the time our bird has been in flight - this will act as our gravity
			AngryFlightVars::bird_flight_time += dt_sec;

			//Move bird dependant on user input
			angrybirds_sprites.devtest.subtractFromY((AngryFlightVars::pullback_angle * 10 * dt_sec) - (AngryFlightVars::bird_flight_time / 2));
			angrybirds_sprites.devtest.addToX(AngryFlightVars::pullback_force * 10 * dt_sec);

			//Off window
			if (angrybirds_sprites.devtest.spriteComponent()->getSprite()->yPos() > (int)AngryGameVars::GAME_HEIGHT ||
				//angrybirds_sprites.devtest.spriteComponent()->getSprite()->yPos() < -angrybirds_sprites.devtest.spriteComponent()->getSprite()->height() ||
				angrybirds_sprites.devtest.spriteComponent()->getSprite()->xPos() > (int)AngryGameVars::GAME_WIDTH ||
				angrybirds_sprites.devtest.spriteComponent()->getSprite()->xPos() < -angrybirds_sprites.devtest.spriteComponent()->getSprite()->width())
			{
				angrybirds_sprites.devtest.setBirdState(AngryBirdStates::SHOULD_DESPAWN);
			}

			break;
		}
		/* Bird is off window and should despawn... */
		case (AngryBirdStates::SHOULD_DESPAWN):
		{
			//Reset bird position (will want to actually "despawn" here eventually.
			angrybirds_sprites.devtest.spriteComponent()->getSprite()->xPos(0);
			angrybirds_sprites.devtest.spriteComponent()->getSprite()->yPos(0);

			break;
		}
	}
}
