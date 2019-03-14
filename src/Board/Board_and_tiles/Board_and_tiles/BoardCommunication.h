#pragma once

#include "../../../SharedClasses/Board.hpp"
#include <vector>

class BoardToGrammer: public BoardCommunicator {

public:

    BoardToGrammer();
    ~BoardToGrammer();

    // overrided methods:
    std::vector<char>& getNextVerticalState();
    std::vector<char>& getNextHorizontalState();
    std::vector<char>& getTiles();
    /**
     *  function: 
     *      has-a-Tile: checks if a tile exists at a certain position
     *  
     *  inputs:
     *      row: integer, index of row between 0-14
     *      col: integer, index of col between 0-14
     * 
     *  returns:
     *      bool hasTile; True when there exist a tile in the given position
     *                    False when there does not exist a tile in the given position
    */ 
    bool hasaTile(int row, int col);
    
    /**
     *  function: 
     *      get tile at posiotion: gets the tile at a certain position
     *  
     *  inputs:
     *      row: integer, index of row between 0-14
     *      col: integer, index of col between 0-14
     * 
     *  returns:
     *      tile char; a letter from a-z when there exist a tile in the given position
     *                    astrisc '*' when there does not exist a tile in the given position
    */
    char getTileAtPosition(int row, int col);
protected:
    // add any protected methods or data members
	int HorizontalIndex;
	int VerticalIndex;

private:
    // add any utility functions
};