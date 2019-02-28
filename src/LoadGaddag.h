/*
   ScrabbleGame.ai -- Crossword artificial intelligence game
   Copyright (C) 2018-2019 MI Team.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 */

#ifndef GADDAG_H 
#define GADDAG_H 

//INCLUDES: 
#include <unordered_map>
#include<bitset>
using namespace std;

#define CHAR_OFFSET 90 // 'a' character is 97 so starting from 7
class LoadNode {
    /* Contains a letter and pointers to successor letters
     to construct the whole GADDAG Tree.*/
    private:
        char letter;
        unordered_map<char,LoadNode*> childeren;
        bool isTerminal;
        bool isLastChar;

    public:

        Node(char letter); //Init.
        void addChild(char letter ,Node* &node); // Adding successor.
        char getLetter(); // Retuns the node character.
        bool isTerminal(); // i.e. Node is last character in a valid word.
        bool isEndOfWord(); // i.e. Node contains EOW character.
        Node* getNextChild(char letter); // Gets successor which holds with given character.

};

#endif 