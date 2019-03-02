#include "Board.h"
#include "BoardConst.h"

#include <iostream>

using namespace std;


int main()
{
	for (int i = 0; i < 255; ++i)
	{
		if (i % 15 == 0)
			cout << endl;
		cout << getBit(WSx3, i) << " ";
	}
	int x;
	cin >> x;
	return 0;
}