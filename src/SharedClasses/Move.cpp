#include "./Move.h"

#include <string>
#include <iostream>

//NOTE: Feel Free To Add But See Notes in Move.h Before Adding .....
// Initialize
Move::Move(string word,bool horizontal,Position position,int usedTiles){   
    this->word = word;
    this->horizontal = horizontal;
    this->startPosition = position;
    this->moveUsedTiles = usedTiles;
}

// Setting Move Score.
void Move::setScore(int score){
    this->moveScore = score;
}

