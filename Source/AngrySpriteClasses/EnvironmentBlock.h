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

	void setScale(float scale);
	float getScale();

	void despawn();
	void spawn();
	bool hasSpawned();

	DestructionStates getDestruction();
	void setDestruction(DestructionStates state);
	bool doDamage();

	BlockTypes getBlockType();
	void setBlockType(BlockTypes blocktype);

	SpriteComponent* spriteComponent();

private:
	irrklang::ISoundEngine* sound_engine;

	bool has_spawned = false;
	DestructionStates destruction_state = DestructionStates::DEFAULT;
	BlockTypes block_type;

	void freeSpriteComponent(int state);
	SpriteComponent* sprite[(int)DestructionStates::DESTRUCTION_COUNT];
};