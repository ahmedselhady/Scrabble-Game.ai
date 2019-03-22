#include "BoardCommunication.h"

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
	return (BoardPtr->getNextHorizontal(HorizontalIndex++));// what if reached to 15?
}

//This Function will call the GUI function which will aquire the move played by the player
std::vector<char>& BoardToGrammer::getTiles(){
	//will call the GUI function which will aquire the move played by the player
        // TODO: complete the implementation

		return TilesPtr->getRackTiles();
}

//This Function will get the tile that is in the given rows and coloumns
char BoardToGrammer::getTileAtPosition(int row, int col){
   
	vector<char> CurrentRow=BoardPtr->getNextHorizontal(row);
	//vector<char> CurrentCol=BoardPtr->getNextVertical(col);
        char Empty=' ';
        if (CurrentRow[col]==Empty)
	{
 		return '*';
	}
	else
	return CurrentRow[col];
}

//This function checks if this place contain a tile or not
bool BoardToGrammer::hasaTile(int row, int col){
        
	vector<char> CurrentRow=BoardPtr->getNextHorizontal(row);
	//vector<char> CurrentCol=BoardPtr->getNextVertical(col);
	
	 char Empty=' ';
        if (CurrentRow[col]==Empty)
	{
 		return false;
	}
	else
	return true;
}
