#include "BoardCommunication.h"


BoardToGrammer::BoardToGrammer() {
	BoardCommunicator::BoardPtr=Board::getBoard();// need to edit this 
}

BoardToGrammer::~BoardToGrammer()
{
}

std::vector<char>& BoardToGrammer::getNextVerticalState() {
	//will call the function from the AI module to determine the next state given the current board
	return(BoardPtr->getNextVertical(VerticalIndex++));
}

std::vector<char>& BoardToGrammer::getNextHorizontalState(){
	return(BoardPtr->getNextHorizontal(HorizontalIndex++));// what if reached to 15?
}

std::vector<char>& BoardToGrammer::getTiles(){
	//will call the GUI function which will aquire the move played by the player
        // TODO: complete the implementation

		// for Dummy:
		std::vector<char>* tiles = new std::vector<char>();
		for (int i = (int)'a'; i <= (int)'g'; ++i) {
			tiles->push_back(i);
		}
		return (*tiles);
}

char BoardToGrammer::getTileAtPosition(int row, int col){
        // TODO: complete the implementation
	return 'a';
}


bool BoardToGrammer::hasaTile(int row, int col){
        // TODO: complete the implementation
	return true;
}