//Test Main:


//INCLUDES:

#include "LoadGaddag.h"
#include "Gaddag.h"
#include <iostream>
#include "../SharedClasses/Logger.hpp"
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
    string word ="landlessnesses";
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

    for(int index = word.size()-1 ;index>=0;--index){
            nodePtr = nodePtr->findChildChar(word[index]);
            if(nodePtr == NULL){cout<<"null : "<<word[index]<<endl;}
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

    system("pause");
    return 0;
}
