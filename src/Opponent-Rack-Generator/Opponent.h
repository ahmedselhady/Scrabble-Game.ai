#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>

#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>

using namespace std;

/*
Written by: Amr Khaled

NOTE TO DEVELOPERS:
Please Consult the document InstallingBoostLibrary.md concerning the installation of the boost library.

------------------------------------------------------------------------------
NOTE:

This code takes as input:

 -Unordered Map of Pairs containing:

	1- First: The 27 Letters of the scrabble Language. (26 English Letters + Blank)
	2- Second: Number of remaining letters of each letter. ( Remaining Letters = 100 - My rack - Ground Tiles).


*/

//Class To Generate the possible racks of the opponent:

class OpponentRack {

public:

	OpponentRack();
	vector<char> RackGenerator(unordered_map<char, int>); //Function to create the Opponent rack to be used.
	vector<char> GetRack(); //Getter for the rack.

	//-----------------------------------------------------------//
	int LeftLetters(unordered_map<char, int>); //Function to get Number letters left: (Not in my hand and not on the board)
	vector<double> GetProbabilities(unordered_map<char, int>, int); //Function to get probabilities of each letter.

	///////////////////////////////////////////////////////////////
private:

	vector<char> Rack;

	///////////////////////////////////////////////////////////////
};