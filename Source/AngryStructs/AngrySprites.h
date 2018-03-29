#pragma once
#include "GameObject.h"
#include "../AngryEnums/AngryGameVars.h"
#include "../AngryEnums/AngryBackgrounds.h"

struct AngrySprites
{
	static GameObject backgrounds[(int)AngryBackgrounds::NUMBER_OF_BACKGROUNDS]; //Backgrounds
	static GameObject flight_marker[(int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS]; //All flight marker dots
	static GameObject cursor[2]; //Both cursor states for the game
	static GameObject active_bird; //The active player controlled bird
	static GameObject waiting_birds[(int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1]; //All birds waiting to be fired
	static GameObject slingshot[2]; //Slingshot (main Y shape foreground & background and cable)
};