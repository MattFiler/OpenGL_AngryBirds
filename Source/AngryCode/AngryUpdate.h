#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"
#include "../AngryStructs/AngryFlightVars.h"
#include "../AngryStructs/AngryMouseData.h"

#include "../AngryEnums/AngryBirdStates.h"
#include "../AngryEnums/AngryGameVars.h"

class AngryUpdate {
	public:
		AngryUpdate();
		~AngryUpdate();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);

		//Handle Bird Movement
		void handleBirdMovement(double dt_sec, GameObject &bird);

	private:
		/* AngryStructs */
		AngryGamestateData angrybirds_gamestate;
		AngryMouseData angrybirds_mousedata;
		AngrySprites angrybirds_sprites;
};