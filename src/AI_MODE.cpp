#pragma once

#include "AI_MODE.h"
#include <utility>

/*
Written By: Amr Khaled

Note for Developers: 20/4/2019
- Include Board, I don't know where to find it that is why iput it as int to elemenate errors only..
- Assuming that unordered_map<char,int> Tiles contains all tiles that aren't played yet after removing our tiles.
-

*/
//Constructor for Ai_Mode:

AI_MODE::AI_MODE(int Board ,unordered_map<char,int> Tiles,unordered_map<char,int> OurRack ,int OurScore,int TheirScore,time_t t) {
        
////////////////////////////////////////////////////////////
/*To be Added:
    -Generate Moves Function here

*/
////////////////////////////////////////////////////////////        
list<Move> L;
OpponentRack OP;
AI_MODE::TheOpponentRack = OP.RackGenerator(Tiles);
int TilesLeft =0;
	for (auto Letter_Iterator : Tiles) {

		TilesLeft += Letter_Iterator.second;

	}

// Create the Monte Carlo Search Tree:
MCTSearch MonteCarlo(L);


//NOTE: I don't remember the exact number from which i should change from MidGame to EndGame so i assumed 10:
int Index = 0; //Index of best Move in Moves Lists.

//Get Game Phase:
if(TilesLeft > 10){

Index = MonteCarlo.midGameMCTS();

}else{

Index = MonteCarlo.midGameMCTS();

}

// Create iterator pointing to first element
list<Move>::iterator it = L.begin();
// Advance the iterator by n->index positions,
std::advance(it, Index);
//Assign BestMove to the n-th element in Moves List.
AI_MODE::BestMove = L.front;

// AI_MODE::MyRack = OurRack // I don't know if a function to change from unordered_map to vector was already implmeneted in another module.



}




//Getters for Private Elements: 
vector<char> AI_MODE::getMyRack(){
    return AI_MODE::MyRack;
}

vector<char> AI_MODE::getOpponentRack(){
    return AI_MODE::TheOpponentRack;
}

Move AI_MODE::getBestMove(){

    return AI_MODE::BestMove;
}
