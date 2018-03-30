#include <Engine\Renderer.h>
#include "EnvironmentBlock.h"

EnvironmentBlock::EnvironmentBlock()
{
	//As default, all destruction states are null - we want to allocate them
	for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i] = nullptr;
	}
}
EnvironmentBlock::~EnvironmentBlock()
{
	freeSpriteComponent();
}

//State is passed to here as an int - which is representative of the enum index for AngryDestructionState
bool EnvironmentBlock::addSpriteComponent(
	ASGE::Renderer* renderer, const std::string& texture_file_name, int state)
{
	freeSpriteComponent();

	sprite[state] = new SpriteComponent();
	if (sprite[state]->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent();
	return false;
}

void  EnvironmentBlock::freeSpriteComponent()
{
	for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
	{
		delete sprite[i];
		sprite[i] = nullptr;
	}
}


SpriteComponent* EnvironmentBlock::spriteComponent()
{
	return sprite[(int)destruction_state];
}

void EnvironmentBlock::addToX(float addX)
{
	sprite[(int)destruction_state]->getSprite()->xPos(sprite[(int)destruction_state]->getSprite()->xPos() + addX);
}
void EnvironmentBlock::addToY(float addY)
{
	sprite[(int)destruction_state]->getSprite()->yPos(sprite[(int)destruction_state]->getSprite()->yPos() + addY);
}

void EnvironmentBlock::subtractFromX(float minusX)
{
	sprite[(int)destruction_state]->getSprite()->xPos(sprite[(int)destruction_state]->getSprite()->xPos() - minusX);
}
void EnvironmentBlock::subtractFromY(float minusY)
{
	sprite[(int)destruction_state]->getSprite()->yPos(sprite[(int)destruction_state]->getSprite()->yPos() - minusY);
}

float EnvironmentBlock::getX()
{
	return sprite[(int)destruction_state]->getSprite()->xPos();
}
float EnvironmentBlock::getY()
{
	return sprite[(int)destruction_state]->getSprite()->yPos();
}

void EnvironmentBlock::setX(float x)
{
	sprite[(int)destruction_state]->getSprite()->xPos(x);
}
void EnvironmentBlock::setY(float y)
{
	sprite[(int)destruction_state]->getSprite()->yPos(y);
}

float EnvironmentBlock::getHeight()
{
	return sprite[(int)destruction_state]->getSprite()->height();
}
float EnvironmentBlock::getWidth()
{
	return sprite[(int)destruction_state]->getSprite()->width();
}

void EnvironmentBlock::despawn()
{
	has_spawned = false;
}
void EnvironmentBlock::spawn()
{
	has_spawned = true;
}
bool EnvironmentBlock::hasSpawned()
{
	return has_spawned;
}

AngryDestructionStates EnvironmentBlock::getDestruction()
{
	return destruction_state;
}
void EnvironmentBlock::setDestruction(AngryDestructionStates state)
{
	destruction_state = state;
}