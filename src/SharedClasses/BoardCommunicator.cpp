#include "./BoardCommunicator.hpp"
#include "../Board/Board_and_tiles/Board_and_tiles/BoardConst.h"

int BoardCommunicator::calculateScore(string suggestedMove, int row, int col,
                                      bool horizontal)

{
  // BoardMask
  // WordScoreMultiplyBy3(0b0000000000000000000000000000000000000000000000000100000010000001,
  // 0b0000000010000000000000100000000000000000000000000000000000000000,
  // 0b0000000000000000000000000000000000000000000000000000000000000000,
  // 0b0000000000000000000000000000000100000010000001000000000000000000);

  // BoardMask
  // WordScoreMultiplyBy2(0b0000000100000001000001000000000100010000000000010000000000000000,
  // 0b0000000000000001000000000000000000000000000000000000000001000001,
  // 0b0000000001000001000000010000000100000100000000000000000000000000,
  // 0b0000000000000000000000000000000000000000000000010000000000010001);

  // BoardMask
  // WordScoreMultiplyBy2(0b0000000100000001000001000000000100010000000000010000000000000000,
  // 0b0000000000000001000000000000000000000000000000000000000001000001,
  // 0b0000000001000001000000010000000100000100000000000000000000000000,
  // 0b0000000000000000000000000000000000000000000000010000000000010001);

  // BoardMask
  // LetterScoreMultiplyBy2(0b0000100000010000001000000101000000000000000000000000100000001000,
  // 0b0100010000010000000100000100010100010000000000000000000000000000,
  // 0b0001010000001000000100000010000000000000000000000000000000010001,
  // 0b0000000000000000000000000000000000100000001000000000000000000000);

  // BoardMask
  // LetterScoreMultiplyBy3(0b0000000000000000000000000000000000000001000100000000000000000000,
  // 0b0000000000000000000000000000000000000001000100010001000000000000,
  // 0b0000000000000000000000000000000000000000000100010001000100000000,
  // 0b0000000000000000000000000000000000000000000000000001000100000000);

  int intersectionScore = 0;

  int TileValues[26] = {
      1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};  // need to add the blank

  int offsit = row + col * 15;

  char charOffsit = ' ';

  bool Wsx3 = false;

  bool Wsx2 = false;

  int Wsx3M = 1;  // multiplyer

  int Wsx2M = 1;

  int WordScore = 0;

  BoardMask CurrentBoard = BoardPtr->getBoardStatus();

  int preOffsit = (horizontal) ? offsit - 1 : offsit - 15;

  int posOffsit = (horizontal) ? offsit + 1 : offsit + 15;

  int boarderCheck =
      (horizontal) ? row : col;  // above or bellow and vice versa.

  bool blank = false;

  int x;

  // if (suggestedMove == "Adaw" && col == 4 && row == 6)

  // {

  // 	x = 9;

  // 	if (true)

  // 	{

  // 	}

  // }

  // 0--25 on board
  // blank: capital
  // not blank: small


  for (std::size_t i = 0; i < suggestedMove.length(); ++i)

  {
    blank = (suggestedMove[i] >= 65 && suggestedMove[i] <= 90) ? true : false;

    charOffsit = (suggestedMove[i] >= 0 && suggestedMove[i] <= 25) ? 0 : 97;

    if ((suggestedMove[i] >= charOffsit &&
         suggestedMove[i] <= (charOffsit + 26 - 1)) ||
        blank)  // editt this coditio in case of blank

    {
      if (!blank)

      {
        if (LetterScoreMultiplyBy2.getBit(offsit) &&
            !CurrentBoard.getBit(offsit))

        {
          WordScore += TileValues[suggestedMove[i] - charOffsit] * 2;

        }

        else if (LetterScoreMultiplyBy3.getBit(offsit) &&
                 !CurrentBoard.getBit(offsit))

        {
          WordScore += TileValues[suggestedMove[i] - charOffsit] * 3;

        }

        else

        {
          WordScore += TileValues[suggestedMove[i] - charOffsit];
        }
      }

      if ((WordScoreMultiplyBy2.getBit(offsit)) &&
          !CurrentBoard.getBit(offsit))  // the start square

      {
        if (offsit == 7 + 15 * 7)

        {
          if (!CurrentBoard.getBit(7 + 15 * 7))

          {
            Wsx2 = true;

            Wsx2M *= 2;
          }

        }

        else

        {
          Wsx2 = true;

          Wsx2M *= 2;
        }

      }

      else if (WordScoreMultiplyBy3.getBit(offsit) &&
               !CurrentBoard.getBit(offsit))

      {
        Wsx3 = true;

        Wsx3M *= 3;
      }

      if (((boarderCheck > 0 && boarderCheck <= 14) &&
           CurrentBoard.getBit(preOffsit) && preOffsit >= 0 &&
           preOffsit <= 224) ||
          ((boarderCheck >= 0 && boarderCheck < 14) &&
           CurrentBoard.getBit(posOffsit) && posOffsit >= 0 &&
           preOffsit <= 224))  // there is an intersecition with other word

      {
        if (!CurrentBoard.getBit(offsit))

        {
          char offset = 0;

          if ((suggestedMove[i] >= 0 && suggestedMove[i] <= 25))

          {
            offset = 97;
          }

          intersectionScore += BoardPtr->calculateScore(
              offsit, horizontal, suggestedMove[i] + offset);
        }
      }

      blank = false;
    }

    // incremntal

    if (horizontal)  // row

    {
      offsit = offsit + 15;

      preOffsit += 15;

      posOffsit += 15;

    }

    else

    {
      offsit++;  //  move in coloum

      preOffsit++;

      posOffsit++;
    }
  }

  if (Wsx2)

  {
    WordScore = WordScore * Wsx2M;
  }

  if (Wsx3)

  {
    WordScore = WordScore * Wsx3M;
  }

  WordScore += intersectionScore;

  // whole word

  return WordScore;
}