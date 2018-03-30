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

void LevelSetups::ResetLevel() 
{
	for (int x = 0; x < (int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; x++)
	{
		/* Wood Blocks */
		sprites.wood_rectangle_long[x].despawn();
		sprites.wood_rectangle_tall[x].despawn();
		sprites.wood_square[x].despawn();

		/* Ice Blocks */
		sprites.ice_rectangle_long[x].despawn();
		sprites.ice_rectangle_tall[x].despawn();
		sprites.ice_square[x].despawn();

		/* Rock Blocks */
		sprites.rock_rectangle_long[x].despawn();
		sprites.rock_rectangle_tall[x].despawn();
		sprites.rock_square[x].despawn();
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