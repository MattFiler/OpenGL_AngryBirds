#include <Engine\Renderer.h>
#include "AngryScores.h"

Scores::Scores()
{

}
Scores::~Scores()
{

}

void Scores::saveScores()
{
	for (int i = 0; i < (int)GameVars::NUMBER_OF_LEVELS; i++)
	{
		std::ofstream score_file;
		score_file.open("Resources\\SAVES\\" + std::to_string(i) + ".score");
		score_file << std::to_string(gamestate.highscores[i]);
		score_file.close();
	}
}
void Scores::loadScores()
{
	for (int i = 0; i < (int)GameVars::NUMBER_OF_LEVELS; i++)
	{
		std::string line;
		std::ifstream score_file("Resources\\SAVES\\"+std::to_string(i)+".score");
		while (getline(score_file, line))
		{
			gamestate.highscores[i] = std::stoi(line);
		}
		score_file.close();
	}
}


/*

void Scores::saveScores()
{
std::fstream scoreboard_file;
for (int i = 0; i < (int)GameVars::NUMBER_OF_LEVELS; i++)
{
scoreboard_file.open("Resources//SAVES//" + std::to_string(i) + ".score");
scoreboard_file << gamestate.highscores[i];
scoreboard_file.close();
}
}
void Scores::loadScores()
{
std::fstream scoreboard_file;
for (int i = 0; i < (int)GameVars::NUMBER_OF_LEVELS; i++)
{
scoreboard_file.open("Resources//SAVES//"+std::to_string(i)+".score");
scoreboard_file >> gamestate.highscores[i];
scoreboard_file.close();
}
}

*/