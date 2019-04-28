#pragma once

#include "Evaluator.hpp"

double Evaluator::equity(std::vector<char> &Rack, bool isEmptyBoard, Move &move) const
{
    return move.moveScore;
}

double Evaluator::CalculateRackLeave(std::vector<char> &Rack, Move &move) const
{
    return 0;
}

double Evaluator::leaveValue(std::vector<char> &Rack) const
{
    return 0;
}
