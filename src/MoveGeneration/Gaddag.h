
#ifndef GADDAG_H
#define GADDAG_H

//INCLUDES:

#include <unordered_map>
#include<bitset>
using namespace std;

#define CHAR_OFFSET 96 // 'a' character is 97 so starting from 1
class Node {
    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
    private:
        unsigned int nodeInfo; /* Contains:
                                1 - "Letter Number" from 7 -> 31 a mapping only.
                                2 -  A last char state or not 0 -> Not, 1 -> Yes.
                                3 -  Succesive child nodes if
                                EX: 000101010 this is a char: 'k' and it is a last character.
                                */

    public:

        Node(); //Init.
        Node* getFirstChild(); // Gets first childs uncompressed.
        Node* findChildChar(char letter); // given a letter it finds the child with this specific letter returns NULL if not found.
        char getNodeLetter(); // Retuns the node character.
        bool isLastChild(); // i.e. Node is last character in a valid word.
        bool isEndOfWord(); // i.e. Node contains EOW character.
        Node* getNextChild(); // Gets a successor in parents childs.
        int getNodeInfo(); // returns node info.
};

#endif
