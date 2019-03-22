#pragma once

#include <vector>
#include "BoardMask.h"
#include "BoardConst.h"

#include <unordered_map>
#include <iostream>
using namespace std;
class Board
{
private:
	unordered_map<char, BoardMask> BoardMap;
	Board();
	static Board* BoardInst_;

 
public:
	static Board* getBoard();//it gets instance of the board
	
	std::vector<char>& getNextHorizontal(int HorizontalIndex);//it will call the function from the AI module to determine the next state given the current board Horizontally
	std::vector<char>& getNextVertical(int VerticalIndex);//it will call the function from the AI module to determine the next state given the current board Vertically
	void SetCharPos(char Letter,int Row,int Col);// This Func is to Set the bit for this char in board
	int calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal);//it calculates the word and letter score
	void print();
	~Board();//Destructor


};

