#include <Engine\Renderer.h>
#include "EnvironmentBlock.h"


/*
	-- DESTRUCTION --
*/

/* Get/Set Destruction State */
DestructionStates EnvironmentBlock::getDestruction()
{
	return destruction_state;
}
void EnvironmentBlock::setDestruction(DestructionStates state)
{
	destruction_state = state;
	setCurrentFrame((int)destruction_state);
}

/* Deal Damage To Block */
bool EnvironmentBlock::doDamage()
{
	DestructionStates new_destruction_state = (DestructionStates)((int)destruction_state + 1);

	if ((int)new_destruction_state > (int)DestructionStates::DESTRUCTION_COUNT - 1) {
		switch (block_type) {
			case BlockTypes::ICE: {
				sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ICE\\SFX\\1.mp3", false);
				break;
			}
			case BlockTypes::ROCK: {
				sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\SFX\\1.mp3", false);
				break;
			}
			case BlockTypes::WOOD: {
				sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\SFX\\1.mp3", false);
				break;
			}
		}
		despawn(); //Block is destroyed
		return false;
	}
	else
	{
		switch (block_type) {
			case BlockTypes::ICE: {
				sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ICE\\SFX\\0.mp3", false);
				break;
			}
			case BlockTypes::ROCK: {
				sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\SFX\\0.mp3", false);
				break;
			}
			case BlockTypes::WOOD: {
				sound_engine->play2D("Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\SFX\\0.mp3", false);
				break;
			}
		}
		setDestruction(new_destruction_state);//Deal damage
		return true;
	}
}


/*
	-- BLOCK TYPE --
*/

/* Get/Set Block Type */
BlockTypes EnvironmentBlock::getBlockType()
{
	return block_type;
}
void EnvironmentBlock::setBlockType(BlockTypes blocktype)
{
	block_type = blocktype;
}