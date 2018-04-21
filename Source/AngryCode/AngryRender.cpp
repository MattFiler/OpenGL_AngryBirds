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
			for (int i = 0; i < (int)GameVars::NUMBER_OF_LEVELS; i++)
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
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FLIGHT_MARKER_DOTS; i++)
	{
		if (sprites.flight_marker[i].hasSpawned())
		{
			renderer->renderSprite(*sprites.flight_marker[i].spriteComponent()->getSprite());
		}
	}

	//Slingshot background
	renderer->renderSprite(*sprites.slingshot[0].spriteComponent()->getSprite());

	//Blocks
	for (int i = 0; i < (int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION; i++)
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
	for (int i = 0; i < (int)GameVars::NUMBER_OF_PIGS; i++)
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

	//Inactive birds 
	for (int i = 0; i < (int)GameVars::NUMBER_OF_STARTING_BIRDS - 1; i++)
	{
		if (sprites.waiting_birds[i].hasSpawned())
		{
			renderer->renderSprite(*sprites.waiting_birds[i].spriteComponent()->getSprite());
		}
	}

	//Explosion FX
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FX_AVAILABLE; i++)
	{
		if (sprites.explosion[i].hasSpawned()) 
		{
			renderer->renderSprite(*sprites.explosion[i].spriteComponent()->getSprite());
		}
	}

	//Score Bonuses
	for (int i = 0; i < (int)GameVars::NUMBER_OF_STARTING_BIRDS; i++)
	{
		if (sprites.score_bonus_10000[i].hasSpawned())
		{
			renderer->renderSprite(*sprites.score_bonus_10000[i].spriteComponent()->getSprite());
		}
	}
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FX_AVAILABLE; i++)
	{
		if (sprites.score_bonus_5000[i].hasSpawned())
		{
			renderer->renderSprite(*sprites.score_bonus_5000[i].spriteComponent()->getSprite());
		}
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

	//Render stars
	renderer->renderSprite(*sprites.score_stars[gamestate.awarded_stars].spriteComponent()->getSprite());

	//Exit/Quit Options
	renderer->renderText(gamestate.game_over_menu_index == 0 ? "> BACK" : "  BACK", ((int)GameVars::GAME_WIDTH / 2) - 70, ((int)GameVars::GAME_HEIGHT / 2) + 170, 1, ASGE::COLOURS::WHITE);
	renderer->renderText(gamestate.game_over_menu_index == 1 ? "> QUIT" : "  QUIT", ((int)GameVars::GAME_WIDTH / 2) - 70, ((int)GameVars::GAME_HEIGHT / 2) + 250, 1, ASGE::COLOURS::WHITE);
}

/*
Level Builder
*/
void RenderStates::gstateLevelBuilder(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Background
	renderer->renderSprite(*sprites.backgrounds[(int)BackgroundSprites::LEVEL_BUILDER_BACKGROUND].spriteComponent()->getSprite());

	//Slingshot
	renderer->renderSprite(*sprites.slingshot[0].spriteComponent()->getSprite());
	renderer->renderSprite(*sprites.slingshot[1].spriteComponent()->getSprite());

	//Set default font
	renderer->setFont(0);

	//Render builder overlay
	renderer->renderText("LEVEL EDITOR MODE ACTIVE", 50, 75, 2, ASGE::COLOURS::RED);
	renderer->renderText("CURRENT X: " + std::to_string(mousedata.mouse_x), 50, 100, 1, ASGE::COLOURS::RED);
	renderer->renderText("CURRENT Y: " + std::to_string(mousedata.mouse_y - 10), 50, 125, 1, ASGE::COLOURS::RED);
	renderer->renderText("CURRENT SCALE: " + std::to_string(gamestate.debug_block_scale), 50, 150, 1, ASGE::COLOURS::RED);
	renderer->renderText("SCALE DOES NOT APPLY TO CHARACTERS!", 50, 175, 1, ASGE::COLOURS::RED);
	renderer->renderText("LMB: PLACE ENTITY", 50, 265, 1, ASGE::COLOURS::RED);
	renderer->renderText("RMB: SWAP ENTITY TYPE", 50, 290, 1, ASGE::COLOURS::RED);
	renderer->renderText("UP/DOWN ARROW: SCALE BLOCK", 50, 315, 1, ASGE::COLOURS::RED);

	//Render placeholders
	if (gamestate.current_gamestate == Gamestate::LEVEL_BUILDER_MODE)
	{
		for (int i = 0; i < ((int)GameVars::NUMBER_OF_BLOCK_VARIATIONS + 1); i++)
		{
			renderer->renderSprite(*sprites.placeholder_marker[i].spriteComponent()->getSprite());
		}
	}
}