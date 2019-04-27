#pragma once

#include <iostream>
#include <string>
#include "Move.hpp"
#include <zmq.hpp>
#include <zmq.h>
#include <cstdint>
#include <vector>

using namespace std;

class TrainerComm
{
	Move* ReceivedPlayerMove;
    Move* PlayerMoveFromServer;
public:
	TrainerComm();
	void SetReceivedPlayerMove(Move* ReceivedMove);
	void SendReceivedPlayerMoveToGUI();
	void ReceiveMoveFromGUI();
    int ReceiveScoreFromServer(int Score);
	~TrainerComm();
};

