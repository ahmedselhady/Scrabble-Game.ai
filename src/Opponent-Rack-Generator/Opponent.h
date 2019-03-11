#pragma once

#include <iostream>
#include <vector>
#include <ctime>


#include "Letter.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>

using namespace std;

/*
Written by: Amr Khaled

NOTE TO DEVELOPERS:
Please Consult the document concerning the installation of the boost library.

------------------------------------------------------------------------------
NOTE:

This code takes as input a struct containing:

1- The 27 Letters of the scrabble Language.
2- Number of remaining letters of each letter. ( Remaining Letters = 100 - My rack - Ground Tiles).




*/

//Class To Generate the possible racks of the opponent:

class OpponentRack{

public:

OpponentRack();
vector<char> RackGenerator(vector<Letter>); //Function to create the Opponent rack to be used.
vector<char> GetRack(); //Getter for the rack.

//-----------------------------------------------------------//
int OpponentRack::LeftLetters(vector<Letter>);
vector<double> OpponentRack::GetProbabilities(vector<Letter>,int);
///////////////////////////////////////////////////////////////
private:

vector<char> Rack;

///////////////////////////////////////////////////////////////
};