#pragma once
#include <string>
#include <irrklang.h>
#include "SpriteComponent.h"
#include "Vector2.h"

#include "../AngryEnums/AngryDestructionStates.h"
#include "../AngryEnums/AngryBlockTypes.h"

class EnvironmentBlock
{
public:
	EnvironmentBlock();
	~EnvironmentBlock();

	bool addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name, int state);

	void addToX(float addX);
	void addToY(float addY);

	void subtractFromX(float minusX);
	void subtractFromY(float minusY);

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);

	void setRotation(float degrees);

	float getHeight();
	float getWidth();

	void despawn();
	void spawn();
	bool hasSpawned();

	AngryDestructionStates getDestruction();
	void setDestruction(AngryDestructionStates state);
	bool doDamage();

	AngryBlockTypes getBlockType();
	void setBlockType(AngryBlockTypes blocktype);

	SpriteComponent* spriteComponent();

private:
	irrklang::ISoundEngine* sound_engine;

	bool has_spawned = false;
	AngryDestructionStates destruction_state = AngryDestructionStates::DEFAULT;
	AngryBlockTypes block_type;

	void freeSpriteComponent(int state);
	SpriteComponent* sprite[(int)AngryDestructionStates::DESTRUCTION_COUNT];
};