#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"
#include "../AngryStructs/AngryFlightVars.h"
#include "../AngryStructs/AngryMouseData.h"

#include "../AngryEnums/AngryPigStates.h"
#include "../AngryEnums/AngryGameVars.h"

class AngryUpdate {
	public:
		AngryUpdate();
		~AngryUpdate();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);

		void handleBirdMovement(double dt_sec);

	private:
		AngryGamestateData angrybirds_gamestate;
		AngryMouseData angrybirds_mousedata;
		AngrySprites angrybirds_sprites;
};