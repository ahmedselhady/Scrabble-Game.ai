
#pragma once

//INCLUDES:

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <list>
#include <string.h>
#include <string>

#include"LoadNode.hpp"
#include "Gaddag.hpp"
using namespace std;

#define GADDAG_DELIMITER '^'
#define GADDAG_ROOT '/'
#define COMPRESSED_GADDAG_DELIMITER 28
#define COMPRESSED_GADDAG_ROOT 29

class LoadGaddag { // just a static class no need to create an explicit object.

    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
    private:
        LoadNode Root; // Gaddag Root Node.

    public:

        LoadGaddag() ; //Init.
        void readDictFile(vector< string >& dictGaddagWords,const char* fileName); // reads dict. files which contains valid words given filename.
        void insertGaddagWord(string gaddagWord); // inserts a word in gaddag trie.
        Node* constructGaddag(); // builds Gaddag trie and returns compressed trie node.
        void compressGaddag(unsigned int *& gaddagRootNode,vector< LoadNode* >& gaddagNodes); // compresses the trie into an array of nodes using byte offset techinque.
};
