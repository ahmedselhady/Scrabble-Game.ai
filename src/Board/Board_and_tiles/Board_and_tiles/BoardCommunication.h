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

protected:
    // add any protected methods or data members
	int HorizontalIndex;
	int VerticalIndex;

private:
    // add any utility functions
};