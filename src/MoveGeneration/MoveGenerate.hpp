
//TODO: Completion of Move Generation Algorithm.
#pragma once
//INCLUDES:

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <string.h>
#include <string>

#include "Gaddag.hpp"
#include "../SharedClasses/Move.hpp"
#include "..\Board\Board_and_tiles\Board_and_tiles\BoardCommunication.hpp"
#include "../SharedClasses/Move.hpp"
using namespace std;

#define MAX_BOARD_ROWS 15
#define MAX_BOARD_COLS 15
#define BLANK_CHAR 32 // Capitalize The Blank Character Used To Mark it as 'BLANK'

// dummylist:
// a particular sqaure.
#define HorizCrossSet 1; // each will be replaced by the coreponding sqaure crossset
#define VerticalCrossSet 0;
#define BLANK ' ' // CHANGE IT IF WANTED NOT DEPENDANT ..

//TODO: Section Will Be Removed After Adding a "MOVE CLASS"
///
// struct Position{ // defines what a "Move" is.
//     char ROW;
//     char COL;
// };

// struct Move{ // defines what a "Move" is.
//     string word;
//     int moveScore;
//     Position startPosition;
//     bool horizontal; // true -> horiz false -> vertical.
//     char moveUsedTiles;
// };
///
//struct Position{ // defines what a "Move" is.
//    char ROW;
//    char COL;
//};
//
//struct Move{ // defines what a "Move" is.
//    string word;
//    int moveScore;
//    Position startPosition;
//    bool horizontal; // true -> horiz false -> vertical.
//    char moveUsedTiles;
//};

class WordGenerate
{ // just a static class no need to create an explicit object.

    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
private:
    BoardToGrammer *board;
    list<Move> moves; // all possible moves provided a Rack and and a Board at a given instant.
    Node *root;       // gaddag root tree.
    unordered_map<char, int> tilesCount;
    list<string> nonRepeatedMoves;
    char maxBorder; // Utility Variables inside fuctions helping in Transformation from Vertical to Horiz and vice versa.
    char colOffset;
    char rowOffset;
    char currDirection; // i.e. if horizontal move we choose the col else the row.
    bitset<27> Horiz_crossset[15][15];
    bitset<27> Vertical_crossset[15][15];
    bitset<27> (*currCrossSet)[15][15];
    //bitset<27> (*currCrossSet)(int row,int col);
    char countRoomLeft = 0; // count of chars directly left to an anchor sqaure.
    char cancelIndex = 0;   // just a factor to eliminate duplicate of code.

    bool blankUsed;
    char anchorRow; // chosen anchor square postion.
    char anchorCol;
    char usedTiles = 0;

    bool emptyBoard = false;

public:
    WordGenerate(BoardToGrammer *board, Node *root); // Takes a Reference to the Board.
    void setBoardState(BoardToGrammer *board);       // Assigns Different Board States For Monte Carlo.
    void generateWords();                            // iterates on each sqaure in the board and performing the algo. Taking the board 2-Dimensions into Consideration.
    int roomLeftCount(int row, int col);
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
    bool isAnchor(int row, int col);                  // is this square given row and col an anchor sqaure?
    void gen(int pos, string word, Node *gaddagNode); // Gordon Gen funtion first function in Move Generation Algo.
    /*
       pos: offset to a square in the board -> left/down (-ve) right/up (+ve).
       word: 
       rack: all 7 possible tiles that can be used in a move.
       root: the root node which is start of GADDAG root tree.
       */
    void goOn(int pos, char boardLetter, string word, Node *gaddagNode); // Gordon GO ON funtion first function in Move Generation Algo.
    void countTilesRack(vector<char> *rackTiles);                        // Calculates the no. of tiles for each character in Rack.
    list<Move> allMoves();                                               // Returns all moves.
    void setDirectionOptions(int row, int col, bool isHorizontal);       // Sets the Options needed for transforming from Horiz. to vertical and vice versa.
    void duplicateMovesRemoval();                                        // TODO: removes duplicate moves occuring from a one tile play. (vertically + Horizonatally)
    void generateEmpty(Node *node, string &word);                        // For Empty Board State Moves.
    void emptyBoardMoves();                                              // Generate all possible moves availabe given certain Rack when the status of the board is empty only.
    void crosssets();                                                    // calculate the crosssets of each square.
    void updateCrossSet(Move *move);                                     /////TODO: Just Updates Changed CrossSet.
    bool checkWordDict(string word);                                     // Given a Word it checks Whether This word in Dict or NOT.
    Move *bestScoreMove();                                               // TODO: Returns Best (Highest Score) Move From The Last Generated Moves RUN.
    void moveCalcHeuristic();                                            // TODO: Calculates 'RackLeave' Heuristic of a Move with Accumalation with its score.
    void sortMoves(MoveRank rank, int numberMoves);                      // TODO: Sorts Moves Based on a Given Criteria and Returns The 'K' Highest Moves Controlled By numberMoves.
    //--> TODO: Optimize CrossSet Calculation Each Move Played. Should Be Called After Each Play t.
    void printCrossSet(); // TEST FUNCTION ONLY.
};

// NOTES: (Put Critical Questions Here For Furthur Development)
/*
        1- Case where the Board will be empty with no anchors at the start of game ??
        2- Fear of duplicate moves/words ??
        3- There is an idea that enhance the Creation time of the GADDAG Tree (LAST IMPROVEMENT). (DONE)
        4- Removal of redundant "cancelIndex".
        5- Optimimize crosssets founder after a move been made to only consider certain square to update thier crossset.
        6- optimizing "RoomLeft".
        7- RESET Moves,RackCount and optimizing in pass, exchange, noplay etc. plays.
        8- Adding Horiz. CrossSet in gen function.
    */
