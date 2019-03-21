#include "./Tiles.h"
#include "./BoardCommunication.h"
#include "./Board.h"

//Constructor
BoardToGrammer::BoardToGrammer() {
	BoardCommunicator::BoardPtr=Board::getBoard();// need to edit this 
	BoardCommunicator::TilesPtr=Tiles::getTiles();// need to edit this 
}
//Destructor
BoardToGrammer::~BoardToGrammer()
{
}

//This Function it will call the function from the AI module to determine the next state given the current board Vertically
std::vector<char>& BoardToGrammer::getNextVerticalState() {
	//will call the function from the AI module to determine the next state given the current board
	return (BoardPtr->getNextVertical(VerticalIndex++));
}

//This Function it will call the function from the AI module to determine the next state given the current board Horizontally
std::vector<char>& BoardToGrammer::getNextHorizontalState(){
	return (BoardPtr->getNextHorizontal(HorizontalIndex++)); // what if reached to 15?
}

//This Function will call the GUI function which will aquire the move played by the player
std::vector<char>& BoardToGrammer::getTiles(){
	return (* new std::vector<char>(TilesPtr->getRackTiles()));
}
//This Function will get the tile that is in the given rows and coloumns
char BoardToGrammer::getTileAtPosition(int row, int col) {
	vector<char> CurrentRow = BoardPtr->getNextHorizontal(row);
	return (CurrentRow[col] == '*') ? '*' : CurrentRow[col];
}

//This function set character postion
void BoardToGrammer::SetChar(char Letter, int Row, int Col)
{
	BoardPtr->SetCharPos(Letter, Row, Col);
}

void BoardToGrammer::PrintBitBoard()
{
	BoardPtr->print();
}

//This function checs if this place contain a tile or not
bool BoardToGrammer::hasaTile(int row, int col){     
	vector<char> CurrentRow=BoardPtr->getNextHorizontal(row);
	return (CurrentRow[col] == '*') ? false : true;
}
