
#include "../AI_MODE.hpp"


//Constructor for Ai_Mode:
inline Node* createGaddag(){ // just a test function.
	 LoadGaddag gaddagConstructor;
	 Node* gaddagRoot = gaddagConstructor.constructGaddag();
	 return gaddagRoot;
}

AI_MODE::AI_MODE(unordered_map<char,int>& Tiles, vector<char>& Rack, bool isEmpty) {

BoardToGrammer* B = new BoardToGrammer() ;
Node* gaddagRoot;
gaddagRoot = createGaddag();

	//Thread 1:
	/////////////////////////////////////////////////////
	cout << "Starting thread 1: Move generation"<<endl;
	std::future<list<Move>> MovesGenerationThread = std::async(MovesGeneration, B, Rack, gaddagRoot, isEmpty);

////////////////////////////////////////////////

	//Thread 2:
	//////////////////////////////////////////////////////////
	cout << "Starting thread 2: rack generation" << endl;
	std::future<void> RackGenerator = std::async(RackGen, Tiles, this);

/////////////////////////////////////*////////////////////////

//Thread Joining.
RackGenerator.get();
list<Move> listOfMoves = MovesGenerationThread.get();

	cout << endl;
	
	listOfMoves.sort([](const Move & a, const Move & b) { return a.moveScore > b.moveScore; });

if(listOfMoves.size() > 23){

    listOfMoves.resize(23);

	}

	/////////////////////////////////////////////////////////////////////
	int TilesLeft = 0;


	for (auto Letter_Iterator : Tiles) {

		TilesLeft += Letter_Iterator.second;

	}
	cout << "List of Moves Arr:";
	for (auto tryIt: listOfMoves) {
		cout << "Word: " << tryIt.word << " Score:" << tryIt.moveScore << endl;
	}

	/*
	// Create the Monte Carlo Search Tree:
	cout << "Entering Monte Carlo!"<<endl;
	MCTSearch MonteCarlo(listOfMoves);

	int Index = 0; //Index of best Move in Moves Lists.

	//Get Game Phase:
	if (TilesLeft > 9) {

int Index = 0; //Index of best Move in Moves Lists.

//Get Game Phase:
if(TilesLeft > 9){

Index = MonteCarlo.midGameMCTS();

}else{

Index = MonteCarlo.endGameMCTS();

	if (Index != -1) {
		std::advance(it, Index);
		//Assign BestMove to the n-th element in Moves List.
		AI_MODE::BestMove = listOfMoves.front();
	}
	else {
		Move DummyMove;
		DummyMove.moveScore = -1;
		AI_MODE::BestMove = DummyMove;
	}
	*/

	AI_MODE::BestMove = listOfMoves.front();




}


//Getters for Private Elements: 

vector<char> AI_MODE::getOpponentRack(){
    return AI_MODE::TheOpponentRack;
}

Move AI_MODE::getBestMove(){

    return AI_MODE::BestMove;
}


 void AI_MODE::setOpponentRack(vector<char>R){

        AI_MODE::TheOpponentRack = R;
 }



Move AI_Mode_Function(unordered_map<char,int>& Tiles, vector<char>& Rack, bool isEmpty){
    
    AI_MODE* AI = new AI_MODE(Tiles,Rack,isEmpty);
    return AI->getBestMove();
}


void RackGen(unordered_map<char,int>& Tiles, AI_MODE* AI) {
    OpponentRack OP;
    AI->setOpponentRack(OP.RackGenerator(Tiles));
}


list <Move> MovesGeneration (BoardToGrammer* B , vector<char>& Rack, Node* gaddagRoot, bool isEmpty)
{
    WordGenerate * Gen = new WordGenerate(B,gaddagRoot);

	Gen->countTilesRack(&Rack); 

    if(isEmpty){
        cout<< "Empty board"<<endl;
    Gen->emptyBoardMoves();
    }else{
		cout << "Non-Empty board" << endl;
    Gen->crosssets(); // Gen->Updatecrosssets();
    Gen->generateWords();
    }


return Gen->allMoves();

}