#include "AngryRender.h"

AngryRender::AngryRender() {

}
AngryRender::~AngryRender() {

}


/*
GAMESTATE_IN_MENU
*/
void AngryRender::gstateInMenu(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	switch (angrybirds_gamestate.menu_screen) {
		//Splashscreen
		case AngryMenuScreens::SPLASHSCREEN: {
			renderer->renderSprite(*angrybirds_sprites.backgrounds[(int)AngryBackgrounds::SPLASHSCREEN_BACKGROUND].spriteComponent()->getSprite());
			renderer->renderText("PRESS ENTER TO BEGIN", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2) + ((int)AngryGameVars::GAME_HEIGHT / 2.7), 1, ASGE::COLOURS::WHITE);
			break;
		}
		//Main menu
		case AngryMenuScreens::MAIN_MENU: {
			renderer->renderSprite(*angrybirds_sprites.backgrounds[(int)AngryBackgrounds::MAIN_MENU_BACKGROUND].spriteComponent()->getSprite());
			renderer->renderText("MAIN MENU", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2) + ((int)AngryGameVars::GAME_HEIGHT / 2.7), 1, ASGE::COLOURS::WHITE);
			break;
		}
	}
}

/*
GAMESTATE_IS_PLAYING
*/
void AngryRender::gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer) 
{
	//In-game background
	renderer->renderSprite(*angrybirds_sprites.backgrounds[(int)AngryBackgrounds::INGAME_BACKGROUND].spriteComponent()->getSprite());

	//Render Spawned Flight Marker Dots 
	for (int i = 0; i < (int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS; i++)
	{
		if (angrybirds_sprites.flight_marker[i].hasSpawned())
		{
			renderer->renderSprite(*angrybirds_sprites.flight_marker[i].spriteComponent()->getSprite());
		}
	}

	//Slingshot background
	renderer->renderSprite(*angrybirds_sprites.slingshot[0].spriteComponent()->getSprite());

	//Blocks
	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; i++)
	{
		//Wood
		if (angrybirds_sprites.wood_rectangle_long[i].hasSpawned())
			angrybirds_sprites.wood_rectangle_long[i].spriteComponent()->getSprite();
		if (angrybirds_sprites.wood_rectangle_tall[i].hasSpawned())
			angrybirds_sprites.wood_rectangle_tall[i].spriteComponent()->getSprite();
		if (angrybirds_sprites.wood_square[i].hasSpawned())
			angrybirds_sprites.wood_square[i].spriteComponent()->getSprite();

		//Ice
		if (angrybirds_sprites.ice_rectangle_long[i].hasSpawned())
			angrybirds_sprites.ice_rectangle_long[i].spriteComponent()->getSprite();
		if (angrybirds_sprites.ice_rectangle_tall[i].hasSpawned())
			angrybirds_sprites.ice_rectangle_tall[i].spriteComponent()->getSprite();
		if (angrybirds_sprites.ice_square[i].hasSpawned())
			angrybirds_sprites.ice_square[i].spriteComponent()->getSprite();

		//Rock
		if (angrybirds_sprites.rock_rectangle_long[i].hasSpawned())
			angrybirds_sprites.rock_rectangle_long[i].spriteComponent()->getSprite();
		if (angrybirds_sprites.rock_rectangle_tall[i].hasSpawned())
			angrybirds_sprites.rock_rectangle_tall[i].spriteComponent()->getSprite();
		if (angrybirds_sprites.rock_square[i].hasSpawned())
			angrybirds_sprites.rock_square[i].spriteComponent()->getSprite();
	}

	//Active player controlled bird
	if (angrybirds_sprites.active_bird.hasSpawned()) 
	{
		renderer->renderSprite(*angrybirds_sprites.active_bird.spriteComponent()->getSprite());
	}

	//Slingshot foreground
	renderer->renderSprite(*angrybirds_sprites.slingshot[1].spriteComponent()->getSprite());

	//Inactive birds (only render number of lives - 1)
	for (int i = 0; i < angrybirds_gamestate.lives - 1; i++)
	{
		renderer->renderSprite(*angrybirds_sprites.waiting_birds[i].spriteComponent()->getSprite());
	}
}

/*
HAS_WON, HAS_LOST
*/
void AngryRender::gstateGameOver(const ASGE::GameTime & us, ASGE::Renderer* renderer) 
{
	if (angrybirds_gamestate.win_state == AngryGamestate::HAS_LOST) 
	{
		renderer->renderText("YOU LOST", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2), 1, ASGE::COLOURS::WHITE);
	}
	if (angrybirds_gamestate.win_state == AngryGamestate::HAS_WON)
	{
		renderer->renderText("YOU WON", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2), 1, ASGE::COLOURS::WHITE);
	}
}