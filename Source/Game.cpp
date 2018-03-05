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

	toggleFPS();
	renderer->setWindowTitle("Angry Birds!");
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);
	
	mouse_callback_id =inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);

	//Apply background sprites
	if (!loadBackgrounds())
	{
		return false;
	}

	//Apply menu sprite
	if (!angrybirds_sprites.menu_layer.addSpriteComponent(renderer.get(), "Resources\\Textures\\menu.jpg"))
	{
		return false;
	}

	//Spawn and apply sprite to every bird
	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_BIRDS; i++)
	{
		if (!angrybirds_sprites.birds[i].addSpriteComponent(renderer.get(), "Resources\\Textures\\kenney_physicspack\\PNG\\Aliens\\alienGreen_square.png"))
		{
			return false;
		}
		angrybirds_sprites.birds[i].spawn();
	}

	//Spawn and apply sprite to every pig
	for (int i = 0; i < (int)AngryGameVars::MAX_NUMBER_OF_PIGS; i++)
	{
		if (!angrybirds_sprites.pigs[i].addSpriteComponent(renderer.get(), "Resources\\Textures\\kenney_physicspack\\PNG\\Aliens\\alienBlue_square.png"))
		{
			return false;
		}
		angrybirds_sprites.pigs[i].despawn();
	}

	return true;
}

bool AngryBirdsGame::loadBackgrounds()
{
	std::string filename = "Resources\\Textures\\lvl";
	filename += std::to_string(std::rand() % 3 + 1);
	filename += ".png";

	if (!angrybirds_sprites.background_layer.addSpriteComponent(renderer.get(), filename))
	{
		return false;
	}

	return true;
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
	
	//Close the game when ESC is pressed
	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
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

	if (click->button == 0) 
	{
		//Let the game world know we're pulling the bird back
		angrybirds_sprites.birds[(int)AngryGamestateData::current_bird].setBirdState(AngryBirdStates::IN_CANNON);
	}

	if (click->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Set physics values of bird
		AngryFlightVars::pullback_force = ((int)AngryGameVars::SLINGSHOT_X_ORIGIN - angrybirds_mousedata.mouse_x);
		AngryFlightVars::pullback_angle = ((int)AngryGameVars::SLINGSHOT_Y_ORIGIN - angrybirds_mousedata.mouse_y) * -1;

		//Let the game world know we've released the bird
		angrybirds_sprites.birds[(int)AngryGamestateData::current_bird].setBirdState(AngryBirdStates::HAS_BEEN_FIRED);
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

	switch (angrybirds_gamestate.current_gamestate) {
		//IN GAME
		case AngryGamestate::IS_PLAYING: {
			angrybirds_update.gstatePlaying(us);
			break;
		}
	}
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
	renderer->setFont(0);

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
	}

	renderer->renderText(std::to_string(angrybirds_mousedata.mouse_x), 500, 20, ASGE::COLOURS::RED);
	renderer->renderText(std::to_string(angrybirds_mousedata.mouse_y), 500, 60, ASGE::COLOURS::RED);
}
