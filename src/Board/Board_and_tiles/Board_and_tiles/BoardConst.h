#pragma once
#include "uint256_t-master\uint256_t.h"
typedef uint256_t Bitboard;
//000000000000000
Bitboard w = 0b1000000100000010000000000000000000000000000000000000000000000000;
Bitboard x = 0b0000000000000000000000000000000000000000010000000000000100000000;
Bitboard y = 0b0000000000000000000000000000000000000000000000000000000000000000;
Bitboard z = 0b000000000000000000100000010000001;
Bitboard Wide(Bitboard w, Bitboard x, Bitboard y, Bitboard z)
{
	Bitboard result;
	result = w;
	result << 64;
	result = result | x;
	result << 64;
	result = result | y;
	result << 64;
	result = result | z;
	return result;
}


//Bitboard x = 0b10000000000000;

//const Bitboard WSx3 = 0b;*/