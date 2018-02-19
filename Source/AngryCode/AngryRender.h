#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "../AngryStructs/AngryGamestateData.h"

class AngryRender {
	public:
		AngryRender();
		~AngryRender();

		//Render Handlers
		void gstateInMenu(const ASGE::GameTime & us, ASGE::Renderer* renderer);
		void gstatePlaying(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	private:
		AngryGamestateData angrybirds_gamestate;
};