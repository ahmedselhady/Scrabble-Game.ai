#include <iostream>
#include <vector>
#include <ctime>
#include <list>
#include <unordered_map>
#include <math.h> 
#include <utility>

#include "Board/Board_and_tiles/Board_and_tiles/Board.h";
#include "Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h";
#include "Board/Board_and_tiles/Board_and_tiles/Tiles.h";
#include "Opponent-Rack-Generator/Opponent.h"
#include "../SharedClasses/MCTSearch.h"
using namespace std;


class AI_MODE {

public:

  AI_MODE(Board B,unordered_map<char,int> Tiles,unordered_map<char,int> OurRack ,list<Move> L ,int OurScore,int TheirScore,time_t t) {
         vector<char> getMyRack();
    vector<char> getOpponentRack();
    Move getBestMove();
    AI_MODE();
private:

  	vector<char> MyRack;
    vector<char> TheOpponentRack;
    Move BestMove;
	///////////////////////////////////////////////////////////////
};

Move AI_Mode_Function(Board ,unordered_map<char,int> ,unordered_map<char,int>, list<Move> ,int,int,time_t);