#include <Engine\Renderer.h>
#include "UI.h"

UI::UI()
{

}
UI::~UI()
{
	freeSpriteComponent();
}

bool UI::addSpriteComponent(
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

void  UI::freeSpriteComponent()
{
	delete sprite_component;
	sprite_component = nullptr;
}


SpriteComponent* UI::spriteComponent()
{
	return sprite_component;
}

void UI::addToX(float addX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() + addX);
}
void UI::addToY(float addY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() + addY);
}

void UI::subtractFromX(float minusX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() - minusX);
}
void UI::subtractFromY(float minusY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() - minusY);
}

float UI::getX()
{
	return sprite_component->getSprite()->xPos();
}
float UI::getY()
{
	return sprite_component->getSprite()->yPos();
}

void UI::setX(float x)
{
	sprite_component->getSprite()->xPos(x);
}
void UI::setY(float y)
{
	sprite_component->getSprite()->yPos(y);
}

float UI::getHeight()
{
	return sprite_component->getSprite()->height();
}
float UI::getWidth()
{
	return sprite_component->getSprite()->width();
}

void UI::despawn()
{
	has_spawned = false;
}
void UI::spawn()
{
	has_spawned = true;
}
bool UI::hasSpawned()
{
	return has_spawned;
}