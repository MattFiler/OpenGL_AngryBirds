#pragma once

/*
Define all pig states.
*/
enum class AngryPigStates : int
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