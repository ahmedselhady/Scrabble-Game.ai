#include "./Tiles.h"
#include "./BoardCommunication.h"
#include "./Board.h"


BoardToGrammer::BoardToGrammer() {
	BoardCommunicator::BoardPtr=Board::getBoard();// need to edit this 
	BoardCommunicator::TilesPtr=Tiles::getTiles();// need to edit this 
}

BoardToGrammer::~BoardToGrammer()
{
}

std::vector<char>& BoardToGrammer::getNextVerticalState() {
	//will call the function from the AI module to determine the next state given the current board
	return (BoardPtr->getNextVertical(VerticalIndex++));
}

std::vector<char>& BoardToGrammer::getNextHorizontalState(){
	return (BoardPtr->getNextHorizontal(HorizontalIndex++)); // what if reached to 15?
}

std::vector<char>& BoardToGrammer::getTiles(){
	//will call the GUI function which will aquire the move played by the player
	return (* new std::vector<char>(TilesPtr->getRackTiles()));
}

char BoardToGrammer::getTileAtPosition(int row, int col) {
	vector<char> CurrentRow = BoardPtr->getNextHorizontal(row);
	return (CurrentRow[col] == '*') ? '*' : CurrentRow[col];
}


bool BoardToGrammer::hasaTile(int row, int col){     
	vector<char> CurrentRow=BoardPtr->getNextHorizontal(row);
	return (CurrentRow[col] == '*') ? false : true;
}