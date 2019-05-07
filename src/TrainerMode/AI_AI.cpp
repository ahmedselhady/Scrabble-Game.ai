
#include "AI_AI.hpp"

<<<<<<< HEAD
AI_AI::AI_AI()
{
    this->MyBoard = NULL;
    this->AI_Tiles = NULL;
    this->AI_Agent = NULL;
    this->Bag = NULL;
    this->BoardStatus = NULL;
    this->Communicator = NULL;
}

bool AI_AI::SetBag(unordered_map<char, int> *bag)
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

bool AI_AI::SetCommunicator(TrainerComm *communicator)
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
=======
AI_AI::AI_AI() {
  this->MyBoard = NULL;
  this->AI_Tiles = NULL;
  this->AI_Agent = NULL;
  this->Bag = NULL;
  this->BoardStatus = NULL;
  // this->Communicator = NULL;
}

bool AI_AI::SetBag(unordered_map<char, int> *Bag) {
  try {
    this->Bag = Bag;
    return true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
>>>>>>> 60ddf8760638ce82e892fc00c9797c3375660a50

  return false;
}

<<<<<<< HEAD
bool AI_AI::SetTiles(vector<char> *tiles)
{
    try
    {
        this->AI_Tiles = tiles;
        this->AI_Agent->setTiles(*tiles);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_AI::SetBoard(Board *board)
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
=======
bool AI_AI::SetTiles(vector<char> *AI_Tiles) {
  try {
    this->AI_Tiles = AI_Tiles;
    return true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  return false;
}
>>>>>>> 60ddf8760638ce82e892fc00c9797c3375660a50

bool AI_AI::SetAgent(AI_MODE *AI_Agent) {
  if (this->Bag == NULL || this->BoardStatus == NULL ||
      this->AI_Tiles == NULL ||
      this->MyBoard == NULL)  // || this->Communicator == NULL
  {
    return false;
  }
  AI_Agent = new AI_MODE();
  AI_Agent->setTiles(*AI_Tiles);
  AI_Agent->setBagPointer(this->Bag);
  return true;
}

<<<<<<< HEAD
Move *AI_AI::DoWork(bool isFuckinBitchEmpty, int bagSize, LoadHeuristics* loader)
{
    Move *BestMove = nullptr;
    BestMove = this->AI_Agent->doWork(isFuckinBitchEmpty,bagSize,loader);
    return BestMove;
}

bool AI_AI::SetAgent(AiMode *AI_Agent)
{

    AI_Agent->setBagPointer(this->Bag);
    AI_Agent->setBoardToGrammar(b2g);
    this->AI_Agent = AI_Agent;
    return true;
=======
bool AI_AI::SetBoard(Board *MyBoard) {
  try {
    this->MyBoard = MyBoard;
    return true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  return false;
}

bool AI_AI::IsEmptyBoard() {
  // this->BoardStatus = &this->MyBoard->getBoardStatus();
  auto x = this->MyBoard->getBoardStatus();
  this->BoardStatus = &x;
  return this->BoardStatus->isEmpty();
}

Move *AI_AI::DoWork() {
  Move *BestMove = AI_Agent->doWork();
  return BestMove;
>>>>>>> 60ddf8760638ce82e892fc00c9797c3375660a50
}
