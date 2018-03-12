#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"

class AngryInput {
	public:
		AngryInput();
		~AngryInput();

		//Input Handlers
		void gstateInMenu(ASGE::SharedEventData data);
		void gstatePlaying(ASGE::SharedEventData data);

	private:
		/* AngryStructs */
		AngryGamestateData angrybirds_gamestate;
};