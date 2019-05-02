
#pragma once

#include "../AI_MODE/AI_MODE.hpp"
#include "../SharedClasses/TrainerComm.hpp"

using namespace std;
class AI_AI
{
private:
    Board *MyBoard;
    vector<char> *AI_Tiles;
    unordered_map<char, int> *Bag;
    BoardMask *BoardStatus;
    AiMode *AI_Agent;
    TrainerComm *Communicator;
    BoardToGrammer b2g;

public:
    AI_AI();
    bool SetTiles(vector<char> *);
    bool SetBag(unordered_map<char, int> *);
    bool SetBoard(Board *);
    bool SetCommunicator(TrainerComm *);
    bool SetAgent(AiMode *);
    Move *DoWork(bool);
};