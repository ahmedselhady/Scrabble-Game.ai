//Test Main:


//INCLUDES:

#include "LoadGaddag.h"
#include "MoveGenerate.h"
#include "Gaddag.h"
#include "../Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "../Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include <iostream>

#define EMPTY_BOARD_TEST 1
#define REGULAR_BOARD_TEST 0
#define TEST 0

// NOTE: when printing cout use the Logger class utility function 'log'.
// Description of How Classes Work Down Below.

using namespace std;

inline Node* createGaddag(){ // just a test function.
	 LoadGaddag gaddagConstructor;
	 Node* gaddagRoot = gaddagConstructor.constructGaddag();
	 return gaddagRoot;
}

int main() {
	Node* gaddagRoot;


	gaddagRoot = createGaddag(); // THIS FUCNTION ONLY USED FOR TESTING.

    //cout <<std::hex<< gaddagRoot->getNodeInfo()<< endl;
    unsigned int x = 0x000000ff;
    //cout << std::hex<< x<<endl;
    string word ="fissiparousness";
    Node* nodePtr = gaddagRoot;
    string gaddagWord = "";
    char letter;
    Node*temp;

//    for(int index = 0 ;index<word.size();index++){
//    	temp = gaddagRoot->findChildChar(word[index]);
//    	cout <<temp<<endl;
//    	if(temp == NULL){
//    		cout<<word[index]<<endl;
//    	}
//    }

    //nodePtr = nodePtr->findChildChar(word[0]);
    //nodePtr = nodePtr->findChildChar(GADDAG_DELIMITER);

    BoardToGrammer *Ptr2G=new BoardToGrammer();

    
    vector<char> Rack;
    Rack.push_back('m');
    Rack.push_back('q');
    Rack.push_back('z');
    Rack.push_back(BLANK);
    Rack.push_back('n');
    Rack.push_back('e');
    Rack.push_back('s');
    
    WordGenerate * Gen = new WordGenerate(Ptr2G,gaddagRoot);
    Gen->countTilesRack(&Rack); 

    #if TEST == EMPTY_BOARD_TEST
        Gen->emptyBoardMoves();
    #elif TEST == REGULAR_BOARD_TEST // i.e. : Contains Words.
        Ptr2G->SetChar('B', 7, 6);
	    Ptr2G->SetChar('O', 7, 7);
 	    Ptr2G->SetChar('Y', 7, 8);

	  

       Ptr2G->PrintBitBoard();


        Gen->crosssets();
        Gen->printCrossSet();
        Gen->generateWords();
    #endif



    list<Move> moves = Gen->allMoves();
    

    for (std::list<Move>::iterator it = moves.begin(); it != moves.end(); it++)
    {
        if(it->word == "zoom")
        {
            cout<<endl<<it->word<<endl;
        }
    }
    
	int movesCount = moves.size();
    //  simple test case i have a vertical word apple and 1 intersecition and 1 x3 score and x2 letter score


    // for(int index = word.size()-1 ;index>=0;--index){
    //         nodePtr = nodePtr->findChildChar(word[index]);
    //         if(nodePtr == NULL){
    //             cout<<"Not Found Null For Letter : "<<word[index]<<endl;
    //             break;
    //         }
    //         letter = nodePtr->getNodeLetter();
           
    //         if(letter != COMPRESSED_GADDAG_DELIMITER)
    //         {
    //                     gaddagWord.push_back(letter);
    //                     if(nodePtr->isEndOfWord()){
    //                        cout<< endl<<gaddagWord<<endl;
    //                     }
    //         }
    // }
    // //cout << gaddagRoot->findChildChar('z')<<endl;
    // cout<<endl<<l<<endl;
    system("pause");
    return 0;
}

    // NOTE: The Generated Moves are From Type Move in The Struct "Move" inside "MoveGenerate.h"
/*
    How To Use The GADDAG DataStructure (DS):
        1- Create an Object From the "LoadGaddag" Class Used in The Creation of The DataStructure.
        2- Call "constructGaddag()" Function Found in "LoadGaddag" class Responsible For The Creation of DS it returns a Pointer of Type "Node*" Class which will have the address the Root of the GADDAG TREE.
        3- Now You Have The GADDAG ;) Enjoy.

    How To Use The "WordGenerate" Class Found inside "MoveGenerate.h and .cpp" Responsible for Possible Moves Given a Board State and a Rack:
        1- Create an object of from "WordGenerate" class and pass to it in the constructor the Board as "BoardToGrammer*" and the GADDAG Root Tree "Node*".
        2- To Set The DESIRED Rack For Generations, Call The Function "countTilesRack(&Rack)" and pass a "vector<char>*rackTiles" as an argument inside "WordGenerate" Class, This Sets The Rack Tiles From the Inside.
        3- You Can Also Set The (Board State) using The "setBoardState(BoardToGrammer*board)" given a "BoardToGrammer*" For Different Board State Configurations.
        4- Now You Have SET UP the Needed Environment for this Class,  NOW ITS TIME FOR MOVES !!?
        5- There Are Two Methods Depending On Board State:
                                        1- emptyBoardMoves() --> 1st State of The Board Where No one Played Any Moves.
                                        2- generateWords() --> Whereever There are WORDS on The Board.
                                        -------> Choose Wisely and Call The Appropriate One.
        7- Now After All of This you are One Step Away from Your GOAL : MOVES, Just Call "allMoves()" to Get a List of Moves.
        8- New Functionalities May Be ADDED For Better, Optimized and Fast Possible Move Generations --> STAY TUNED!!.
*/

/* TESTED :
    	1- EmptyBoard Generation. Using Different Tiles in Rack including BLANKS.
*/
