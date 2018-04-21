#include <Engine\Renderer.h>
#include "Character.h"

Character::Character()
{
	//Assign nullptr to every pre-allocated frame
	for (int i = 0; i < 10; i++)
	{
		sprite_component[i] = nullptr;
	}

	//Character defaults
	character_state = CharacterStates::SHOULD_SPAWN;
	character_injuries = CharacterInjuries::FEELIN_FINE;

	//Initialise the sound engine
	sound_engine = irrklang::createIrrKlangDevice();
}
Character::~Character()
{
	//Deallocate sprites from every frame
	for (int i = 0; i < 10; i++) 
	{
		freeSpriteComponent(i);
	}

	//Destruct the sound engine
	sound_engine->drop();
}


/*
	-- SPRITES --
*/

/* Add Sprite To Frame */
bool Character::addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name, int sprite_index)
{
	freeSpriteComponent(sprite_index);

	sprite_component[sprite_index] = new SpriteComponent();
	if (sprite_component[sprite_index]->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent(sprite_index);
	return false;
}

/* Deallocate Memory For Sprite In Frame */
void Character::freeSpriteComponent(int sprite_index)
{
	delete sprite_component[sprite_index];
	sprite_component[sprite_index] = nullptr;
}

/* Return Sprite For Current Frame */
SpriteComponent* Character::spriteComponent()
{
	return sprite_component[current_frame];
}


/*
	-- POSITIONING --
*/

/* Set X/Y To Pre-Defined Value */
void Character::setX(float x)
{
	for (int i = 0; i < sprite_frames; i++)
	{
		sprite_component[i]->getSprite()->xPos(x);
	}
}
void Character::setY(float y)
{
	for (int i = 0; i < sprite_frames; i++)
	{
		sprite_component[i]->getSprite()->yPos(y);
	}
}

/* Add To Existing X/Y Value */
void Character::addToX(float addX)
{
	for (int i = 0; i < sprite_frames; i++)
	{
		sprite_component[i]->getSprite()->xPos(sprite_component[i]->getSprite()->xPos() + addX);
	}
}
void Character::addToY(float addY)
{
	for (int i = 0; i < sprite_frames; i++)
	{
		sprite_component[i]->getSprite()->yPos(sprite_component[i]->getSprite()->yPos() + addY);
	}
}

/* Subtract From Existing X/Y Value */
void Character::subtractFromX(float minusX)
{
	for (int i = 0; i < sprite_frames; i++)
	{
		sprite_component[i]->getSprite()->xPos(sprite_component[i]->getSprite()->xPos() - minusX);
	}
}
void Character::subtractFromY(float minusY)
{
	for (int i = 0; i < sprite_frames; i++)
	{
		sprite_component[i]->getSprite()->yPos(sprite_component[i]->getSprite()->yPos() - minusY);
	}
}

/* Return X/Y Value */
float Character::getX()
{
	return sprite_component[current_frame]->getSprite()->xPos();
}
float Character::getY()
{
	return sprite_component[current_frame]->getSprite()->yPos();
}

/* Return Sprite Height/Width Respectively */
float Character::getHeight()
{
	return sprite_component[current_frame]->getSprite()->height();
}
float Character::getWidth()
{
	return sprite_component[current_frame]->getSprite()->width();
}


/*
	-- SPAWNING --
*/

/* Despawn Entity */
void Character::despawn()
{
	has_spawned = false;
}

/* Spawn Entity */
void Character::spawn()
{
	has_spawned = true;
}

/* Return If Entity Has Spawned */
bool Character::hasSpawned()
{
	return has_spawned;
}


/*
	-- ANIMATION --
*/

/* Get/Set Total Animation Frames */
int Character::getFrameCount()
{
	return sprite_frames;
}
void Character::setFrameCount(int count)
{
	sprite_frames = count;
}

/* Get/Set Current Animation Frame */
int Character::getCurrentFrame()
{
	return current_frame;
}
void Character::setCurrentFrame(int frame, float game_time)
{
	current_frame = frame;
	last_update_time = game_time;
}

/* Return Time of Last Frame Update */
float Character::getLastFrameUpdateTime() 
{
	return last_update_time;
}


/*
	-- STATES --
*/

/* Get/Set Injury State */
CharacterInjuries Character::getInjuryLevel()
{
	return character_injuries;
}
void Character::setInjuryLevel(CharacterInjuries injuryLevel)
{
	character_injuries = injuryLevel;

	if (character_injuries == CharacterInjuries::FEELIN_FINE)
	{
		setCurrentFrame(0, 0);
	}
	else if (character_injuries == CharacterInjuries::SLIGHTLY_INJURED)
	{
		setCurrentFrame(2, 0); 
		sound_engine->play2D("Resources\\CHARACTERS\\PIGS\\SFX\\2.mp3", false);
	}
	else if (character_injuries == CharacterInjuries::HIGHLY_INJURED)
	{
		setCurrentFrame(4, 0);
		sound_engine->play2D("Resources\\CHARACTERS\\PIGS\\SFX\\3.mp3", false);
	}
}

/* Get/Set Character Entity State */
CharacterStates Character::getState()
{
	return character_state;
}
void Character::setState(CharacterStates newState)
{
	character_state = newState;
}