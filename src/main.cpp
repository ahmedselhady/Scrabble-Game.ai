<<<<<<< HEAD
//#include "./SharedClasses/TrainerComm.hpp"
//
//void main()
//{
//	TrainerComm Communicator;
//	while (1)
//	{
//		PossibleMoves ret = Communicator.SendAndReceiveGUI("1/2/3/4", true, true);
//		cout << ret << endl;
//	}
//
//	system("pause");
//	return;
//}

#include "./Brain.hpp"
#include "./Definitions.hpp"

int main()
{

	std::cout << "Human starts...." << std::endl;

	Board *board = Board::getBoard();

	// edeelo el tiles:
	GameBrain *brain = new GameBrain(new TrainerComm(), board, true);
	brain->work_human_vs_computer();

	system("pause");
	return 0;
}
=======
// #include "./Brain.hpp"
// #include "./Definitions.hpp"

// int main()
// {
// 	GameBrain *brain = new GameBrain();
// 	brain->work_computer_vs_computer();

// 	system("pause");
// 	return 0;
// }
>>>>>>> a3b0ccf98f9db4b067d7026ee5159f29475a9e5c
