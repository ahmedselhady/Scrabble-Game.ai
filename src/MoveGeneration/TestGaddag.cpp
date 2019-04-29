
//Test Main:

//INCLUDES:

#include "LoadGaddag.h"
#include "MoveGenerate.h"
#include "Gaddag.h"
#include <algorithm>
#include <string>
#include "../Board/Board_and_tiles/Board_and_tiles/Tiles.h"
#include "../Board/Board_and_tiles/Board_and_tiles/BoardCommunication.h"
#include <iostream>
#include <cctype>
#include <time.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include "../SharedClasses/Options.hpp"

#define EMPTY_BOARD_TEST 1
#define REGULAR_BOARD_TEST 0
#define TEST 0
// NOTE: when printing cout use the Logger class utility function 'log'.
// Description of How Classes Work Down Below.

using namespace std;

inline Node *createGaddag()
{ // just a test function.
    LoadGaddag gaddagConstructor;
    Node *gaddagRoot = gaddagConstructor.constructGaddag();
    return gaddagRoot;
}

int main()
{
    Node *gaddagRoot;
    using namespace std::chrono;
    Move *move = new Move();
    vector<char> TestRack;
    vector<char> *rem;
    vector<char> *sorted;
    TestRack.push_back('a');
    TestRack.push_back('d');
    TestRack.push_back('p');
    TestRack.push_back('c');
    TestRack.push_back(BLANK);
    TestRack.push_back('e');
    TestRack.push_back('w');

    sorted = Options::sortRack(&TestRack);
    char onboard = 2;
    move->word = "Ae";
    move->word = onboard + move->word;
    rem = Options::unusedRackTiles(&TestRack, move);
    int y = 0;

    // string move;
    // string move2;

    // unordered_map<string,int> countStrings;

    // ifstream MoveFileT ("moves.txt");
    // ifstream Scrabes ("out.txt");

    // while (Scrabes >> move)
    // {
    //     std::transform(move.begin(), move.end(), move.begin(), std::tolower);

    //      countStrings[move]++;

    // }
    // Scrabes.close();

    // int temp3;
    // while (MoveFileT >> move)
    // {
    //     std::transform(move.begin(), move.end(), move.begin(), std::tolower);

    //      countStrings[move]++;
    //     MoveFileT>>temp3;
    //     MoveFileT>>temp3;
    //     MoveFileT>>temp3;

    // }
    // MoveFileT.close();

    // ifstream MoveFileT2 ("moves.txt");
    // while (MoveFileT2 >> move)
    // {
    //      std::transform(move.begin(), move.end(), move.begin(), std::tolower);
    //      if(countStrings[move]%2!=0){
    //          cout<<move<<endl;
    //      }
    //      MoveFileT2>>temp3;
    //      MoveFileT2>>temp3;
    //      MoveFileT2>>temp3;
    // }

    // MoveFileT2.close();

    // ifstream MoveFile ("moves.txt");
    // ifstream Scrabe ("out.txt");

    // int count = 0;
    // int temp666;

    // while (Scrabe>>move)
    // {
    //     count++ ;
    //     MoveFile.clear();
    //     MoveFile.seekg(0, ios::beg);
    //     while (MoveFile>>move2)
    //     {

    //         std::transform(move.begin(), move.end(), move.begin(), std::tolower);
    //         std::transform(move2.begin(), move2.end(), move2.begin(), std::tolower);
    //         if(move == move2){
    //             break;
    //         }
    //         MoveFile>>temp666;
    //         MoveFile>>temp666;
    //         MoveFile>>temp666;
    //     }
    //     if(move != move2){
    //         cout << count;
    //     }
    // }
    // Scrabe.close();
    // MoveFile.close();

    gaddagRoot = createGaddag(); // THIS FUCNTION ONLY USED FOR TESTING.

    //cout <<std::hex<< gaddagRoot->getNodeInfo()<< endl;
    unsigned int x = 0x000000ff;
    //cout << std::hex<< x<<endl;
    string word = "fissiparousness";
    Node *nodePtr = gaddagRoot;
    string gaddagWord = "";
    char letter;
    Node *temp;

    //    for(int index = 0 ;index<word.size();index++){
    //    	temp = gaddagRoot->findChildChar(word[index]);
    //    	cout <<temp<<endl;
    //    	if(temp == NULL){
    //    		cout<<word[index]<<endl;
    //    	}
    //    }

    //nodePtr = nodePtr->findChildChar(word[0]);
    //nodePtr = nodePtr->findChildChar(GADDAG_DELIMITER);

    BoardToGrammer *Ptr2G = new BoardToGrammer();

    vector<char> Rack;
    // Rack.push_back('e');
    // Rack.push_back(BLANK);
    // Rack.push_back('n');
    // Rack.push_back('a');
    // Rack.push_back('t');
    // Rack.push_back('r');
    // Rack.push_back('s');

    Rack.push_back('a');
    Rack.push_back('d'); ///////////////////////////////////////////////////////////////////
    Rack.push_back('p');
    Rack.push_back('c');
    Rack.push_back(BLANK);
    Rack.push_back('e');
    Rack.push_back('w');

    // Rack.push_back(BLANK);
    // Rack.push_back('a');
    // Rack.push_back('s'); ///////////////////////////////////////////////////////////////////
    // Rack.push_back('e');
    // Rack.push_back('c');

    // Rack.push_back('f');
    // Rack.push_back('g');
    // Rack.push_back('o');
    // Rack.push_back('a');
    // Rack.push_back('p');
    // Rack.push_back('e');
    // Rack.push_back('n');

    // Rack.push_back('t');
    // Rack.push_back('r');
    // Rack.push_back('q');
    // Rack.push_back('z');
    // Rack.push_back('o');
    // Rack.push_back('e');
    // Rack.push_back('s');

    // Rack.push_back('e');
    // Rack.push_back('o');
    // Rack.push_back('n');
    // Rack.push_back('a');
    // Rack.push_back('t');
    // Rack.push_back('r');
    // Rack.push_back('s');

    // Rack.push_back(BLANK);
    // Rack.push_back(BLANK);
    // Rack.push_back('n');
    // Rack.push_back('m');
    // Rack.push_back('t');
    // Rack.push_back('r');
    // Rack.push_back('s');

    WordGenerate *Gen = new WordGenerate(Ptr2G, gaddagRoot);
    Gen->countTilesRack(&Rack);

#if TEST == EMPTY_BOARD_TEST
    cout << "HERE MPTY" << endl;
    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    Gen->emptyBoardMoves();
    high_resolution_clock::time_point endTime = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(endTime - startTime);
    cout << "HERE : " << time_span.count() << endl;

#elif TEST == REGULAR_BOARD_TEST // i.e. : Contains Words.
    //TEST CASE 2:
    // Ptr2G->SetChar('B', 6, 7);
    // Ptr2G->SetChar('A', 7, 7);
    // Ptr2G->SetChar('B', 8, 7);
    // Ptr2G->SetChar('E', 9, 7);

    // Ptr2G->SetChar('A', 9, 8);
    // Ptr2G->SetChar('R', 9, 9);
    // Ptr2G->SetChar('S', 9, 10);

    // Ptr2G->SetChar('A', 6, 8);
    // Ptr2G->SetChar('L', 6, 9);
    // Ptr2G->SetChar('L', 6, 10);

    // Ptr2G->SetChar('O', 5, 10);

    // Ptr2G->SetChar('D', 7, 10);
    // Ptr2G->SetChar('O', 7, 11);
    // Ptr2G->SetChar('G', 7, 12);

    // Ptr2G->SetChar('O', 8, 12);
    // Ptr2G->SetChar('O', 9, 12);
    // Ptr2G->SetChar('D', 10, 12);

    // Ptr2G->SetChar('O', 10, 13);
    // Ptr2G->SetChar('L', 10, 14);

    //TEST CASE:1
    // Ptr2G->SetChar('B', 7, 4);
    // Ptr2G->SetChar('A', 7, 5);
    // Ptr2G->SetChar('B', 7, 6);
    // Ptr2G->SetChar('E', 7, 7);
    // // BABE

    // // EAR
    // Ptr2G->SetChar('A', 8, 7);
    // Ptr2G->SetChar('R', 9, 7);

    // //RAM
    // Ptr2G->SetChar('A', 9, 8);
    // Ptr2G->SetChar('M', 9, 9);

    // // DOM
    // Ptr2G->SetChar('O', 8, 9);
    // Ptr2G->SetChar('D', 7, 9);

    // //DAM

    // Ptr2G->SetChar('A', 7, 10);
    // Ptr2G->SetChar('M', 7, 11);

    //TEST CASE 4:

    //TEST CASE 3:
    Ptr2G->SetChar('E', 7, 2);
    Ptr2G->SetChar('Q', 7, 3);
    Ptr2G->SetChar('U', 7, 4);
    Ptr2G->SetChar('I', 7, 5);
    Ptr2G->SetChar('P', 7, 6);
    Ptr2G->SetChar('S', 7, 7);
    //    // BABE
    Ptr2G->SetChar('U', 1, 2);
    Ptr2G->SetChar('t', 2, 2);
    Ptr2G->SetChar('I', 3, 2);
    Ptr2G->SetChar('L', 4, 2);
    Ptr2G->SetChar('I', 5, 2);
    Ptr2G->SetChar('Z', 6, 2);

    Ptr2G->SetChar('L', 1, 3);
    Ptr2G->SetChar('T', 1, 4);
    Ptr2G->SetChar('R', 1, 5);
    Ptr2G->SetChar('A', 1, 6);

    Ptr2G->SetChar('S', 0, 6);
    Ptr2G->SetChar('B', 2, 6);

    Ptr2G->SetChar('U', 8, 3);
    Ptr2G->SetChar('A', 9, 3);
    Ptr2G->SetChar('L', 10, 3);
    Ptr2G->SetChar('I', 11, 3);
    Ptr2G->SetChar('T', 12, 3);
    Ptr2G->SetChar('Y', 13, 3);

    Ptr2G->SetChar('A', 4, 4);
    Ptr2G->SetChar('D', 5, 4);
    Ptr2G->SetChar('J', 6, 4);
    Ptr2G->SetChar('S', 8, 4);
    Ptr2G->SetChar('T', 9, 4);

    Ptr2G->SetChar('D', 12, 0);
    Ptr2G->SetChar('A', 12, 1);
    Ptr2G->SetChar('R', 12, 2);

    Ptr2G->SetChar('T', 9, 5);
    Ptr2G->SetChar('A', 9, 6);
    Ptr2G->SetChar('C', 9, 7);
    Ptr2G->SetChar('K', 9, 8);
    Ptr2G->SetChar('E', 9, 9);
    Ptr2G->SetChar('R', 9, 10);
    Ptr2G->SetChar('S', 9, 11);

    Ptr2G->SetChar('S', 5, 7);
    Ptr2G->SetChar('O', 6, 7);

    Ptr2G->SetChar('E', 5, 8);
    Ptr2G->SetChar('X', 5, 9);

    Ptr2G->SetChar('I', 6, 9);
    Ptr2G->SetChar('S', 7, 9);

    Ptr2G->SetChar('O', 7, 10);
    Ptr2G->SetChar('U', 7, 11);
    Ptr2G->SetChar('L', 7, 12);

    Ptr2G->SetChar('A', 5, 11);
    Ptr2G->SetChar('M', 6, 11);

    Ptr2G->SetChar('L', 5, 12);

    Ptr2G->SetChar('A', 10, 5);
    Ptr2G->SetChar('K', 11, 5);
    Ptr2G->SetChar('E', 12, 5);

    Ptr2G->SetChar('D', 12, 6);

    Ptr2G->SetChar('O', 13, 6);
    Ptr2G->SetChar('M', 14, 6);

    Ptr2G->SetChar('A', 14, 7);
    Ptr2G->SetChar('N', 14, 8);

    Ptr2G->SetChar('A', 10, 11);
    Ptr2G->SetChar('B', 11, 11);
    Ptr2G->SetChar('A', 12, 11);
    Ptr2G->SetChar('L', 13, 11);
    Ptr2G->SetChar('S', 14, 11);

    Ptr2G->SetChar('O', 14, 12);
    Ptr2G->SetChar('U', 14, 13);
    Ptr2G->SetChar('P', 14, 14);

    Ptr2G->SetChar('S', 12, 12);
    Ptr2G->SetChar('S', 12, 13);

    //TEST FOR WORD DICT CHECK :
    cout << "yahia" << (bool)Gen->checkWordDict("yahia") << endl;
    cout << "YDF" << (bool)Gen->checkWordDict("YDF") << endl;
    cout << "cat" << (bool)Gen->checkWordDict("cat") << endl;
    cout << "catz" << (bool)Gen->checkWordDict("catz") << endl;
    cout << "zcat" << (bool)Gen->checkWordDict("zcat") << endl;
    cout << "syz" << (bool)Gen->checkWordDict("syz") << endl;
    cout << "syzxxx" << (bool)Gen->checkWordDict("syzxxx") << endl;
    cout << "malpractitioner" << (bool)Gen->checkWordDict("malpractitioner") << endl;
    cout << "malpractitionerx" << (bool)Gen->checkWordDict("malpractitionerx") << endl;
    cout << "xmalpractitioner" << (bool)Gen->checkWordDict("xmalpractitioner") << endl;
    cout << "malpracvvtitioner" << (bool)Gen->checkWordDict("malpracvvtitioner") << endl;

    ///

    Ptr2G->PrintBitBoard();

    cout << "HERE" << endl;
    Gen->crosssets();
    cout << "HERE" << endl;
    Gen->printCrossSet();
    cout << "HERE" << endl;

    high_resolution_clock::time_point startTime = high_resolution_clock::now();
    Gen->generateWords();
    high_resolution_clock::time_point endTime = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(endTime - startTime);
    cout << "HERE : " << time_span.count() << endl;
#endif

    list<Move> moves = Gen->allMoves();
    cout << " DONE " << endl;
    ofstream MovesFile;
    MovesFile.open("moves.txt");

    for (std::list<Move>::iterator it = moves.begin(); it != moves.end(); it++)
    {
        MovesFile << it->word << " " << it->horizontal << " " << (int)it->startPosition.ROW << " " << (int)it->startPosition.COL << " "
                  << it->moveScore << "\n";
        if (it->word == "azo")
        {
            cout << endl
                 << it->word << endl
                 << it->horizontal << it->startPosition.ROW << it->startPosition.COL << it->moveScore;
        }
    }
    MovesFile.close();
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
