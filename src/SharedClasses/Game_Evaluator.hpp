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

    /** evaluate Move Heuristic:  this function evaluates the static score for the suggested move by the Grammar as the first step in game evaluation process
     * 
     * inputs: 
     *      list of moves: list<T>; the list of suggested moves --passed by reference 
     *      current game phase: GamePhase; the game phase depending on the number of tiles in bag 
     * returns:
     *      returns the list of moves with their modified static scores 
    */
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