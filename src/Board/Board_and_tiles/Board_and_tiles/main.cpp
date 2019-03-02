#include "Board.h"
#include "BoardConst.h"
#include <iostream>

using namespace std;

bool getBit(Bitboard byte, int position) // position in range 0-7
{
	return (byte >> position) & 0x1;
}

int main()
{
	
	

	Bitboard WSx3 = Wide(w, x, y, z);

	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			//cout << getBit(WSx3, j) << " ";
		}
	}
	return 0;
}