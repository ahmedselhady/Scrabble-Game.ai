
#pragma once
#include <vector>
#include "Move.hpp"
#include "../MoveGeneration/MoveGenerate.h"

// This class acts as utility class functions for anyone who want to use ... add any like the bellow functions.
class Options
{
public:
    static std::vector<char> *unusedRackTiles(std::vector<char> *Rack, Move *move); // Returns unusedTile in a rack given a move.
    static std::vector<char> *sortRack(std::vector<char> *Rack);                    // Returns Alphabetic Sorted Rack.
    static bool isVowel(char *letter);                                              // Returns if the given letter is vowel.
    //
private:
    Options();
};