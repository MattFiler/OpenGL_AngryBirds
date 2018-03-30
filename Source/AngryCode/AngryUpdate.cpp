#include "AngryUpdate.h"

//Create and destroy the sound engine when the class is called
AngryUpdate::AngryUpdate() {
	sound_engine = irrklang::createIrrKlangDevice();
}
AngryUpdate::~AngryUpdate() {
	sound_engine->drop();
}


/*
GAMESTATE_IN_MENU
*/
void AngryUpdate::gstateInMenu(const ASGE::GameTime & us) {
	//If not already playing, play background music
	if (menu_music == NOT_PLAYING)
	{
		sound_engine->play2D("Resources\\UI\\MUSIC\\0.mp3", true);
		menu_music = PLAYING;
	}
}

/*
GAMESTATE_IS_PLAYING
*/
void AngryUpdate::gstatePlaying(const ASGE::GameTime & us) {
	//Calculate frame time in seconds
	auto dt_sec = us.delta_time.count() / 1000.0;
	game_time += dt_sec; //update gametime

	//Generate level if it hasn't already been
	if (level_spawn == NEEDS_TO_SPAWN) 
	{
		angrybirds_sprites.wood_rectangle_long[0].setX(500);
		angrybirds_sprites.wood_rectangle_long[0].setY(500);
		angrybirds_sprites.wood_rectangle_long[0].setDestruction(AngryDestructionStates::DEFAULT);
		angrybirds_sprites.wood_rectangle_long[0].spawn();
		angrybirds_sprites.wood_square[1].setX(200);
		angrybirds_sprites.wood_square[1].setY(200);
		angrybirds_sprites.wood_square[1].setRotation(90);
		angrybirds_sprites.wood_square[1].setDestruction(AngryDestructionStates::DEFAULT);
		angrybirds_sprites.wood_square[1].spawn();
		angrybirds_sprites.rock_rectangle_long[1].setX(400);
		angrybirds_sprites.rock_rectangle_long[1].setY(400);
		angrybirds_sprites.rock_rectangle_long[1].setRotation(90);
		angrybirds_sprites.rock_rectangle_long[1].setDestruction(AngryDestructionStates::DEFAULT);
		angrybirds_sprites.rock_rectangle_long[1].spawn();
		angrybirds_sprites.rock_rectangle_tall[0].setX(800);
		angrybirds_sprites.rock_rectangle_tall[0].setY(800);
		angrybirds_sprites.rock_rectangle_tall[0].setDestruction(AngryDestructionStates::DEFAULT);
		angrybirds_sprites.rock_rectangle_tall[0].spawn();
		angrybirds_sprites.ice_rectangle_long[0].setX(300);
		angrybirds_sprites.ice_rectangle_long[0].setY(800);
		angrybirds_sprites.ice_rectangle_long[0].setDestruction(AngryDestructionStates::DEFAULT);
		angrybirds_sprites.ice_rectangle_long[0].spawn();
		level_spawn = HAS_SPAWNED;
	}

	//If not already playing, play background music and intro sfx
	if (game_music == NOT_PLAYING)
	{
		sound_engine->stopAllSounds();
		sound_engine->play2D("Resources\\ENVIRONMENT\\MUSIC\\0.mp3", false);
		sound_engine->play2D("Resources\\ENVIRONMENT\\SOUNDSCAPES\\0.mp3", true);
		game_music = PLAYING;
	}

	//Handle movement of the currently active bird
	handleBirdMovement(dt_sec, angrybirds_sprites.active_bird);

	//Handle block collision - this NEEDS refactoring ASAP.
	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; i++)
	{
		//Wood
		if (angrybirds_sprites.wood_rectangle_long[i].hasSpawned())
		{
			if (angrybirds_sprites.wood_rectangle_long[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.wood_rectangle_long[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
		if (angrybirds_sprites.wood_rectangle_tall[i].hasSpawned())
		{
			if (angrybirds_sprites.wood_rectangle_tall[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.wood_rectangle_tall[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
		if (angrybirds_sprites.wood_square[i].hasSpawned())
		{
			if (angrybirds_sprites.wood_square[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.wood_square[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}

		//Ice
		if (angrybirds_sprites.ice_rectangle_long[i].hasSpawned())
		{
			if (angrybirds_sprites.ice_rectangle_long[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.ice_rectangle_long[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
		if (angrybirds_sprites.ice_rectangle_tall[i].hasSpawned())
		{
			if (angrybirds_sprites.ice_rectangle_tall[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.ice_rectangle_tall[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
		if (angrybirds_sprites.ice_square[i].hasSpawned())
		{
			if (angrybirds_sprites.ice_square[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.ice_square[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}

		//Rock
		if (angrybirds_sprites.rock_rectangle_long[i].hasSpawned())
		{
			if (angrybirds_sprites.rock_rectangle_long[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.rock_rectangle_long[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
		if (angrybirds_sprites.rock_rectangle_tall[i].hasSpawned())
		{
			if (angrybirds_sprites.rock_rectangle_tall[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.rock_rectangle_tall[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
		if (angrybirds_sprites.rock_square[i].hasSpawned())
		{
			if (angrybirds_sprites.rock_square[i].spriteComponent()->getBoundingBox().isInside(angrybirds_sprites.active_bird.spriteComponent()->getBoundingBox()))
			{
				if (!angrybirds_sprites.rock_square[i].doDamage()) {
					//Block has been destroyed
					//SCORE += 100
				}
				else
				{
					//Block has been damaged but not destroyed
					//SCORE += 50
				}
				angrybirds_sprites.active_bird.setState(AngryCharacterStates::DESPAWNED);
			}
		}
	}

	//Reload bird?
	if (angrybirds_sprites.active_bird.getState() == AngryCharacterStates::DESPAWNED)
	{
		if (angrybirds_gamestate.lives != 0) 
		{
			//If bird has despawned, put it back in cannon
			angrybirds_sprites.active_bird.setState(AngryCharacterStates::IN_CANNON);
		}
		else
		{
			//We're out of lives, can't put a bird in the cannon.
			angrybirds_gamestate.current_gamestate = AngryGamestate::GAME_OVER;
			angrybirds_gamestate.win_state = AngryGamestate::HAS_LOST;
		}
	}
}


/*
Handle movement of the currently active bird
*/
void AngryUpdate::handleBirdMovement(double dt_sec, Character &bird)
{
	switch (bird.getState())
	{
		/* Bird is loaded in cannon and should spawn... */
		case (AngryCharacterStates::IN_CANNON):
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

			//Play SFX
			if (bird_sfx == NOT_PLAYING)
			{
				sound_engine->play2D("Resources\\CHARACTERS\\BIRDS\\RED\\SFX\\0.mp3", false);
				bird_sfx = PLAYING;
			}

			break;
		}

		/* Bird is in cannon and about to be fired... */
		case (AngryCharacterStates::ABOUT_TO_BE_FIRED):
		{
			//Set position of bird to mouse position
			bird.setY(angrybirds_mousedata.mouse_y - (bird.spriteComponent()->getSprite()->height() / 2));
			bird.setX(angrybirds_mousedata.mouse_x - (bird.spriteComponent()->getSprite()->width() / 2));

			break;
		}

		/* Bird has been fired from cannon... */
		case (AngryCharacterStates::HAS_BEEN_FIRED):
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
				bird.setState(AngryCharacterStates::SHOULD_DESPAWN);
			}

			//Place down a flight marker if enough time has elapsed
			AngryFlightVars::time_between_markers += dt_sec;
			if (AngryFlightVars::time_between_markers > 0.1)
			{
				angrybirds_sprites.flight_marker[AngryFlightVars::number_of_markers].spawn();
				angrybirds_sprites.flight_marker[AngryFlightVars::number_of_markers].setX(bird.getX() + (bird.getWidth() / 2));
				angrybirds_sprites.flight_marker[AngryFlightVars::number_of_markers].setY(bird.getY() + (bird.getHeight() / 2));

				AngryFlightVars::number_of_markers += 1;
				AngryFlightVars::time_between_markers = 0;
			}

			break;
		}

		/* Bird is off window and should despawn... */
		case (AngryCharacterStates::SHOULD_DESPAWN):
		{
			//Reset position
			bird.setX((int)AngryGameVars::DESPAWN_X_POS);
			bird.setY((int)AngryGameVars::DESPAWN_Y_POS);

			//Despawn
			bird.despawn();
			bird.setState(AngryCharacterStates::DESPAWNED);

			//Reset music trigger
			bird_sfx = NOT_PLAYING;

			//Update lives accordingly
			angrybirds_gamestate.lives -= 1;

			break;
		}
	}
}
