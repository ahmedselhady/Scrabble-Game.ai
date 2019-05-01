#pragma once
#include "AI_Human.hpp"
AI_Human::AI_Human()
{
    this->MyBoard = NULL;
    this->HumanTiles = NULL;
    this->AI_Agent = NULL;
    this->Bag = NULL;
    this->BoardStatus = NULL;
    this->Communicator = NULL;
}

bool AI_Human::SetBag(unordered_map<char,int>* Bag)
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

bool AI_Human::SetCommunicator(TrainerComm* Communicator)
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

bool AI_Human::IsEmptyBoard()
{
    
    this->BoardStatus=&this->MyBoard->getBoardStatus();
   return this->BoardStatus->isEmpty();
}

bool AI_Human::SetTiles(vector<char>* HumanTiles)
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
  
bool AI_Human::SetAgent()
{
    if( this->Bag==NULL || this->BoardStatus==NULL || this->Communicator==NULL || this->HumanTiles == NULL || this->MyBoard==NULL){
        return false;
    }
    AI_Agent= new AI_MODE(*this->Bag, *HumanTiles,this->IsEmptyBoard());
}

bool AI_Human::SetBoard(Board* MyBoard)
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

Move* AI_Human::DoWork()
    {
        Move BestMove=AI_Agent->getBestMove();
        
        Move *PlayerMove=nullptr;
        while(PlayerMove==nullptr)
        {
            PlayerMove=Communicator->SendPlayerMove();
        }
        

        if(BestMove.moveScore>PlayerMove->moveScore)
        {
            Communicator->ReceiveString("AI Move was Better than Player Move ");
            Communicator->SetReceivedPlayerMove(&BestMove);
        }
        
        if(BestMove.moveScore<PlayerMove->moveScore)
        {
            Communicator->ReceiveString("Congratulations !!!!!!! your move is better than what I thought");
        }
        
        if(BestMove.moveScore==PlayerMove->moveScore)
        {
            Communicator->ReceiveString("Congratulations !!!!!!! your move is equal to what I thought");
        }
            return PlayerMove;
    }

