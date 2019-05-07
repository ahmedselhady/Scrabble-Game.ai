
#include "Brain.hpp"

Node *GameBrain::_gaddagInstance = nullptr;

void GameBrain::updateBag(std::vector<char> &tilesToReduce) {
  for (int i = 0; i < (int)tilesToReduce.size(); ++i) {
    try {
      GameBrain::bag[tilesToReduce[i]] -= 1;
      --this->bagSize;
    } catch (const std::exception &e) {
      // ! how on earth did you place a non alphabet character!
      std::cout << e.what() << std::endl;
    }
  }

  GameBrain::game_phase =
      (bagSize <= 7) ? END_GAME_MODE
                     : (bagSize <= 9) ? PREEND_GAME_MODE : MID_GAME_MODE;
}

Node *GameBrain::__get_gaddag() {
  if (GameBrain::_gaddagInstance == nullptr) {
    GameBrain::_gaddagInstance = createGaddag();
  }

  return GameBrain::_gaddagInstance;
}

GameBrain::GameBrain(TrainerComm *comm, Board *MyBoard, bool whoseTurn)
{
	this->bestMove = NULL;
	this->iWantToReceive = false;
	this->returnOfReceiver = DUMMY;
    this->heuristicsLoader = new LoadHeuristics();
    this->heuristicsLoader->loadALL();

    readyToSend = false;
    this->isFuckinBitchEmpty = true;
    this->turn_TrainerMode = whoseTurn;
    this->comm = comm;
    this->MyBoard = MyBoard;
    this->heuristicsLoader = new LoadHeuristics();
    T1 = new TimerGUI(comm, 1200);
    T2 = new TimerGUI(comm, 600);
    T3 = new TimerGUI(comm, 600);
    this->bagSize = 100;

    rackoftiles = new RackOfTiles(&bag, bagSize, comm);
    MyBoard = Board::getBoard();
    game_phase = MID_GAME_MODE;
    this->ourBelovedIntelligentAgent = new AiMode();
    this->HumanTiles.reserve(7);
    this->AI_Tiles.reserve(7);

    bag['a'] = 9;
    bag['b'] = 2;
    bag['c'] = 2;
    bag['d'] = 4;
    bag['e'] = 12;
    bag['f'] = 2;
    bag['g'] = 3;
    bag['h'] = 2;
    bag['i'] = 9;
    bag['j'] = 1;
    bag['k'] = 1;
    bag['l'] = 4;
    bag['m'] = 2;
    bag['n'] = 6;
    bag['o'] = 8;
    bag['p'] = 2;
    bag['q'] = 1;
    bag['r'] = 6;
    bag['s'] = 4;
    bag['t'] = 6;
    bag['u'] = 4;
    bag['v'] = 2;
    bag['w'] = 2;
    bag['x'] = 1;
    bag['y'] = 2;
    bag['z'] = 1;
    bag[' '] = 2;
}

void GameBrain::updateBoard(Move *move)
{
    move->word = *Options::moveChar(move);

	std::cout << "Evvvvvery thing about the move: ";

    std::cout << move->word << std::endl;
	std::cout << move->horizontal << std::endl;
	std::cout << move->startPosition.ROW+'0' <<","<<	move->startPosition.COL+'0'  << std::endl;
	std::cout << move->isBingo << std::endl;
	std::cout << move->moveScore << std::endl;
	
	BoardToGrammer b2g;
    for (int i = 0, index = 0; index < move->word.length(); ++i)
    {
		// lower caps: blank
		// upper caps: letter
        if (move->horizontal)
        {
            std::cout << index << std::endl;
            if (!b2g.hasaTile(move->startPosition.ROW, move->startPosition.COL + i))
            {
				b2g.SetChar(move->word[index++] , move->startPosition.ROW, move->startPosition.COL + i);
            }
        }
        else
        {
            if (!b2g.hasaTile(move->startPosition.ROW + i, move->startPosition.COL))
            {
                b2g.SetChar(move->word[index++] - 32, move->startPosition.ROW + i, move->startPosition.COL);
            }
        }
    }

}

void GameBrain::refillTiles(std::vector<char> &tiles, Move *move)
{
    string word = *Options::moveChar(move);

    int lenghtOfMove = word.length();

    std::vector<char> temp = rackoftiles->RandomizeTiles(lenghtOfMove);
    int index = 0;

    for (int i = 0; i < tiles.size(); i++)
    {
        int p = count(word.begin(), word.end(), tiles[i]);
        if (p > 0)
        {
            char t = tiles[i];
            tiles[i] = temp[index++];
            for (int j = 0; j < word.size(); j++)
            {
                if (word[j] == t)
                {
                    word.erase(j, j + 1);
                    break;
                }
            }
        }
    }
}

