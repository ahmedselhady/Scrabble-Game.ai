#include "RackOfTiles.hpp"

RackOfTiles::RackOfTiles(std::unordered_map<char, int> *Bag, int BagSize, TrainerComm *Comm)
{
    bag = Bag;
    bagSize = BagSize;
    this->Communicator = Comm;
}

RackOfTiles::~RackOfTiles()
{
}

bool RackOfTiles::updateBag(char tileToReduce)
{
    if ((*bag)[tileToReduce] > 0)
    {
        try
        {
            (*bag)[tileToReduce] -= 1;
            --bagSize;
            return true;
        }
        catch (const std::exception &e)
        {
            // ! how on earth did you place a non alphabet character!
            std::cout << e.what() << std::endl;
            return false;
        }
    }
    else
    {
        return false;
    }
}

std::vector<char> RackOfTiles::RandomizeTiles(int WantedTiles)
{

    srand(time(NULL));
    std::vector<char> Rack;
    int count = 0;
    int SizeOfTiles;
    if (bagSize < WantedTiles)
    {
        SizeOfTiles = bagSize;
    }
    else
    {
        SizeOfTiles = WantedTiles;
    }

    while (count != SizeOfTiles)
    {
        int Tile = rand() % 27;
        Tile += 'a';
        string SendRack;
        if (updateBag((char)Tile))
        {
            count++;
            Rack.push_back((char)Tile);
            SendRack += (char)Tile;
        }
    }
    //Communicator->ReceiveRackString(SendRack);
    return Rack;
}