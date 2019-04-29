
#include "Brain.hpp"
#include <utility>
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
        }
    }

    GameBrain::game_phase = (bagSize <= 7) ? END_GAME_MODE : (bagSize <= 9) ? PREEND_GAME_MODE : MID_GAME_MODE;
}

GameBrain::GameBrain()
{
    this->bagSize = 100;
    game_phase = MID_GAME_MODE;

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

    AI_MODE *aimode = new AI_MODE();
    aimode->setTiles(Rack);
    aimode->setBoardToGrammar(Ptr2G);
    aimode->setBagPointer(&this->bag);

    Move *move = aimode->doWork();
    std::cout << "Move Score: " << move->evaluatedScore << std::endl;
}
