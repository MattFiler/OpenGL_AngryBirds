#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "Rect.h"

#include "AngrySpriteClasses/Character.h"
#include "AngrySpriteClasses/EnvironmentBlock.h"
#include "AngrySpriteClasses/UI.h"

#include "AngryCode/AngryRender.h"
#include "AngryCode/AngryUpdate.h"
#include "AngryCode/AngryInput.h"

#include "AngryStructs/AngryGamestateData.h"
#include "AngryStructs/AngryFonts.h"

#include "AngryEnums/AngryGameVars.h"

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

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */
	int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

	bool in_menu = true;

	enum cursor_types { STANDARD, INTERACTION };
	int cursor_type = STANDARD;

	/* AngryCode */
	AngryUpdate game_update;
	AngryRender game_render;
	AngryInput game_input;
	
	/* AngryStructs */
	GamestateData gamestate;
	MouseData mousedata;
	Sprites sprites;
};