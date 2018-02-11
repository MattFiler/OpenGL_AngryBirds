#include <Engine\Renderer.h>
#include "GameObject.h"

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

