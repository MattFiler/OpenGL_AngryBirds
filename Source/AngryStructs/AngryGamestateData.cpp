#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryEnums/AngryGameVars.h"

AngryGamestate AngryGamestateData::current_gamestate = AngryGamestate::IN_MENU; //By default, gamestate is IN_MENU 
int AngryGamestateData::lives = (int)AngryGameVars::NUMBER_OF_STARTING_BIRDS; //Lives defaults are preset in AngryGameVars