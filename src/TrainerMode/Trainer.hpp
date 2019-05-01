#pragma once

#include "AI_Human.hpp"
#include "AI_AI.hpp"
#include "Timer.hpp"
#include "RackOfTiles.hpp"
#include <vector>
#include "AI_MODE/AI_MODE.hpp"

class Trainer
{
public:
    Board *MyBoard;
    vector<char> AI_Tiles, HumanTiles;
    AI_Human Human;
    AI_AI AI;
    Timer Time;
    RackOfTiles MyRack;
    Trainer();

    void AI_AI_func(Board *b, vector<char> *tile, unordered_map<char, int> *bag, AI_AI *h, AiMode *mode);
    void AI_Human_func(Board *b, vector<char> *tile, unordered_map<char, int> *bag, AI_Human *h, AiMode *mode);
};