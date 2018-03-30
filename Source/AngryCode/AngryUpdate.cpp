#include "AngryUpdate.h"

//Create and destroy the sound engine when the class is called
UpdateState::UpdateState() {
	sound_engine = irrklang::createIrrKlangDevice();
}
UpdateState::~UpdateState() {
	sound_engine->drop();
}


/*
GAMESTATE_IN_MENU
*/
void UpdateState::gstateInMenu(const ASGE::GameTime & us) {
	//Game has just been won or lost - reset everything here
	if (gamestate.win_state != Gamestate::NO_STATE) 
	{
		//Reset music
		menu_music = NOT_PLAYING;
		game_music = NOT_PLAYING;
		game_over_music = NOT_PLAYING;
		bird_sfx = NOT_PLAYING;
		sound_engine->stopAllSounds();

		//Reset gamestate & score
		gamestate.win_state = Gamestate::NO_STATE;
		gamestate.lives = (int)GameVars::NUMBER_OF_STARTING_BIRDS;

		//Reset level build
		level_spawn = NEEDS_TO_SPAWN;
		level.ResetLevel();

		//Reset menu marker positions
		gamestate.main_menu_index = 0;
		gamestate.level_select_menu_index = 0;
		gamestate.game_over_menu_index = 0;
		gamestate.pause_menu_index = 0;

		//Reset flight marker dots
		for (int i = 0; i < (int)GameVars::MAX_FLIGHT_MARKER_DOTS; i++)
		{
			sprites.flight_marker[i].despawn();
		}
	}

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
void UpdateState::gstatePlaying(const ASGE::GameTime & us) {
	//Calculate frame time in seconds
	auto dt_sec = us.delta_time.count() / 1000.0;
	game_time += dt_sec; //update gametime

	//Ensure we get the victory/defeat track!
	game_over_music = NOT_PLAYING;
	gamestate.pause_menu_index = 0; //Also keep pause menu index reset.

	//Generate level if it hasn't already been
	if (level_spawn == NEEDS_TO_SPAWN) 
	{
		level.GenerateLevel(gamestate.current_level);
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
	handleBirdMovement(dt_sec, sprites.active_bird);

	//Handle block collision
	for (int i = 0; i < (int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; i++)
	{
		//Wood
		detectCollision(sprites.wood_rectangle_long[i]);
		detectCollision(sprites.wood_rectangle_tall[i]);
		detectCollision(sprites.wood_square[i]);

		//Ice
		detectCollision(sprites.ice_rectangle_long[i]);
		detectCollision(sprites.ice_rectangle_tall[i]);
		detectCollision(sprites.ice_square[i]);

		//Rock
		detectCollision(sprites.rock_rectangle_long[i]);
		detectCollision(sprites.rock_rectangle_tall[i]);
		detectCollision(sprites.rock_square[i]);
	}

	//Reload bird?
	if (sprites.active_bird.getState() == CharacterStates::DESPAWNED)
	{
		if (gamestate.lives != 0) 
		{
			//If bird has despawned, put it back in cannon
			sprites.active_bird.setState(CharacterStates::IN_CANNON);
		}
		else
		{
			//We're out of lives, can't put a bird in the cannon.
			gamestate.current_gamestate = Gamestate::GAME_OVER;
			gamestate.win_state = Gamestate::HAS_LOST;
		}
	}
}

/*
HAS_WON HAS_LOST
*/
void UpdateState::gstateGameOver(const ASGE::GameTime & us)
{
	//If not already playing, play background music
	if (game_over_music == NOT_PLAYING)
	{
		sound_engine->stopAllSounds();
		sound_engine->play2D("Resources\\UI\\MUSIC\\1.mp3", false);
		game_over_music = PLAYING;
	}
}


//Detect collision on spawned items
void UpdateState::detectCollision(EnvironmentBlock& block)
{
	if (block.hasSpawned())
	{
		if (block.spriteComponent()->getBoundingBox().isInside(sprites.active_bird.spriteComponent()->getBoundingBox()))
		{
			if (!block.doDamage()) {
				//Block has been destroyed
				//SCORE += 100
			}
			else
			{
				//Block has been damaged but not destroyed
				//SCORE += 50
			}
			sprites.active_bird.setState(CharacterStates::DESPAWNED);
		}
	}
}


/*
Handle movement of the currently active bird
*/
void UpdateState::handleBirdMovement(double dt_sec, Character &bird)
{
	switch (bird.getState())
	{
		/* Bird is loaded in cannon and should spawn... */
		case (CharacterStates::IN_CANNON):
		{
			//Spawn
			bird.spawn();

			//Set Position to cannon
			bird.setX((float)GameVars::SLINGSHOT_X_ORIGIN);
			bird.setY((float)GameVars::SLINGSHOT_Y_ORIGIN);

			//Reset vars
			FlightVars::bird_flight_time = 0;
			FlightVars::pullback_angle = 0;
			FlightVars::pullback_force = 0;

			//Play SFX
			if (bird_sfx == NOT_PLAYING)
			{
				sound_engine->play2D("Resources\\CHARACTERS\\BIRDS\\RED\\SFX\\0.mp3", false);
				bird_sfx = PLAYING;
			}

			break;
		}

		/* Bird is in cannon and about to be fired... */
		case (CharacterStates::ABOUT_TO_BE_FIRED):
		{
			//Set position of bird to mouse position
			bird.setY(mousedata.mouse_y - (bird.spriteComponent()->getSprite()->height() / 2));
			bird.setX(mousedata.mouse_x - (bird.spriteComponent()->getSprite()->width() / 2));

			break;
		}

		/* Bird has been fired from cannon... */
		case (CharacterStates::HAS_BEEN_FIRED):
		{
			//Calculate the time our bird has been in flight - this will act as our gravity
			FlightVars::bird_flight_time += dt_sec;

			//Move bird dependant on user input
			bird.subtractFromY((FlightVars::pullback_angle * (int)GameVars::FLIGHT_ANGLE_MODIFIER * dt_sec) - 
							   (FlightVars::bird_flight_time / (int)GameVars::FLIGHT_TIME_MODIFIER));
			bird.addToX(FlightVars::pullback_force * 
						(int)GameVars::FLIGHT_FORCE_MODIFIER * dt_sec);

			//Off window
			if (bird.getY() > (int)GameVars::GAME_HEIGHT ||
				//bird.getY() < -bird.spriteComponent()->getSprite()->height() ||
				bird.getX() > (int)GameVars::GAME_WIDTH ||
				bird.getX() < -bird.spriteComponent()->getSprite()->width())
			{
				bird.setState(CharacterStates::SHOULD_DESPAWN);
			}

			//Place down a flight marker if enough time has elapsed
			FlightVars::time_between_markers += dt_sec;
			if (FlightVars::time_between_markers > 0.1)
			{
				sprites.flight_marker[FlightVars::number_of_markers].spawn();
				sprites.flight_marker[FlightVars::number_of_markers].setX(bird.getX() + (bird.getWidth() / 2));
				sprites.flight_marker[FlightVars::number_of_markers].setY(bird.getY() + (bird.getHeight() / 2));

				FlightVars::number_of_markers += 1;
				FlightVars::time_between_markers = 0;
			}

			break;
		}

		/* Bird is off window and should despawn... */
		case (CharacterStates::SHOULD_DESPAWN):
		{
			//Reset position
			bird.setX((int)GameVars::DESPAWN_X_POS);
			bird.setY((int)GameVars::DESPAWN_Y_POS);

			//Despawn
			bird.despawn();
			bird.setState(CharacterStates::DESPAWNED);

			//Reset music trigger
			bird_sfx = NOT_PLAYING;

			//Update lives accordingly
			gamestate.lives -= 1;

			break;
		}
	}
}
