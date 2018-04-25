#pragma once
#include <string>
#include <irrklang.h>
#include "SpriteComponent.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void despawn();
	void spawn();
	bool hasSpawned();

protected:
	irrklang::ISoundEngine* sound_engine;

private:
	bool has_spawned = false;
};