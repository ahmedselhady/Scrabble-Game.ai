#pragma once
#include <vector>
#include "../Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "../Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "../SharedClasses/Move.hpp"

class BoardCommunicator
{

public:
	/*
	 * Constructor
	 *     The communication module creates and instance of the current board state 
	 * inputs:
	 *      TODO: datastructure(i.e the container) of the tiles on the board.
	 *		board state
	 * returns:
	 *      Instance of Board Communicator
	*/

	//Assuming the next state is an integer, Might be changed later as the moves will be updated to the board
	/**
	 * function: 
	 * getNextVerticalState; calculates and returns the next vertical possible coloumn from the board to the grammer module
	 * inputs: 
	 * 		void
	 * returns:
	 * 		the next column in the board
	*/
	virtual std::vector<char> &getNextVerticalState() = 0;

	/**
	 * function: 
	 * 		getNextHorizontalState; calculates and returns the next vertical possible row from the board to the grammer module
	 * inputs: 
	 * 		void
	 * returns:
	 * 		the next row in the board
	*/
	virtual std::vector<char> &getNextHorizontalState() = 0;

	//assume tiles chosen in player mode from thew GUI return in an array, will be changed later
	/**
	 * function: getTiles; calculates and returns the tiles in player's rack
	 * 
	 * inputs: 
	 * 		void
	 * returns:
	 * 		the rack of tiles with player
	*/
	virtual std::vector<char> &getTiles() = 0;

	/**
	 * function: getTiles; calculates and returns the Score gained by the suggested move
	 * 
	 * inputs: 
	 * 		suggestedMove: Vector of Characters; The suggested update to a row/coloumn for which the score is to be calculated
	 * 
	 * 		position: integer; offset of row/coloumn at which the move will be placed
	 * 
	 * 		horizontal: boolean; True value means the move suggested is to be placed horizontally
	 * 							 False value means the move suggested is to be placed vertically
	 * returns:
	 * 		score: integer; The score calculated for the suggested move
	*/
	int calculateScore(string suggestedMove, int row, int col, bool horizontal);

protected:
	// TODO: add the Board Class as a data member:
	Board *BoardPtr;
	Tiles *TilesPtr;

private:
	//Data members
	/*
	* datastructure(i.e the container) of the tiles on the board.
	*board state
	*/
};