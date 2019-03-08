#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "BoardMask.h";
using namespace std;
class Board
{
private:
	BoardMask A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
	Board();
	static Board* BoardInst_;
public:
	static Board* getBoard();
	std::vector<char>& getNextHorizontal(int HorizontalIndex);
	std::vector<char>& getNextVertical(int VerticalIndex);
	int calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal)



};

#endif