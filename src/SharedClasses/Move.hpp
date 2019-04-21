#pragma once
//INCLUDES:

#include <string.h>
#include <string>
// ADD Includes : if Needed ...

/*NOTES:
    1- Please Don't Change The Names of The Below Pre-Defined Attributes As We Already Integrated Them in Some Modules.
    2- Please Feel Free To Add Any Needed Attributes OR Functions To Suit Your Modules.
    3- Refer To Ahmed Salem For Any Adjustments.
*/
struct Position { // defines what a "Move" is.
    char ROW;
    char COL;
};

class Move { // Move or Play.
    // Add if Needed ...
  
public:
    std::string word; // Extra Notes : The Returned word will be lowered Case and a Capitalized Letter in case of a BLANK USED.
    int moveScore; // type maybe changed...
    Position startPosition;
    bool horizontal; // true -> horiz false -> vertical.
    char moveUsedTiles; // Number of Tiles used in a Move Excluding Already on-Board Tiles. 
    bool isBingo; // Can Be Removed Redundant. Ask First if Before Removal To Check That Nobody Uses it.

    Move(std::string word,bool horizontal,Position position,int usedTiles); // Init. 
    void setScore(int score);   // Setting Move Score.
};