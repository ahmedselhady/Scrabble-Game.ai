
//INCLUDES:

#include <iostream>
#include <math.h>
#include <unordered_map>
#include "Gaddag.h"
#include "LoadGaddag.h"
using namespace std;

Node::Node(){
    //nothing
	nodeInfo = 0;
}

Node* Node::findChildChar(char letter){
    Node*child = getFirstChild();
    cout<<std::hex<<this<<endl;
    while(!child->isLastChild())
    {
    	cout<<std::hex<<this<<endl;
    	char temp = child->getNodeLetter();
        if(temp == letter){return child;}
        child = child->getNextChild();
    }

    return NULL; // not found.
} // given a letter it finds the child (domain of search only in this parent's childs) with this specific letter returns NULL if not found.

inline Node* Node::getFirstChild(){
    int addressCastOffset = (nodeInfo & 0x00FFFFFF);
    return addressCastOffset != 0 ? this + (addressCastOffset) : 0;
} // Gets first childs uncompressed.

inline bool Node::isLastChild(){
    return ((nodeInfo & 0x40000000) == 0x40000000);
} // i.e. Node is last character in a valid word.

inline Node* Node::getNextChild(){
    if (!isLastChild()){
        return this + 1;
    }
    else {return 0;}
} // Gets a successor in parent's childs.

inline char Node::getNodeLetter(){
    if(((nodeInfo>>24) & 0x1F) ==  COMPRESSED_GADDAG_DELIMITER){
        return GADDAG_DELIMITER;
    }
    return (char)(CHAR_OFFSET + ((nodeInfo>>24) & 0x1F));
} // Retuns the node character.

int Node :: getNodeInfo(){
	return nodeInfo;
}// returns node info.

inline bool Node::isEndOfWord(){
    return ((nodeInfo & 0x20000000) == 0x20000000);
 } // i.e. Node is EOW .. end of word means a word or sub-word has been reached.

