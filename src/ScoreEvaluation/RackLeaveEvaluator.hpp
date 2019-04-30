#pragma once
#include "Evaluator.hpp"
#include "../SharedClasses/Options.hpp"
#include "../MoveGeneration/MoveGenerate.h"
#include "LoadHeuristics.hpp"

class RackLeaveEvaluator : public Evaluator
{
private:
    LoadHeuristics *heuristicsValues;

public:
    RackLeaveEvaluator();
    RackLeaveEvaluator(LoadHeuristics *heuristicsValues);
    virtual ~RackLeaveEvaluator(){};

    virtual double equity(std::vector<char> *Rack, int bagSize, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move);
    virtual double leaveValue(std::vector<char> *Rack);
    virtual double CalculateRackLeave(std::vector<char> *Rack, Move *move);
};