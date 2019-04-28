#pragma once
#include "../SharedClasses/Move.hpp"
#include <vector>

class Evaluator
{
public:
    virtual ~Evaluator(){};

    virtual double CalculateRackLeave(std::vector<char> &Rack, Move &move) const;
    virtual double equity(std::vector<char> &Rack, bool isEmptyBoard, Move &move) const;
    virtual double leaveValue(std::vector<char> &Rack) const;
};