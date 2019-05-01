#pragma once
#include"../SharedClasses/BoardCommunicator.hpp"
#include"../AI_MODE.hpp"
#include"../SharedClasses/TrainerComm.hpp"
using namespace std;
class AI_AI{
    private:
    Board* MyBoard;
    vector<char>* AI_Tiles;
    unordered_map<char,int>* Bag;
    BoardMask* BoardStatus;
    AI_MODE* AI_Agent;
    TrainerComm* Communicator;

    public:
    AI_AI();
    bool SetBag(unordered_map<char,int>* Bag);
    bool SetTiles(vector<char> *AI_Tiles);
    bool SetBoard(Board* MyBoard);
    bool SetCommunicator(TrainerComm* Communicator);
    bool SetAgent();
    //bool SetisEmtyBoard(bool isEmty);
    Move* DoWork();
    bool IsEmptyBoard();
 
    

};