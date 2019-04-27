#include <iostream>
#include <vector>
#include <ctime>
#include <list>
#include <unordered_map>
#include <math.h> 
#include <utility>
#include <future>

#include "Board/Board_and_tiles/Board_and_tiles/Board.hpp"
#include "Board/Board_and_tiles/Board_and_tiles/Tiles.hpp"
#include "Opponent-Rack-Generator/Opponent.h"
#include "SharedClasses/MCTSearch.hpp"
#include "../src/MoveGeneration/LoadGaddag.hpp"
#include "../src/MoveGeneration/MoveGenerate.hpp"
#include "Move.hpp"
#include "../src/MoveGeneration/Gaddag.hpp"
#include <algorithm>
#include <string> 
#include "../src/Board/Board_and_tiles/Board_and_tiles/BoardCommunication.hpp"
#include <iostream>
#include <cctype>

using namespace std;


class AI_MODE {

public:

    AI_MODE(unordered_map<char,int>&, vector<char>&, bool);
    vector<char> getOpponentRack();
    Move getBestMove();
    static void setOpponentRack(vector<char>);
	
private:

  static  vector<char> TheOpponentRack;
 
  Move BestMove;
	///////////////////////////////////////////////////////////////
};

//Functions outside the class:

Move AI_Mode_Function(unordered_map<char,int>& Tiles, vector<char>& Rack, bool);

//Thread 1: Moves Generation:
list <Move> MovesGeneration (BoardToGrammer* B , vector<char>& Rack, Node*,bool );

//Thread 2: Rack Generation:
void RackGen(unordered_map<char,int>& Tiles);