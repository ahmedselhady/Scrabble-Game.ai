#include"RackOfTiles.hpp"

RackOfTiles::RackOfTiles(std::unordered_map<char, int> * Bag,int BagSize)
{
    bag=Bag;
    bagSize=BagSize;
}

RackOfTiles::~RackOfTiles()
{
}

bool RackOfTiles::updateBag(char tileToReduce)
{
    if((*bag)[tileToReduce]>0)
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

std::vector<char> RackOfTiles:: RandomizeTiles(int WantedTiles)
{
    std::vector<char> Rack;
    int count=0; 
    int SizeOfTiles;
    if(bagSize<WantedTiles)
    {
       SizeOfTiles= bagSize;
    }
    else
    {
        SizeOfTiles=WantedTiles;
    }
    
    while(count==SizeOfTiles)
    {
        int Tile=rand() % 27;
        Tile-=97;
        if(updateBag((char)Tile))
        {
            count++;
            Rack.push_back((char)Tile);
        }  
    }
    return Rack;
}