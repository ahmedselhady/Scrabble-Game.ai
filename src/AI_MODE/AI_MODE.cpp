#include "AI_MODE.hpp"

#include "../Brain.hpp"

#include "../Board/Board_and_tiles/Board_and_tiles/Board.h"

#include <future>

#include <list>



AiMode::AiMode()

{

    this->gaddag_instance = GameBrain::__get_gaddag();

}



Move *AiMode::doWork(bool isFuckinEmpty, int bagSize, LoadHeuristics *loader)

{

    // first: generate all possible moves given the tiles and board:

    std::cout << "creating gaddag started....\n";



    // ! this is for debug purposes only:

    std::cout << "creating gaddag completed....\n";



    // TODO: check for this isEmpty for board:



    // !std::future<list<Move>> generate_moves_thread = std::async(&AiMode::MovesGeneration, this, isFuckinEmpty);



    // meanwhile: generate the opponunts most probable rack:

    std::cout << "creating opponent's rack started....\n";

    // std::unordered_map<char, int> localBag(GameBrain::bag);

    //   std::future<std::vector<char>> rack_generation_thread = std::async(&OpponentRack::RackGenerator, &opponentRackGenerator, *this->bagReference);

    std::cout << "creating opponent's rack completed....\n";



    // TODO: change the game phase to the global one by main class



    this->evaluator = new VCValueEvaluator(loader, NULL, bagSize, isFuckinEmpty);



    // Join Threads:

    //! std::list<Move> listOfMoves = generate_moves_thread.get();

    std::list<Move> listOfMoves = this->MovesGeneration(isFuckinEmpty);

    //std::vector<char> opponentRack = rack_generation_thread.get();



    std::cout << "threads data retrieved...\n";



    // sort the moves based on their huristic value!

    gameEvaluator::__get_Instance()->evaluateMovesHuristic(listOfMoves, END_GAME_MODE);



    std::cout << "Moves Sorted...\n";

    // when done with those: use game evaluator to limit the moves to 23 moves only:

    if (listOfMoves.size() > 23)

    {

        listOfMoves.resize(23);

    }



    // TODO: simulate with monte carlo



    // return best move

    if (listOfMoves.size() == 0)

        return nullptr;



    delete this->evaluator;

    std::cout << "Finished Generation of Best Word...\n";



    return new Move(*listOfMoves.begin());

}



list<Move> AiMode::MovesGeneration(bool isEmpty)

{



    // TODO: EDIT THE VALUES PASSED TO CONSTRUCTOR OF WORDGENERATE (BAG SIZE,BAGSIZE ...).

    WordGenerate *Gen = new WordGenerate(this->b2g, this->gaddag_instance, this->evaluator);



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