#include "AngryRender.h"

RenderStates::RenderStates() {
	levels.loadLevels();
}
RenderStates::~RenderStates() {

}


/*
GAMESTATE_IN_MENU
*/
void RenderStates::gstateInMenu(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	switch (gamestate.menu_screen) {
		//Splashscreen
		case MenuScreen::SPLASHSCREEN: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::SPLASHSCREEN_BACKGROUND].spriteComponent()->getSprite());

			renderer->renderText("PRESS SPACE TO BEGIN", ((int)GameVars::GAME_WIDTH / 2) - 240, ((int)GameVars::GAME_HEIGHT / 2) + ((int)GameVars::GAME_HEIGHT / 2.7), 1, ASGE::COLOURS::WHITE);

			break;
		}
		//Main menu
		case MenuScreen::MAIN_MENU: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::MAIN_MENU_BACKGROUND].spriteComponent()->getSprite());

			//Play/Quit Options
			renderer->renderText(gamestate.main_menu_index == 0 ? "> PLAY" : "  PLAY", (int)GameVars::GAME_WIDTH - 350, 150, 1, ASGE::COLOURS::WHITE);
			renderer->renderText(gamestate.main_menu_index == 1 ? "> QUIT" : "  QUIT", (int)GameVars::GAME_WIDTH - 350, 250, 1, ASGE::COLOURS::WHITE);

			break;
		}
		//Level select
		case MenuScreen::LEVEL_SELECT: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::LEVEL_SELECT_MENU_BACKGROUND].spriteComponent()->getSprite());

			//All Level Options (dynamically generated and handled from the number of level configs)
			for (int i = 0; i < (int)GameVars::LEVELS; i++)
			{
				std::string level_name = levels.getLevelName(i);
				renderer->renderText(gamestate.level_select_menu_index == i ? ("> " + level_name) : ("  " + level_name), (int)GameVars::GAME_WIDTH - 350, ((i + 1) * 100) + 50, 1, ASGE::COLOURS::WHITE);
			}

			break;
		}
		//Pause menu
		case MenuScreen::PAUSE_MENU: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::PAUSE_MENU_BACKGROUND].spriteComponent()->getSprite());

			//Exit/Resume Options
			renderer->renderText(gamestate.pause_menu_index == 0 ? "> CONTINUE" : "  CONTINUE", ((int)GameVars::GAME_WIDTH / 2) - 125, ((int)GameVars::GAME_HEIGHT / 2) + 170, 1, ASGE::COLOURS::WHITE);
			renderer->renderText(gamestate.pause_menu_index == 1 ? "> QUIT" : "  QUIT", ((int)GameVars::GAME_WIDTH / 2) - 70, ((int)GameVars::GAME_HEIGHT / 2) + 250, 1, ASGE::COLOURS::WHITE);

			break;
		}
	}
}

/*
GAMESTATE_IS_PLAYING
*/
void RenderStates::gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer) 
{
	//In-game background
	renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::INGAME_BACKGROUND].spriteComponent()->getSprite());

	//Render Spawned Flight Marker Dots 
	for (int i = 0; i < (int)GameVars::MAX_FLIGHT_MARKER_DOTS; i++)
	{
		if (sprites.flight_marker[i].hasSpawned())
		{
			renderer->renderSprite(*sprites.flight_marker[i].spriteComponent()->getSprite());
		}
	}

	//Slingshot background
	renderer->renderSprite(*sprites.slingshot[0].spriteComponent()->getSprite());

	//Blocks
	for (int i = 0; i < (int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; i++)
	{
		//Wood
		if (sprites.wood_rectangle_long[i].hasSpawned())
			renderer->renderSprite(*sprites.wood_rectangle_long[i].spriteComponent()->getSprite());
		if (sprites.wood_rectangle_tall[i].hasSpawned())
			renderer->renderSprite(*sprites.wood_rectangle_tall[i].spriteComponent()->getSprite());
		if (sprites.wood_square[i].hasSpawned())
			renderer->renderSprite(*sprites.wood_square[i].spriteComponent()->getSprite());

		//Ice
		if (sprites.ice_rectangle_long[i].hasSpawned())
			renderer->renderSprite(*sprites.ice_rectangle_long[i].spriteComponent()->getSprite());
		if (sprites.ice_rectangle_tall[i].hasSpawned())
			renderer->renderSprite(*sprites.ice_rectangle_tall[i].spriteComponent()->getSprite());
		if (sprites.ice_square[i].hasSpawned())
			renderer->renderSprite(*sprites.ice_square[i].spriteComponent()->getSprite());

		//Rock
		if (sprites.rock_rectangle_long[i].hasSpawned())
			renderer->renderSprite(*sprites.rock_rectangle_long[i].spriteComponent()->getSprite());
		if (sprites.rock_rectangle_tall[i].hasSpawned())
			renderer->renderSprite(*sprites.rock_rectangle_tall[i].spriteComponent()->getSprite());
		if (sprites.rock_square[i].hasSpawned())
			renderer->renderSprite(*sprites.rock_square[i].spriteComponent()->getSprite());
	}

	//Pigs
	for (int i = 0; i < (int)GameVars::MAX_NUMBER_OF_PIGS; i++)
	{
		if (sprites.pigs[i].hasSpawned())
		{
			renderer->renderSprite(*sprites.pigs[i].spriteComponent()->getSprite());
		}
	}

	//Active player controlled bird
	if (sprites.active_bird.hasSpawned()) 
	{
		renderer->renderSprite(*sprites.active_bird.spriteComponent()->getSprite());
	}

	//Slingshot foreground
	renderer->renderSprite(*sprites.slingshot[1].spriteComponent()->getSprite());

	//Inactive birds (only render number of lives - 1)
	for (int i = 0; i < gamestate.lives - 1; i++)
	{
		renderer->renderSprite(*sprites.waiting_birds[i].spriteComponent()->getSprite());
	}
}

/*
HAS_WON, HAS_LOST
*/
void RenderStates::gstateGameOver(const ASGE::GameTime & us, ASGE::Renderer* renderer) 
{
	//Win/loss specific backgrounds
	switch (gamestate.win_state) {
		case Gamestate::HAS_LOST: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::LOSS_SCREEN_BACKGROUND].spriteComponent()->getSprite());
			break;
		}
		case Gamestate::HAS_WON: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::WIN_SCREEN_BACKGROUND].spriteComponent()->getSprite());
			break;
		}
	}

	//Exit/Quit Options
	renderer->renderText(gamestate.game_over_menu_index == 0 ? "> BACK" : "  BACK", ((int)GameVars::GAME_WIDTH / 2) - 70, ((int)GameVars::GAME_HEIGHT / 2) + 170, 1, ASGE::COLOURS::WHITE);
	renderer->renderText(gamestate.game_over_menu_index == 1 ? "> QUIT" : "  QUIT", ((int)GameVars::GAME_WIDTH / 2) - 70, ((int)GameVars::GAME_HEIGHT / 2) + 250, 1, ASGE::COLOURS::WHITE);
}