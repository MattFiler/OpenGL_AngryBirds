#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryEnums/AngryGameVars.h"

Gamestate GamestateData::current_gamestate = Gamestate::IN_MENU; //By default, gamestate is IN_MENU 
MenuScreens GamestateData::menu_screen = MenuScreens::SPLASHSCREEN; //By default we land on the splashscreen
Gamestate GamestateData::win_state = Gamestate::HAS_WON; //Set as "won" by default, but this is actually set at runtime before called
int GamestateData::lives = (int)GameVars::NUMBER_OF_STARTING_BIRDS; //Lives defaults are preset in AngryGameVars
int GamestateData::current_level = 0; //Set from Main Menu at runtime