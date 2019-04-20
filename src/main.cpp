#include <iostream>
#include "Definitions.hpp"
#include"Board\Board_and_tiles\Board_and_tiles\BoardCommunication.h"
int main(int, char**) {
	//----------------------- Game Definitions:
	AgentResponse AI;
	GamePhase CurrentPhase=GamePhase::MID_GAME_MODE;
	GameMode CurrentMode=GameMode::TEACHER_MODE;
	//----------------------- Board Definitions:
	BoardToGrammer *BoardAndTiles = new BoardToGrammer();
	Board*Board = nullptr;
	std::vector<char>* Tiles = nullptr;
	Tiles = &BoardAndTiles->getTiles();
	Board = &BoardAndTiles->getBoard;
	if (CurrentMode == TEACHER_MODE)
	{
		while (CurrentPhase != GamePhase::END_GAME_MODE)
		{
		//-------------------Human Should Start

		}
	}
}
