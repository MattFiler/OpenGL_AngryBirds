#pragma once

#include "../AngrySpriteClasses/Character.h"
#include "../AngrySpriteClasses/EnvironmentBlock.h"
#include "../AngrySpriteClasses/UI.h"
#include "../AngrySpriteClasses/FX.h"

#include "../AngryEnums/AngryGameVars.h"
#include "../AngryEnums/AngryBackgrounds.h"

struct Sprites
{
	//UI Elements
	static UI backgrounds[(int)BackgroundSprites::NUMBER_OF_BACKGROUNDS]; 
	static UI flight_marker[(int)GameVars::NUMBER_OF_FLIGHT_MARKER_DOTS]; 
	static UI cursor[(int)GameVars::NUMBER_OF_CURSOR_STATES]; 

	//Slingshot
	static UI slingshot[2]; 

	//Birds
	static Character active_bird;
	static Character waiting_birds[(int)GameVars::NUMBER_OF_STARTING_BIRDS - 1]; 

	//Pigs
	static Character pigs[(int)GameVars::NUMBER_OF_PIGS];

	//Wood Blocks
	static EnvironmentBlock wood_rectangle_long[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];
	static EnvironmentBlock wood_rectangle_tall[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];
	static EnvironmentBlock wood_square[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];

	//Ice Blocks
	static EnvironmentBlock ice_rectangle_long[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];
	static EnvironmentBlock ice_rectangle_tall[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];
	static EnvironmentBlock ice_square[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];

	//Rock Blocks
	static EnvironmentBlock rock_rectangle_long[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];
	static EnvironmentBlock rock_rectangle_tall[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];
	static EnvironmentBlock rock_square[(int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION];

	//Level Editor Resources
	static EnvironmentBlock placeholder_marker[(int)GameVars::NUMBER_OF_BLOCK_VARIATIONS + 1]; //+1 for pigs!

	//All FX
	static FX explosion[(int)GameVars::NUMBER_OF_FX_AVAILABLE];
};