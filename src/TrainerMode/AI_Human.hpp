#pragma once
#include"../SharedClasses/BoardCommunicator.hpp"
#include"../AI_MODE.h"
#include"../SharedClasses/TrainerComm.hpp"

class AI_Human{
    private:
    Board* MyBoard;
    vector<char>* HumanTiles;
    unordered_map<char,int>* Bag;
    BoardMask* BoardStatus;
    AI_MODE* AI_Agent;
    TrainerComm* Communicator;
    
    public:
    AI_Human();
    bool IsEmptyBoard();
    bool SetBag(unordered_map<char,int>* Bag);
    bool SetTiles(vector<char>* HumanTiles);
    bool SetBoard(Board* MyBoard);
    bool SetAgent();
    bool DoWork();
};