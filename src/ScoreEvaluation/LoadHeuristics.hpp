#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include "../MoveGeneration/MoveGenerate.h"
#include "../SharedClasses/Options.hpp"

#define SYNERGY "./Heuristics/Synergy"
#define VC_PLACE "./Heuristics/VCPlace"
#define WORTHS "./Heuristics/Worths"
#define SUPER_LEAVES "./Heuristics/superleaves"
#define BLANK_OFFSET BLANK - 27 + 1 // remove 5 from 32 which is the ' ' (BLANK) CHANG it if you changed the blank char
// BLANK is 26 char  starting from 0
#define NUM_LETTERS 26            // English Letters + include BLANK
#define MAX_VC_EMPTY_BOARD_MOVE 7 // beacuse I have 7 tiles + empty board max length = 7.
#define VC_PACKET 128             // For a Max 7 word move each bit represent cosseponding VC ratio.

class LoadHeuristics
{
public:
    LoadHeuristics(); // for loading 3 Heuristics : Synergy, Worths, VCplace.
    double syn2(char letter1, char letter2);
    double tileWorth(char letter);
    double vcPlace(int start, int length, int consbits);
    //double bogowin(int lead, int unseen, int blanks);
    double superleave(std::vector<char> *Rack);

protected:
    bool loadSyn2(const std::string &filename = SYNERGY);
    bool loadWorths(const std::string &filename = WORTHS);
    bool loadVcPlace(const std::string &filename = VC_PLACE);
    //bool loadBogowin(const std::string &filename = WORTHS);
    bool loadSuperleaves(const std::string &filename = SUPER_LEAVES);

    int mapLetter(char letter);

    double m_syn2[27][27];
    double m_tileWorths[27];
    double m_vcPlace[15][15][128];

    static const int m_bogowinArrayWidth = 601;
    static const int m_bogowinArrayHeight = 94;
    double m_bogowin[m_bogowinArrayWidth][m_bogowinArrayHeight];
    typedef map<std::vector<char>, double> SuperLeavesMap; // preCalculated Rack leaves.
    SuperLeavesMap superLeaves;
};