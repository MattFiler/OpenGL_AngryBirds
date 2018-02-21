#pragma once

struct AngryWorldVars
{
	static const int gravity; //The force of gravity in-game
	static int pullback_force; //The force applied to a bird by a player
	static int pullback_angle; //The angle applied to a bird by a player
	static int bird_flight_time; //The total time a bird has been in flight

	static int total_game_time; //The total time of the game
};