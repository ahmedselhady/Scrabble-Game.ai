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

using namespace std;

inline Node* createGaddag(){ // just a test function.
	 LoadGaddag gaddagConstructor;
	 Node* gaddagRoot = gaddagConstructor.constructGaddag();
	 return gaddagRoot;
}

int main() {
	Node* gaddagRoot;


	gaddagRoot = createGaddag();

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
    nodePtr = nodePtr->findChildChar(word[0]);
    nodePtr = nodePtr->findChildChar(GADDAG_DELIMITER);

    BoardToGrammer *Ptr2G=new BoardToGrammer();

    Ptr2G->PrintBitBoard();

    vector<char> Rack;
    Rack.push_back('b');
    Rack.push_back('t');
    Rack.push_back('t');
    Rack.push_back('a');
    Rack.push_back('a');
    Rack.push_back('r');
    Rack.push_back(' ');

    if(Ptr2G->hasaTile(7,7))
    {
        cout<<endl<<"YES"<<endl;
    }
    char l = Ptr2G->getTileAtPosition(7,7);
    
    WordGenerate * Gen = new WordGenerate(Ptr2G,gaddagRoot);
    Gen->countTilesRack(&Rack); 

    #if TEST == EMPTY_BOARD_TEST
        Gen->emptyBoardMoves();
    #elif TEST == REGULAR_BOARD_TEST
        Ptr2G->SetChar('B', 7, 7);
	    Ptr2G->SetChar('O', 7, 8);
 	    Ptr2G->SetChar('Y', 7, 9);
        Gen->generateWords();
    #endif



    list<Move> moves = Gen->allMoves();
    

    for (std::list<Move>::iterator it = moves.begin(); it != moves.end(); it++)
    {
        if(it->word == "moz")
        {
            cout<<endl<<it->word<<endl;
        }
    }
    
	int movesCount = moves.size();
    //  simple test case i have a vertical word apple and 1 intersecition and 1 x3 score and x2 letter score


    for(int index = word.size()-1 ;index>=0;--index){
            nodePtr = nodePtr->findChildChar(word[index]);
            if(nodePtr == NULL){
                cout<<"Not Found Null For Letter : "<<word[index]<<endl;
                break;
            }
            letter = nodePtr->getNodeLetter();
           
            if(letter != COMPRESSED_GADDAG_DELIMITER)
            {
                        gaddagWord.push_back(letter);
                        if(nodePtr->isEndOfWord()){
                           cout<< endl<<gaddagWord<<endl;
                        }
            }
    }
    //cout << gaddagRoot->findChildChar('z')<<endl;
    cout<<endl<<l<<endl;
    system("pause");
    return 0;
}
