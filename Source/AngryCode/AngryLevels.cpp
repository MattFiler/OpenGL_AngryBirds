#include "AngryLevels.h"

int LevelSetups::count = 2; //This is used throughout the game to define the max number of levels

void LevelSetups::GenerateLevel(int level) {
	switch (level) {
		case 1: {
			/* LEVEL ONE */
			placeItem(sprites.wood_rectangle_long[0], 500, 500, 0, DestructionStates::DEFAULT);
			placeItem(sprites.wood_square[0], 200, 200, 90, DestructionStates::DEFAULT);
			placeItem(sprites.rock_rectangle_long[0], 400, 400, 90, DestructionStates::DEFAULT);
			placeItem(sprites.rock_rectangle_tall[0], 800, 800, 0, DestructionStates::DEFAULT);
			placeItem(sprites.ice_rectangle_long[0], 300, 800, 0, DestructionStates::DEFAULT);
		}
		case 2: {
			/* LEVEL TWO */
			placeItem(sprites.ice_square[0], 800, 300, 0, DestructionStates::DEFAULT);
			placeItem(sprites.ice_rectangle_long[0], 300, 800, 0, DestructionStates::DEFAULT);
		}
	}
}

void LevelSetups::placeItem(EnvironmentBlock& item, float x_pos, float y_pos, int rotation, DestructionStates destruction)
{
	item.setX(x_pos);
	item.setY(y_pos);
	item.setRotation(rotation);
	item.setDestruction(destruction);
	item.spawn();
}