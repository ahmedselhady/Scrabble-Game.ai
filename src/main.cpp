#include "./Brain.hpp"
#include "./Definitions.hpp"

int main()
{

	/**
	 * teacher mode main
	std::cout << "Human starts ...." << std::endl;

	Board *board = Board::getBoard();

	// edeelo el tiles:
	GameBrain *brain = new GameBrain(new TrainerComm(), board, false);
	brain->work_human_vs_computer();

	*/

	/*
	Board* boardInstance= Board::getBoard();
	GameBrain* brainAdams = new GameBrain(new TrainerComm(),boardInstance, false);
	brainAdams->initialize_computer_vs_computer();

	//*koll marra:
	brainAdams->fillComputerTiles();
	// law kan el door 3alaya
	Move* myMove=brainAdams->work_computer_vs_computer();

	if(myMove!=NULL){ // send it to GUI

		brainAdams->sendMessage = brainAdams->constructString(myMove,opponentScore,myScore,myTime,OppenetTime,totalTime,myRack,"not applicable");
		brainAdams->readyToSend = true;

	}

	brainAdams->updateBoard(opponentMocve);
	*/
	system("pause");
	return 0;
}
