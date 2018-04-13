#include "AngryLevels.h"

int LevelSetups::count = 2; //This is used throughout the game to define the max number of levels

/* Generate levels. */
void LevelSetups::GenerateLevel(int level) {
	switch (level) {
		case 1: {
			/* LEVEL ONE */
			placeBlock(sprites.wood_rectangle_long[0], 500, 500, 0, DestructionStates::DEFAULT);
			placeBlock(sprites.wood_square[0], 200, 200, 90, DestructionStates::DEFAULT);
			placeBlock(sprites.rock_rectangle_long[0], 400, 400, 90, DestructionStates::DEFAULT);
			placeBlock(sprites.rock_rectangle_tall[0], 800, 800, 0, DestructionStates::DEFAULT);
			placeBlock(sprites.ice_rectangle_long[0], 300, 800, 0, DestructionStates::DEFAULT);
			placePig(sprites.pigs[0], 700, 700);
		}
		case 2: {
			/* LEVEL TWO */
			placeBlock(sprites.ice_square[0], 800, 300, 0, DestructionStates::DEFAULT);
			placeBlock(sprites.ice_rectangle_long[0], 300, 800, 0, DestructionStates::DEFAULT);
			placePig(sprites.pigs[0], 700, 700);
		}
	}
}

/* Reset all objects in the level. */
void LevelSetups::ResetLevel() 
{
	for (int i = 0; i < (int)GameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; i++)
	{
		/* Wood Blocks */
		sprites.wood_rectangle_long[i].despawn();
		sprites.wood_rectangle_tall[i].despawn();
		sprites.wood_square[i].despawn();

		/* Ice Blocks */
		sprites.ice_rectangle_long[i].despawn();
		sprites.ice_rectangle_tall[i].despawn();
		sprites.ice_square[i].despawn();

		/* Rock Blocks */
		sprites.rock_rectangle_long[i].despawn();
		sprites.rock_rectangle_tall[i].despawn();
		sprites.rock_square[i].despawn();
	}

	for (int i = 0; i < (int)GameVars::MAX_NUMBER_OF_PIGS; i++)
	{
		/* Pigs */
		sprites.pigs[i].despawn();
	}
}

/* Return the number of levels in the game. */
int LevelSetups::getLevelCount()
{
	return count;
}

/* Place objects in the level. */
void LevelSetups::placeBlock(EnvironmentBlock& item, float x_pos, float y_pos, int rotation, DestructionStates destruction)
{
	item.setX(x_pos);
	item.setY(y_pos);
	item.setRotation(rotation);
	item.setDestruction(destruction);
	item.spawn();
}
void LevelSetups::placePig(Character& item, float x_pos, float y_pos)
{
	item.setX(x_pos);
	item.setY(y_pos);
	item.setInjuryLevel(CharacterInjuries::FEELIN_FINE);
	item.spawn();
}