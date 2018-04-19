#include "../AngryStructs/AngrySprites.h"

//UI Elements
UI Sprites::backgrounds[(int)BackgroundSprites::NUMBER_OF_BACKGROUNDS];
UI Sprites::flight_marker[(int)GameVars::MAX_FLIGHT_MARKER_DOTS];
UI Sprites::cursor[6]; //2 Cursors, 4 Level Editor Sprites

//Slingshot
UI Sprites::slingshot[2];

//Birds
Character Sprites::active_bird;
Character Sprites::waiting_birds[(int)GameVars::NUMBER_OF_STARTING_BIRDS - 1];

//Pigs
Character Sprites::pigs[(int)GameVars::MAX_NUMBER_OF_PIGS];

//Wood Blocks
EnvironmentBlock Sprites::wood_rectangle_long[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock Sprites::wood_rectangle_tall[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock Sprites::wood_square[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

//Ice Blocks
EnvironmentBlock Sprites::ice_rectangle_long[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock Sprites::ice_rectangle_tall[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock Sprites::ice_square[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

//Rock Blocks
EnvironmentBlock Sprites::rock_rectangle_long[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock Sprites::rock_rectangle_tall[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];
EnvironmentBlock Sprites::rock_square[(int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE];

//Level Editor Resources
EnvironmentBlock Sprites::placeholder_marker[(int)GameVars::BLOCK_VARIATIONS + 1]; //+1 for pigs!