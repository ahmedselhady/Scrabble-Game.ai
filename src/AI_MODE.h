#include <iostream>
#include <vector>
#include <ctime>
#include <list>
#include "Opponent-Rack-Generator/Opponent.h"
#include <unordered_map>
#include <math.h> 
#include "SharedClasses/MCTSearch.h"
using namespace std;


class AI_MODE {

public:

    AI_MODE();
  AI_MODE(int Board,unordered_map<char,int> ,unordered_map<char,int>  ,int,int,time_t);
    vector<char> getMyRack();
    vector<char> getOpponentRack();
    Move getBestMove();
private:

	vector<char> MyRack;
    vector<char> TheOpponentRack;
    Move BestMove;
	///////////////////////////////////////////////////////////////
};