#include "Board.h"

Board::Board()
{
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
	CheckBoard=CheckBoard <<15*HorizontalIndex; // shift 15 in  each column 
	if((A&CheckBoard).isEmpty())
	{
		CharVect.push_back('A');
	}
	if((B&CheckBoard).isEmpty())
	{
		CharVect.push_back('B');
	}
	if((C&CheckBoard).isEmpty())
	{
		CharVect.push_back('C');
	}
	if((D&CheckBoard).isEmpty())
	{
		CharVect.push_back('D');
	}
	if((E&CheckBoard).isEmpty())
	{
		CharVect.push_back('E');
	}

	if((F&CheckBoard).isEmpty())
	{
		CharVect.push_back('F');
	}
	if((G&CheckBoard).isEmpty())
	{
		CharVect.push_back('G');
	}
	if((H&CheckBoard).isEmpty())
	{
		CharVect.push_back('H');
	}
	if((I&CheckBoard).isEmpty())
	{
		CharVect.push_back('I');
	}
	if((J&CheckBoard).isEmpty())
	{
		CharVect.push_back('J');
	}
	if((K&CheckBoard).isEmpty())
	{
		CharVect.push_back('K');
	}
	if((L&CheckBoard).isEmpty())
	{
		CharVect.push_back('L');
	}
	if((M&CheckBoard).isEmpty())
	{
		CharVect.push_back('M');
	}
	if((N&CheckBoard).isEmpty())
	{
		CharVect.push_back('N');
	}
	if((O&CheckBoard).isEmpty())
	{
		CharVect.push_back('O');
	}
	if((P&CheckBoard).isEmpty())
	{
		CharVect.push_back('P');
	}
	if((Q&CheckBoard).isEmpty())
	{
		CharVect.push_back('Q');
	}
	if((R&CheckBoard).isEmpty())
	{
		CharVect.push_back('R');
	}
	if((S&CheckBoard).isEmpty())
	{
		CharVect.push_back('S');
	}
	if((T&CheckBoard).isEmpty())
	{
		CharVect.push_back('T');

	}
	if((U&CheckBoard).isEmpty())
	{
		CharVect.push_back('U');
	}

	if((V&CheckBoard).isEmpty())
	{
		CharVect.push_back('V');

	}
	if((W&CheckBoard).isEmpty())
	{
		CharVect.push_back('W');

	}
	if((X&CheckBoard).isEmpty())
	{
		CharVect.push_back('X');
	}
	if((Y&CheckBoard).isEmpty())
	{
		CharVect.push_back('Y');
	}
	if((Z&CheckBoard).isEmpty())
	{
		CharVect.push_back('Z');
	}
	return CharVect;
}
std::vector<char>& Board::getNextVertical(int VerticalIndex)
{
	vector<char> CharVect;

	BoardMask CheckBoard(0b0001000000000000001000000000000001000000000000001000000000000001,0b0000000100000000000000100000000000000100000000000000100000000000, 0b0000000000010000000000000010000000000000010000000000000010000000, 0b0000000000000001000000000000001000000000000001000000000000001000);
	CheckBoard=CheckBoard >>VerticalIndex;
	if((A&CheckBoard).isEmpty())
	{
		CharVect.push_back('A');
	}
	if((B&CheckBoard).isEmpty())
	{
		CharVect.push_back('B');
	}
	if((C&CheckBoard).isEmpty())
	{
		CharVect.push_back('C');
	}
	if((D&CheckBoard).isEmpty())
	{
		CharVect.push_back('D');
	}
	if((E&CheckBoard).isEmpty())
	{
		CharVect.push_back('E');
	}

	if((F&CheckBoard).isEmpty())
	{
		CharVect.push_back('F');
	}
	if((G&CheckBoard).isEmpty())
	{
		CharVect.push_back('G');
	}
	if((H&CheckBoard).isEmpty())
	{
		CharVect.push_back('H');
	}
	if((I&CheckBoard).isEmpty())
	{
		CharVect.push_back('I');
	}
	if((J&CheckBoard).isEmpty())
	{
		CharVect.push_back('J');
	}
	if((K&CheckBoard).isEmpty())
	{
		CharVect.push_back('K');
	}
	if((L&CheckBoard).isEmpty())
	{
		CharVect.push_back('L');
	}
	if((M&CheckBoard).isEmpty())
	{
		CharVect.push_back('M');
	}
	if((N&CheckBoard).isEmpty())
	{
		CharVect.push_back('N');
	}
	if((O&CheckBoard).isEmpty())
	{
		CharVect.push_back('O');
	}
	if((P&CheckBoard).isEmpty())
	{
		CharVect.push_back('P');
	}
	if((Q&CheckBoard).isEmpty())
	{
		CharVect.push_back('Q');
	}
	if((R&CheckBoard).isEmpty())
	{
		CharVect.push_back('R');
	}
	if((S&CheckBoard).isEmpty())
	{
		CharVect.push_back('S');
	}
	if((T&CheckBoard).isEmpty())
	{
		CharVect.push_back('T');

	}
	if((U&CheckBoard).isEmpty())
	{
		CharVect.push_back('U');
	}

	if((V&CheckBoard).isEmpty())
	{
		CharVect.push_back('V');

	}
	if((W&CheckBoard).isEmpty())
	{
		CharVect.push_back('W');

	}
	if((X&CheckBoard).isEmpty())
	{
		CharVect.push_back('X');
	}
	if((Y&CheckBoard).isEmpty())
	{
		CharVect.push_back('Y');
	}
	if((Z&CheckBoard).isEmpty())
	{
		CharVect.push_back('Z');
	}
	return CharVect;

}