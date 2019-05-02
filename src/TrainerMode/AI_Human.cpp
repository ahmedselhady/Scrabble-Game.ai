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

bool AI_Human::SetBag(unordered_map<char, int> *bag)
{
    try
    {
        this->Bag = bag;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetCommunicator(TrainerComm *communicator)
{
    try
    {
        this->Communicator = communicator;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetTiles(vector<char> *tiles)
{
    try
    {
        this->HumanTiles = tiles;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetAgent()
{
    if (this->Bag == NULL || this->BoardStatus == NULL || this->Communicator == NULL || this->HumanTiles == NULL || this->MyBoard == NULL)
    {
        return false;
    }
}

bool AI_Human::SetBoard(Board *board)
{
    try
    {
        this->MyBoard = board;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

Move *AI_Human::DoWork()
{
    //Move BestMove = AI_Agent->getBestMove();
    Move *BestMove = nullptr;
    Move *PlayerMove = nullptr;
    while (PlayerMove == nullptr)
    {
        //PlayerMove = Communicator->SendPlayerMove();
    }

    if (BestMove->moveScore > PlayerMove->moveScore)
    {
        //Communicator->ReceiveString("Bravo! But You Could Do Better..");
        //Communicator->SetReceivedPlayerMove(BestMove);
    }

    if (BestMove->moveScore < PlayerMove->moveScore)
    {
        //Communicator->ReceiveString("Marvellous! your move is better than what I thought");
    }

    if (BestMove->moveScore == PlayerMove->moveScore)
    {
        //Communicator->ReceiveString("Excellent! I Couldn't do better");
    }
    return PlayerMove;
}
