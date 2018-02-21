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
	HAS_BEEN_FIRED,
	IS_IN_AIR,
	HAS_HIT,
	SHOULD_DESPAWN
};