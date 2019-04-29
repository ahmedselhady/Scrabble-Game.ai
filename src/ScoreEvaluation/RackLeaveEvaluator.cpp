#pragma once
#include "RackLeaveEvaluator.hpp"

double RackLeaveEvaluator::equity(std::vector<char> *Rack, bool isEmptyBoard, Move *move)
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

    double value = 0;

    if (!(Rack->empty()))
    {
        double synergy = 0;
        vector<char> uniqueRack;

            for (const auto &leaveIt : leave)
                value += QUACKLE_STRATEGY_PARAMETERS->tileWorth(leaveIt);

        if (QUACKLE_STRATEGY_PARAMETERS->hasSyn2())
            for (unsigned int i = 0; i < alphabetized.length() - 1; ++i)
                if (alphabetized[i] == alphabetized[i + 1])
                    value += QUACKLE_STRATEGY_PARAMETERS->syn2(alphabetized[i], alphabetized[i]);

        uniqleave += alphabetized[0];
        for (unsigned int i = 1; i < alphabetized.length(); ++i)
            if (uniqleave[uniqleave.length() - 1] != alphabetized[i])
                uniqleave += alphabetized[i];

        if (uniqleave.length() >= 2 && QUACKLE_STRATEGY_PARAMETERS->hasSyn2())
        {
            for (unsigned int i = 0; i < uniqleave.length() - 1; ++i)
                for (unsigned int j = i + 1; j < uniqleave.length(); ++j)
                    synergy += QUACKLE_STRATEGY_PARAMETERS->syn2(uniqleave[i], uniqleave[j]);

            // TODO handle the Q

            bool holding_bad_tile = false;
            for (unsigned int i = 0; i < uniqleave.length(); ++i)
            {
                if (QUACKLE_STRATEGY_PARAMETERS->tileWorth(uniqleave[i]) < -5.5)
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