#ifndef BOARDConstants_H
#define BOARDConstants_H

#include <iostream>
#include "BoardMask.h"

using namespace std;

typedef BoardMask Bitboard;

//000000000000000
/*
bool getBit(Bitboard byte, int position) // position in range 0-7
{
	return (byte >> position) & 0x1;
}


Bitboard Wide(Bitboard w, uint64_t x, uint64_t y, uint64_t z)
{
	Bitboard result,a;
	result |= 1ULL << 63;
	a |= result << 63;
	//result = result | w>>64;
	//result = result | x;
	//result << 64;
	//result = result | y;
	//result << 64;
	//result = result | z;
	return result;
}

Bitboard w = 0b1000000100000010000000000000000000000000000000000000000000000000;
uint64_t x = 0b0000000000000000000000000000000000000000010000000000000100000000;
uint64_t y = 0b0000000000000000000000000000000000000000000000000000000000000000;
uint64_t z = 0b000000000000000000100000010000001;
Bitboard WSx3 = Wide(w, x, y, z);
*/

#endif