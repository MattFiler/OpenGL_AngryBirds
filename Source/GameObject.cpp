#include <Engine\Renderer.h>
#include "GameObject.h"

GameObject::GameObject() 
{
	/* APPLIES TO BIRDS ONLY */
	bird_state = AngryBirdStates::SHOULD_SPAWN;
}

GameObject::~GameObject()
{
	freeSpriteComponent();
}

bool GameObject::addSpriteComponent(
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

void  GameObject::freeSpriteComponent()
{
	delete sprite_component;
	sprite_component = nullptr;
}


SpriteComponent* GameObject::spriteComponent() 
{
	return sprite_component;
}

void GameObject::addToX(float addX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() + addX);
}
void GameObject::addToY(float addY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() + addY);
}

void GameObject::subtractFromX(float minusX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() - minusX);
}
void GameObject::subtractFromY(float minusY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() - minusY);
}

float GameObject::getX()
{
	return sprite_component->getSprite()->xPos();
}
float GameObject::getY()
{
	return sprite_component->getSprite()->yPos();
}

void GameObject::setX(float x)
{
	sprite_component->getSprite()->xPos(x);
}
void GameObject::setY(float y)
{
	sprite_component->getSprite()->yPos(y);
}

void GameObject::despawn()
{
	isSpawned = false;
}
void GameObject::spawn()
{
	isSpawned = true;
}
bool GameObject::hasSpawned()
{
	return isSpawned;
}

/* APPLIES TO BIRDS ONLY */
AngryBirdStates GameObject::getBirdState()
{
	return bird_state;
}
void GameObject::setBirdState(AngryBirdStates newBirdState)
{
	bird_state = newBirdState;
}