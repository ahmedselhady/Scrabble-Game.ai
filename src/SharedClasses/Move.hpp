#pragma once
//INCLUDES:

#include <string>
#include "CommInfo.hpp"
// ADD Includes : if Needed ...

/*NOTES:
    1- Please Don't Change The Names of The Below Pre-Defined Attributes As We Already Integrated Them in Some Modules.
    2- Please Feel Free To Add Any Needed Attributes OR Functions To Suit Your Modules.
    3- Refer To Ahmed Salem For Any Adjustments.
*/

/* CHAR : 
    1- if a small (97->122) regular char so it is a new tile that will be played in this turn.
    2- if Large (65->90) it means a Blank so it is a new tile that will be played in this turn.
    3- from (0->25) (26 Letters) means that it was on board before 
   */
#define ON_BOARD_CHAR 97
struct Position
{ // defines what a "Move" is.
    char ROW;
    char COL;
};

enum MoveRank
{
    Score = 0,
    Heuristic
};

class Move
{ // Move or Play.
    // Add if Needed ...

public:
    std::string word; // Extra Notes : The Returned word will be lowered Case and a Capitalized Letter in case of a BLANK USED.
    double moveScore;    // type maybe changed...
    Position startPosition;
    bool horizontal; // true -> horiz false -> vertical.
    double testHScore;
    char moveUsedTiles; // Number of Tiles used in a Move Excluding Already on-Board Tiles.
    bool isBingo;       // Can Be Removed Redundant. Ask First if Before Removal To Check That Nobody Uses it.
    double evaluatedScore;
    Move();
    Move(std::string word, bool horizontal, Position position, int usedTiles); // Init.
    void setScore(int score);                                                  // Setting Move Score.
    std::string moveServerFormat();                                            // Format the move for server's use.
    std::string moveGUIFormat();                                               // For GUI use.
};