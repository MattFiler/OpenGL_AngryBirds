#pragma once

/*
	Define all bird states.
*/
enum class AngryBirdStates : int
{
	SHOULD_SPAWN,
	SPAWNED,
	IN_LINEUP,
	IN_CANNON,
	ABOUT_TO_BE_FIRED,
	HAS_BEEN_FIRED,
	IS_IN_AIR,
	HAS_HIT,
	SHOULD_DESPAWN,
	DESPAWNED
};