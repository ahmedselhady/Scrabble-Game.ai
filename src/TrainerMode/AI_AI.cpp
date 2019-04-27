
#pragma once
#include "AI_AI.hpp"
AI_AI::AI_AI()
{
    AI_Agent(Bag,HumanTiles,isEmty);
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
    bool AI_AI::SetisEmtyBoard(bool isEmty)
    {
        try
        {
            this->isEmty=isEmty;
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
            
        return false;
    }

    bool AI_AI::SetTiles(vector<char> &HumanTiles)
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

    Move* AI_AI::DoWork()
    {
        
      Move* BestMove=AI_Agent.getBestMove();
       return BestMove;
    }

