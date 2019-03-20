#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <unordered_map>

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
	int LeftLetters(std::vector<std::pair<char,int>>); //Function to get Number letters left: (Not in my hand and not on the board)
	vector<double> GetProbabilities(std::vector<std::pair<char,int>>, int); //Function to get probabilities of each letter.
	void RemoveZeroProbabilities(std::vector<std::pair<char,int>>&); // Remove all elements that have a probability of zero from the map.
	///////////////////////////////////////////////////////////////
	
private:

	vector<char> Rack;

	///////////////////////////////////////////////////////////////
};