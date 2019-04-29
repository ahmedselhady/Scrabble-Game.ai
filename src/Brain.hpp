#pragma once

#include <unordered_map>
#include <vector>
#include "./Definitions.hpp"
#include "./AI_MODE/AI_MODE.hpp"
#include "./MoveGeneration/Gaddag.h"
#include "./MoveGeneration/LoadGaddag.h"
#include "./MoveGeneration/LoadNode.h"

class GameBrain
{
private:
    int bagSize;
    static Node *_gaddagInstance;
    static inline Node *createGaddag()
    {
        LoadGaddag gaddagConstructor;
        Node *gaddagRoot = gaddagConstructor.constructGaddag();
        return gaddagRoot;
    }

public:
    static Node *__get_gaddag();

    std::unordered_map<char, int> bag;
    GamePhase game_phase;

    GameBrain();
    void updateBag(std::vector<char> &);
    void work_computer_vs_computer();
    void work_human_vs_computer();
};