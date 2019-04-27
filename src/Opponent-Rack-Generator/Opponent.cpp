#pragma once

#include "Opponent.h"
#include <utility>

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




//Constructor for Rack Generation of the Opponent:
OpponentRack::OpponentRack() {

}


//Function to get Number letters left: (Not in my hand and not on the board)
int OpponentRack::LeftLetters(std::vector<std::pair<char,int>> Letters) {

	//Get Number of Remaining Letters that aren't on board or in my hand:
	int Number_Of_Remaining_Letters = 0;
	for (auto Letter_Iterator : Letters) {

		Number_Of_Remaining_Letters += Letter_Iterator.second;

	}

	return Number_Of_Remaining_Letters;
}


void OpponentRack::RemoveZeroProbabilities(std::vector<std::pair<char,int>> &Copy_Letters) {

	for (auto it = begin(Copy_Letters); it != end(Copy_Letters);)
	{
		if (it->second == 0)
		{
			it = Copy_Letters.erase(it);
		}
		else
			++it;
	}
}

//Function to get probabilities of each letter:
vector<double> OpponentRack::GetProbabilities(std::vector<std::pair<char,int>>Letters, int Number_Of_Remaining_Letters) {

	vector<double> Letter_Probabilities;
	//Get Number of Remaining Letters that aren't on board or in my hand:
	for (auto Letter_Iterator : Letters) {

		//Get Probability of each letter:
		double Let_Prob = (static_cast<double>(Letter_Iterator.second)) / (static_cast<double>(Number_Of_Remaining_Letters));

		//Save the Probabilities in a vector to be used in random generator:
		Letter_Probabilities.push_back(Let_Prob);

	}

	return Letter_Probabilities;
}


std::vector<std::pair<char,int>> copy(std::unordered_map<char,int>& map){
	
	std::vector<std::pair<char,int>> vec; 

	for(auto iteratorI: map){
		vec.push_back(*new std::pair<char,int>(iteratorI.first,iteratorI.second));
	}
	return vec;
}

//Function to create the rack to be used:
vector<char> OpponentRack::RackGenerator(unordered_map<char, int> Letters) {
	OpponentRack::Rack.clear();
	//Taking a copy of letters vector:
	std::vector<std::pair<char,int>> Copy_Letters = copy(Letters);

	//-------------------------------------------------------------------------------------------------------//
	//Remove any element with prob of zero:
	OpponentRack::RemoveZeroProbabilities(Copy_Letters);
	//-------------------------------------------------------------------------------------------------------//


   //Data Members where data will be returned in.
	vector<double> Letter_Probabilities; //Vector containing probability of finding a letter in a rack.
	int Number_Of_Remaining_Letters; //Number of Remaining Letters in the Bag and Opponent Hand.

	//Get Number of Remaining Letters that aren't on board or in my hand:
	Number_Of_Remaining_Letters = OpponentRack::LeftLetters(Copy_Letters);

	//Get Probability of each character being drawn from the bag:
	Letter_Probabilities = OpponentRack::GetProbabilities(Copy_Letters, Number_Of_Remaining_Letters);


	//std::mt19937 Generator;
	std::random_device Generator;


	//Populate one rack:
	for (int i = 0; i < 7;i++) {

		//Function that Generates integers based on their different probabilities:
	    //boost::random::discrete_distribution<> Distribution(Letter_Probabilities);
		std::discrete_distribution<int> Distribution(Letter_Probabilities.begin(),Letter_Probabilities.end());

		//Distribution generates numbers from 0 --> 26:
		int Letter_Ascii = Distribution(Generator);

		//Push one randomly selected letter into the suggested opponent rack:
		//int LetterFinal = Letters[Letter_Ascii];

		if (OpponentRack::Rack.size() >= 7)
			return OpponentRack::Rack;

		if (Copy_Letters[Letter_Ascii].second > 0) {

			OpponentRack::Rack.push_back(Copy_Letters[Letter_Ascii].first);
		
			//Decrement remaining Number of all characters:
			Number_Of_Remaining_Letters--;

			//Decrement Number of remaining instances of the character:
			Copy_Letters[Letter_Ascii].second--;
		}
		else {

		 RemoveZeroProbabilities(Copy_Letters);
		
		}
		//Update New Probabilities of Letters after removing the current letter:
		Letter_Probabilities = OpponentRack::GetProbabilities(Copy_Letters, Number_Of_Remaining_Letters);


	}

	//Change the rack from int to char:



	return OpponentRack::Rack;
}


//Getter function for the suggested rack:
vector<char> OpponentRack::GetRack() {
	return OpponentRack::Rack;
}
