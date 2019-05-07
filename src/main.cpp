

#include "./Brain.hpp"
#include "./Definitions.hpp"

int main()
{

	std::cout << "Human starts ...." << std::endl;

	Board *board = Board::getBoard();

	// edeelo el tiles:
	GameBrain *brain = new GameBrain(new TrainerComm(), board, false);
	brain->work_human_vs_computer();

	system("pause");
	return 0;
}
