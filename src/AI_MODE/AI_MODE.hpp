#pragma once

#include "./Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "./Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include "./Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "Opponent-Rack-Generator/Opponent.h"
#include "SharedClasses/MCTSearch.h"
#include "../src/MoveGeneration/LoadGaddag.h"
#include "../src/MoveGeneration/MoveGenerate.h"
#include "../src/MoveGeneration/Gaddag.h"
#include "../src/Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "../src/Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include "./SharedClasses/Game_Evaluator.hpp"
#include "./ScoreEvaluation/Evaluator.hpp"
#include "./ScoreEvaluation/VCValueEvaluator.hpp"
#include "./ScoreEvaluation/LoadHeuristics.hpp"

class AiMode
{
public:
    //
    void setTiles(std::vector<char> &t)
    {
        this->tiles = &t;
    }
    void setBoardToGrammar(BoardToGrammer &bg)
    {
        this->b2g = &bg;
    }

    void setBagPointer(std::unordered_map<char, int> *bag)
    {
        this->bagReference = bag;
    }

    Move *doWork(bool, int, LoadHeuristics *);

    AiMode();

private:
	Node *gaddag_instance;
	BoardToGrammer *b2g;
	std::vector<char> *tiles;
	std::unordered_map<char, int> *bagReference;
	OpponentRack opponentRackGenerator;
	Evaluator* evaluator;

    list<Move> MovesGeneration(bool);

    std::vector<char> RackGen(unordered_map<char, int> &);
};
