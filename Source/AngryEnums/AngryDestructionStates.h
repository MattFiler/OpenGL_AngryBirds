#pragma once

/*
Define all destruction states for blocks
*/
enum class DestructionStates : int
{
	DEFAULT,
	DAMAGE_LOW,
	DAMAGE_MEDIUM,
	DAMAGE_HIGH,

	DESTRUCTION_COUNT //This must always be last!
};