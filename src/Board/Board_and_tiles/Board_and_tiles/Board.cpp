#include "./Board.hpp"

//Constructor
Board::Board()
{
	blankCounter = 0;
	blank_ = new int[2];
	blank_[0] = -1;
	blank_[1] = -1;
	for (int i = 0; i < 26; i++) // i want to create them at insertion of the letter as i dont need the whole 26 char along the game
	{
		BoardMap[(char)('A' + i)] = BoardMask(0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000);
	}
}

Board *Board::BoardInst_ = nullptr;

//The Function getBoard it gets instance of the board
Board *Board::getBoard()
{

	if (BoardInst_ == nullptr)
	{
		BoardInst_ = new Board;
	}

	return (BoardInst_);
}

//The Function getBoardStatus it returns all charcters in board
BoardMask Board::getBoardStatus()
{
	return AllCharBoard;
}

//The Function getCharByOffset it gets the character whose offset is given
char Board::getCharByOffsit(int offsit)
{
	for (auto Instance : BoardMap) // an instance of a letter
	{

		if (Instance.second.getBit(offsit))
		{
			return Instance.first;
		}
	}
	return '*';
}

//The Function getNextHorizontal it will call the function from the AI module to determine the next state given the current board Horizontally
std::vector<char> &Board::getNextHorizontal(int HorizontalIndex)
{
	HorizontalIndex = HorizontalIndex % 15;
	std::vector<char> CharVect;
	std::vector<char> *HorizontalVector = new std::vector<char>(15, '*');
	int ResIndex = 0;
	BoardMask CheckBoard;
	int dummyoffsit = HorizontalIndex;
	for (int i = 0; i < 15; i++)
	{
		CheckBoard.setBit(dummyoffsit);
		dummyoffsit += 15;
	}
	for (auto Instance : BoardMap) // an instance of a letter
	{

		if ((Instance.second & CheckBoard).isEmpty())
		{
			CharVect.push_back(Instance.first); //  need to edit the position in the vector
		}
	}
	int mOffsit = HorizontalIndex;
	for (int j = 0; j < 15; j++) // looping on the col
	{

		for (std::size_t i = 0; i < CharVect.size(); ++i) // looking on the char board that has  this bit
		{
			if (BoardMap[CharVect[i]].getBit(mOffsit))
			{
				(*HorizontalVector)[ResIndex++] = CharVect[i];
				break;
			}
			if (i == CharVect.size() - 1)			   // i reached the end and this offsit is not in any char board
				(*HorizontalVector)[ResIndex++] = '*'; //changed this to * instead of ' '
		}
		mOffsit += 15;
	}
	return *HorizontalVector;
}

//This Function it will call the function from the AI module to determine the next state given the current board Vertically
std::vector<char> &Board::getNextVertical(int VerticalIndex)
{
	VerticalIndex = VerticalIndex % 15;
	vector<char> CharVect;
	vector<char> *VerticalVector = new std::vector<char>(15, '*');
	int ResIndex = 0;
	BoardMask CheckBoard;
	for (int i = (15 * VerticalIndex); i < (15 * VerticalIndex) + 15; ++i)
	{
		CheckBoard.setBit(i);
	}
	for (auto Instance : BoardMap)
	{
		if ((Instance.second & CheckBoard).isEmpty())
		{
			CharVect.push_back(Instance.first);
		}
	}
	for (int mOffsit = VerticalIndex * 15; mOffsit < (VerticalIndex * 15 + 15); mOffsit++) // looping on the col
	{
		for (std::size_t i = 0; i < CharVect.size(); ++i) // looking on the char board that has  this bit
		{
			if (BoardMap[CharVect[i]].getBit(mOffsit))
			{
				(*VerticalVector)[ResIndex++] = CharVect[i];
				break;
			}
			if (i == CharVect.size() - 1)			 // i reached the end and this offsit is not in any char board
				(*VerticalVector)[ResIndex++] = '*'; //changed this to * instead of ' '
		}
	}
	return *VerticalVector;
}

//This Function setCharPos it sets the character postion on the board
void Board::SetCharPos(char Letter, int Row, int Col)
{
	int Offsit = Row + 15 * Col;

	if (Letter >= (65 + 32) && Letter <= (90 + 32)) //  blank
	{
		blank_[blankCounter++] = Offsit;
		Letter -= 32;
	}
	if (Offsit < 0 || Offsit > (14 + 15 * 14))
	{
		return;
	}
	BoardMap[Letter].setBit(Offsit);
	AllCharBoard.setBit(Offsit); // for all Titles
}

