#pragma once

#include "AI_MODE.h"

/*
Written By: Amr Khaled

Note for Developers: 20/4/2019

- Include Board, I don't know where to find it that is why iput it as int to elemenate errors only..
- Assuming that unordered_map<char,int> Tiles contains all tiles that aren't played yet after removing our tiles.
-

*/
//Constructor for Ai_Mode:

AI_MODE::AI_MODE(Board B,unordered_map<char,int> Tiles,unordered_map<char,int> OurRack ,list<Move> L ,int OurScore,int TheirScore,time_t t) {
        
OpponentRack OP;
AI_MODE::TheOpponentRack = OP.RackGenerator(Tiles);
int TilesLeft =0;
	for (auto Letter_Iterator : Tiles) {

		TilesLeft += Letter_Iterator.second;

	}

// Create the Monte Carlo Search Tree:
MCTSearch MonteCarlo(L);

int Index = 0; //Index of best Move in Moves Lists.

//Get Game Phase:
if(TilesLeft > 9){

Index = MonteCarlo.midGameMCTS();

}else{

Index = MonteCarlo.endGameMCTS();

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



Move AI_Mode_Function(Board B,unordered_map<char,int> Tiles,unordered_map<char,int> OurRack ,list<Move> L ,int OurScore,int TheirScore,time_t t){
    
    AI_MODE* AI = new AI_MODE(B,Tiles,OurRack,L,OurScore,TheirScore,t);
    Move M = AI->getBestMove();
    return M;
}
