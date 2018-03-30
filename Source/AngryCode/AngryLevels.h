#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngrySprites.h"

class AngryLevels {
public:
	void GenerateLevel(int level);
	static int count;

private:
	Sprites sprites;
	void placeItem(EnvironmentBlock& item, float x_pos, float y_pos, int rotation, DestructionStates destruction);
};