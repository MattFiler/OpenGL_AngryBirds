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
	renderer->setWindowTitle("Angry Birds");
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
	renderer->setClearColour(ASGE::COLOURS::WHITE);

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);
	
	mouse_callback_id =inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);

	//If editor file exists, we must be in level editor mode.
	std::ifstream file("level.editor");
	if (file)
	{
		gamestate.current_gamestate = Gamestate::LEVEL_BUILDER_MODE;
		mousedata.cursor = Cursors::LONG_BLOCK;
	}
	
	//Load textures
	assignTextures();

	//Load font
	Fonts::fonts[0] = new Fonts(renderer->loadFont("Resources\\UI\\FONTS\\0.ttf", 55), "default", 55);

	return true;
}

/* Assign textures to sprites */
bool AngryBirdsGame::assignTextures()
{
	/* Backgrounds */
	for (int i = 0; i < (int)BackgroundSprites::NUMBER_OF_BACKGROUNDS; i++) 
	{
		if (!sprites.backgrounds[i].addSpriteComponent(renderer.get(), "Resources\\UI\\BACKGROUNDS\\" + std::to_string(i) + ".jpg"))
		{
			return false;
		}
	}

	/* Menu Elements */
	for (int i = 0; i < (int)MenuElement::MENU_ELEMENT_COUNT; i++) 
	{
		if (!sprites.menu_elements[i].addSpriteComponent(renderer.get(), "Resources\\UI\\MENU_ELEMENTS\\" + std::to_string(i) + ".png"))
		{
			return false;
		}
	}
	sprites.menu_elements[(int)MenuElement::MAIN_LOGO].setOpacity(0);
	sprites.menu_elements[(int)MenuElement::PRESS_SPACE_TO_START].setOpacity(0);
	sprites.menu_elements[(int)MenuElement::LEVEL_SELECT_BACKGROUND].setOpacity(0);
	sprites.menu_elements[(int)MenuElement::CONTROLS_TEXT].setOpacity(0);

	/* Cursors */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_CURSOR_STATES; i++)
	{
		if (!sprites.cursor[i].addSpriteComponent(renderer.get(), "Resources\\UI\\CURSOR\\" + std::to_string(i) + ".png"))
		{
			return false;
		}
	}

	/* Active Bird */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_CHARACTER_FRAMES; i++)
	{
		if (!sprites.active_bird.addSpriteComponent(renderer.get(), "Resources\\CHARACTERS\\BIRDS\\RED\\" + std::to_string(i) + ".png", i))
		{
			return false;
		}
	}
	sprites.active_bird.spawn();
	sprites.active_bird.setState(CharacterStates::IN_CANNON);

	/* Inactive Birds */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_STARTING_BIRDS - 1; i++)
	{
		for (int x = 0; x < (int)GameVars::NUMBER_OF_CHARACTER_FRAMES; x++)
		{
			if (!sprites.waiting_birds[i].addSpriteComponent(renderer.get(), "Resources\\CHARACTERS\\BIRDS\\RED\\" + std::to_string(x) + ".png", x))
			{
				return false;
			}
		}
		sprites.waiting_birds[i].spawn();
		sprites.waiting_birds[i].setX((int)GameVars::SLINGSHOT_X_ORIGIN - (45 * i) - 40);
		sprites.waiting_birds[i].setY((int)GameVars::SLINGSHOT_Y_ORIGIN + 240 - (5 * i));
	}

	/* All Possible Pigs */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_PIGS; i++)
	{
		for (int x = 0; x < (int)GameVars::NUMBER_OF_CHARACTER_FRAMES; x++)
		{
			if (!sprites.pigs[i].addSpriteComponent(renderer.get(), "Resources\\CHARACTERS\\PIGS\\MEDIUM\\MERGED\\" + std::to_string(x) + ".png", x))
			{
				return false;
			}
		}
		sprites.pigs[i].despawn();
	}

	/* Slingshot Components */
	for (int i = 0; i < 2; i++) 
	{
		if (!sprites.slingshot[i].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\SLINGSHOT\\" + std::to_string(i) + ".png"))
		{
			return false;
		}
		sprites.slingshot[i].setX((int)GameVars::SLINGSHOT_X_ORIGIN - 25);
		sprites.slingshot[i].setY((int)GameVars::SLINGSHOT_Y_ORIGIN);
	}

	/* Victory Stars */
	for (int i = 0; i < 4; i++)
	{
		if (!sprites.gameover_score_stars.addSpriteComponent(renderer.get(), "Resources\\UI\\SCORE\\STARS\\" + std::to_string(i) + ".png", i))
		{
			return false;
		}
		for (int x = 0; x < (int)GameVars::NUMBER_OF_LEVELS; x++)
		{
			if (!sprites.menu_score_stars[i].addSpriteComponent(renderer.get(), "Resources\\UI\\SCORE\\SMALL_STARS\\" + std::to_string(x) + ".png", x))
			{
				return false;
			}
		}
		sprites.menu_score_stars[i].setCurrentFrame(0);
		sprites.menu_score_stars[i].setY(860);
	}
	sprites.menu_score_stars[0].setX(625);
	sprites.menu_score_stars[1].setX(848);
	sprites.menu_score_stars[2].setX(1074);
	sprites.menu_score_stars[3].setX(1300);
	sprites.gameover_score_stars.setCurrentFrame(0);

	/* Score Bonuses */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_STARTING_BIRDS; i++)
	{
		if (!sprites.score_bonus_10000[i].addSpriteComponent(renderer.get(), "Resources\\UI\\SCORE\\SCORE_BONUS\\10000\\" + std::to_string(i) + ".png"))
		{
			return false;
		}
		sprites.score_bonus_10000[i].despawn();
	}
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FX_AVAILABLE; i++)
	{
		if (!sprites.score_bonus_5000[i].addSpriteComponent(renderer.get(), "Resources\\UI\\SCORE\\SCORE_BONUS\\5000\\0.png"))
		{
			return false;
		}
		sprites.score_bonus_5000[i].despawn();
	}

	/* Flight Marker Dots */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FLIGHT_MARKER_DOTS; i++)
	{
		if (!sprites.flight_marker[i].addSpriteComponent(renderer.get(), "Resources\\UI\\POSITION_MARKER\\0.png"))
		{
			return false;
		}
		sprites.flight_marker[i].despawn();
	}

	/* Explosion FX */
	for (int i = 0; i < (int)GameVars::NUMBER_OF_FX_AVAILABLE; i++)
	{
		for (int x = 0; x < (int)GameVars::NUMBER_OF_FRAMES_IN_FX; x++)
		{
			if (!sprites.explosion[i].addSpriteComponent(renderer.get(), "Resources\\UI\\FX\\EXPLOSION\\" + std::to_string(x) + ".png",x))
			{
				return false;
			}
		}
		sprites.explosion[i].despawn();
		sprites.explosion[i].setCurrentFrame(0);
	}

	/* All Environment Blocks */
	for (int x = 0; x < (int)GameVars::NUMBER_OF_BLOCKS_PER_VARIATION; x++)
	{
		/* Wood Blocks */
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.wood_rectangle_long[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\LONG_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.wood_rectangle_long[x].setDestruction(DestructionStates::DEFAULT);
		sprites.wood_rectangle_long[x].setBlockType(BlockTypes::WOOD);
		sprites.wood_rectangle_long[x].despawn();
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.wood_rectangle_tall[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\TALL_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.wood_rectangle_tall[x].setDestruction(DestructionStates::DEFAULT);
		sprites.wood_rectangle_tall[x].setBlockType(BlockTypes::WOOD);
		sprites.wood_rectangle_tall[x].despawn();
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.wood_square[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\WOOD\\SQUARE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.wood_square[x].setDestruction(DestructionStates::DEFAULT);
		sprites.wood_square[x].setBlockType(BlockTypes::WOOD);
		sprites.wood_square[x].despawn();

		/* Ice Blocks */
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.ice_rectangle_long[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ICE\\LONG_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.ice_rectangle_long[x].setDestruction(DestructionStates::DEFAULT);
		sprites.ice_rectangle_long[x].setBlockType(BlockTypes::ICE);
		sprites.ice_rectangle_long[x].despawn();
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.ice_rectangle_tall[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ICE\\TALL_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.ice_rectangle_tall[x].setDestruction(DestructionStates::DEFAULT);
		sprites.ice_rectangle_tall[x].setBlockType(BlockTypes::ICE);
		sprites.ice_rectangle_tall[x].despawn();
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.ice_square[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ICE\\SQUARE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.ice_square[x].setDestruction(DestructionStates::DEFAULT);
		sprites.ice_square[x].setBlockType(BlockTypes::ICE);
		sprites.ice_square[x].despawn();

		/* Rock Blocks */
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.rock_rectangle_long[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\LONG_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.rock_rectangle_long[x].setDestruction(DestructionStates::DEFAULT);
		sprites.rock_rectangle_long[x].setBlockType(BlockTypes::ROCK);
		sprites.rock_rectangle_long[x].despawn();
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.rock_rectangle_tall[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\TALL_RECTANGLE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.rock_rectangle_tall[x].setDestruction(DestructionStates::DEFAULT);
		sprites.rock_rectangle_tall[x].setBlockType(BlockTypes::ROCK);
		sprites.rock_rectangle_tall[x].despawn();
		for (int i = 0; i < (int)DestructionStates::DESTRUCTION_COUNT; i++)
		{
			if (!sprites.rock_square[x].addSpriteComponent(renderer.get(), "Resources\\ENVIRONMENT\\BLOCKS\\ROCK\\SQUARE\\" + std::to_string(i) + ".png", i))
			{
				return false;
			}
		}
		sprites.rock_square[x].setDestruction(DestructionStates::DEFAULT);
		sprites.rock_square[x].setBlockType(BlockTypes::ROCK);
		sprites.rock_square[x].despawn();
	}

	/* Placeholders for Level Editor */
	if (gamestate.current_gamestate == Gamestate::LEVEL_BUILDER_MODE)
	{
		for (int i = 0; i < (int)GameVars::NUMBER_OF_BLOCK_VARIATIONS + 1; i++)
		{
			for (int x = 0; x < (int)DestructionStates::DESTRUCTION_COUNT; x++)
			{
				if (!sprites.placeholder_marker[i].addSpriteComponent(renderer.get(), "Resources\\UI\\CURSOR\\" + std::to_string(i + 2) + ".png", x))
				{
					return false;
				}
			}
			sprites.placeholder_marker[i].setX((int)GameVars::DESPAWN_X_POS - sprites.placeholder_marker[i].getHeight());
			sprites.placeholder_marker[i].setY((int)GameVars::DESPAWN_Y_POS - sprites.placeholder_marker[i].getWidth());
			//These are never "despawned" - just hidden offscreen when not used.
		}
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
	game_width = (int)GameVars::GAME_WIDTH;
	game_height = (int)GameVars::GAME_HEIGHT;
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
	switch (gamestate.current_gamestate) 
	{
		//IN MENU
		case Gamestate::IN_MENU: 
		{
			game_input.gstateInMenu(data);
			break;
		}
		//IN GAME
		case Gamestate::IS_PLAYING: 
		{
			game_input.gstatePlaying(data);
			break;
		}		
		//HAS WON or LOST
		case Gamestate::GAME_OVER: 
		{
			game_input.gstateGameOver(data);
			break;
		}
		//Level Builder Mode (intended for developers only)
		case Gamestate::LEVEL_BUILDER_MODE: 
		{
			game_input.gstateLevelBuilder(data);
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

	if (gamestate.current_gamestate == Gamestate::LEVEL_BUILDER_MODE)
	{
		//Level Editor mode active - place blocks on left click
		if (click->button == 0 && click->action == ASGE::KEYS::KEY_RELEASED) 
		{
			gamestate.debug_place_block = true;
		}
		//Cycle block type on right click
		if (click->button == 1 && click->action == ASGE::KEYS::KEY_RELEASED) 
		{
			if ((int)mousedata.cursor + 1 > (int)Cursors::PIG)
			{
				mousedata.cursor = Cursors::LONG_BLOCK;
			}
			else
			{
				mousedata.cursor = (Cursors)((int)mousedata.cursor + 1);
			}
		}
	}
	else
	{
		if (gamestate.win_state != Gamestate::ON_HOLD && 
			gamestate.current_gamestate == Gamestate::IS_PLAYING) 
		{
			if (click->button == 0 && 
				sprites.active_bird.getState() == CharacterStates::IN_CANNON &&
				(mousedata.mouse_x >= sprites.active_bird.getX() - (int)GameVars::BIRD_CLICK_HITBOX_LEEWAY &&
				mousedata.mouse_x <= sprites.active_bird.getX() + (int)GameVars::BIRD_CLICK_HITBOX_LEEWAY + sprites.active_bird.getWidth()) &&
				(mousedata.mouse_y >= sprites.active_bird.getY() - (int)GameVars::BIRD_CLICK_HITBOX_LEEWAY &&
				mousedata.mouse_y <= sprites.active_bird.getY() + (int)GameVars::BIRD_CLICK_HITBOX_LEEWAY + sprites.active_bird.getHeight()))
			{
				//Let the game world know we're pulling the bird back
				sprites.active_bird.setState(CharacterStates::ABOUT_TO_BE_FIRED);

				//Let the cursor know we're interacting
				mousedata.cursor = Cursors::INTERACTION;
			}

			if (click->action == ASGE::KEYS::KEY_RELEASED && sprites.active_bird.getState() == CharacterStates::ABOUT_TO_BE_FIRED)
			{
				//Set physics values of bird
				FlightVars::pullback_force = ((int)GameVars::SLINGSHOT_X_ORIGIN - sprites.active_bird.getX());
				FlightVars::pullback_angle = ((int)GameVars::SLINGSHOT_Y_ORIGIN - sprites.active_bird.getY()) * -1;

				//Let the game world know we've released the bird
				sprites.active_bird.setState(CharacterStates::HAS_BEEN_FIRED);

				//Let the cursor know we've finished
				mousedata.cursor = Cursors::STANDARD;

				//Reset flight marker dots ready to track the movement
				for (int i = 0; i < (int)GameVars::NUMBER_OF_FLIGHT_MARKER_DOTS; i++)
				{
					sprites.flight_marker[i].despawn();
				}
				FlightVars::number_of_markers = 0;
			}
		}
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
	inputs->getCursorPos(mousedata.mouse_x, mousedata.mouse_y);

	//Hide the cursor within the window (we use our own)
	inputs->setCursorMode(ASGE::CursorMode::HIDDEN);

	switch (gamestate.current_gamestate) 
	{
		//IN MENU
		case Gamestate::IN_MENU:
		{
			game_update.gstateInMenu(us);
			break;
		}
		//IN GAME
		case Gamestate::IS_PLAYING:
		{
			game_update.gstatePlaying(us);
			break;
		}
		//HAS_WON or HAS_LOST
		case Gamestate::GAME_OVER: 
		{
			game_update.gstateGameOver(us);
			break;
		}
		//REQUESTED QUIT
		case Gamestate::REQUESTED_QUIT: 
		{
			signalExit();
			break;
		}
		//Level Builder Mode (intended for developers only)
		case Gamestate::LEVEL_BUILDER_MODE:
		{
			game_update.gstateLevelBuilder(us);
			break;
		}
	}

	//Always update cursor position
	sprites.cursor[(int)mousedata.cursor].setX(mousedata.mouse_x);
	sprites.cursor[(int)mousedata.cursor].setY(mousedata.mouse_y - 10);

	//Update cursor scale if in editor
	if (gamestate.current_gamestate == Gamestate::LEVEL_BUILDER_MODE &&
		mousedata.cursor != Cursors::PIG) 
	{
		sprites.cursor[(int)mousedata.cursor].setScale(gamestate.debug_block_scale);
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
	renderer->setFont(Fonts::fonts[0]->id);

	//Render gamestate-specific sprites
	switch (gamestate.current_gamestate)
	{
		//IN MENU
		case Gamestate::IN_MENU:
		{
			//Menu screen
			game_render.gstateInMenu(us, renderer.get());
			break;
		}
		//IN GAME
		case Gamestate::IS_PLAYING: 
		{
			//Render game
			game_render.gstatePlaying(us, renderer.get());
			break;
		}
		//HAS WON or HAS LOST
		case Gamestate::GAME_OVER: 
		{
			//Render win/loss screen
			game_render.gstateGameOver(us, renderer.get());
			break;
		}
		//Level Builder Mode (intended for developers only)
		case Gamestate::LEVEL_BUILDER_MODE:
		{
			game_render.gstateLevelBuilder(us, renderer.get());
			break;
		}
	}
}
