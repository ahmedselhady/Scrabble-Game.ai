#pragma once

#include "../AI_MODE/AI_MODE.hpp"
#include "../SharedClasses/TrainerComm.hpp"

class AI_Human
{
private:
	std::string messageToHuman;
    Board *MyBoard;
    vector<char> *HumanTiles;
    unordered_map<char, int> *Bag;
    BoardMask *BoardStatus;
    BoardToGrammer b2g;

    AiMode *AI_Agent;
    TrainerComm *Communicator;
	
    void exchange(std::vector<char> *, char, char);

public:
    AI_Human();
    void exchangeTiles(std::vector<char> *, char);
    bool SetBag(unordered_map<char, int> *);
    bool SetTiles(vector<char> *);
    bool SetCommunicator(TrainerComm *);
    bool SetBoard(Board *MyBoard);
    bool SetAgent(AiMode *AI_Agent);
    Move *DoWork(bool);
	std::string getString() const {
		return this->messageToHuman;
	}
};