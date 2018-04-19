#pragma once
#include <string>
#include <fstream>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngrySprites.h"

#include "../AngryEnums/AngryGameVars.h"

class LevelSetups {
public:
	void loadLevels();
	std::string getLevelName(int level);

	void GenerateLevel(int level);
	void ResetLevel();

private:
	Sprites sprites;

	std::string level_build[(int)GameVars::LEVELS][(int)GameVars::MAX_LEVEL_COMPONENTS][4];
	int entity_count[((int)GameVars::BLOCK_VARIATIONS * 3) + 1]; //3 = Rock, Ice, Wood, +1 = Pig

	void placeComponent(std::string requested_sprite, std::string x_position, std::string y_position, std::string rotation);
	EnvironmentBlock& getSpriteForBlock(std::string requested_sprite);
	Character& getSpriteForCharacter(std::string requested_sprite);

	void placeBlock(EnvironmentBlock& item, float x_pos, float y_pos, float rotation, DestructionStates destruction);
	void placePig(Character& item, float x_pos, float y_pos);
};