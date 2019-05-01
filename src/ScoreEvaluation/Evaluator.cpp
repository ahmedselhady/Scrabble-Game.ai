#pragma once

#include "Evaluator.hpp"

Evaluator::Evaluator(int bagSize, bool isEmptyBoard)
{
    this->bagSize = bagSize;
    this->isEmptyBoard = isEmptyBoard;
}
double Evaluator::equity(std::vector<char> *Rack, Move *move)
{
    return move->moveScore;
}

double Evaluator::CalculateRackLeave(std::vector<char> *Rack, Move *move)
{
    return 0;
}

double Evaluator::leaveValue(std::vector<char> *Rack)
{
    return 0;
}
