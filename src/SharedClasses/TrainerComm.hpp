#pragma once

#include <string>
#include "Move.hpp"
#include <zmq.hpp>
#include <zmq.h>
#include <cstdint>
#include <vector>
#include "BoardCommunicator.hpp"

class TrainerComm
{
private:
    Move *ReceivedPlayerMove;
    Move *PlayerMoveFromServer;
    std::string ReceivedString;

public:
    TrainerComm();
    void SetReceivedPlayerMove(Move *ReceivedMove);
    void SendReceivedPlayerMoveToGUI();

    void ReceiveMoveFromGUI();
    int ReceiveScoreFromServer(int Score);
    Move *SendPlayerMove();

    void ReceiveString(string str);
    void SendReceivedStringToGUI();
    ~TrainerComm();
};
