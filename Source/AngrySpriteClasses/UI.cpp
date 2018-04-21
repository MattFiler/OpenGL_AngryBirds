#include <Engine\Renderer.h>
#include "UI.h"

UI::UI()
{

}
UI::~UI()
{
	//Deallocate sprite memory on destruction
	freeSpriteComponent();
}


/*
	-- SPRITE --
*/

/* Add Sprite To UI Element */
bool UI::addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name)
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

/* Deallocate Sprite From Element */
void UI::freeSpriteComponent()
{
	delete sprite_component;
	sprite_component = nullptr;
}

/* Return Element's Sprite */
SpriteComponent* UI::spriteComponent()
{
	return sprite_component;
}


/*
	-- POSITIONING --
*/

/* Set X/Y To Pre-Defined Value */
void UI::setX(float x)
{
	sprite_component->getSprite()->xPos(x);
}
void UI::setY(float y)
{
	sprite_component->getSprite()->yPos(y);
}

/* Add To Existing X/Y Value */
void UI::addToX(float addX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() + addX);
}
void UI::addToY(float addY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() + addY);
}

/* Subtract From Existing X/Y Value */
void UI::subtractFromX(float minusX)
{
	sprite_component->getSprite()->xPos(sprite_component->getSprite()->xPos() - minusX);
}
void UI::subtractFromY(float minusY)
{
	sprite_component->getSprite()->yPos(sprite_component->getSprite()->yPos() - minusY);
}

/* Return X/Y Value */
float UI::getX()
{
	return sprite_component->getSprite()->xPos();
}
float UI::getY()
{
	return sprite_component->getSprite()->yPos();
}

/* Return UI Element Height/Width Respectively */
float UI::getHeight()
{
	return sprite_component->getSprite()->height();
}
float UI::getWidth()
{
	return sprite_component->getSprite()->width();
}

/* Set Scale */
void UI::setScale(float scale)
{
	sprite_component->getSprite()->scale(scale);
}

/* Return Scale */
float UI::getScale()
{
	return sprite_component->getSprite()->scale();
}


/*
	-- SPAWNING --
*/

/* Despawn UI Element */
void UI::despawn()
{
	has_spawned = false;
	sprite_component->getSprite()->opacity(1);
}

/* Spawn UI Element */
void UI::spawn()
{
	has_spawned = true;
	sprite_component->getSprite()->opacity(1);
}

/* Return If UI Element Has Spawned */
bool UI::hasSpawned()
{
	return has_spawned;
}


/*
	-- ANIMATION --
*/

/* Fade Out Up */
bool UI::animateFadeOutUp(float frame_time)
{
	//Move up, lower opacity
	subtractFromY(frame_time * 10);
	sprite_component->getSprite()->opacity(sprite_component->getSprite()->opacity() - (frame_time/2));

	//If opacity is 0, we've finished
	if (sprite_component->getSprite()->opacity() <= 0)
	{
		return true;
	}
	return false;
}