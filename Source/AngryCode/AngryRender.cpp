#include "AngryRender.h"

RenderStates::RenderStates() {

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
		case MenuScreens::SPLASHSCREEN: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::SPLASHSCREEN_BACKGROUND].spriteComponent()->getSprite());

			renderer->renderText("PRESS SPACE TO BEGIN", ((int)GameVars::GAME_WIDTH / 2) - 180, ((int)GameVars::GAME_HEIGHT / 2) + ((int)GameVars::GAME_HEIGHT / 2.7), 1, ASGE::COLOURS::WHITE);

			break;
		}
		//Main menu
		case MenuScreens::MAIN_MENU: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::MAIN_MENU_BACKGROUND].spriteComponent()->getSprite());

			renderer->renderText(gamestate.main_menu_index == 0 ? "> PLAY" : "  PLAY", (int)GameVars::GAME_WIDTH - 350, 150, 1, ASGE::COLOURS::WHITE);
			renderer->renderText(gamestate.main_menu_index == 1 ? "> QUIT" : "  QUIT", (int)GameVars::GAME_WIDTH - 350, 250, 1, ASGE::COLOURS::WHITE);

			break;
		}
		//Level select
		case MenuScreens::LEVEL_SELECT: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::LEVEL_SELECT_MENU_BACKGROUND].spriteComponent()->getSprite());

			for (int i = 0; i < LevelSetups::count; i++)
			{
				int current_level = i + 1;
				renderer->renderText(gamestate.level_select_menu_index == i ? ("> LEVEL " + std::to_string(current_level)) : ("  LEVEL " + std::to_string(current_level)), (int)GameVars::GAME_WIDTH - 350, (current_level * 100) + 50, 1, ASGE::COLOURS::WHITE);
			}

			break;
		}
		//Pause menu
		case MenuScreens::PAUSE_MENU: {
			renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::PAUSE_MENU_BACKGROUND].spriteComponent()->getSprite());
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
	if (gamestate.win_state == Gamestate::HAS_LOST) 
	{
		renderer->renderText("YOU LOST", ((int)GameVars::GAME_WIDTH / 2) - 180, ((int)GameVars::GAME_HEIGHT / 2), 1, ASGE::COLOURS::WHITE);
	}
	if (gamestate.win_state == Gamestate::HAS_WON)
	{
		renderer->renderText("YOU WON", ((int)GameVars::GAME_WIDTH / 2) - 180, ((int)GameVars::GAME_HEIGHT / 2), 1, ASGE::COLOURS::WHITE);
	}
}