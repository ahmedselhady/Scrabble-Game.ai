#include "Game_Evaluator.hpp"

gameEvaluator *gameEvaluator::_instance = nullptr;

gameEvaluator *gameEvaluator::__get_Instance()
{
    if (gameEvaluator::_instance == nullptr)
    {
        gameEvaluator::_instance = new gameEvaluator();
    }

    return gameEvaluator::_instance;
}

int gameEvaluator::moveUtility(Move &move, GamePhase currentPhase)
{
    switch (currentPhase)
    {
    case MID_GAME_MODE:
        return this->midgame_preEndgameUtility(move);
    case PREEND_GAME_MODE:
        return this->midgame_preEndgameUtility(move);
    case END_GAME_MODE:
        return this->endgameUtility(move);
    default:
        throw "invalid game phase";
    }
}

void gameEvaluator::evaluateMovesHuristic(std::list<Move> &moves, GamePhase currentPhase)
{
    for (std::list<Move>::iterator itr = moves.begin(); itr != moves.end(); ++itr)
    {
        itr->evaluatedScore = this->moveUtility(*itr, currentPhase);
    }

    moves.sort([](const Move &a, const Move &b) { return a.evaluatedScore > b.evaluatedScore; });
}
