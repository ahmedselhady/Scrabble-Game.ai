
#ifndef GADDAG_CCP 
#define GADDAG_CCP 

//INCLUDES: 
#include <iostream>
#include <math.h>
#include <unordered_map>
#include "Gaddag.h"
using namespace std;

Node::Node(){

}

void Node::addChild(char letter ,Node* &node){

} // Adding successor.

inline bool Node::isTerminal(){
    return (nodeInfo & 0x20 == 0x20);
} // i.e. Node is last character in a valid word.

inline bool Node::getNextChild(int x){
     return (this.letter == '/');
} // i.e. Node contains EOW character.

inline char Node::getLetter(){
    return (char)(CHAR_OFFSET + nodeInfo & 0x1F);
} // Retuns the node character.
    

#endif 