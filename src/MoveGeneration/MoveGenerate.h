
//TODO: Completion of Move Generation Algorithm.

#ifndef MOVEGENERATE_H
#define MOVEGENERATE_H

//INCLUDES:

#include <iostream>
#include <vector>
#include <list>
#include <string.h>
#include <string>

#include "Gaddag.h"
#include "..\Board\Board_and_tiles\Board_and_tiles\BoardCommunication.h"
using namespace std;

struct Move{ // defines what a "Move" is.
    int moveScore;
    int startPosition;
    bool horizontal; // true -> horiz false -> vertical.
};

class WordGenerate { // just a static class no need to create an explicit object.

    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
    private:
    BoardToGrammer * board; 
    public:

       WordGenerate(BoardToGrammer&board); // Takes a Reference to the Board.
       void gen(int pos,string word,Node*root); // Gordon Gen funtion first function in Move Generation Algo.
       /*
       pos: offset to a square in the board -> left/down (-ve) right/up (+ve).
       word: 
       rack: all 7 possible tiles that can be used in a move.
       root: the root node which is start of GADDAG root tree.
       */
       void goOn(); // Gordon GO ON funtion first function in Move Generation Algo.

};

#endif
