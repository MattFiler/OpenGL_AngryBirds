#include <Engine\Renderer.h>
#include "Character.h"

Character::Character()
{
	character_state = AngryCharacterStates::SHOULD_SPAWN;
}
Character::~Character()
{
	freeSpriteComponent();
}

bool Character::addSpriteComponent(
	ASGE::Renderer* renderer, const std::string& texture_file_name)
{
	freeSpriteComponent();

	sprite_component = new SpriteComponent();
	if (sprite_component->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent();
	return false;
}

void  Character::freeSpriteComponent()
{
	delete sprite_component;
	sprite_component = nullptr;
}


SpriteComponent* Character::spriteComponent()
{
	return sprite_component;
}

void Character::addToX(float addX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() + addX);
}
void Character::addToY(float addY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() + addY);
}

void Character::subtractFromX(float minusX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() - minusX);
}
void Character::subtractFromY(float minusY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() - minusY);
}

float Character::getX()
{
	return sprite_component->getSprite()->xPos();
}
float Character::getY()
{
	return sprite_component->getSprite()->yPos();
}

void Character::setX(float x)
{
	sprite_component->getSprite()->xPos(x);
}
void Character::setY(float y)
{
	sprite_component->getSprite()->yPos(y);
}

float Character::getHeight()
{
	return sprite_component->getSprite()->height();
}
float Character::getWidth()
{
	return sprite_component->getSprite()->width();
}

void Character::despawn()
{
	has_spawned = false;
}
void Character::spawn()
{
	has_spawned = true;
}
bool Character::hasSpawned()
{
	return has_spawned;
}

AngryCharacterStates Character::getState()
{
	return character_state;
}
void Character::setState(AngryCharacterStates newState)
{
	character_state = newState;
}