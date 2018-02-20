#include <Engine\Renderer.h>
#include "GameObject.h"

GameObject::GameObject() 
{
	/* APPLIES TO PIGS ONLY */
	pig_state = AngryPigStates::SHOULD_SPAWN;
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

/* APPLIES TO PIGS ONLY */
AngryPigStates GameObject::getPigState()
{
	return pig_state;
}
void GameObject::setPigState(AngryPigStates pigState)
{
	pig_state = pigState;
}