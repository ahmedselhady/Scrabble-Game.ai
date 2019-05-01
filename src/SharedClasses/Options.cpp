
#include "Options.hpp"
#include <unordered_map>

static std::unordered_map<char, bool> VOWELS = {{'a', true}, {'b', false}, {'c', false}, {'d', false}, {'e', true}, {'f', false}, {'g', false}, {'h', false}, {'i', true}, {'j', false}, {'k', false}, {'l', false}, {'m', false}, {'n', false}, {'o', true}, {'p', false}, {'q', false}, {'r', false}, {'s', false}, {'t', false}, {'u', true}, {'v', false}, {'w', false}, {'x', false}, {'y', false}, {'z', false}};
Options::Options()
{ //nothing
}
bool Options::isVowel(char *letter)
{
    return VOWELS[*letter];
} // Returns Alphabetic Sorted Rack.
std::vector<char> *Options::readSuperLeave(const char *rack, unsigned int rackSize)
{
    std::vector<char> *newRack = new std::vector<char>();

    for (int index = 0; index < rackSize; ++index)
    {
        newRack->push_back(rack[index]);
    }
    return newRack;
} // Returns rack-leave read from superLeaves File.

std::vector<char> *Options::unusedRackTiles(std::vector<char> *Rack, Move *move)
{
    std::unordered_map<char, int> rackLetters;
    std::vector<char> *remainedTiles = new std::vector<char>();

    rackLetters[BLANK_OFFSET] = 0; // usedTiles from The Rack.

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
                rackLetters[BLANK_OFFSET]++; // usedTiles from The Rack.
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
std::vector<char> *Options::sortRack(std::vector<char> *Rack)
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
    while (rackLetters[BLANK_OFFSET] > 0)
    {
        sortedTiles->push_back(BLANK_OFFSET);
        rackLetters[BLANK_OFFSET]--;
    }

    return sortedTiles;
} // Returns Alphabetic Sorted Rack.

std::string Options::regularWordString(Move *move)
{
    std::string newWord = "";
    for (int index = 0; index < move->word.length(); ++index)
    {
        if (move->word[index] >= 0 && move->word[index] <= 25) // on Board char.
        {
            newWord.push_back(move->word[index] + 97);
        }
        else if ((move->word[index] >= 65 && move->word[index] <= 90))
        {
            newWord.push_back(move->word[index] + 32);
        }
        else
        {
            newWord.push_back(move->word[index]);
        }
    }
    return newWord;
} // Returns a regular and readable format of the Move string without wierd chars (ALL SMALL CHARS).

std::vector<char> *Options::moveTiles(Move *move)
{
    std::vector<char> *tiles = new std::vector<char>();
    for (int index = 0; index < move->word.length(); ++index)
    {
        if (move->word[index] >= 97 && move->word[index] <= 122)
        {
            tiles->push_back(move->word[index]);
        }
        else if ((move->word[index] >= 65 && move->word[index] <= 90))
        {
            tiles->push_back(move->word[index] + 32);
        }
    }
    return tiles;
} // Returns Move Tiles Used only.

std::vector<char> *Options::setRackGrounded(std::vector<char> *Rack)
{
    std::vector<char> *offsetTiles = new std::vector<char>();
    for (int index = 0; index < Rack->size(); ++index)
    {
        offsetTiles->push_back((*Rack)[index] - 'a');
    }

    return offsetTiles;
} // Returns Offset Chars starting from ZERO.

int Options::rackScore(std::vector<char> *Rack)
{
    int TileValues[27] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0}; // Scores
    int score = 0;
    for (int index = 0; index < Rack->size(); ++index)
    {
        if ((*Rack)[index] == ' ') //! BLANK IS SPACE  ..
        {
            score += TileValues[26];
        }
        else
        {
            score += TileValues[(*Rack)[index] - 'a'];
        }
    }
    return score;
} // Returns Rack Leave Score for Individuals Chars.

std::string *Options::moveChar(Move *move)
{
    std::string *newMove = new std::string();
    for (int index = 0; index < move->word.length(); ++index)
    {
        if ((move->word[index] >= 0 && move->word[index] <= 25)) // on Board char.
        {
            continue;
        }
        else
        {
            if ((move->word[index] >= 97 && move->word[index] <= 122))
            {
                newMove->push_back(move->word[index]);
            }
            else
            {
                newMove->push_back(move->word[index] + 32);
            }
        }
    }
    return newMove;
} // Returns actual new tile of a move that will be played.

// std::string *Options::moveChar(Move *move)
// {
//     std::string *newMove = new std::string();
//     for (int index = 0; index < move->word.length(); ++index)
//     {
//         if ((move->word[index] >= 0 && move->word[index] <= 25)) // on Board char.
//         {
//             continue;
//         }
//         else
//         {
//             if ((move->word[index] >= 97 && move->word[index] <= 122))
//             {
//                 newMove->push_back(move->word[index]);
//             }
//             else
//             {
//                 newMove->push_back(move->word[index] + 32);
//             }
//         }
//     }
//     return newMove;
// } // Returns actual new tile of a move that will be played.
