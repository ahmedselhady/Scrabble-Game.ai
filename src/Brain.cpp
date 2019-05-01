
#include "Brain.hpp"
#include <utility>

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

GameBrain::GameBrain() 
{
    T1=new Timer(comm,1200);
    T2=new Timer(comm,600);
    T3=new Timer(comm,600);
    rackoftiles = new RackOfTiles(&bag,bagSize,comm);
    MyBoard=Board::getBoard();
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
    bag[' '] = 2;

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

void GameBrain::setTurnOfTrainerMode(bool turn)
{
    turn_TrainerMode=turn;
}

void GameBrain::work_human_vs_computer()
{
    trainer.AI.SetBoard(MyBoard);
    trainer.Human.SetBoard(MyBoard);

    AI_Tiles=rackoftiles->RandomizeTiles(7);
    HumanTiles=rackoftiles->RandomizeTiles(7);
    
    trainer.AI.SetTiles(&AI_Tiles);
    trainer.Human.SetTiles(&HumanTiles);

    trainer.AI.SetBag(&bag);
    trainer.Human.SetBag(&bag);

    trainer.AI.SetCommunicator(comm);
    trainer.Human.SetCommunicator(comm);

    trainer.AI.SetAgent();
    trainer.Human.SetAgent();

    T1->start();
    T2->start();
    T3->start();
    
    int lenghtOfMove,index;
    vector<char> temp;

    while(!IsFinished())
    {
        if(turn_TrainerMode==true) //Player turn
        {
            T3->stop();
            Move* move=trainer.Human.DoWork();
            int lenghtOfMove=move->word.size();
            temp=rackoftiles->RandomizeTiles(lenghtOfMove);
            index=0;
            for(int i=0;i<HumanTiles.size();i++)
            {
                if(move->word.find(HumanTiles[i]))
                {
                    if(temp.size()>index)
                        HumanTiles[i]=temp[index++];
                }
            }
            trainer.Human.SetTiles(&HumanTiles);

            turn_TrainerMode=false;
            T3->start();
            T1->SendTime();
            T2->SendTime();
            T3->SendTime();
        }
        else
        {
            T2->stop();
            Move* move=trainer.AI.DoWork();
            
            //TODO: we have the mode now but we have to send it to the GUI
            
            int lenghtOfMove=move->word.size();
            temp=rackoftiles->RandomizeTiles(lenghtOfMove);
            index=0;
            for(int i=0;i<AI_Tiles.size();i++)
            {
                if(move->word.find(AI_Tiles[i]))
                {
                    if(temp.size()>index)
                        AI_Tiles[i]=temp[index++];
                }
            }
            trainer.AI.SetTiles(&AI_Tiles);

            turn_TrainerMode=true;
            T2->start();
            T1->SendTime();
            T2->SendTime();
            T3->SendTime();
        }
    }
    
    
}

bool GameBrain::IsFinished()
{
    if(this->bagSize==0&&((AI_Tiles.size()==0)||(HumanTiles.size()==0)))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}