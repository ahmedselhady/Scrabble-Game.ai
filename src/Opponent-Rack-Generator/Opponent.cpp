#pragma once

#include "Opponent.h"

// The Number of Distinct Letters in scrabble is: 26 English Letters + Blank:
#define DISTINCT_SCRABBLE_LETTERS 27
 
//Number of Letters in a rack:
#define RACK_LETTERS 7

/*
Written by: Amr Khaled

NOTE TO DEVELOPERS:
Please Consult the document InstallingBoostLibrary.md concerning the installation of the boost library.

------------------------------------------------------------------------------
NOTE:

This code takes as input a class containing:

1- The 27 Letters of the scrabble Language. (26 English Letters + Blank)
2- Number of remaining letters of each letter. ( Remaining Letters = 100 - My rack - Ground Tiles).


*/




//Constructor for Rack Generation of the Opponent:
OpponentRack::OpponentRack(){

}


int OpponentRack::LeftLetters(vector<Letter>Letters){

    //Get Number of Remaining Letters that aren't on board or in my hand:
    int Number_Of_Remaining_Letters=0;
    for(int Letter_Iterator=0;Letter_Iterator<DISTINCT_SCRABBLE_LETTERS;Letter_Iterator++){
        
        Number_Of_Remaining_Letters += Letters[Letter_Iterator].Number_Of_Remaining;

    } 

    return Number_Of_Remaining_Letters;
}


vector<double> OpponentRack::GetProbabilities(vector<Letter>Letters,int Number_Of_Remaining_Letters ){

    vector<double> Letter_Probabilities;
    //Get Number of Remaining Letters that aren't on board or in my hand:
    for(int Letter_Iterator=0;Letter_Iterator<DISTINCT_SCRABBLE_LETTERS;Letter_Iterator++){
        
        double Let_Prob = Letters[Letter_Iterator].Number_Of_Remaining/Number_Of_Remaining_Letters;
        Letter_Probabilities.push_back(Let_Prob);

    }

    return Letter_Probabilities;
}



//Function to create the rack to be used:
vector<char> OpponentRack::RackGenerator(vector<Letter> Letters){ 

    //Taking a copy of letters vector:
    vector<Letter> Copy_Letters=Letters;

    //Boost Library:
    //Applying Srand() but for Boost Library:
    std::time_t now = std::time(0);
    boost::mt19937 Generator{static_cast<std::uint32_t>(now)}; //Mersenne Random number generator: produce unsigned int (0 -> 2^w -1)
   
   //Data Members where data will be returned in.
    vector<double> Letter_Probabilities; //Vector containing probability of finding a letter in a rack.
    int Number_Of_Remaining_Letters; //Number of Remaining Letters in the Bag and Opponent Hand.

    //Get Number of Remaining Letters that aren't on board or in my hand:
    Number_Of_Remaining_Letters = OpponentRack::LeftLetters(Letters);

    //Get Probability of each character being drawn from the bag:
    Letter_Probabilities = OpponentRack::GetProbabilities(Letters,Number_Of_Remaining_Letters);

    //Populate one rack:
    for(int Rack_Letter=0;Rack_Letter<RACK_LETTERS;Rack_Letter++){

     //Function that Generates integers based on their different probabilities:
     boost::random::discrete_distribution<> Distribution(Letter_Probabilities);

        int Letter_Position = Distribution(Generator);
        //Push one randomly selected letter into the suggested opponent rack:
        OpponentRack::Rack.push_back(Copy_Letters[Letter_Position].Letter_Character);
        
        //Decrement Number of remaining instances of the character:
        Copy_Letters[Letter_Position].Number_Of_Remaining--;
        
        //Decrement remaining Number of all characters:
        Number_Of_Remaining_Letters--;

        //Update New Probabilities of Letters after removing the current letter:
        Letter_Probabilities = OpponentRack::GetProbabilities(Copy_Letters,Number_Of_Remaining_Letters);

    
    }

return OpponentRack::Rack;
}


//Getter function for the suggested rack:
vector<char> OpponentRack::GetRack(){
    return OpponentRack::Rack;
}
