#include "BoardConst.h"
#include <iostream>

int main() {
	BoardMask B= WordScoreMultiplyBy3 | WordScoreMultiplyBy2 | LetterScoreMultiplyBy2 | LetterScoreMultiplyBy3;
	B.print();
	system("pause");
	return 0;
}