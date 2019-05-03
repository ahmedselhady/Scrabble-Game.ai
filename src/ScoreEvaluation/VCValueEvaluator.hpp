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
    VCValueEvaluator(int bagSize, bool isEmptyBoard);
    VCValueEvaluator(LoadHeuristics *heuristicsValues, std::vector<char> *opponentRack, int bagSize, bool isEmptyBoard);
    virtual ~VCValueEvaluator(){};
    virtual double equity(std::vector<char> *Rack, Move *move);

    double endgameResult(std::vector<char> *Rack, Move *move); // Endgame Value ..
};
