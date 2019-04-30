#include "VCValueEvaluator.hpp"

VCValueEvaluator::VCValueEvaluator(LoadHeuristics *heuristicsValues, std::vector<char> *opponentRack) : RackLeaveEvaluator(heuristicsValues)
{
    this->heuristicsValues = heuristicsValues;
    this->opponentRack = opponentRack;
}

double VCValueEvaluator::equity(std::vector<char> *Rack, int bagSize, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move)
{
    if (isEmptyBoard)
    {
        double adjustment = 0; //if (move.action == Move::Place) //
                               //{

        int start = move->startPosition.COL;
        if (move->startPosition.ROW < start)
        {
            start = move->startPosition.ROW;
        }
        string wordString = Options::regularWordString(move);

        vector<char> *wordTiles = Options::moveTiles(move);
        int length = wordTiles->size();

        int consbits = 0;
        for (signed int index = wordTiles->size() - 1; index >= 0; --index)
        {
            consbits <<= 1;
            if (Options::isVowel(&(*wordTiles)[index]))
            {
                consbits |= 1;
            }
        }

        adjustment = heuristicsValues->vcPlace(start, length, consbits);
        // else
        // {
        //     adjustment = 3.5;
        // }

        return RackLeaveEvaluator::equity(Rack, bagSize, isEmptyBoard, bagSizeGreaterThanZero, move) + adjustment;
    }

    else if (bagSizeGreaterThanZero)
    {
        int leftInBagPlusSeven = bagSize - move->moveUsedTiles + 7;
        double heuristicArray[13] =
            {
                0.0, -8.0, 0.0, -0.5, -2.0, -3.5, -2.0,
                2.0, 10.0, 7.0, 4.0, -1.0, -2.0};
        double timingHeuristic = 0.0;
        if (leftInBagPlusSeven < 13)
        {
            timingHeuristic = heuristicArray[leftInBagPlusSeven];
        }
        return RackLeaveEvaluator::equity(Rack, bagSize, isEmptyBoard, bagSizeGreaterThanZero, move) + timingHeuristic;
    }
    else
    {
        return endgameResult(Rack, move) + move->moveScore;
    }
}

double VCValueEvaluator::endgameResult(std::vector<char> *Rack, Move *move)
{
    std::vector<char> *remainingRack = Options::unusedRackTiles(Rack, move);

    if (remainingRack->empty())
    {
        double deadwood = 0;
        deadwood += Options::rackScore(opponentRack);

        return deadwood * 2;
    }

    return -8.00 - 2.61 * Options::rackScore(remainingRack);
}