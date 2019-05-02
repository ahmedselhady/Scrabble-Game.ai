
#include "Brain.hpp"

Node *GameBrain::_gaddagInstance = nullptr;

void GameBrain::updateBag(std::vector<char> &tilesToReduce)
{
    for (int i = 0; i < tilesToReduce.size(); ++i)
    {
        try
        {
            GameBrain::bag[tilesToReduce[i]] -= 1;
            --this->bagSize;
        }
        catch (const std::exception &e)
        {
            // ! how on earth did you place a non alphabet character!
            std::cout << e.what() << std::endl;
        }
    }

    GameBrain::game_phase = (bagSize <= 7) ? END_GAME_MODE : (bagSize <= 9) ? PREEND_GAME_MODE : MID_GAME_MODE;
}

Node *GameBrain::__get_gaddag()
{
    if (GameBrain::_gaddagInstance == nullptr)
    {
        GameBrain::_gaddagInstance = createGaddag();
    }

    return GameBrain::_gaddagInstance;
}

GameBrain::GameBrain(TrainerComm *comm, Board *MyBoard, bool whoseTurn)
{
    this->isFuckinBitchEmpty = true;
    this->turn_TrainerMode = whoseTurn;
    this->comm = comm;
    this->MyBoard = MyBoard;
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
    BoardToGrammer b2g;
    for (int i = 0; i < move->word.length();)
    {
        if (move->horizontal)
        {
            if (!b2g.hasaTile(move->startPosition.ROW, move->startPosition.COL + i))
            {
                b2g.SetChar(move->word[i] - 32, move->startPosition.ROW, move->startPosition.COL + i);
                ++i;
            }
        }
        else
        {
            if (!b2g.hasaTile(move->startPosition.ROW, move->startPosition.COL))
            {
                b2g.SetChar(move->word[i] - 32, move->startPosition.ROW + i, move->startPosition.COL);
                ++i;
            }
        }
    }
}

void GameBrain::work_computer_vs_computer()
{
    // trial:

    vector<char> Rack;
    Rack.push_back('f');
    Rack.push_back('g');
    Rack.push_back('o');
    Rack.push_back('a');
    Rack.push_back('p');
    Rack.push_back('e');
    Rack.push_back('n');

    BoardToGrammer Ptr2G = BoardToGrammer();
    Ptr2G.SetChar('B', 6, 7);
    Ptr2G.SetChar('A', 7, 7);
    Ptr2G.SetChar('B', 8, 7);
    Ptr2G.SetChar('E', 9, 7);
    Ptr2G.SetChar('A', 9, 8);
    Ptr2G.SetChar('R', 9, 9);
    Ptr2G.SetChar('S', 9, 10);

    AiMode *aimode = new AiMode();
    aimode->setTiles(Rack);
    aimode->setBoardToGrammar(Ptr2G);
    aimode->setBagPointer(&this->bag);

    Move *move = aimode->doWork(this->isFuckinBitchEmpty);
    std::cout << "Move Score: " << move->evaluatedScore << std::endl;
}

void GameBrain::refillTiles(std::vector<char> &tiles, Move *move)
{
    int lenghtOfMove = move->word.size();
    std::vector<char> temp = rackoftiles->RandomizeTiles(lenghtOfMove);
    int index = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        int p = count(move->word.begin(), move->word.end(), tiles[i]);
        if (p > 0)
        {
            if (temp.size() > index)
                tiles[i] = temp[index++];
        }
    }
}

void GameBrain::work_human_vs_computer()
{
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
    // T1->start();
    // T2->start();
    // T3->start();

    // *local parameters
    int lenghtOfMove, index;
    vector<char> temp(7);

    while (!IsFinished())
    {
        // ! in testing only: print the board and human tiles to allow human to think
        std::cout << "Human Score: " << humanScore << "\t\tComputer Score: " << computerScore << std::endl;
        MyBoard->print();
        std::cout << "your tiles are:\n";
        for (int i = 0; i < 7; ++i)
        {
            std::cout << HumanTiles[i] << " ";
        }
        std::cout << std::endl;

        if (turn_TrainerMode == true) // *Human Player turn
        {
            //T3->stop();
            // *let the thinker do the magic
            Move *move = trainer.Human.DoWork(this->isFuckinBitchEmpty);

            // *refill the tiles of the human player's rack
            this->refillTiles(HumanTiles, move);

            // *update the board with the human's move
            this->updateBoard(move);

            // *updating human score
            humanScore += move->moveScore;
            // T3->start();
            // T1->SendTime();
            // T2->SendTime();
            // T3->SendTime();
        }
        else // *Computer Player turn
        {
            //T2->stop();
            // ! in testing only: print the board and human tiles to allow human to think
            std::cout << "computer tiles are:\n";
            for (int i = 0; i < 7; ++i)
            {
                std::cout << AI_Tiles[i] << " ";
            }
            std::cout << std::endl;

            trainer.AI.SetTiles(&AI_Tiles);
            Move *move = trainer.AI.DoWork(this->isFuckinBitchEmpty);

            //TODO: we have the move now but we have to send it to the GUI

            // *update the board with the human's move
            this->updateBoard(move);

            // *refill the tiles of the computer player's rack
            this->refillTiles(AI_Tiles, move);

            // *updating computer score
            computerScore += move->moveScore;
            // T2->start();
            // T1->SendTime();
            // T2->SendTime();
            // T3->SendTime();
        }
        // *reverse the turn
        turn_TrainerMode = !turn_TrainerMode;
        this->isFuckinBitchEmpty = (this->isFuckinBitchEmpty) ? false : false;
    }
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