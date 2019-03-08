#include "Board.hpp"

int BoardCommunicator::calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal)
{

	//int WSx3[]={0,7,14,7*15,7*15+14,7*15,7*15 + 7,7*15+14};// cells that contain tripple Word
	//int WSx2[];
	//int LSx3[]
	//	int LSx2
	int Score=0;
	int TileValues[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 }; //need to add the blank
	int offsit=position;
	bool Wsx3=false;
	bool Wsx2=false;
	int Wsx3M=1;// multiplyer
	int Wsx2M=1;
	int WordScore;
	bool StartOfWord=false;

	for(std::size_t i=0; i<suggestedMove.size(); ++i) 
	{
		if(suggestedMove[i] >='A' ||  suggestedMove[i] <='Z')// editt this coditio in case of blank 
		{
			if(LetterScoreMultiplyBy2.getBit[offsit])
			{
				WordScore +=TileValues[suggestedMove[i] -'A']*2;
			}
			else if(LetterScoreMultiplyBy3.getBit[offsit])
			{
				WordScore +=TileValues[suggestedMove[i] -'A']*3;
			}
			else
			{
				WordScore +=TileValues[suggestedMove[i] -'A'];
			}
			if(WordScoreMultiplyBy2.getBit[offsit] || offsit=7+15*7)  // the start square 
			{
				Wsx2=true;
				Wsx2M*=2;
			}
			else if(WordScoreMultiplyBy3.getBit[offsit])
			{
				Wsx3=true;
				Wsx3M*=3;
			}

		}
		else// reaching an empty slot  maybe
		{// need to count after reaching here if the word of 7 tiles  Add 50points
			// end  of a word
			if(Wsx2)
			{
				Score+= WordScore*Wsx2M;
			}
			else if(Wsx3)
			{
				Score+=  WordScore*Wsx3M;
			}
			else
				Score+=WordScore;

			WordScore=0;// reset the word variables 
			Wsx2=false;
			Wsx3=false;

		}
		//incremntal  
		if (horizontal)// row 
		{
			offsit=offsit+15;
		}
		else
		{
			offsit++;//  move in coloum
		}
	} 
	return 0;
}
