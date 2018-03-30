#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryEnums/AngryMenuScreens.h"
#include "../AngryEnums/AngryGameVars.h"

#include "../AngryCode/AngryLevels.h"

class InputStates {
	public:
		InputStates();
		~InputStates();

		//Input Handlers
		void gstateInMenu(ASGE::SharedEventData data);
		void gstatePlaying(ASGE::SharedEventData data);

	private:
		/* AngryStructs */
		GamestateData gamestate;
};