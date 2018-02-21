#include "../AngryStructs/AngryWorldVars.h"

int const AngryWorldVars::gravity = 10; //Constant force of gravity
int AngryWorldVars::pullback_force = 0; //The force applied by the player to a bird
int AngryWorldVars::pullback_angle = 0; //The angle applied by the player to a bird
int AngryWorldVars::bird_flight_time = 0; //Reset every time a bird is fired

int AngryWorldVars::total_game_time = 0; //Updated whenever gamestate IS_PLAYING