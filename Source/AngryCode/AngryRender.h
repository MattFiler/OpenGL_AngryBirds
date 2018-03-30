#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"

#include "../AngryEnums/AngryMenuScreens.h"
#include "../AngryEnums/AngryGameVars.h"
#include "../AngryEnums/AngryBackgrounds.h"

class AngryRender {
	public:
		AngryRender();
		~AngryRender();

		//Render Handlers
		void gstateInMenu(const ASGE::GameTime & us, ASGE::Renderer* renderer);
		void gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer);
		void gstateGameOver(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	private:
		/* AngryStructs */
		GamestateData gamestate;
		Sprites sprites;
};