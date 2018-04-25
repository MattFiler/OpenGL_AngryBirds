#include <Engine\Renderer.h>
#include "FX.h"

FX::FX()
{
	//Assign nullptr to every frame on initialisation
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FRAMES_IN_FX; i++)
	{
		sprite[i] = nullptr;
	}
}
FX::~FX()
{
	//De-assign the sprite from every frame on destruction
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FRAMES_IN_FX; i++)
	{
		freeSpriteComponent(i);
	}
}


/*
	-- SPRITES --
*/

/* Add Sprite To Each Frame */
bool FX::addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name, int frame)
{
	freeSpriteComponent(frame);

	sprite[frame] = new SpriteComponent();
	if (sprite[frame]->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent(frame);
	return false;
}

/* Deallocate Memory For Sprite In Each State */
void  FX::freeSpriteComponent(int frame)
{
	delete sprite[frame];
	sprite[frame] = nullptr;
}

/* Return Sprite For Current Frame State */
SpriteComponent* FX::spriteComponent()
{
	return sprite[current_frame];
}


/*
	-- POSITIONING --
*/

/* Set X/Y To Pre-Defined Value */
void FX::setX(float x)
{
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FRAMES_IN_FX; i++)
	{
		sprite[i]->getSprite()->xPos(x);
	}
}
void FX::setY(float y)
{
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FRAMES_IN_FX; i++)
	{
		sprite[i]->getSprite()->yPos(y);
	}
}

/* Return X/Y Value */
float FX::getX()
{
	return sprite[current_frame]->getSprite()->xPos();
}
float FX::getY()
{
	return sprite[current_frame]->getSprite()->yPos();
}

/* Return Sprite Height/Width Respectively */
float FX::getHeight()
{
	return sprite[current_frame]->getSprite()->height();
}
float FX::getWidth()
{
	return sprite[current_frame]->getSprite()->width();
}

/* Set Scale */
void FX::setScale(float scale)
{
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FRAMES_IN_FX; i++)
	{
		sprite[i]->getSprite()->scale(scale);
	}
}

/* Return Scale */
float FX::getScale()
{
	return sprite[current_frame]->getSprite()->scale();
}


/*
	-- FRAME --
*/

/* Get/Set Current Frame */
void FX::setFrame(int frame)
{
	current_frame = frame;
}
int FX::getFrame()
{
	return current_frame;
}


/*
	-- ANIMATION --
*/

/* Animate FX */
bool FX::animate(float frame_time)
{
	//Keep track of the animation time
	runtime_count += frame_time;

	//Cycle frames
	if (runtime_count < 0.1) {
		current_frame = 0;
		return false;
	}
	else if (runtime_count > 0.1 && 
		runtime_count < 0.2)
	{
		current_frame = 1;
		return false;
	}
	else if (runtime_count > 0.2 &&
				runtime_count < 0.3)
	{
		current_frame = 2;
		return false;
	}
	else if (runtime_count > 0.3 &&
				runtime_count < 0.4)
	{
		current_frame = 3;
		return false;
	}

	//Animation finished
	return true;
}