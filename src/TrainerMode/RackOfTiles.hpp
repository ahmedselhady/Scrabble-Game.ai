#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include"../SharedClasses/TrainerComm.hpp"

class RackOfTiles
{
private:
    std::unordered_map<char, int> * bag;
    int bagSize;
    TrainerComm* Communicator;
public:
    RackOfTiles(std::unordered_map<char, int> * Bag,int BagSize,TrainerComm* Comm);
    ~RackOfTiles();
    bool updateBag(char tileToReduce);
    std::vector<char> RandomizeTiles(int WantedTiles);
};


