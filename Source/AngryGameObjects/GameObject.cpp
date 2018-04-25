#include <Engine\Renderer.h>
#include "GameObject.h"

GameObject::GameObject()
{
	//Initialise the sound engine
	sound_engine = irrklang::createIrrKlangDevice();
}
GameObject::~GameObject()
{
	//Destruct the sound engine
	sound_engine->drop();
}


/*
-- SPAWNING --
*/

/* Despawn Entity */
void GameObject::despawn()
{
	//TODO: SET OPACITY 1
	has_spawned = false;
}

/* Spawn Entity */
void GameObject::spawn()
{
	//TODO: SET OPACITY 1
	has_spawned = true;
}

/* Return If Entity Has Spawned */
bool GameObject::hasSpawned()
{
	return has_spawned;
}