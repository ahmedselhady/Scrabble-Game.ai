#pragma once

#include "Move.hpp"
#include "./Definitions.hpp"

#include <list>

/**
 *  This is the brain of the project
*/

class gameEvaluator
{
public:
    static gameEvaluator *__get_Instance();

    int moveUtility(Move &, GamePhase);

    void evaluateMovesHuristic(std::list<Move> &, GamePhase);

private:
    static gameEvaluator *_instance;

    inline int midgame_preEndgameUtility(Move &)
    {
        // TODO: add seif's implementation for this function
        return 0;
    }

    inline int endgameUtility(Move &move)
    {
        // Simply: work greedy:
        return move.moveScore;
    }

    gameEvaluator()
    {
    }
};