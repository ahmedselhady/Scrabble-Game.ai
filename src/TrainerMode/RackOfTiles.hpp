#pragma once

#include <unordered_map>
#include <iostream>

class RackOfTiles
{
private:
    std::unordered_map<char, int> * bag;
    int bagSize;
public:
    RackOfTiles(std::unordered_map<char, int> * Bag,int BagSize);
    ~RackOfTiles();
    bool updateBag(char tileToReduce);
    std::vector<char> RandomizeTiles(int WantedTiles);
};


