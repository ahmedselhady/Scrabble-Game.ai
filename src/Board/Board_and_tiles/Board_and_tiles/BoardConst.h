#ifndef BOARDConstants_H
#define BOARDConstants_H

#include "BoardMask.h"

using namespace std;

BoardMask WordScoreMultiplyBy3(0b1000000100000010000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000010000000000000100000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000001000000100000010000000000000000000000000000000);
BoardMask WordScoreMultiplyBy2(0b0000000000000000100000000000100010000000001000001000000010000000, 0b1000001000000000000000000000000000000000000000001000000000000000, 0b0000000000000000000000000010000010000000100000001000001000000000, 0b1000100000000000100000000000000000000000000000000000000000000000);
BoardMask LetterScoreMultiplyBy2(0b0001000000010000000000000000000000001010000001000000100000010000, 0b0000000000000000000000000000100010100010000010000000100000100010, 0b1000100000000000000000000000000000000100000010000001000000101000, 0b0000000000000000000001000000010000000000000000000000000000000000);
BoardMask LetterScoreMultiplyBy3(0b0000000000000000000010001000000000000000000000000000000000000000, 0b0000000000001000100010001000000000000000000000000000000000000000, 0b0000000010001000100010000000000000000000000000000000000000000000, 0b0000000010001000000000000000000000000000000000000000000000000000);

#endif