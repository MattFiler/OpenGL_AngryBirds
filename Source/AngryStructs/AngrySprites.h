#pragma once
#include "GameObject.h"
#include "../AngryEnums/AngryGameVars.h"

struct AngrySprites
{
	static GameObject background_layer; //Main Game Background
	static GameObject menu_layer; //Main Menu Background
	static GameObject active_bird; //The active player controlled bird
	static GameObject waiting_birds[(int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1]; //All birds waiting to be fired
	static GameObject slingshot[2]; //Slingshot (main Y shape foreground & background and cable)
};