#include "AngryRender.h"

AngryRender::AngryRender() {

}
AngryRender::~AngryRender() {

}


/*
GAMESTATE_IN_MENU
*/
void AngryRender::gstateInMenu(const ASGE::GameTime & us, ASGE::Renderer* renderer) {
	renderer->renderSprite(*angrybirds_sprites.menu_layer.spriteComponent()->getSprite());
}

/*
GAMESTATE_IS_PLAYING
*/
void AngryRender::gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer) {
	//Render background
	renderer->renderSprite(*angrybirds_sprites.background_layer.spriteComponent()->getSprite());

	//Render birds
	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_BIRDS; i++) 
	{
		if (angrybirds_sprites.birds[i].hasSpawned()) //Only render if spawned in world
		{
			renderer->renderSprite(*angrybirds_sprites.birds[i].spriteComponent()->getSprite());
		}
	}

	//Render pigs
	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_PIGS; i++)
	{
		if (angrybirds_sprites.pigs[i].hasSpawned()) //Only render if spawned in world
		{
			renderer->renderSprite(*angrybirds_sprites.pigs[i].spriteComponent()->getSprite());
		}
	}

	//Render slingshot (placeholder for now)
	renderer->renderText(".", (int)AngryGameVars::SLINGSHOT_X_ORIGIN, (int)AngryGameVars::SLINGSHOT_Y_ORIGIN, ASGE::COLOURS::BLACK);
}