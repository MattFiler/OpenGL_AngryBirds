#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngrySprites.h"

#include "../AngryEnums/AngryGameVars.h"

class LevelSetups {
public:
	void GenerateLevel(int level);
	void ResetLevel();

	int getLevelCount();

private:
	Sprites sprites;

	void placeBlock(EnvironmentBlock& item, float x_pos, float y_pos, int rotation, DestructionStates destruction);
	void placePig(Character& item, float x_pos, float y_pos);

	static int count;
};