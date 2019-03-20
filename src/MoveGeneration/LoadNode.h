
#ifndef LOADNODE_H
#define LOADNODE_H

//INCLUDES:

#include <vector>
#include<string>
#include<string.h>
using namespace std;

class LoadNode {
    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
    private:
        char letter;
        vector<LoadNode> childeren;
        int numberChilds;
        //bool isTerminal; // last node in trie.
        bool lastChar; // to indicate if there is a subword inside another. -->> "log" and "logger".
        bool lastChild; // useful for the "NodeClass" explained in "Gaddag.h"

    public:

        LoadNode(char letter); //Init.
        int numberOfChilds(); // return number of childern.
        inline void addChild(char letter ,LoadNode &node); // Adding successor.
        void insertGaddagWord(string gaddagWord); //// inserts a word in gaddag trie.
        void storeNodes(vector< LoadNode* >& gaddagNodes); // store nodes in gaddagNodes.
        //void setTerminal(); // returns terminal state.
        inline void setLastChild();// returns last child state.
        inline void setLastChar();// returns last char state.
        char getLetter(); // Retuns the node character.
        bool isLastChild(); // i.e. Node is last child of his parent.
        //bool isTerminal(); // i.e. Node is last character in a valid word.
        bool isEndOfWord(); // i.e. Node contains EOW character (last character).
        inline int getChild(char letter); // Gets successor which holds with given character.
        bool findWord(string word);

};

#endif
