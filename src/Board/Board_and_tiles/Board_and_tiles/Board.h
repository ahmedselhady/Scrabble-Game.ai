#pragma once

#include "Board/Board_and_tiles/Board_and_tiles/BoardMask.h"

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Board {
 private:
  unordered_map<char, BoardMask> BoardMap;
  Board();  // Constructor
  static Board *BoardInst_;
  BoardMask AllCharBoard;

 public:
  static Board *getBoard();    // it gets instance of the board
  BoardMask getBoardStatus();  // it returns all charcters in board
  char getCharByOffsit(
      int offsit);  // it gets the character whose offset is given
  std::vector<char> &getNextHorizontal(
      int HorizontalIndex);  // it will call the function from the AI module to
                             // determine the next state given the current board
                             // Horizontally
  std::vector<char> &getNextVertical(
      int VerticalIndex);  // it will call the function from the AI module to
                           // determine the next state given the current board
                           // Vertically
  void SetCharPos(
      char Letter, int Row,
      int Col);  // This Func is to Set the bit for this char in board
  int calculateScore(
      int offsit, bool horizontal,
      char intersectionLetter);  // it calculates the word and letter score
  void print();
  ~Board();  // Destructor
};
