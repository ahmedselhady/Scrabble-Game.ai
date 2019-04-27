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


void main()
{
	unordered_map<char,int> Tiles;
	Tiles['b'] = 1;
	Tiles['e'] = 1;
	Tiles['l'] = 1;
	Tiles['z'] = 1;
	Tiles['n'] = 1;
	Tiles['g'] = 1;
	Tiles['h'] = 1;
	Tiles['o'] = 1;
	Tiles['q'] = 1;
	Tiles['y'] = 1;
	vector<char> Rack;
    Rack.push_back('f');
    Rack.push_back('x');
    Rack.push_back('a');
    Rack.push_back('g');

    Rack.push_back('o');
    Rack.push_back('v');
    Rack.push_back('b');
    bool isEmpty=true;
    Move recommendedMove = AI_Mode_Function(Tiles,Rack,isEmpty);
    std::cout <<"Move word: "<< recommendedMove.word<< "recommended move score:" << recommendedMove.moveScore<<endl;

}
