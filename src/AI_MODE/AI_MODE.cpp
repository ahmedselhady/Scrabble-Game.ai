#include "AI_MODE.hpp"
#include "../Brain.hpp"
#include <future>
#include <list>

AI_MODE::AI_MODE()
{
    this->gaddag_instance = GameBrain::__get_gaddag();
}

Move *AI_MODE::doWork()
{
    // first: generate all possible moves given the tiles and board:
    std::cout << "creating gaddag started....\n";

    // ! this is for debug purposes only:
    std::cout << "creating gaddag completed....\n";

    // TODO: check for this isEmpty for board:
    bool isEmpty = false;

    std::future<list<Move>> generate_moves_thread = std::async(&AI_MODE::MovesGeneration, this, isEmpty);

    // meanwhile: generate the opponunts most probable rack:
    std::cout << "creating opponent's rack started....\n";
    // std::unordered_map<char, int> localBag(GameBrain::bag);
    std::future<std::vector<char>> rack_generation_thread = std::async(&OpponentRack::RackGenerator, &opponentRackGenerator, *this->bagReference);
    std::cout << "creating opponent's rack completed....\n";

    // Join Threads:
    std::list<Move> listOfMoves = generate_moves_thread.get();
    std::vector<char> opponentRack = rack_generation_thread.get();

    std::cout << "threads data retrieved...\n";

    // sort the moves based on their huristic value!
    // TODO: change the game phase to the global one by main class
    gameEvaluator::__get_Instance()->evaluateMovesHuristic(listOfMoves, END_GAME_MODE);

    // when done with those: use game evaluator to limit the moves to 23 moves only:
    if (listOfMoves.size() > 23)
    {
        listOfMoves.resize(23);
    }

    // TODO: simulate with monte carlo

    // return best move
    return new Move(*listOfMoves.begin());
}

list<Move> AI_MODE::MovesGeneration(bool isEmpty)
{
    WordGenerate *Gen = new WordGenerate(this->b2g, this->gaddag_instance);

    Gen->countTilesRack(tiles);

    if (isEmpty)
    {
        cout << "Empty board" << endl;
        Gen->emptyBoardMoves();
    }
    else
    {
        cout << "Non-Empty board" << endl;
        Gen->crosssets(); // Gen->Updatecrosssets(); // ! REMEBER NEEDS UPDATE TO MAKE IT FAST ..
        Gen->generateWords();
    }
    return Gen->allMoves();
}