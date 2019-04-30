#pragma once

#include <unordered_map>
#include <vector>
#include "./Definitions.hpp"
#include "Trainer.hpp"
#include "./AI_MODE/AI_MODE.hpp"
#include "Trainer.hpp"
#include "./MoveGeneration/Gaddag.hpp"
#include "./MoveGeneration/LoadGaddag.hpp"
#include "./MoveGeneration/LoadNode.hpp"

class GameBrain
{
private:
    int bagSize;
    Trainer trainer;
    vector<char> AI_Tiles,HumanTiles;
    TrainerComm *comm;
    Board* MyBoard;
    RackOfTiles* rackoftiles;
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
    bool IsFinished();
};