std::string GameBrain::constructString(Move *move, int humanScore, int computerScore, unsigned long myTime, unsigned long opponentTime, unsigned long totalTime, std::vector<char> &humanRack, std::string messageFromTeacher)
{
	std::string stringToComm = (this->bestMove == NULL) ? "play/tm/" : "best/tm/";
	stringToComm += (this->turn_TrainerMode) ? "1/" : "0/";

    // *it's a play:
	if (move == NULL) {
		stringToComm += "1/1";
		stringToComm += "/true/";
		stringToComm += "----";
	}
	else {
		stringToComm += (std::to_string(move->startPosition.COL) + "/" + std::to_string(move->startPosition.ROW));
		stringToComm += (move->horizontal) ? "/true/" : "/false/";
		stringToComm += move->word;
	}
    

    stringToComm += ("/" + std::to_string(humanScore) + "/" + std::to_string(computerScore));
    stringToComm += ("/" + std::to_string(myTime) + "/" + std::to_string(opponentTime) + "/" + std::to_string(totalTime) + "/");

    std::string rackString = "1234567";
    for (int i = 0; i < humanRack.size(); ++i)
    {
        rackString[i] = humanRack[i];
    }
    stringToComm += (rackString + "/" + messageFromTeacher);

	// 
	if (this->bestMove != NULL) // I have correctly constructly constructed the string:
		this->bestMove = NULL;
    // *
	std::cout << stringToComm << std::endl;
    return stringToComm;
}

void GameBrain::communicatorThreadSynch()
{
	returnOfReceiver;

    while (true)
    {

        if (this->readyToSend)
        {
			returnOfReceiver=this->comm->SendAndReceiveGUI(this->sendMessage, true, true);
			if (returnOfReceiver != DUMMY) {
				this->iWantToReceive = true;
			}
			else {
				this->iWantToReceive = false;
			}
            this->readyToSend = false;
        }
        else
        {
			returnOfReceiver = this->comm->SendAndReceiveGUI("dummyText", false, true);
			if (returnOfReceiver != DUMMY) {
				this->iWantToReceive = true;
			}
			else {
				this->iWantToReceive = false;
			}
        }
    }
}

void GameBrain::work_human_vs_computer()
{
    auto thread = std::async(&GameBrain::communicatorThreadSynch, this);

    // *set board reference to both agents:
    /**
     * set board for Computer Agent
    */
    trainer.AI.SetBoard(MyBoard);
    /**
     * set board for Teacher Agent
    */
    trainer.Human.SetBoard(MyBoard);

    // *set agents' reference to bags
    /**
     * set computer agent's reference to the global bag
    */
    trainer.AI.SetBag(&bag);
    /**
     * set teacher agent's reference to the global bag
    */
    trainer.Human.SetBag(&bag);

    // *set agents' reference to the GUI communicator
    /**
     * set computer agent's reference to the communicator
    */
    trainer.AI.SetCommunicator(comm);
    /**
     * set teacher agent's reference to the global bag
    */
    trainer.Human.SetCommunicator(comm);

    // *set agents' referene to the Thinker module
    /**
     * set computer agent's reference to the Thinking Agent 
    */
    trainer.AI.SetAgent(this->ourBelovedIntelligentAgent);
    /**
     * set teacher agent's reference to the global bag
    */
    trainer.Human.SetAgent(this->ourBelovedIntelligentAgent);

    // *game mode initializations initiallizations:
    /**
     * initialize tiles of computer with 7 random tiles
    */
    AI_Tiles = rackoftiles->RandomizeTiles(7);
    /**
     * initialize tiles of human teacher with 7 random tiles
    */
    HumanTiles = rackoftiles->RandomizeTiles(7);

    // *set agent's references to the initialized tiles
    /**
     * set computer's reference to the AI tiles
    */
    trainer.AI.SetTiles(&AI_Tiles);
    /**
     * set teacher's reference to the human tiles
    */
    trainer.Human.SetTiles(&HumanTiles);

    // *initializing scores:

    int humanScore = 0, computerScore = 0;
    // Todo : start timers on separate thread;
    T1->start();
    T2->start();
    T3->start();

    // *local parameters
	int lenghtOfMove, index, penaltyOnHumanTime = 0;
    vector<char> temp(7);


    while (!IsFinished())
    {
        std::cout << "Human Score: " << humanScore << "/t/tComputer Score: " << computerScore << std::endl;
        MyBoard->print();
        std::cout << "your tiles are:\n";
        for (int i = 0; i < 7; ++i)
        {
            std::cout << HumanTiles[i] << " ";
        }
        std::cout << std::endl;

        if (turn_TrainerMode == true) // *Human Player turn
        {
            T3->stop();

            trainer.Human.SetTiles(&HumanTiles);
            // *let the thinker do the magic
            Move *move = trainer.Human.DoWork(this->isFuckinBitchEmpty, this->bagSize, this->heuristicsLoader,&returnOfReceiver,&iWantToReceive);
			
			this->bestMove = this->trainer.Human.getBestMove();
			
			if(this->bestMove != NULL){
				this->sendMessage = this->constructString(this->bestMove, humanScore, computerScore, T2->getTime(), T3->getTime(), T1->getTime(), HumanTiles, trainer.Human.getString());
				this->readyToSend = true;
			}

            if (move != nullptr)
            {
                std::cout << "EXIEDDDDDDDDDDDDD ..:" << move->word << std::endl;
                // *refill the tiles of the human player's rack
                this->refillTiles(HumanTiles, move);

                // *update the board with the human's move
                this->updateBoard(move);

                // *updating human score
				humanScore += (move->moveScore); 
					

                // final board update
                this->isFuckinBitchEmpty = (this->isFuckinBitchEmpty) ? false : false;

				this->sendMessage = this->constructString(move, humanScore , computerScore, T2->getTime(), T3->getTime(), T1->getTime(), HumanTiles, trainer.Human.getString());
				this->readyToSend = true;
            }

            T3->start();
            // !testing:

            std::cout << "game total time: ";
            T1->SendTime();
            std::cout << "Player 1 Time time: ";
            T2->SendTime();
            std::cout << "Player 2 Time time: ";
            T3->SendTime();
        }
        else // *Computer Player turn
        {
            T2->stop();
            // ! in testing only: print the board and human tiles to allow human to think
            std::cout << "computer tiles are:\n";
            for (int i = 0; i < 7; ++i)
            {
                std::cout << AI_Tiles[i] << " ";
            }
            std::cout << std::endl;

            trainer.AI.SetTiles(&AI_Tiles);
            Move *move = trainer.AI.DoWork(this->isFuckinBitchEmpty, this->bagSize, this->heuristicsLoader);

            //TODO: we have the move now but we have to send it to the GUI
            if (move != nullptr)
            {
                std::cout << "Updating Board...\n";
                // *update the board with the human's move
                this->updateBoard(move);

                // *refill the tiles of the computer player's rack
                this->refillTiles(AI_Tiles, move);
                std::cout << "Refiled Computer Tiles...\n";

                // *updating computer score
                computerScore += move->moveScore;

                this->isFuckinBitchEmpty = (this->isFuckinBitchEmpty) ? false : false;
            }
            T2->start();
            // !testing:
            std::cout << "game total time: ";
            T1->SendTime();
            std::cout << "Player 1 Time time: ";
            T2->SendTime();
            std::cout << "Player 2 Time time: ";
            T3->SendTime();

			if(T2->isOver(T2->getTime())){
				long SendTime = T2->finalendtime - T2->getTime();
				penaltyOnHumanTime = (SendTime / 60) * 10;
				penaltyOnHumanTime = (penaltyOnHumanTime < 0) ? penaltyOnHumanTime : 0;
			}
            this->sendMessage = this->constructString(move, humanScore + penaltyOnHumanTime, computerScore, T2->getTime(), T3->getTime(), T1->getTime(), HumanTiles, trainer.Human.getString());
            this->readyToSend = true;
        }
        // *reverse the turn
        turn_TrainerMode = !turn_TrainerMode;
        // *call trainer Comm to send the update:

        // ! if the human played a pass!
    }
}

