#pragma once
#include"../SharedClasses/BoardCommunicator.hpp"
#include"../AI_MODE.hpp"
#include"../SharedClasses/TrainerComm.hpp"
using namespace std;
class AI_AI{
    private:
    Board* MyBoard;
    vector<char> HumanTiles;
    unordered_map<char,int>* Bag;
    bool isEmty;

    AI_MODE AI_Agent;
    TrainerComm Communicator;

    public:
    AI_AI();
    bool SetBag(unordered_map<char,int>* Bag);
    bool SetTiles(vector<char> &HumanTiles);
    bool SetBoard(Board* MyBoard);
    bool SetisEmtyBoard(bool isEmty);
    Move* DoWork();

};