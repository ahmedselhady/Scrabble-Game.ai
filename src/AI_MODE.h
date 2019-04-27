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
#include "SharedClasses/MCTSearch.h"
#include "../src/MoveGeneration/LoadGaddag.h"
#include "../src/MoveGeneration/MoveGenerate.h"
#include "../src/MoveGeneration/Gaddag.h"
#include <algorithm>
#include <string> 
#include "../src/Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "../src/Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include <iostream>
#include <cctype>

using namespace std;


class AI_MODE {

public:

    AI_MODE(BoardToGrammer* ,unordered_map<char,int>, vector<char>&);
    vector<char> getMyRack();
    vector<char> getOpponentRack();
    Move getBestMove();
private:

  	vector<char> MyRack;
    vector<char> TheOpponentRack;
    Move BestMove;
	///////////////////////////////////////////////////////////////
};

Move AI_Mode_Function(BoardToGrammer* B,unordered_map<char,int> Tiles, vector<char>& Rack);