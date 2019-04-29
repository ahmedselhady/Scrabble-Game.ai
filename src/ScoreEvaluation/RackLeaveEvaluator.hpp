#pragma once
#include "Evaluator.hpp"
#include "../SharedClasses/Options.hpp"
#include "../MoveGeneration/MoveGenerate.h"

class RackLeaveEvaluator : public Evaluator
{
public:
    virtual ~RackLeaveEvaluator(){};

    virtual double equity(std::vector<char> *Rack, bool isEmptyBoard, Move *move);
    virtual double leaveValue(std::vector<char> *Rack);
    virtual double CalculateRackLeave(std::vector<char> *Rack, Move *move);
};