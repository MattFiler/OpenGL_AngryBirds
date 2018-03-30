#pragma once
#include <string>
#include "SpriteComponent.h"
#include "Vector2.h"

#include "../AngryEnums/AngryDestructionStates.h"

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

	float getHeight();
	float getWidth();

	void despawn();
	void spawn();
	bool hasSpawned();

	AngryDestructionStates getDestruction();
	void setDestruction(AngryDestructionStates state);

	SpriteComponent* spriteComponent();

private:
	bool has_spawned = false;
	AngryDestructionStates destruction_state = AngryDestructionStates::DEFAULT;

	void freeSpriteComponent();
	SpriteComponent* sprite[(int)AngryDestructionStates::DESTRUCTION_COUNT];
};