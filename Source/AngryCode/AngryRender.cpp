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
	renderer->renderSprite(*angrybirds_sprites.background_layer.spriteComponent()->getSprite());
	renderer->renderSprite(*angrybirds_sprites.devtest.spriteComponent()->getSprite());

	renderer->renderText(".", (int)AngryGameVars::SLINGSHOT_X_ORIGIN, (int)AngryGameVars::SLINGSHOT_Y_ORIGIN, ASGE::COLOURS::BLACK);
}