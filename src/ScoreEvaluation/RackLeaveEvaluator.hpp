#pragma once
#include "Evaluator.hpp"

class ScorePlusLeaveEvaluator : public Evaluator
{
public:
    virtual ~ScorePlusLeaveEvaluator(){};

    virtual double equity(std::vector<char> &Rack, bool isEmptyBoard, Move &move) const;
    virtual double leaveValue(std::vector<char> &Rack) const;
};