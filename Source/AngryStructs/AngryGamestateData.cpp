#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryEnums/AngryGameVars.h"

//By default, gamestate is IN_MENU
AngryGamestate AngryGamestateData::current_gamestate = AngryGamestate::IN_MENU;
int AngryGamestateData::current_bird = (int)AngryGameVars::MAX_NUMBER_OF_BIRDS - 1;