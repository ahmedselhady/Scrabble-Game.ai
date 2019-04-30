#pragma once

#include "../Board/Board_and_tiles/Board_and_tiles/Board.hpp"
#include "../Board/Board_and_tiles/Board_and_tiles/BoardCommunication.hpp"
#include "../Board/Board_and_tiles/Board_and_tiles/Tiles.hpp"
#include "../Opponent-Rack-Generator/Opponent.h"
#include "../SharedClasses/MCTSearch.hpp"
#include "../src/MoveGeneration/LoadGaddag.hpp"
#include "../src/MoveGeneration/MoveGenerate.hpp"
#include "../src/MoveGeneration/Gaddag.hpp"
#include "../src/Board/Board_and_tiles/Board_and_tiles/Tiles.hpp"
#include "../src/Board/Board_and_tiles/Board_and_tiles/BoardCommunication.hpp"
#include "./SharedClasses/Game_Evaluator.hpp"
#include "./Brain.hpp"

class AI_MODE
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

    Move *doWork();

    AI_MODE();

private:
    Node *gaddag_instance;
    BoardToGrammer *b2g;
    std::vector<char> *tiles;
    std::unordered_map<char, int> *bagReference;
    OpponentRack opponentRackGenerator;

    list<Move> MovesGeneration(bool);

    std::vector<char> RackGen(unordered_map<char, int> &);
};
