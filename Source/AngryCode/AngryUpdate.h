#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"

class AngryUpdate {
	public:
		AngryUpdate();
		~AngryUpdate();

		//Update Handlers
		void gstateInMenu(const ASGE::GameTime & us);
		void gstatePlaying(const ASGE::GameTime & us);

	private:
		AngryGamestateData angrybirds_gamestate;
};