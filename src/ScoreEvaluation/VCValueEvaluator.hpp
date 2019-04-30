#pragma once
#include "RackLeaveEvaluator.hpp"
#include "../SharedClasses/Options.hpp"
#include <vector>

class VCValueEvaluator : public RackLeaveEvaluator
{
private:
    LoadHeuristics *heuristicsValues;
    std::vector<char> *opponentRack;

public:
    VCValueEvaluator();
    VCValueEvaluator(LoadHeuristics *heuristicsValues, std::vector<char> *opponentRack);
    virtual ~VCValueEvaluator(){};
    virtual double equity(std::vector<char> *Rack, int bagSize, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move);

    double endgameResult(std::vector<char> *Rack, Move *move); // Endgame Value ..
};
