#include "Board.h"
#include "BoardMask.cpp"


//Constructor
Board::Board()
{
	for(int i=0;i<26;i++)// i want to create them at insertion of the letter as i dont need the whole 26 char along the game
	{
		BoardMap[(char)('A'+i)]= BoardMask(0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000);
	}
}
Board* Board::BoardInst_=nullptr;

//The Function getBoard it gets instance of the board
Board* Board::getBoard()
{

	if(BoardInst_==nullptr)
	{
		BoardInst_=new Board;
	}
	
	return (BoardInst_);
}


//The Function getNextHorizontal it will call the function from the AI module to determine the next state given the current board Horizontally
std::vector<char>& Board::getNextHorizontal(int HorizontalIndex)
{
	std::vector<char> CharVect;
	std::vector<char>* HorizontalVector = new std::vector<char>(15);
	int ResIndex=0;

	BoardMask CheckBoard;
	for (int i = (15*HorizontalIndex); i < (15 * HorizontalIndex)+15; ++i)
	{
		CheckBoard.setBit(i);
	}
	
	for (auto Instance : BoardMap) // an instance of a letter
	{

		if((Instance.second&CheckBoard).isEmpty()) 
		{
			CharVect.push_back(Instance.first);//  need to edit the position in the vector 

		}
	}
	for(int mOffsit=HorizontalIndex*15;mOffsit<(HorizontalIndex*15+15);mOffsit++)// looping on the col
	{
		for(std::size_t i=0; i<CharVect.size(); ++i) // looking on the char board that has  this bit
		{
			if(BoardMap[CharVect[i]].getBit(mOffsit))
			{
				(*HorizontalVector)[ResIndex++]=CharVect[i];
				break; 
			}
			if(i==CharVect.size()-1)// i reached the end and this offsit is not in any char board
				(*HorizontalVector)[ResIndex++]=' ';
		}
	}
	return *HorizontalVector;
}

//This Function it will call the function from the AI module to determine the next state given the current board Vertically
std::vector<char>& Board::getNextVertical(int VerticalIndex)
{
	vector<char> CharVect;
	vector<char>* VerticalVector = new std::vector<char>(15);
	int ResIndex=0;
	
	BoardMask CheckBoard;
	int dummyoffsit = VerticalIndex;
	for (int i = 0; i < 15; i++)
	{
		

		CheckBoard.setBit(dummyoffsit);
		dummyoffsit += 15;
	}
	//CheckBoard=CheckBoard >>VerticalIndex;  // as each row is difference from its next row by 1
	for (auto Instance : BoardMap) 
	{
		if((Instance.second&CheckBoard).isEmpty())
		{
			CharVect.push_back(Instance.first);

		}
	}
	int mOffsit = VerticalIndex;
	for (int i = 0;i<15;i++)// looping on the col
	{

		for(std::size_t i=0; i<CharVect.size(); ++i) // looking on the char board that has  this bit
		{
			if(BoardMap[CharVect[i]].getBit(mOffsit))
			{
				(*VerticalVector)[ResIndex++]=CharVect[i];
				break; 
			}
			if(i==CharVect.size()-1)// i reached the end and this offsit is not in any char board
				(*VerticalVector)[ResIndex++]=' ';
		}
		mOffsit += 15;
	}
	return *VerticalVector;

}

//This Function setCharPos it sets the character postion on the board
void Board::SetCharPos(char Letter,int Row,int Col)
{
	int Offsit=Row +15*Col;
	if(Offsit<0 || Offsit >(14+15*14) )
	return;
	BoardMap[Letter].setBit(Offsit);
}


//This Function calculateScore it calulates the word and letter score
int Board::calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal)
{
	return 0;
}

void Board::print()
{
	BoardMask AllCharBoard;
	for (auto Instance : BoardMap) // an instance of a letter
	{
		AllCharBoard = AllCharBoard | Instance.second;
	}
	int  mOffsit;
	for (int i = 0; i < 15; i++)
	{
		mOffsit = i;
		for (int j = 0; j < 15; j++)
		{
			
			if (AllCharBoard.getBit(mOffsit))
			{
				for (auto Instance : BoardMap) // an instance of a letter
				{
					if (Instance.second.getBit(mOffsit))
						cout << Instance.first << " ";
				}

			}
			else
			{
				cout << "0" << " ";
			}
			mOffsit += 15;
		}
		cout << "\n";
	}
}

//Destructor
Board::~Board()
{
	Board::BoardInst_ = nullptr;
}

int main(){
	return 0;
}
