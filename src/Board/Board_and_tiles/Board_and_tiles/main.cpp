#include "BoardMask.h"
#include <iostream>

int main() {

	//BoardMask bm;
	BoardMask bm2(0,5, 5,0 );
	BoardMask bm3(0, 0, 2, 0);

	bm2 |= bm3 &=bm3;

	bm3 = bm2;
	//bm & bm2 | bm3;*/

	/*BoardMask bm;

	bm.setBit(16);
	bm.setBit(100);
	bm.setBit(160);
	bm.setBit(196);
	bm.setBit(90);

	bm.unsetBit(90);
	bm.unsetBit(100);

	std::cout << bm.getBit(160)<<" "<<bm.getBit(90)<<std::endl;
*/
	system("pause");
	return 0;
}