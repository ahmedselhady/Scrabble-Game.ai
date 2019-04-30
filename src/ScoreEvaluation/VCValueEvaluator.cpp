#include "VCValueEvaluator.hpp"

VCValueEvaluator::VCValueEvaluator(LoadHeuristics *heuristicsValues)
{
    this->heuristicsValues = heuristicsValues;
}

double VCValueEvaluator::equity(std::vector<char> *Rack, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move)
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

        LetterString wordTiles = move.tiles();

        int length = wordTiles.length();

        int consbits = 0;
        for (signed int i = wordTiles.length() - 1; i >= 0; i--)
        {
            consbits <<= 1;
            if (QUACKLE_ALPHABET_PARAMETERS->isVowel(QUACKLE_ALPHABET_PARAMETERS->clearBlankness(wordTiles[i])))
                consbits |= 1;
        }

        adjustment = QUACKLE_STRATEGY_PARAMETERS->vcPlace(start, length, consbits);
    }
    else
    {
        adjustment = 3.5;
    }

    // UVcout << "placement adjustment for " << move << " is " << adjustment << endl;
    return ScorePlusLeaveEvaluator::equity(Rack, move) + adjustment;
}

else if (position.bag().size() > 0)
{
    int leftInBagPlusSeven = position.bag().size() - move.usedTiles().length() + 7;
    double heuristicArray[13] =
        {
            0.0, -8.0, 0.0, -0.5, -2.0, -3.5, -2.0,
            2.0, 10.0, 7.0, 4.0, -1.0, -2.0};
    double timingHeuristic = 0.0;
    if (leftInBagPlusSeven < 13)
        timingHeuristic = heuristicArray[leftInBagPlusSeven];
    return ScorePlusLeaveEvaluator::equity(position, move) + timingHeuristic;
}
else
{
    return endgameResult(position, move) + move.score;
}
}

double CatchallEvaluator::endgameResult(const GamePosition &position, const Move &move) const
{
    Rack leave = position.currentPlayer().rack() - move;

    if (leave.empty())
    {
        double deadwood = 0;
        for (PlayerList::const_iterator it = position.players().begin();
             it != position.players().end(); ++it)
        {
            if (!(*it == position.currentPlayer()))
            {
                deadwood += it->rack().score();
            }
        }

        return deadwood * 2;
    }

    return -8.00 - 2.61 * leave.score();
}