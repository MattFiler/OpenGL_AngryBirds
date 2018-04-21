#pragma once
#include <string>
#include <irrklang.h>
#include "SpriteComponent.h"
#include "Vector2.h"

#include "AngryEnums\AngryCharacterStates.h"
#include "AngryEnums\AngryCharacterInjury.h"

class Character
{
public:
	Character();
	~Character();

	bool  addSpriteComponent(ASGE::Renderer* renderer, const std::string& texture_file_name, int sprite_index);

	void addToX(float addX);
	void addToY(float addY);

	void subtractFromX(float minusX);
	void subtractFromY(float minusY);

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);

	float getHeight();
	float getWidth();

	void despawn();
	void spawn();
	bool hasSpawned();

	int getFrameCount();
	void setFrameCount(int count);

	int getCurrentFrame();
	void setCurrentFrame(int frame, float game_time);

	float getLastFrameUpdateTime();

	CharacterInjuries getInjuryLevel();
	void setInjuryLevel(CharacterInjuries injuryLevel);

	CharacterStates getState();
	void setState(CharacterStates newBirdState);

	SpriteComponent* spriteComponent();

private:
	irrklang::ISoundEngine* sound_engine;

	bool has_spawned = false;

	int sprite_frames = 6; //By default, we have 6 frames - but this can vary by character.
	int current_frame = 0; //The current animation frame.
	float last_update_time = 0; //The last time a frame updated.

	void freeSpriteComponent(int sprite_index);
	SpriteComponent* sprite_component[10]; //All frames are null, and assigned on game load. Only assigned frames will be called.

	CharacterInjuries character_injuries;
	CharacterStates character_state;
};