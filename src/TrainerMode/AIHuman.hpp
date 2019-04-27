#pragma once
#include"../SharedClasses/BoardCommunicator.hpp"
#include"../AI_Mode/AI_MODE.h"
#include"../SharedClasses/TrainerComm.hpp"
class AIHuman{
    
    Board* MyBoard;
    vector<char> HumanTiles;
    AI_MODE AI_Agent;
    TrainerComm Communicator;

    bool SetTiles(vector<char> &HumanTiles)
    {
        try
        {
                 this->HumanTiles=HumanTiles;
                 return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    return false;

    }
    bool DoWork()
    {
        Move BestMove=AI_Agent.getBestMove();
        
        if(BestMove.moveScore>Communicator.GetMovePlayer.moveScore)
        {
            Communicator.RecievedMoveMsg("AI Move was Better than Player Move ");
            Communicator.ReceivedPlayer(BestMove);
          
        }
        else if(BestMove.moveScore<Communicator.GetMovePlayer.moveScore)
        {
          Communicator.RecievedMoveMsg("Congratulations !!!!!!! your move is better than what I thought");
        }
        else if(BestMove.moveScore==Communicator.GetMovePlayer.moveScore)
        {
            Communicator.RecievedMoveMsg("Congratulations !!!!!!! your move is equal to what I thought");

        }
        
            return false
        
        
    }

}