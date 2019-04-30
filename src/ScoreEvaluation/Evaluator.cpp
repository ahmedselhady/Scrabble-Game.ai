#pragma once

#include "Evaluator.hpp"

double Evaluator::equity(std::vector<char> *Rack, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move)
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
