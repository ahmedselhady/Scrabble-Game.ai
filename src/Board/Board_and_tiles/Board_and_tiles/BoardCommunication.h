#pragma once

#include "SharedClasses/Board.hpp"
#include <vector>

class BoardToGrammer: public BoardCommunicator {

public:

    BoardToGrammer();//Constructor
    ~BoardToGrammer();//Destructor

    // overrided methods:
    std::vector<char>& getNextVerticalState();//it will call the function from the AI module to determine the next state given the current board Vertically
    std::vector<char>& getNextHorizontalState();//it will call the function from the AI module to determine the next state given the current board Horizontally
    std::vector<char>& getTiles();//it will call the GUI function which will aquire the move played by the player

protected:
    // add any protected methods or data members

private:
    // add any utility functions
};
