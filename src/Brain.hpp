#pragma once

#include <unordered_map>
#include <vector>
#include "./Definitions.hpp"
#include "./MoveGeneration/Gaddag.h"
#include "./MoveGeneration/LoadGaddag.h"
#include "./MoveGeneration/LoadNode.h"
#include "./AI_MODE/AI_MODE.hpp"
#include ".\TrainerMode\RackOfTiles.hpp"
#include ".\TrainerMode\Timer.hpp"
#include <utility>
#include "./Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "./TrainerMode/Trainer.hpp"

class GameBrain
{
private:
    int bagSize;
    bool isFuckinBitchEmpty;
	bool readyToSend;
	std::string sendMessage;
    Trainer trainer;
    TimerGUI *T1;
    TimerGUI *T2;
    TimerGUI *T3;
    void updateBoard(Move *);
    void refillTiles(std::vector<char> &, Move *);
    bool turn_TrainerMode;
    vector<char> AI_Tiles, HumanTiles;
    TrainerComm *comm;
    Board *MyBoard;
    RackOfTiles *rackoftiles;
    std::unordered_map<char, int> bag;
    GamePhase game_phase;

    static Node *_gaddagInstance;
    static inline Node *createGaddag()
    {
        LoadGaddag gaddagConstructor;
        Node *gaddagRoot = gaddagConstructor.constructGaddag();
        return gaddagRoot;
    }

    AiMode *ourBelovedIntelligentAgent;
	std::string constructString(Move*, int, int, unsigned long, unsigned long, unsigned long, std::vector<char>&, std::string);
	bool IsFinished();
	void communicatorThreadSynch();

public:
    static Node *__get_gaddag();

    GameBrain(TrainerComm *comm, Board *MyBoard, bool);
    void setTurnOfTrainerMode(bool);
    void updateBag(std::vector<char> &);
    void work_computer_vs_computer();
    void work_human_vs_computer();
};