//This Function calculateScore it calulates the word and letter score
int Board::calculateScore(int offsit, bool horizontal, char intersectionLetter)
{

	BoardMask WordScoreMultiplyBy3(0b0000000000000000000000000000000000000000000000000100000010000001, 0b0000000010000000000000100000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000100000010000001000000000000000000);
	BoardMask WordScoreMultiplyBy2(0b0000000100000001000001000000000100010000000000010000000000000000, 0b0000000000000001000000000000000000000000000000000000000001000001, 0b0000000001000001000000010000000100000100000000000000000000000000, 0b0000000000000000000000000000000000000000000000010000000000010001);
	BoardMask LetterScoreMultiplyBy2(0b0000100000010000001000000101000000000000000000000000100000001000, 0b0100010000010000000100000100010100010000000000000000000000000000, 0b0001010000001000000100000010000000000000000000000000000000010001, 0b0000000000000000000000000000000000100000001000000000000000000000);
	BoardMask LetterScoreMultiplyBy3(0b0000000000000000000000000000000000000001000100000000000000000000, 0b0000000000000000000000000000000000000001000100010001000000000000, 0b0000000000000000000000000000000000000000000100010001000100000000, 0b0000000000000000000000000000000000000000000000000001000100000000);

	int mStartOffsit = offsit;
	int WordScore = 0;
	int TileValues[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; //need to add the blank
	bool Wsx3 = false;
	bool Wsx2 = false;
	int Wsx3M = 1; // multiplyer
	int Wsx2M = 1;
	if (!horizontal) // vertically
	{

		while ((AllCharBoard.getBit(mStartOffsit - 15)) && (mStartOffsit - 15) >= 0)
		{
			mStartOffsit -= 15;
		}
		while ((offsit == mStartOffsit || AllCharBoard.getBit(mStartOffsit)) && (mStartOffsit) <= 224) // the word still didnt complete
		{
			char Tile = ' ';
			char charOffsit = ' ';
			bool addBonus = false;
			bool isBlank = false;
			if (offsit == mStartOffsit)
			{
				if (!AllCharBoard.getBit(mStartOffsit))
				{
					addBonus = true;
				}
				Tile = intersectionLetter;
				if (intersectionLetter >= 65 && intersectionLetter <= 90) //  blank
				{
					isBlank = true;
					charOffsit = 'A';
				}
				else
				{
					charOffsit = 'a';
				}
			}
			else
			{
				Tile = getCharByOffsit(mStartOffsit); // get the current char
				charOffsit = 'A';
			}
			if (addBonus)
			{
				if (LetterScoreMultiplyBy2.getBit(mStartOffsit) && !isBlank)
				{
					WordScore += TileValues[Tile - charOffsit] * 2;
				}
				else if (LetterScoreMultiplyBy3.getBit(mStartOffsit) && !isBlank)
				{
					WordScore += TileValues[Tile - charOffsit] * 3;
				}
				else if (!isBlank)
				{
					WordScore += TileValues[Tile - charOffsit];
				}

				if ((WordScoreMultiplyBy2.getBit(mStartOffsit)) || (mStartOffsit == 7 + 15 * 7)) // the start square
				{
					Wsx2 = true;
					Wsx2M *= 2;
				}
				else if (WordScoreMultiplyBy3.getBit(mStartOffsit))
				{
					Wsx3 = true;
					Wsx3M *= 3;
				}
			}
			else
			{
				if (!isBlank)
				{
					bool boardblank = ((blank_[0] == mStartOffsit) || (blank_[1] == mStartOffsit)) ? true : false;
					if (!boardblank)
					{
						WordScore += TileValues[Tile - charOffsit];
					}
				}
			}

			mStartOffsit += 15;
		}
		if (Wsx2)
		{
			WordScore = WordScore * Wsx2M;
		}
		else if (Wsx3)
		{
			WordScore = WordScore * Wsx3M;
		}
		return WordScore;
	}
	else
	{

		while (AllCharBoard.getBit(mStartOffsit - 1) && (mStartOffsit - 1) >= 0) // need to add a validition if its a valid offsit or not
		{
			mStartOffsit--;
		}
		while ((offsit == mStartOffsit || AllCharBoard.getBit(mStartOffsit)) && (mStartOffsit <= 224)) // the world still didnt complete
		{
			char Tile = ' ';
			char charOffsit = ' ';
			bool addBonus = false;
			bool isBlank = false;
			if (offsit == mStartOffsit)
			{
				if (!AllCharBoard.getBit(mStartOffsit))
				{
					addBonus = true;
				}
				Tile = intersectionLetter;
				if (intersectionLetter >= 65 && intersectionLetter <= 90) //  blank
				{
					isBlank = true;
					charOffsit = 'A';
				}
				else
				{
					charOffsit = 'a';
				}
			}
			else
			{
				Tile = getCharByOffsit(mStartOffsit); // get the current char
				charOffsit = 'A';
			}

			if (addBonus)
			{

				if (LetterScoreMultiplyBy2.getBit(mStartOffsit) && !isBlank)
				{
					WordScore += TileValues[Tile - charOffsit] * 2;
				}
				else if (LetterScoreMultiplyBy3.getBit(mStartOffsit) && !isBlank)
				{
					WordScore += TileValues[Tile - charOffsit] * 3;
				}
				else if (!isBlank)
				{
					WordScore += TileValues[Tile - charOffsit];
				}

				if ((WordScoreMultiplyBy2.getBit(mStartOffsit)) || (mStartOffsit == 7 + 15 * 7)) // the start square
				{
					Wsx2 = true;
					Wsx2M *= 2;
				}
				else if (WordScoreMultiplyBy3.getBit(mStartOffsit))
				{
					Wsx3 = true;
					Wsx3M *= 3;
				}
			}
			else
			{
				if (!isBlank)
				{
					bool boardblank = ((blank_[0] == mStartOffsit) || (blank_[1] == mStartOffsit)) ? true : false;
					if (!boardblank)
					{
						WordScore += TileValues[Tile - charOffsit];
					}
				}
			}

			mStartOffsit += 1;
		}
		if (Wsx2)
		{
			WordScore = WordScore * Wsx2M;
		}
		else if (Wsx3)
		{
			WordScore = WordScore * Wsx3M;
		}
		return WordScore;
	}
}

void Board::print()
{
	for (auto Instance : BoardMap) // an instance of a letter
	{
		AllCharBoard = AllCharBoard | Instance.second;
	}
	int mOffsit;
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
				cout << "0"
					 << " ";
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

//int main(){
//	return 0;
//}
