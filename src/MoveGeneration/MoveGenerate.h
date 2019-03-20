
//TODO: Completion of Move Generation Algorithm.

#ifndef MOVEGENERATE_H
#define MOVEGENERATE_H

//INCLUDES:

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <string.h>
#include <string>

#include "Gaddag.h"
#include "..\Board\Board_and_tiles\Board_and_tiles\BoardCommunication.h"
using namespace std;

#define MAX_BOARD_ROWS 15
#define MAX_BOARD_COLS 15

struct Move{ // defines what a "Move" is.
    string word;
    int moveScore;
    int startPosition;
    bool horizontal; // true -> horiz false -> vertical.
};

class WordGenerate { // just a static class no need to create an explicit object.

    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
    private:
    BoardToGrammer * board; 
    list<Move> Moves; // all possible moves provided a Rack and and a Board at a given instant.
    Node*root; // gaddag root tree.
    unordered_map<char,int> tilesCount;
    char maxBorder; // Utility Variables inside fuctions helping in Transformation from Vertical to Horiz and vice versa.
    char colOffset;
    char rowOffset;
    char currDirection; // i.e. if horizontal move we choose the col else the row.
	bitset<26> Horiz_crossset[15][15];
	bitset<26> Vertical_crossset[15][15];
	bitset<26> currCrossSet;
    char countRoomLeft = 0; // count of chars directly left to an anchor sqaure.
    char cancelIndex = 0; // just a factor to eliminate duplicate of code.
    
    char anchorRow; // chosen anchor square postion.
    char anchorCol;

    public:

       WordGenerate(BoardToGrammer&board); // Takes a Reference to the Board.
       void generateWords(); // iterates on each sqaure in the board and performing the algo. Taking the board 2-Dimensions into Consideration.
       int roomLeftCount(int row,int col); 
       /*
            this function may seem awkward but it's usefull.
            it's important to stop right before a letter found while travesring the board leftward generating possible moves
            so, if you have a 2 horiz. words and an empty square inbetween "PA" '  ' "ABLE"  if you started traversing from the first anchor which is 'E' to the left,
            you will end up facing the other word "PA" in your way. if you continued your traversal you will get a possible word "payable".
            Now if you ran the algo. on the other anchor "A" of the word "PA" you will also generate the same word "Payable" 
            ----> Did you see the problem ? == REPEATED WORDS.
            So, we prevent that by stopping the right word at a specific depth(left or up) limited by the word left to it. "ABLE" --> From "E" go until you found a Letter.
            we count this as "RoomLeft=4" for last example.
       */
       bool isAnchor(int row,int col); // is this square given row and col an anchor sqaure?
       void gen(int pos,string &word,Node*gaddagNode); // Gordon Gen funtion first function in Move Generation Algo.
       /*
       pos: offset to a square in the board -> left/down (-ve) right/up (+ve).
       word: 
       rack: all 7 possible tiles that can be used in a move.
       root: the root node which is start of GADDAG root tree.
       */
       void goOn(int pos,char boardLetter,string&word,Node*gaddagNode); // Gordon GO ON funtion first function in Move Generation Algo.
       void countTilesRack(); // Calculates the no. of tiles for each character in Rack.
       list<Move> allMoves(); // TODO:Returns all moves.
       void setDirectionOptions(int row,int col ,bool isHorizontal); // Sets the Options needed for transforming from Horiz. to vertical and vice versa.
       void duplicateMovesRemoval(); // TODO: removes duplicate moves occuring from a one tile play. (vertically + Horizonatally)
       void emptyBoardMoves(); //TODO: Generate all possible moves availabe given certain Rack when the status of the board is empty only.
	   void crosssets(); // calculate the crosssets of each square.
};

// NOTES: (Put Critical Questions Here For Furthur Development)
    /*
        1- Case where the Board will be empty with no anchors at the start of game ??
        2- Fear of duplicate moves/words ??
        3- There is an idea that enhance the Creation time of the GADDAG Tree (LAST IMPROVEMENT). 
        4- Removal of redundant "cancelIndex".
        5- Optimimize crosssets founder after a move been made to only consider certain square to update thier crossset.
    */
#endif
