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
	//Menu background
	renderer->renderSprite(*angrybirds_sprites.menu_layer.spriteComponent()->getSprite());

	//Press enter text
	renderer->renderText("PRESS ENTER TO BEGIN", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2) + ((int)AngryGameVars::GAME_HEIGHT / 2.7), 1, ASGE::COLOURS::WHITE);
}

/*
GAMESTATE_IS_PLAYING
*/
void AngryRender::gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer) 
{
	//In-game background
	renderer->renderSprite(*angrybirds_sprites.background_layer.spriteComponent()->getSprite());

	//Slingshot background
	renderer->renderSprite(*angrybirds_sprites.slingshot[1].spriteComponent()->getSprite());

	//Active player controlled bird
	if (angrybirds_sprites.active_bird.hasSpawned()) 
	{
		renderer->renderSprite(*angrybirds_sprites.active_bird.spriteComponent()->getSprite());
	}

	//Slingshot foreground
	renderer->renderSprite(*angrybirds_sprites.slingshot[0].spriteComponent()->getSprite());

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
	if (angrybirds_gamestate.current_gamestate == AngryGamestate::HAS_LOST) 
	{
		renderer->renderText("YOU LOST", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2), 1, ASGE::COLOURS::WHITE);
	}
	if (angrybirds_gamestate.current_gamestate == AngryGamestate::HAS_WON)
	{
		renderer->renderText("YOU WON", ((int)AngryGameVars::GAME_WIDTH / 2) - 180, ((int)AngryGameVars::GAME_HEIGHT / 2), 1, ASGE::COLOURS::WHITE);
	}
}