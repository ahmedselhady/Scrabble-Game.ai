#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "BoardMask.h"
#include "BoardConst.h"
#include <unordered_map>
using namespace std;
class Board
{
private:
	unordered_map<char, BoardMask> BoardMap;
	Board();
	static Board* BoardInst_;
public:
	static Board* getBoard();
	std::vector<char>& getNextHorizontal(int HorizontalIndex);
	std::vector<char>& getNextVertical(int VerticalIndex);
	int calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal);



}

#endif