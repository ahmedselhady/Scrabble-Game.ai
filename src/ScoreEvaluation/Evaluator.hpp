#pragma once
#include "../SharedClasses/Move.hpp"
#include "../SharedClasses/Options.hpp"
#include <vector>

class Evaluator
{

public:
    int bagSize;
    bool isEmptyBoard;
    Evaluator(int bagSize, bool isEmptyBoard);
    virtual ~Evaluator(){};
    virtual double CalculateRackLeave(std::vector<char> *Rack, Move *move);
    virtual double equity(std::vector<char> *Rack, Move *move);
    virtual double leaveValue(std::vector<char> *Rack);
};