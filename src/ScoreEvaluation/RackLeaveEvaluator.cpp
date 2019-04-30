#pragma once
#include "RackLeaveEvaluator.hpp"

RackLeaveEvaluator::RackLeaveEvaluator(LoadHeuristics *heuristicsValues)
{
    this->heuristicsValues = heuristicsValues;
}

double RackLeaveEvaluator::equity(std::vector<char> *Rack, bool isEmptyBoard, bool bagSizeGreaterThanZero, Move *move)
{
    return CalculateRackLeave(Rack, move);
}

double RackLeaveEvaluator::CalculateRackLeave(std::vector<char> *Rack, Move *move)
{
    vector<char> *remainedTiles = Options::unusedRackTiles(Rack, move);
    return leaveValue(remainedTiles); // remaining tiles only.
}

double RackLeaveEvaluator::leaveValue(std::vector<char> *Rack)
{
    vector<char> *sortedRack = Options::sortRack(Rack);

    // if (QUACKLE_STRATEGY_PARAMETERS->hasSuperleaves() && QUACKLE_STRATEGY_PARAMETERS->superleave(alphabetized))
    //     return QUACKLE_STRATEGY_PARAMETERS->superleave(alphabetized);
    return heuristicsValues->superleave(sortedRack);

    double value = 0;

    if (!(Rack->empty()))
    {
        double synergy = 0;
        vector<char> uniqueRack;

        for (int index = 0; index < Rack->size(); ++index)
        {
            value += heuristicsValues->tileWorth((*Rack)[index]);
        }

        for (unsigned int index = 0; index < sortedRack->size() - 1; ++index)
        {
            if ((*sortedRack)[index] == (*sortedRack)[index + 1])
            {
                value += heuristicsValues->syn2((*sortedRack)[index], (*sortedRack)[index]);
            }
        }

        uniqueRack.push_back((*sortedRack)[0]);

        for (unsigned int index = 1; index < sortedRack->size(); ++index)
        {
            if (uniqueRack[uniqueRack.size() - 1] != (*sortedRack)[index])
            {
                uniqueRack.push_back((*sortedRack)[index]);
            }
        }

        if (uniqueRack.size() >= 2)
        {
            for (unsigned int indexLetter1 = 0; indexLetter1 < uniqueRack.size() - 1; ++indexLetter1)
            {
                for (unsigned int indexLetter2 = indexLetter1 + 1; indexLetter2 < uniqueRack.size(); ++indexLetter2)
                {
                    synergy += heuristicsValues->syn2(uniqueRack[indexLetter1], uniqueRack[indexLetter2]);
                }
            }

            bool holding_bad_tile = false;
            for (unsigned int index = 0; index < uniqueRack.size(); ++index)
            {
                if (heuristicsValues->tileWorth(uniqueRack[index]) < -5.5)
                {
                    holding_bad_tile = true;
                }
            }

            if ((synergy > 3.0) && !holding_bad_tile)
            {
                synergy += 1.5 * (synergy - 3.0);
            }

            value += synergy;
        }
    }
    const float vcvalues[8][8] =
        {
            {0.0, 0.0, -1.0, -2.5, -5.0, -8.5, -13.5, -18.5},
            {-1.0, 0.0, 0.5, 0.0, -1.5, -5.0, -10.0, 0.0},
            {-3.5, -1.0, 0.5, 1.5, -1.5, -3.0, 0.0, 0.0},
            {-7.0, -3.5, -0.5, 2.5, 0.0, 0.0, 0.0, 0.0},
            {-10.0, -6.5, -3.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {-13.5, -11.5, -8.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {-18.5, -16.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {-23.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
        };
    int vowels = 0;
    int cons = 0;

    for (int index = 0; index < Rack->size(); ++index)
    {
        if ((*Rack)[index] != BLANK)
        {
            if (Options::isVowel(&(*Rack)[index]))
            {
                vowels++;
            }
            else
            {
                cons++;
            }
        }
    }

    value += vcvalues[vowels][cons];

    if (value < -40)
    {
        value = -40;
    }

    return value;
}