#pragma once
#include "Evaluator.hpp"
#include "../SharedClasses/Options.hpp"
#include "../SharedClasses/Move.hpp"
#include <vector>
#include "LoadHeuristics.hpp"

class RackLeaveEvaluator : public Evaluator
{
private:
    LoadHeuristics *heuristicsValues;

public:
    RackLeaveEvaluator(int bagSize, bool isEmptyBoard);
    RackLeaveEvaluator(LoadHeuristics *heuristicsValues, int bagSize, bool isEmptyBoard);
    virtual ~RackLeaveEvaluator(){};

    virtual double equity(std::vector<char> *Rack, Move *move);
    virtual double leaveValue(std::vector<char> *Rack);
    virtual double CalculateRackLeave(std::vector<char> *Rack, Move *move);
};