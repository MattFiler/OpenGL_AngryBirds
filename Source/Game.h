#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "Rect.h"

#include "AngryGameObjects/Character.h"
#include "AngryGameObjects/EnvironmentBlock.h"
#include "AngryGameObjects/UI.h"

#include "AngryCode/AngryRender.h"
#include "AngryCode/AngryUpdate.h"
#include "AngryCode/AngryInput.h"

#include "AngryStructs/AngryGamestateData.h"
#include "AngryStructs/AngryFonts.h"

#include "AngryEnums/AngryGameVars.h"
#include "AngryEnums/AngryCursors.h"
#include "AngryEnums/AngryMenuElements.h"

/**
*  An OpenGL Game based on ASGE.
*/
class AngryBirdsGame :
	public ASGE::OGLGame
{
public:
	AngryBirdsGame();
	~AngryBirdsGame();
	virtual bool init() override;

	bool assignTextures();

private:
	void keyHandler(const ASGE::SharedEventData data);
	void clickHandler(const ASGE::SharedEventData data);
	void setupResolution();

	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	//Input callbacks
	int key_callback_id = -1;
	int mouse_callback_id = -1;

	/* AngryCode */
	UpdateStates game_update;
	RenderStates game_render;
	InputStates game_input;
	
	/* AngryStructs */
	GamestateData gamestate;
	MouseData mousedata;
	Sprites sprites;
	FlightVars flightdata;
};