#pragma once

struct AngryFlightVars
{
	static int pullback_force; //The force applied to a bird by a player
	static int pullback_angle; //The angle applied to a bird by a player
	static float bird_flight_time; //The total time a bird has been in flight
	static float bird_start_x; //The starting position (X) of the bird
	static float bird_start_y; //The starting position (Y) of the bird
};