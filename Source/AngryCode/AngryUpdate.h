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
#include "../AngryEnums/AngryCharacterInjury.h"

class UpdateState {
	public:
		UpdateState();
		~UpdateState();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);
		void gstateGameOver(const ASGE::GameTime & us);
		void gstateLevelBuilder(const ASGE::GameTime & us);

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

		//Collision handlers
		void detectBlockCollision(EnvironmentBlock& block);
		void detectPigCollision(Character& pig);

		//Handle Bird Movement
		void handleBirdMovement(double dt_sec, Character &bird);

		//Character Animations
		void AnimateBird(Character& bird);
		void AnimatePig(Character& pig);
		float eyes_open_time = 0; //This time randomly generated every frame when playing.
		float eyes_closed_time = 0.5;

		//Game timer
		float game_time = 0;

		/* AngryStructs */
		GamestateData gamestate;
		MouseData mousedata;
		Sprites sprites;
};