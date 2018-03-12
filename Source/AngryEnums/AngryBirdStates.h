#pragma once

/*
	Define all bird states.
*/
enum class AngryBirdStates : int
{
	SHOULD_SPAWN, //Bird should be spawned
	SPAWNED, //Bird has spawned with no active job
	IN_LINEUP, //Bird is idle in lineup
	IN_CANNON, //Bird is idle in cannon
	ABOUT_TO_BE_FIRED, //Bird is about to be fired (player has control over its position)
	HAS_BEEN_FIRED, //Bird has just been fired from cannon (player has released mouse button)
	IS_IN_AIR, //Bird is currently in the air
	HAS_HIT, //Bird has hit an object
	SHOULD_DESPAWN, //Bird is offscreen and should despawn
	DESPAWNED //Bird is not being rendered
};