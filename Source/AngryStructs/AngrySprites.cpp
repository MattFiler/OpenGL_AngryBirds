#include "../AngryStructs/AngrySprites.h"

//UI Elements
UI AngrySprites::backgrounds[(int)AngryBackgrounds::NUMBER_OF_BACKGROUNDS];
UI AngrySprites::flight_marker[(int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS];
UI AngrySprites::cursor[2];

//Slingshot
UI AngrySprites::slingshot[2];

//Birds
Character AngrySprites::active_bird;
Character AngrySprites::waiting_birds[(int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1];

//Wood Blocks
EnvironmentBlock AngrySprites::wood_rectangle_long[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock AngrySprites::wood_rectangle_tall[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock AngrySprites::wood_square[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

//Ice Blocks
EnvironmentBlock AngrySprites::ice_rectangle_long[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock AngrySprites::ice_rectangle_tall[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock AngrySprites::ice_square[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

//Rock Blocks
EnvironmentBlock AngrySprites::rock_rectangle_long[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock AngrySprites::rock_rectangle_tall[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock AngrySprites::rock_square[(int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];