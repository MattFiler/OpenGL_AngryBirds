#pragma once
#include <string>
#include "SpriteComponent.h"
#include "Vector2.h"

#include "AngryEnums\AngryCharacterStates.h"

class Character
{
public:
	Character();
	~Character();

	bool  addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name);

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

	CharacterStates getState();
	void setState(CharacterStates newBirdState);

	SpriteComponent* spriteComponent();

private:
	bool has_spawned = false;

	void freeSpriteComponent();
	SpriteComponent* sprite_component = nullptr;

	CharacterStates character_state;
};