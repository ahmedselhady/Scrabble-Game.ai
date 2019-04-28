
#include "Options.hpp"
#include <unordered_map>

Options::Options()
{ //nothing
}
std::vector<char> *Options::unusedRackTiles(std::vector<char> *Rack, Move *move)
{
    std::unordered_map<char, int> rackLetters;
    std::vector<char> *remainedTiles = new std::vector<char>();

    rackLetters[BLANK] = 0; // usedTiles from The Rack.

    for (int index = 0; index < move->word.length(); ++index)
    {
        if (move->word[index] >= 0 && move->word[index] <= 25) // on Board char.
        {
            continue;
        }
        else
        {
            if ((move->word[index] >= 97 && move->word[index] <= 122))
            {
                rackLetters[move->word[index]] = 0; // usedTiles from The Rack.
            }
        }
    }

    for (int index = 0; index < move->word.length(); ++index)
    {
        if (move->word[index] >= 0 && move->word[index] <= 25) // on Board char.
        {
            continue;
        }
        else
        {
            if (move->word[index] >= 65 && move->word[index] <= 90)
            {
                rackLetters[BLANK]++; // usedTiles from The Rack.
            }
            else
            {
                rackLetters[move->word[index]]++; // usedTiles from The Rack.
            }
        }
    }
    for (int index = 0; index < Rack->size(); ++index)
    {
        if (rackLetters[(*Rack)[index]] == 0)
        {
            remainedTiles->push_back((*Rack)[index]);
        }
        else
        {
            rackLetters[(*Rack)[index]]--;
        }
    }

    return remainedTiles;
} // Returns unusedTile in a rack given a move.
std::vector<char> *sortRack(std::vector<char> *Rack)
{
    std::vector<char> *sortedTiles = new std::vector<char>();
    std::unordered_map<char, int> rackLetters;

    for (int index = 0; index < Rack->size(); ++index)
    {
        rackLetters[(*Rack)[index]] = 0; // usedTiles from The Rack.
    }
    for (int index = 0; index < Rack->size(); ++index)
    {
        rackLetters[(*Rack)[index]]++; // usedTiles from The Rack.
    }

    int index = 97;
    while (index <= 122)
    {
        if (rackLetters[index] == 0)
        {
            index++;
        } // usedTiles from The Rack.
        else
        {
            sortedTiles->push_back(index);
            rackLetters[index]--;
        }
    }
    while (rackLetters[BLANK] > 0)
    {
        sortedTiles->push_back(BLANK);
        rackLetters[BLANK]--;
    }

    return sortedTiles;
} // Returns Alphabetic Sorted Rack.
