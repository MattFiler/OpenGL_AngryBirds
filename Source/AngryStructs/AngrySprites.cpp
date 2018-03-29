#include "../AngryStructs/AngrySprites.h"

//All GameObjects
GameObject AngrySprites::background_layer;
GameObject AngrySprites::menu_layer;
GameObject AngrySprites::active_bird;
GameObject AngrySprites::waiting_birds[(int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1];
GameObject AngrySprites::slingshot[2];