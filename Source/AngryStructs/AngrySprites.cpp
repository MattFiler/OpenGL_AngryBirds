#include "../AngryStructs/AngrySprites.h"

//All GameObjects
GameObject AngrySprites::backgrounds[(int)AngryBackgrounds::NUMBER_OF_BACKGROUNDS];
GameObject AngrySprites::flight_marker[(int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS];
GameObject AngrySprites::cursor[2];
GameObject AngrySprites::active_bird;
GameObject AngrySprites::waiting_birds[(int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1];
GameObject AngrySprites::slingshot[2];