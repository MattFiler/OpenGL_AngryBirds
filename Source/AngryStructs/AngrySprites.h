#pragma once

#include "../AngrySpriteClasses/Character.h"
#include "../AngrySpriteClasses/EnvironmentBlock.h"
#include "../AngrySpriteClasses/UI.h"

#include "../AngryEnums/AngryGameVars.h"
#include "../AngryEnums/AngryBackgrounds.h"

struct AngrySprites
{
	//UI Elements
	static UI backgrounds[(int)AngryBackgrounds::NUMBER_OF_BACKGROUNDS]; 
	static UI flight_marker[(int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS]; 
	static UI cursor[2]; 

	//Slingshot
	static UI slingshot[2]; 

	//Birds
	static Character active_bird;
	static Character waiting_birds[(int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1]; 

	//Wood Blocks
	static EnvironmentBlock wood_rectangle_long[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock wood_rectangle_tall[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock wood_square[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

	//Ice Blocks
	static EnvironmentBlock ice_rectangle_long[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock ice_rectangle_tall[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock ice_square[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

	//Rock Blocks
	static EnvironmentBlock rock_rectangle_long[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock rock_rectangle_tall[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock rock_square[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
};