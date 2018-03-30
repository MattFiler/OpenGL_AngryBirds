#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Game.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
             and even seeding the random number generator.
*/
AngryBirdsGame::AngryBirdsGame()
{
	std::srand(time(NULL));
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
AngryBirdsGame::~AngryBirdsGame()
{
	this->inputs->unregisterCallback(key_callback_id);
	this->inputs->unregisterCallback(mouse_callback_id);
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The keyHandler and clickHandler
			 callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool AngryBirdsGame::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}

	//toggleFPS();
	renderer->setWindowTitle("Angry Birds!");
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);
	
	mouse_callback_id =inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);
	
	//Load textures
	bool failed_loading;
	bool load_response = assignTextures(failed_loading);
	if (failed_loading) return load_response;

	//Load font
	AngryFonts::fonts[0] = new AngryFonts(renderer->loadFont("Resources\\UI\\FONTS\\0.ttf", 45), "default", 45);

	return true;
}

/* Assign textures to sprites */
bool AngryBirdsGame::assignTextures(bool &retflag)
{
	retflag = true;
	/* Menu Background */
	for (int i = 0; i < (int)AngryBackgrounds::NUMBER_OF_BACKGROUNDS; i++) {
		if (!angrybirds_sprites.backgrounds[i].addSpriteComponent(renderer.get(), "Resources\\UI\\BACKGROUNDS\\" + std::to_string(i) + ".jpg"))
		{
			return false;
		}
	}

	/* Cursors */
	if (!angrybirds_sprites.cursor[0].addSpriteComponent(renderer.get(), "Resources\\UI\\CURSOR\\0.png"))
	{
		return false;
	}
	if (!angrybirds_sprites.cursor[1].addSpriteComponent(renderer.get(), "Resources\\UI\\CURSOR\\1.png"))
	{
		return false;
	}

	/* Active Bird */
	if (!angrybirds_sprites.active_bird.addSpriteComponent(renderer.get(), "Resources\\CHARACTERS\\BIRDS\\RED\\0.png"))
	{
		return false;
	}
	angrybirds_sprites.active_bird.spawn();
	angrybirds_sprites.active_bird.setState(AngryCharacterStates::IN_CANNON);

	/* Inactive Birds */
	for (int i = 0; i < (int)AngryGameVars::NUMBER_OF_STARTING_BIRDS - 1; i++)
	{
		if (!angrybirds_sprites.waiting_birds[i].addSpriteComponent(renderer.get(), "Resources\\CHARACTERS\\BIRDS\\RED\\0.png"))
		{
			return false;
		}
		angrybirds_sprites.waiting_birds[i].setX((int)AngryGameVars::SLINGSHOT_X_ORIGIN - (45 * i) - 40);
		angrybirds_sprites.waiting_birds[i].setY((int)AngryGameVars::SLINGSHOT_Y_ORIGIN + 250);
	}

	/* Slingshot Components */
	if (!angrybirds_sprites.slingshot[0].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\SLINGSHOT\\0.png"))
	{
		return false;
	}
	angrybirds_sprites.slingshot[0].setX((int)AngryGameVars::SLINGSHOT_X_ORIGIN - 25);
	angrybirds_sprites.slingshot[0].setY((int)AngryGameVars::SLINGSHOT_Y_ORIGIN);
	if (!angrybirds_sprites.slingshot[1].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\SLINGSHOT\\1.png"))
	{
		return false;
	}
	angrybirds_sprites.slingshot[1].setX((int)AngryGameVars::SLINGSHOT_X_ORIGIN - 25);
	angrybirds_sprites.slingshot[1].setY((int)AngryGameVars::SLINGSHOT_Y_ORIGIN);

	/* Flight Marker Dots */
	for (int i = 0; i < (int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS; i++)
	{
		if (!angrybirds_sprites.flight_marker[i].addSpriteComponent(renderer.get(), "Resources\\UI\\POSITION_MARKER\\0.png"))
		{
			return false;
		}
		angrybirds_sprites.flight_marker[i].despawn();
	}

	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_THIS_BLOCK_TYPE; i++)
	{
		/* Wood Blocks */
		angrybirds_sprites.wood_rectangle_long[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.wood_rectangle_long[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\LONG_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		angrybirds_sprites.wood_rectangle_tall[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.wood_rectangle_tall[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\TALL_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		angrybirds_sprites.wood_square[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.wood_square[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\SQUARE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}

		/* Ice Blocks */
		angrybirds_sprites.ice_rectangle_long[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.ice_rectangle_long[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ICE\\LONG_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		angrybirds_sprites.ice_rectangle_tall[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.ice_rectangle_tall[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ICE\\TALL_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		angrybirds_sprites.ice_square[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.ice_square[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ICE\\SQUARE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}

		/* Rock Blocks */
		angrybirds_sprites.rock_rectangle_long[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.rock_rectangle_long[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\LONG_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		angrybirds_sprites.rock_rectangle_tall[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.rock_rectangle_tall[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\TALL_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		angrybirds_sprites.rock_square[i].setDestruction(AngryDestructionStates::DEFAULT);
		for (int i = 0; i < (int)AngryDestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!angrybirds_sprites.rock_square[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\SQUARE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
	}

	retflag = false;
	return {};
}

/**
*   @brief   Sets the game window resolution
*   @details This function is designed to create the window size, any 
             aspect ratio scaling factors and safe zones to ensure the 
			 game frames when resolutions are changed in size.
*   @return  void
*/
void AngryBirdsGame::setupResolution()
{
	// how will you calculate the game's resolution?
	// will it scale correctly in full screen? what AR will you use?
	// how will the game be framed in native 16:9 resolutions?
	// here are some abritrary values for you to adjust as you see fit
	// https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/Scaling_and_MultiResolution_in_2D_Games.php
	game_width = (int)AngryGameVars::GAME_WIDTH;
	game_height = (int)AngryGameVars::GAME_HEIGHT;
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
			 keyboard input. For this game, calls to this function
			 are thread safe, so you may alter the game's state as you
			 see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Handle keypresses by gamestate
	switch (angrybirds_gamestate.current_gamestate) {
		//IN MENU
		case AngryGamestate::IN_MENU: {
			angrybirds_input.gstateInMenu(data);
			break;
		}
		//IN GAME
		case AngryGamestate::IS_PLAYING: {
			angrybirds_input.gstatePlaying(data);
			break;
		}
	}
	
	/*
	//Go fullscreen if ALT+ENTER is pressed
	else if (key->key == ASGE::KEYS::KEY_ENTER && 
		     key->action == ASGE::KEYS::KEY_PRESSED &&
		     key->mods == 0x0004)
	{
		if (renderer->getWindowMode() == ASGE::Renderer::WindowMode::WINDOWED)
		{
			renderer->setWindowedMode(ASGE::Renderer::WindowMode::FULLSCREEN);
		}
		else
		{
			renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
		}
	}
	*/
}

/**
*   @brief   Processes any click inputs
*   @details This function is added as a callback to handle the game's
		     mouse button input. For this game, calls to this function
             are thread safe, so you may alter the game's state as you
             see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void AngryBirdsGame::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent*>(data.get());

	if (click->button == 0 && angrybirds_sprites.active_bird.getState() == AngryCharacterStates::IN_CANNON)
	{
		//Let the game world know we're pulling the bird back
		angrybirds_sprites.active_bird.setState(AngryCharacterStates::ABOUT_TO_BE_FIRED);

		//Let the cursor know we're interacting
		cursor_type = INTERACTION;
	}

	if (click->action == ASGE::KEYS::KEY_RELEASED && angrybirds_sprites.active_bird.getState() == AngryCharacterStates::ABOUT_TO_BE_FIRED)
	{
		//Set physics values of bird
		AngryFlightVars::pullback_force = ((int)AngryGameVars::SLINGSHOT_X_ORIGIN - angrybirds_mousedata.mouse_x);
		AngryFlightVars::pullback_angle = ((int)AngryGameVars::SLINGSHOT_Y_ORIGIN - angrybirds_mousedata.mouse_y) * -1;

		//Let the game world know we've released the bird
		angrybirds_sprites.active_bird.setState(AngryCharacterStates::HAS_BEEN_FIRED);

		//Let the cursor know we've finished
		cursor_type = STANDARD;

		//Reset flight marker dots ready to track the movement
		for (int i = 0; i < (int)AngryGameVars::MAX_FLIGHT_MARKER_DOTS; i++)
		{
			angrybirds_sprites.flight_marker[i].despawn();
		}
		AngryFlightVars::number_of_markers = 0;
	}
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
		     current frame. Once the current frame is has finished
		     the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void AngryBirdsGame::update(const ASGE::GameTime& us)
{
	//Get current cursor pos
	inputs->getCursorPos(angrybirds_mousedata.mouse_x, angrybirds_mousedata.mouse_y);

	//Hide the cursor within the window (we use our own)
	inputs->setCursorMode(ASGE::CursorMode::HIDDEN);

	switch (angrybirds_gamestate.current_gamestate) {
		//IN MENU
		case AngryGamestate::IN_MENU: {
			angrybirds_update.gstateInMenu(us);
			break;
		}
		//IN GAME
		case AngryGamestate::IS_PLAYING: {
			angrybirds_update.gstatePlaying(us);
			break;
		}
	}

	//Always update cursor position
	angrybirds_sprites.cursor[cursor_type].setX(angrybirds_mousedata.mouse_x);
	angrybirds_sprites.cursor[cursor_type].setY(angrybirds_mousedata.mouse_y - 10);
}

/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
	         Once the current frame is has finished the buffers are
			 swapped accordingly and the image shown.
*   @return  void
*/
void AngryBirdsGame::render(const ASGE::GameTime& us)
{
	renderer->setFont(AngryFonts::fonts[0]->id);

	//Render gamestate-specific sprites
	switch (angrybirds_gamestate.current_gamestate) {
		//IN MENU
		case AngryGamestate::IN_MENU: {
			//Menu screen
			angrybirds_render.gstateInMenu(us, renderer.get());
			break;
		}
		//IN GAME
		case AngryGamestate::IS_PLAYING: {
			//Render game
			angrybirds_render.gstatePlaying(us, renderer.get());
			break;
		}
		//HAS WON or HAS LOST
		case AngryGamestate::GAME_OVER: {
			//Render win/loss screen
			angrybirds_render.gstateGameOver(us, renderer.get());
			break;
		}
	}

	//Always render cursor
	renderer->renderSprite(*angrybirds_sprites.cursor[cursor_type].spriteComponent()->getSprite());
}