void GameBrain::initialize_computer_vs_computer()
{
    auto thread = std::thread(&GameBrain::communicatorThreadSynch, this);
    thread.detach();
    // *set board reference to both agents:
    /**
     * set board for Computer Agent
    */
    trainer.AI.SetBoard(MyBoard);

    // *set agents' reference to bags
    /**
     * set computer agent's reference to the global bag
    */
    trainer.AI.SetBag(&bag);

    // *set agents' reference to the GUI communicator
    /**
     * set computer agent's reference to the communicator
    */
    trainer.AI.SetCommunicator(comm);

    // *set agents' referene to the Thinker module
    /**
     * set computer agent's reference to the Thinking Agent 
    */
    trainer.AI.SetAgent(this->ourBelovedIntelligentAgent);
}

void GameBrain::fillComputerTiles(std::vector<char>& newTiles){
    for(int i=0;i<newTiles.size();++i){
        this->AI_Tiles.push_back(newTiles[i]);
    }
}

Move* GameBrain::work_computer_vs_computer()
{

    // ! in testing only: print the board and human tiles to allow human to think
    std::cout << "computer tiles are:\n";
    for (int i = 0; i < 7; ++i)
    {
        std::cout << AI_Tiles[i] << " ";
    }
    std::cout << std::endl;

    trainer.AI.SetTiles(&AI_Tiles);
    Move *move = trainer.AI.DoWork(this->isFuckinBitchEmpty, this->bagSize, this->heuristicsLoader);

    if (move != nullptr)
    {
        std::cout << "Updating Board...\n";
        // *update the board with the human's move
        this->updateBoard(move);      
        this->isFuckinBitchEmpty = (this->isFuckinBitchEmpty) ? false : false;
    }

    //* remove the tiles used from the bag:
    std::vector<char>* temporaryRack = Options::unusedRackTiles(&AI_Tiles, move);
    AI_Tiles.clear();
    for(int i=0;i<temporaryRack->size();++i){
        AI_Tiles.push_back((*temporaryRack)[i]);
    }
    
    temporaryRack->clear();
    delete temporaryRack;

    return move;
}

bool GameBrain::IsFinished()
{
    if (this->bagSize == 0 && ((AI_Tiles.size() == 0) || (HumanTiles.size() == 0)))
    {
        return true;
    }
    else
    {
        return false;
    }
}