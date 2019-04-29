#pragma once

#include "Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include "Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "Opponent-Rack-Generator/Opponent.h"
#include "SharedClasses/MCTSearch.h"
#include "../src/MoveGeneration/LoadGaddag.h"
#include "../src/MoveGeneration/MoveGenerate.h"
#include "../src/MoveGeneration/Gaddag.h"
#include "../src/Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "../src/Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include "./SharedClasses/Game_Evaluator.hpp"
#include "./Brain.hpp"

inline Node *createGaddag()
{ // just a test function.
    LoadGaddag gaddagConstructor;
    Node *gaddagRoot = gaddagConstructor.constructGaddag();
    return gaddagRoot;
}

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
