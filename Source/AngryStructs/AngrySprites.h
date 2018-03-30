#pragma once

#include "../AngrySpriteClasses/Character.h"
#include "../AngrySpriteClasses/EnvironmentBlock.h"
#include "../AngrySpriteClasses/UI.h"

#include "../AngryEnums/AngryGameVars.h"
#include "../AngryEnums/AngryBackgrounds.h"

struct Sprites
{
	//UI Elements
	static UI backgrounds[(int)BackgroundSprites::NUMBER_OF_BACKGROUNDS]; 
	static UI flight_marker[(int)GameVars::MAX_FLIGHT_MARKER_DOTS]; 
	static UI cursor[2]; 

	//Slingshot
	static UI slingshot[2]; 

	//Birds
	static Character active_bird;
	static Character waiting_birds[(int)GameVars::NUMBER_OF_STARTING_BIRDS - 1]; 

	//Wood Blocks
	static EnvironmentBlock wood_rectangle_long[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock wood_rectangle_tall[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock wood_square[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

	//Ice Blocks
	static EnvironmentBlock ice_rectangle_long[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock ice_rectangle_tall[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock ice_square[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

	//Rock Blocks
	static EnvironmentBlock rock_rectangle_long[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock rock_rectangle_tall[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
	static EnvironmentBlock rock_square[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
};