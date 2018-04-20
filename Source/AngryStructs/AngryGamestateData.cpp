#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryEnums/AngryGameVars.h"

Gamestate GamestateData::current_gamestate = Gamestate::IN_MENU; //By default, gamestate is IN_MENU 
MenuScreen GamestateData::menu_screen = MenuScreen::SPLASHSCREEN; //By default we land on the splashscreen
Gamestate GamestateData::win_state = Gamestate::NO_STATE; //This is set at runtime when we win or lose. Reset on return to menu
int GamestateData::lives = (int)GameVars::NUMBER_OF_STARTING_BIRDS; //Lives defaults are preset in AngryGameVars
int GamestateData::current_level = 0; //Set from Main Menu at runtime
int GamestateData::main_menu_index = 0; //Set as 0 for default
int GamestateData::level_select_menu_index = 0; //Set as 0 for default
int GamestateData::pause_menu_index = 0; //Set as 0 for default
int GamestateData::game_over_menu_index = 0; //Set as 0 for default

bool GamestateData::debug_place_block = false; //True = should place
float GamestateData::debug_block_scale = 1; //1 is default