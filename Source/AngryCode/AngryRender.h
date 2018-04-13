#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"
#include "../AngryStructs/AngrySprites.h"

#include "../AngryEnums/AngryMenuScreens.h"
#include "../AngryEnums/AngryGameVars.h"
#include "../AngryEnums/AngryBackgrounds.h"

#include "../AngryCode/AngryLevels.h"

class RenderStates {
	public:
		RenderStates();
		~RenderStates();

		//Render Handlers
		void gstateInMenu(const ASGE::GameTime & us, ASGE::Renderer* renderer);
		void gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer);
		void gstateGameOver(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	private:
		/* AngryStructs */
		GamestateData gamestate;
		Sprites sprites;

		//Level data
		LevelSetups levels;
};