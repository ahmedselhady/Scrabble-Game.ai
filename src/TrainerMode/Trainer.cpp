#include "Trainer.hpp"

void Trainer::AI_Human_func(Board *b, vector<char> *tile, unordered_map<char, int> *bag, AI_Human *h, AiMode *mode)
{

    h->SetTiles(tile);
    h->SetBag(bag);
    h->SetBoard(b);
    // h->SetAgent(mode);
    h->DoWork();
}
void Trainer::AI_AI_func(Board *b, vector<char> *tile, unordered_map<char, int> *bag, AI_AI *h, AiMode *mode)
{
    h->SetTiles(tile);
    h->SetBag(bag);
    h->SetBoard(b);
    // h->SetAgent(mode);
    h->DoWork();
}
