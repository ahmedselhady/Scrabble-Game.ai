#include "Board.h"

Board::Board()
{
	for(int i=0;i<26;i++)
	{
		BoardMap[(char)('A'+i)]= BoardMask(0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000);
	}
}
Board* Board::BoardInst_=nullptr;
Board* Board::getBoard()
{

	if(BoardInst_==nullptr)
	{
		BoardInst_=new Board;
	}
	return (BoardInst_);
}
std::vector<char>& Board::getNextHorizontal(int HorizontalIndex)
{
	vector<char> CharVect;
	ULL CurrCol;
	BoardMask CheckBoard(0b0000000000000000000000000000000000000000000000000111111111111111, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000);
	CheckBoard=CheckBoard <<15*HorizontalIndex; // shift 15times in  each column 
	for (auto Instance : BoardMap) // an instance of a letter
	{
		if((Instance.second&CheckBoard).isEmpty()) 
		{
			CharVect.push_back(Instance.first);

		}
	}

	return CharVect;
}
std::vector<char>& Board::getNextVertical(int VerticalIndex)
{
	vector<char> CharVect;

	BoardMask CheckBoard(0b0001000000000000001000000000000001000000000000001000000000000001,0b0000000100000000000000100000000000000100000000000000100000000000, 0b0000000000010000000000000010000000000000010000000000000010000000, 0b0000000000000001000000000000001000000000000001000000000000001000);
	CheckBoard=CheckBoard >>VerticalIndex;
	for (auto Instance : BoardMap) 
	{
		if((Instance.second&CheckBoard).isEmpty())
		{
			CharVect.push_back(Instance.first);

		}
	}

	return CharVect;

}
int Board::calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal)
{

}