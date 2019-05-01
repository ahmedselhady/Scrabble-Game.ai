#pragma once

#include <unordered_map>
#include <vector>
#include "./Definitions.hpp"
#include "./AI_MODE/AI_MODE.hpp"
#include "./MoveGeneration/Gaddag.h"
#include "./MoveGeneration/LoadGaddag.h"
#include "./MoveGeneration/LoadNode.h"
#include "./Definitions.hpp"
// #include "./TrainerMode/Trainer.hpp"
#include "./AI_MODE/AI_MODE.hpp"

class GameBrain
{
private:
    int bagSize;
    // Trainer trainer;
    // Timer *T1;
    // Timer *T2;
    // Timer *T3;
    // bool turn_TrainerMode;
    // vector<char> AI_Tiles, HumanTiles;
    // TrainerComm *comm;
    // Board *MyBoard;
    // RackOfTiles *rackoftiles;
    std::unordered_map<char, int> bag;
    GamePhase game_phase;

    static Node *_gaddagInstance;
    static inline Node *createGaddag()
    {
        LoadGaddag gaddagConstructor;
        Node *gaddagRoot = gaddagConstructor.constructGaddag();
        return gaddagRoot;
    }

    bool GameBrain::IsFinished();

public:
    static Node *__get_gaddag();

    GameBrain();
    void setTurnOfTrainerMode(bool);
    void updateBag(std::vector<char> &);
    void work_computer_vs_computer();
    void work_human_vs_computer();
};