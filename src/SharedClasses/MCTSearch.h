#pragma once

#include <math.h>
#include <cfloat>
#include <list>
#include <string>
#include <vector>
#include "MCTreeNode.h"
using namespace std;

class MCTSearch {
  // This class is the actual code implementation for the monte carlo tree
  // search
 public:
  // The Constructor will take all the possible moves from the current rack and
  // will create the root for the tree
  MCTSearch(list<Move> Moves);

  // Selection
  MCTreeNode* SelectBestMove(MCTreeNode* Parent);

  // Main Function that will do the whole search and will finally return the
  // index of best move to be played (d=2)
  int midGameMCTS();

  // Main Function that will do the whole search and will finally return the
  // index of best move to be played (d=2)
  int endGameMCTS();

  // Function to destroy the tree
  void destroyMCTree(MCTreeNode* CurrentNode);

 private:
  MCTreeNode* Root;
};
