#pragma once

#include <string>

class Board {

public:

	/*
	 * Constructor
	 *     The communication module creates and instance of the current board state 
	 * inputs:
	 *      datastructure(i.e the container) of the tiles on the board.
	 *		board state
	 * returns:
	 *      Instance of Board
	*/
	Board();


	//Assuming the next state is an integer, Might be changed later as the moves will be updated to the board
	int getNextState();

	//assume tiles chosen in player mode from thew GUI return in an array, will be changed later
	int* getTilesFromGUI();

private:

	//Data members
	/*
	* datastructure(i.e the container) of the tiles on the board.
	*board state
	*/


};