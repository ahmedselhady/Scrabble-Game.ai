#pragma once
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include "../SharedClasses/Options.hpp"

#define BLANK_OFFSET ' ' // remove 5 from 32 which is the ' ' (BLANK) CHANG it if you changed the blank char
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

    double superleave(std::vector<char> *Rack);
    bool loadSyn2(const char *filename);
    bool loadWorths(const char *filename);
    bool loadVcPlace(const char *filename);

    bool loadSuperleaves(const char *filename);
    void loadALL();
    void calculateAllLeaves(); // precalculates Rack Leaves.

    int mapLetter(char letter);

    double m_syn2[27][27];
    double m_tileWorths[27];
    double m_vcPlace[8][8][128];

    typedef std::map<std::vector<char>, double> SuperLeavesMap; // preCalculated Rack leaves.
    SuperLeavesMap superLeaves;
};