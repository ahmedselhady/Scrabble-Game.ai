#pragma once

#include "Opponent.h"

// The Number of Distinct Letters in scrabble is: 26 English Letters + Blank:
#define START_OF_WANTED_ASCII 49

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
int OpponentRack::LeftLetters(unordered_map<char, int> Letters) {

	//Get Number of Remaining Letters that aren't on board or in my hand:
	int Number_Of_Remaining_Letters = 0;
	for (auto Letter_Iterator : Letters) {

		Number_Of_Remaining_Letters += Letter_Iterator.second;

	}

	return Number_Of_Remaining_Letters;
}


//Function to get probabilities of each letter:
vector<double> OpponentRack::GetProbabilities(unordered_map<char, int>Letters, int Number_Of_Remaining_Letters) {

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



//Function to create the rack to be used:
vector<char> OpponentRack::RackGenerator(unordered_map<char, int> Letters) {
	OpponentRack::Rack.clear();
	//Taking a copy of letters vector:
	unordered_map<char, int> Copy_Letters = Letters;

	//Boost Library:
	//Applying Srand() but for Boost Library:
	
	boost::random_device RandomDevice;
	boost::mt19937 Generator(RandomDevice); //Mersenne Random number generator: produce unsigned int (0 -> 2^w -1)
  
   //Data Members where data will be returned in.
	vector<double> Letter_Probabilities; //Vector containing probability of finding a letter in a rack.
	int Number_Of_Remaining_Letters; //Number of Remaining Letters in the Bag and Opponent Hand.

	//Get Number of Remaining Letters that aren't on board or in my hand:
	Number_Of_Remaining_Letters = OpponentRack::LeftLetters(Letters);

	//Get Probability of each character being drawn from the bag:
	Letter_Probabilities = OpponentRack::GetProbabilities(Letters, Number_Of_Remaining_Letters);

	//Populate one rack:
	for (auto Letter_Position : Copy_Letters) {

		//Function that Generates integers based on their different probabilities:
		boost::random::discrete_distribution<> Distribution(Letter_Probabilities);

		//Position: Starts from:
		// 'a' --> '{'
		// 97  --> 123
		//Distribution generates numbers from 0 --> 26:
		int Position = Distribution(Generator) + START_OF_WANTED_ASCII;
		
		//NOTE: This IS Another Implementation.
		//int Position = Distribution(RandomDevice) + START_OF_WANTED_ASCII;

	   //Letter_Position: Holds the ascii for the generated Letter.
		char Letter_Position;

		if (Position == (123 -'0')) { //if (Position == '{'){
			Position = 35;            //Position = '#'
			Letter_Position = ((char)Position);
		}
		else {
			//Else: Put the ascii of the current letter:
			Letter_Position = ((char)Position) + '0';
		}

		//Push one randomly selected letter into the suggested opponent rack:
		int LetterFinal = Copy_Letters[Letter_Position];
		OpponentRack::Rack.push_back(Letter_Position);

		//Decrement Number of remaining instances of the character:
		Copy_Letters[Letter_Position]--;

		//Decrement remaining Number of all characters:
		Number_Of_Remaining_Letters--;

		//Update New Probabilities of Letters after removing the current letter:
		Letter_Probabilities = OpponentRack::GetProbabilities(Copy_Letters, Number_Of_Remaining_Letters);


	}

	return OpponentRack::Rack;
}


//Getter function for the suggested rack:
vector<char> OpponentRack::GetRack() {
	return OpponentRack::Rack;
}
