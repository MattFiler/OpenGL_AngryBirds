#pragma once
#pragma comment(lib, "irrKlang.lib")

#include <string>
#include <Engine/OGLGame.h>
#include <irrklang.h>

#include "../AngryCode/AngryLevels.h"

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"
#include "../AngryStructs/AngryFlightVars.h"
#include "../AngryStructs/AngryMouseData.h"

#include "../AngryEnums/AngryCharacterStates.h"
#include "../AngryEnums/AngryGameVars.h"

class UpdateState {
	public:
		UpdateState();
		~UpdateState();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);
		void gstateGameOver(const ASGE::GameTime & us);

		//Collision handler
		void detectCollision(EnvironmentBlock& block);

		//Handle Bird Movement
		void handleBirdMovement(double dt_sec, Character &bird);

	private:
		//Define music states (to avoid multiple tracks playing)
		enum music_state { PLAYING, NOT_PLAYING };
		int menu_music = NOT_PLAYING;
		int game_music = NOT_PLAYING;
		int bird_sfx = NOT_PLAYING;
		int game_over_music = NOT_PLAYING;

		//Our class' sound engine
		irrklang::ISoundEngine* sound_engine;

		//Level generation
		enum level_state { NEEDS_TO_SPAWN, HAS_SPAWNED };
		int level_spawn = NEEDS_TO_SPAWN;
		LevelSetups level;

		//Game time
		float game_time = 0;

		/* AngryStructs */
		GamestateData gamestate;
		MouseData mousedata;
		Sprites sprites;
};