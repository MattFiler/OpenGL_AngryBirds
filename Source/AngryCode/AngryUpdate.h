#pragma once
#pragma comment(lib, "irrKlang.lib")

#include <string>
#include <Engine/OGLGame.h>
#include <irrklang.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"
#include "../AngryStructs/AngryFlightVars.h"
#include "../AngryStructs/AngryMouseData.h"

#include "../AngryEnums/AngryCharacterStates.h"
#include "../AngryEnums/AngryGameVars.h"

class AngryUpdate {
	public:
		AngryUpdate();
		~AngryUpdate();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);

		//Handle Bird Movement
		void handleBirdMovement(double dt_sec, Character &bird);

	private:
		//Define music states (to avoid multiple tracks playing)
		enum music_state { PLAYING, NOT_PLAYING };
		int menu_music = NOT_PLAYING;
		int game_music = NOT_PLAYING;
		int bird_sfx = NOT_PLAYING;

		//Our class' sound engine
		irrklang::ISoundEngine* sound_engine;

		//Level generation
		enum level_state { NEEDS_TO_SPAWN, HAS_SPAWNED };
		int level_spawn = NEEDS_TO_SPAWN;

		//Game time
		float game_time = 0;

		/* AngryStructs */
		AngryGamestateData angrybirds_gamestate;
		AngryMouseData angrybirds_mousedata;
		AngrySprites angrybirds_sprites;
};