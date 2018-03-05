#pragma once
#include "GameObject.h"
#include "../AngryEnums/AngryGameVars.h"

struct AngrySprites
{
	//Gameworld
	static GameObject background_layer; //Main Game Background
	static GameObject menu_layer; //Main Menu Background

	//Player controlled entities
	static GameObject birds[(int)AngryGameVars::MAX_NUMBER_OF_BIRDS - 1]; //All available birds

	//Enemy entities
	static GameObject pigs[(int)AngryGameVars::MAX_NUMBER_OF_PIGS - 1]; //All available pig enemies
};