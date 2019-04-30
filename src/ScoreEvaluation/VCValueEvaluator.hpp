#pragma once
#include "RackLeaveEvaluator.hpp"

class VCValueEvaluator : public RackLeaveEvaluator
{
private:
    LoadHeuristics *heuristicsValues;

public:
    VCValueEvaluator();
    VCValueEvaluator(LoadHeuristics *heuristicsValues);
    virtual ~VCValueEvaluator(){};
    virtual double equity(std::vector<char> *Rack, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move);

    double endgameResult(std::vector<char> *Rack, Move *move); // Endgame Value ..
};
