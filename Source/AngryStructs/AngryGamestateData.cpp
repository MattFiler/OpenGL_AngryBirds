#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryEnums/AngryGameVars.h"

AngryGamestate AngryGamestateData::current_gamestate = AngryGamestate::IN_MENU; //By default, gamestate is IN_MENU 
AngryMenuScreens AngryGamestateData::menu_screen = AngryMenuScreens::SPLASHSCREEN; //By default we land on the splashscreen
AngryGamestate AngryGamestateData::win_state = AngryGamestate::HAS_WON; //Set as "won" by default, but this is actually set at runtime before called
int AngryGamestateData::lives = (int)AngryGameVars::NUMBER_OF_STARTING_BIRDS; //Lives defaults are preset in AngryGameVars