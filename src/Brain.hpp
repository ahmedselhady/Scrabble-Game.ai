#pragma once

#include <unordered_map>
#include <vector>
#include "./Definitions.hpp"
#include "./AI_MODE/AI_MODE.hpp"

class GameBrain
{
private:
    int bagSize;

public:
    GameBrain();

    std::unordered_map<char, int> bag;

    GamePhase game_phase;

    void updateBag(std::vector<char> &);

    void work_computer_vs_computer();
    void work_human_vs_computer();
};