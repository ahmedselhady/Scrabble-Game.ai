#pragma once

#include "../AI_MODE/AI_MODE.hpp"
#include "../SharedClasses/TrainerComm.hpp"

class AI_Human
{
private:
    Board *MyBoard;
    vector<char> *HumanTiles;
    unordered_map<char, int> *Bag;
    BoardMask *BoardStatus;
    AiMode *AI_Agent;
    TrainerComm *Communicator;

public:
    AI_Human();
    bool SetBag(unordered_map<char, int> *Bag);
    bool SetTiles(vector<char> *HumanTiles);
    bool SetCommunicator(TrainerComm *Communicator);
    bool SetBoard(Board *MyBoard);
    bool SetAgent();
    Move *DoWork();
};