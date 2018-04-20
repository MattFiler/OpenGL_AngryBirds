#include <Engine\Renderer.h>
#include "EnvironmentBlock.h"

EnvironmentBlock::EnvironmentBlock()
{
	//Assign nullptr to every destruction state on initialisation
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i] = nullptr;
	}

	//Initialise the sound engine
	sound_engine = irrklang::createIrrKlangDevice();
}
EnvironmentBlock::~EnvironmentBlock()
{
	//De-assign the sprite from every destruction state on destruction
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		freeSpriteComponent(i);
	}

	//Destruct the sound engine
	sound_engine->drop();
}


/*
	-- SPRITES --
*/

/* Add Sprite To Each Destruction State */
bool EnvironmentBlock::addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name, int state)
{
	//State is passed here as an integer which is representative of the enum index in AngryDestructionState.h

	freeSpriteComponent(state);

	sprite[state] = new SpriteComponent();
	if (sprite[state]->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent(state);
	return false;
}

/* Deallocate Memory For Sprite In Each State */
void  EnvironmentBlock::freeSpriteComponent(int state)
{
	delete sprite[state];
	sprite[state] = nullptr;
}

/* Return Sprite For Current Destruction State */
SpriteComponent* EnvironmentBlock::spriteComponent()
{
	return sprite[(int)destruction_state];
}


/*
	-- POSITIONING --
*/

/* Set X/Y To Pre-Defined Value */
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

/* Add To Existing X/Y Value */
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

/* Subtract From Existing X/Y Value */
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

/* Return X/Y Value */
float EnvironmentBlock::getX()
{
	return sprite[(int)destruction_state]->getSprite()->xPos();
}
float EnvironmentBlock::getY()
{
	return sprite[(int)destruction_state]->getSprite()->yPos();
}

/* Set Rotation Value (In Degrees) */
void EnvironmentBlock::setRotation(float degrees)
{
	for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
	{
		sprite[i]->getSprite()->rotationInRadians(degrees * (3.14159 / 180));
	}
}

/* Return Sprite Height/Width Respectively */
float EnvironmentBlock::getHeight()
{
	return sprite[(int)destruction_state]->getSprite()->height();
}
float EnvironmentBlock::getWidth()
{
	return sprite[(int)destruction_state]->getSprite()->width();
}

/* Set Scale */
void EnvironmentBlock::setScale(float scale)
{
	sprite[(int)destruction_state]->getSprite()->scale(scale);
}

/* Return Scale */
float EnvironmentBlock::getScale()
{
	return sprite[(int)destruction_state]->getSprite()->scale();
}


/*
	-- SPAWNING --
*/

/* Despawn Entity */
void EnvironmentBlock::despawn()
{
	has_spawned = false;
}

/* Spawn Entity */
void EnvironmentBlock::spawn()
{
	has_spawned = true;
}

/* Return If Entity Has Spawned */
bool EnvironmentBlock::hasSpawned()
{
	return has_spawned;
}


/*
	-- DESTRUCTION --
*/

/* Get/Set Destruction State */
DestructionStates EnvironmentBlock::getDestruction()
{
	return destruction_state;
}
void EnvironmentBlock::setDestruction(DestructionStates state)
{
	destruction_state = state;
}

/* Deal Damage To Block */
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


/*
	-- BLOCK TYPE --
*/

/* Get/Set Block Type */
BlockTypes EnvironmentBlock::getBlockType()
{
	return block_type;
}
void EnvironmentBlock::setBlockType(BlockTypes blocktype)
{
	block_type = blocktype;
}