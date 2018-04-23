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

/* Set Opacity */
void UI::setOpacity(float opacity)
{
	sprite_component->getSprite()->opacity(opacity);
}

/* Return Opacity */
float UI::getOpacity()
{
	return sprite_component->getSprite()->opacity();
}


/*
	-- SPAWNING --
*/

/* Despawn UI Element */
void UI::despawn()
{
	has_spawned = false;
	setOpacity(1);
}

/* Spawn UI Element */
void UI::spawn()
{
	has_spawned = true;
	setOpacity(1);
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
	setOpacity(getOpacity() - (frame_time / 2));

	//If opacity is 0, we've finished
	if (getOpacity() <= 0)
	{
		return true;
	}
	return false;
}

/* Fade In Up */
bool UI::animateFadeInUp(float frame_time)
{
	//This function should be called when the element hasn't spawned (basically a spawn() replacement)
	if (!has_spawned)
	{
		setOpacity(0);
		has_spawned = true;
	}

	if (getOpacity() >= 1)
	{
		//If opacity is 1, we've finished
		return true;
	}
	else
	{
		//Move up, raise opacity
		subtractFromY(frame_time * 10);
		setOpacity(getOpacity() + frame_time);
		return false;
	}
}