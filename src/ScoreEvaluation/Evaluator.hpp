#pragma once
#include "../SharedClasses/Move.hpp"
#include "../SharedClasses/Options.hpp"
#include <vector>

class Evaluator
{
public:
    virtual ~Evaluator(){};

    virtual double CalculateRackLeave(std::vector<char> *Rack, Move *move);
    virtual double equity(std::vector<char> *Rack, int bagSize, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move);
    virtual double leaveValue(std::vector<char> *Rack);
};