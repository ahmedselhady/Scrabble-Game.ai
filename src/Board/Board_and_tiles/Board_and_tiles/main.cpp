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

	// //----------------------- testing for Score:
	// BoardToGrammer *Ptr2G=new BoardToGrammer();
	// Ptr2G->SetChar('A', 0, 0);
	// Ptr2G->SetChar('P', 1, 0);
	// Ptr2G->SetChar('P', 2, 0);
	// Ptr2G->SetChar('L', 3, 0);
	// Ptr2G->SetChar('E', 4, 0);
	// Ptr2G->SetChar('C', 1, 1);//  simple test case i have a vertical word apple and 1 intersecition and 1 x3 score and x2 letter score
	// Ptr2G->PrintBitBoard();
	// vector<char> V = Ptr2G->getNextVerticalState();
	// cout<<Ptr2G->calculateScore(V, 0, false)<<"\n";
	// //...................................
	// Board*Ptr = Board::getBoard();
	// vector<char> VerticalVector;
	// //vector<char> HorizontalVector;
	// VerticalVector=Ptr->getNextHorizontal(0);
	// PrintNext(0,VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(1);
	// PrintNext(1, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(2);
	// PrintNext(2, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(3);
	// PrintNext(3, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(5);
	// PrintNext(5, VerticalVector);

	// cout << "\n---------------------------------------------------";


	// VerticalVector = Ptr->getNextVertical(0);
	// PrintNext(0, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(1);
	// PrintNext(1, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(2);
	// PrintNext(2, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(3);
	// PrintNext(3, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(5);
	// PrintNext(5, VerticalVector);
	// delete Ptr;
	// cout << "\n--------------------2nd test case-------------------------------\n";
	// //2nd TestCase Scenario
    // Ptr = Board::getBoard();
	// Ptr->SetCharPos('A', 0, 0);
	// Ptr->SetCharPos('B', 0, 1);
	// Ptr->SetCharPos('C', 1, 0);
	// Ptr->SetCharPos('D', 1, 1);
	// Ptr->SetCharPos('E', 1, 2);
	// Ptr->SetCharPos('E', 2, 2);
	// Ptr->SetCharPos('Z', 0, 13);
	// Ptr->SetCharPos('Z', 13, 0);
	// Ptr->SetCharPos('F', 5, 5);
	// Ptr->SetCharPos('F', 5, 4);
	// Ptr->SetCharPos('F', 14, 14);
	// Ptr->print();
	// //vector<char> HorizontalVector;
	// VerticalVector = Ptr->getNextHorizontal(0);
	// PrintNext(0, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(1);
	// PrintNext(1, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(2);
	// PrintNext(2, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(3);
	// PrintNext(3, VerticalVector);
	// VerticalVector = Ptr->getNextHorizontal(5);
	// PrintNext(5, VerticalVector);

	// cout << "\n---------------------------------------------------";


	// VerticalVector = Ptr->getNextVertical(0);
	// PrintNext(0, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(1);
	// PrintNext(1, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(2);
	// PrintNext(2, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(3);
	// PrintNext(3, VerticalVector);
	// VerticalVector = Ptr->getNextVertical(5);
	// PrintNext(5, VerticalVector);
	// //delete Ptr;


	//----------------------- testing for Tiles:
	BoardToGrammer b2g;
	b2g.SetChar('b',7,7);
	b2g.SetChar('o',7,8);
	b2g.SetChar('y',7,9);

	b2g.PrintBitBoard();
	Tiles* t = Tiles::getTiles();
	t->addTiles('a');
	t->addTiles('b');
	t->addTiles('c');
	t->addTiles('d');
	t->addTiles('e');
	t->addTiles('f');
	t->addTiles('g');
	t->addTiles('h');
	std::vector<char>* val = nullptr;
	val = &b2g.getNextVerticalState();
	val = &b2g.getNextVerticalState();

	val = &b2g.getTiles();

	std::cout<<b2g.hasaTile(7,7)<<std::endl;
	std::cout<<b2g.getTileAtPosition(7,7);








	return 0;
}