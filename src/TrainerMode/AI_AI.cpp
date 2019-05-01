
#pragma once
#include "AI_AI.hpp"

AI_AI::AI_AI()
{
    this->MyBoard = NULL;
    this->AI_Tiles = NULL;
    this->AI_Agent = NULL;
    this->Bag = NULL;
    this->BoardStatus = NULL;
    this->Communicator = NULL;
   
}
bool AI_AI::SetBag(unordered_map<char,int>* Bag)
{
    try
    {
        this->Bag=Bag;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
        
    return false;
}

bool AI_AI::SetCommunicator(TrainerComm* Communicator)
{
    try
    {
        this->Communicator=Communicator;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
        
    return false;
}

    bool AI_AI::SetTiles(vector<char> *AI_Tiles)
    {
        try
        {
                 this->AI_Tiles=AI_Tiles;
                 return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    return false;

    }

    bool AI_AI::SetBoard(Board* MyBoard)
    {
        try
        {
                 this->MyBoard=MyBoard;
                 return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    return false;

    }
bool AI_AI::IsEmptyBoard()
{
    
    this->BoardStatus=&this->MyBoard->getBoardStatus();
   return this->BoardStatus->isEmpty();
}
    
Move* AI_AI::DoWork()
{     
    Move BestMove=AI_Agent->getBestMove();
    return &BestMove;
}

bool AI_AI::SetAgent()
{
    if( this->Bag==NULL || this->BoardStatus==NULL || this->Communicator==NULL || this->AI_Tiles == NULL || this->MyBoard==NULL){
        return false;
    }
    AI_Agent= new AI_MODE(*this->Bag, *AI_Tiles,this->IsEmptyBoard());
}
