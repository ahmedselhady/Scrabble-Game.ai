#include <iostream>
#include "Definitions.hpp"
#include"Board\Board_and_tiles\Board_and_tiles\BoardCommunication.hpp"
/*int main(int, char**) {
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
}*/
#include "AI_MODE.cpp"
#include "./Brain.hpp"
#include "./Definitions.hpp"

int main()
{
	GameBrain *brain = new GameBrain();
	brain->work_computer_vs_computer();

    Rack.push_back('o');
    Rack.push_back('v');
    Rack.push_back('b');
    bool isEmpty=true;
    Move recommendedMove = AI_Mode_Function(Tiles,Rack,isEmpty);
    std::cout <<"Move word: "<< recommendedMove.word<< "recommended move score:" << recommendedMove.moveScore<<endl;

}
	system("pause");
	return 0;
}
