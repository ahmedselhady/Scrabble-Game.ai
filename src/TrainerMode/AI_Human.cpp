#include "AI_Human.hpp"

Move *getMoveConsole()
{
    std::cout << "enter your move:\n";
    int startCol, endCol, isHorizontal;
    std::cin >> startCol >> endCol >> isHorizontal;

    // read el move nafsaha: el tiles elly msh mab3otaly
    std::string move;
    std::cin >> move; // law#alboard -- 0:26,  small: notblank, capital: blank
    Move *m = new Move();
    m->horizontal = (isHorizontal == 1) ? true : false;
    m->startPosition.COL = endCol;
    m->startPosition.ROW = startCol;
    BoardToGrammer *b2g = new BoardToGrammer();
    m->setScore(b2g->calculateScore(move, startCol, endCol, m->horizontal));
    m->word = move;
    return m;
}

AI_Human::AI_Human()
{
    this->MyBoard = NULL;
    this->HumanTiles = NULL;
    this->AI_Agent = NULL;
    this->Bag = NULL;
    this->BoardStatus = NULL;
    this->Communicator = NULL;
}

bool AI_Human::SetBag(unordered_map<char, int> *bag)
{
    try
    {
        this->Bag = bag;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetCommunicator(TrainerComm *communicator)
{
    try
    {
        this->Communicator = communicator;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetTiles(vector<char> *tiles)
{
    try
    {
        this->HumanTiles = tiles;
        this->AI_Agent->setTiles(*tiles);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetAgent(AiMode *AI_Agent)
{
    AI_Agent->setBagPointer(this->Bag);
    AI_Agent->setBoardToGrammar(b2g);
    this->AI_Agent = AI_Agent;
    return true;
}

bool AI_Human::SetBoard(Board *board)
{
    try
    {
        this->MyBoard = board;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

Move *AI_Human::DoWork(bool isFuckinBitchEmpty)
{
    Move *BestMove = nullptr;
    Move *PlayerMove = nullptr;

    while (PlayerMove == nullptr)
    {
        // todo: replace with communicator:
        PlayerMove = getMoveConsole();
        //PlayerMove = Communicator->SendPlayerMove();
    }
    BestMove = this->AI_Agent->doWork(isFuckinBitchEmpty);

    if (BestMove->moveScore > PlayerMove->moveScore)
    {
        std::cout << "\nBravo! But You Could Do Better..\n";
        // Communicator->ReceiveString("Bravo! But You Could Do Better..");
        // Communicator->SetReceivedPlayerMove(BestMove);
    }

    if (BestMove->moveScore < PlayerMove->moveScore)
    {
        std::cout << "\nMarvellous! your move is better than what I thought\n";
        // Communicator->ReceiveString("Marvellous! your move is better than what I thought");
    }

    if (BestMove->moveScore == PlayerMove->moveScore)
    {
        std::cout << "\nExcellent !I Couldn't do better\n";
        // Communicator->ReceiveString("Excellent! I Couldn't do better");
    }
    return PlayerMove;
}
