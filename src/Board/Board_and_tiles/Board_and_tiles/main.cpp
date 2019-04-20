#include "./Board.h"
#include "./Tiles.h"
#include "./BoardCommunication.h"
void PrintNext(int index, vector<char> X)
{
	cout << "\niam Vector of Index " << index << " => ";
		for (int i = 0; i < 15; i++)
		{
			cout << X[i]<<"/";

		}
}

int main() {

	BoardToGrammer b2g;
	b2g.SetChar('A', 0,0);
	b2g.SetChar('B',1,1);
	b2g.PrintBitBoard();

	std::cout<<b2g.hasaTile(0,0)<<" "<<b2g.getTileAtPosition(1,1)<<std::endl;
	std::cout<<b2g.hasaTile(0,1)<<" "<<b2g.getTileAtPosition(2,1)<<std::endl;



	system("pause");



	return 0;
}