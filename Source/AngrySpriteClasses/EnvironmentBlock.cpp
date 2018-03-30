#include <Engine\Renderer.h>
#include "EnvironmentBlock.h"

EnvironmentBlock::EnvironmentBlock()
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i] = nullptr;
	}

	sound_engine = irrklang::createIrrKlangDevice();
}
EnvironmentBlock::~EnvironmentBlock()
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		freeSpriteComponent(i);
	}

	sound_engine->drop();
}

//State is passed to here as an int - which is representative of the enum index for AngryDestructionState
bool EnvironmentBlock::addSpriteComponent(
	ASGE::Renderer* renderer, const std::string& texture_file_name, int state)
{
	freeSpriteComponent(state);

	sprite[state] = new SpriteComponent();
	if (sprite[state]->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent(state);
	return false;
}

void  EnvironmentBlock::freeSpriteComponent(int state)
{
	delete sprite[state];
	sprite[state] = nullptr;
}


SpriteComponent* EnvironmentBlock::spriteComponent()
{
	return sprite[(int)destruction_state];
}

void EnvironmentBlock::addToX(float addX)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->xPos(sprite[i]->getSprite()->xPos() + addX);
	}
}
void EnvironmentBlock::addToY(float addY)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->yPos(sprite[i]->getSprite()->xPos() + addY);
	}
}

void EnvironmentBlock::subtractFromX(float minusX)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->xPos(sprite[i]->getSprite()->xPos() - minusX);
	}
}
void EnvironmentBlock::subtractFromY(float minusY)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->yPos(sprite[i]->getSprite()->yPos() - minusY);
	}
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
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->xPos(x);
	}
}
void EnvironmentBlock::setY(float y)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->yPos(y);
	}
}

void EnvironmentBlock::setRotation(float degrees)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->rotationInRadians(degrees * (3.14159 / 180));
	}
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

DestructionStates EnvironmentBlock::getDestruction()
{
	return destruction_state;
}
void EnvironmentBlock::setDestruction(DestructionStates state)
{
	destruction_state = state;
}
bool EnvironmentBlock::doDamage()
{
	DestructionStates new_destruction_state = (DestructionStates)((int)destruction_state + 1);

	if ((int)new_destruction_state > (int)DestructionStates::DESTRUCTION_COUNT - 1) {
		switch (block_type) {
		case BlockTypes::ICE: {
			sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ICE\\SFX\\1.mp3", false);
			break;
		}
		case BlockTypes::ROCK: {
			sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\SFX\\1.mp3", false);
			break;
		}
		case BlockTypes::WOOD: {
			sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\SFX\\1.mp3", false);
			break;
		}
		}
		has_spawned = false; //Block is destroyed
		return false;
	}
	else
	{
		switch (block_type) {
		case BlockTypes::ICE: {
			sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ICE\\SFX\\0.mp3", false);
			break;
		}
		case BlockTypes::ROCK: {
			sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\SFX\\0.mp3", false);
			break;
		}
		case BlockTypes::WOOD: {
			sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\SFX\\0.mp3", false);
			break;
		}
		}
		destruction_state = new_destruction_state; //Deal damage
		return true;
	}
}

BlockTypes EnvironmentBlock::getBlockType()
{
	return block_type;
}
void EnvironmentBlock::setBlockType(BlockTypes blocktype)
{
	block_type = blocktype;
}