#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "GameObject.h"
#include "Rect.h"

#include "AngryCode/AngryRender.h"
#include "AngryCode/AngryUpdate.h"
#include "AngryCode/AngryInput.h"

#include "AngryStructs/AngryGamestateData.h"

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
	

private:
	void keyHandler(const ASGE::SharedEventData data);
	void clickHandler(const ASGE::SharedEventData data);
	void setupResolution();
	bool loadBackgrounds();

	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */
	int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

	bool in_menu = true;

	AngryUpdate angrybirds_update;
	AngryRender angrybirds_render;
	AngryInput angrybirds_input;
	
	AngryGamestateData angrybirds_gamestate;
	AngrySprites angrybirds_sprites;
};