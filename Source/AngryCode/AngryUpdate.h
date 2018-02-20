#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"
#include "../AngryEnums/AngryPigStates.h"

class AngryUpdate {
	public:
		AngryUpdate();
		~AngryUpdate();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);

	private:
		AngryGamestateData angrybirds_gamestate;
		AngrySprites angrybirds_sprites;
};