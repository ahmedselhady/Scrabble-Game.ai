#pragma once

#include "../Board_and_tiles/BoardMask.h"
#include "../Board_and_tiles/BoardMask.h"
//#include "BoardConst.h"
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;
class Board
{
private:
	unordered_map<char, BoardMask> BoardMap;
	Board();
	static Board* BoardInst_;
	BoardMask AllCharBoard;

 
public:
	static Board* getBoard();
	BoardMask getBoardStatus();
	char getCharByOffsit(int offsit);
	std::vector<char>& getNextHorizontal(int HorizontalIndex);
	std::vector<char>& getNextVertical(int VerticalIndex);
	void SetCharPos(char Letter,int Row,int Col);// This Func is to Set the bit for this char in board
	int calculateScore(int offsit, bool horizontal);
	void print();
	~Board();


};

