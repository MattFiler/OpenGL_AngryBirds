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
	handleBirdMovement(dt_sec, angrybirds_sprites.active_bird);

	//If bird has despawned, put it back in cannon
	if (angrybirds_sprites.active_bird.getBirdState() == AngryBirdStates::DESPAWNED)
	{
		angrybirds_sprites.active_bird.setBirdState(AngryBirdStates::IN_CANNON);
	}
}


/*
Handle movement of the currently active bird
*/
void AngryUpdate::handleBirdMovement(double dt_sec, GameObject &bird)
{
	switch (bird.getBirdState())
	{
		/* Bird is loaded in cannon and should spawn... */
		case (AngryBirdStates::IN_CANNON):
		{
			//Spawn
			bird.spawn();

			//Set Position to cannon
			bird.setX((float)AngryGameVars::SLINGSHOT_X_ORIGIN);
			bird.setY((float)AngryGameVars::SLINGSHOT_Y_ORIGIN);

			//Reset vars
			AngryFlightVars::bird_flight_time = 0;
			AngryFlightVars::pullback_angle = 0;
			AngryFlightVars::pullback_force = 0;

			break;
		}

		/* Bird is in cannon and about to be fired... */
		case (AngryBirdStates::ABOUT_TO_BE_FIRED):
		{
			//Set position of bird to mouse position
			bird.setY(angrybirds_mousedata.mouse_y - (bird.spriteComponent()->getSprite()->height() / 2));
			bird.setX(angrybirds_mousedata.mouse_x - (bird.spriteComponent()->getSprite()->width() / 2));

			break;
		}

		/* Bird has been fired from cannon... */
		case (AngryBirdStates::HAS_BEEN_FIRED):
		{
			//Calculate the time our bird has been in flight - this will act as our gravity
			AngryFlightVars::bird_flight_time += dt_sec;

			//Move bird dependant on user input
			bird.subtractFromY((AngryFlightVars::pullback_angle * (int)AngryGameVars::FLIGHT_ANGLE_MODIFIER * dt_sec) - 
							   (AngryFlightVars::bird_flight_time / (int)AngryGameVars::FLIGHT_TIME_MODIFIER));
			bird.addToX(AngryFlightVars::pullback_force * 
						(int)AngryGameVars::FLIGHT_FORCE_MODIFIER * dt_sec);

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
			//Reset position
			bird.setX((int)AngryGameVars::DESPAWN_X_POS);
			bird.setY((int)AngryGameVars::DESPAWN_Y_POS);

			//Despawn
			bird.despawn();
			bird.setBirdState(AngryBirdStates::DESPAWNED);

			break;
		}
	}
}
