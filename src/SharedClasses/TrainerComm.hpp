#pragma once

#include <string.h>
#include <zmq.h>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <zmq.hpp>
#include "BoardCommunicator.hpp"
#include "Move.hpp"

using namespace std;

class TrainerComm {
  Move* ReceivedPlayerMove;
  Move* PlayerMoveFromServer;
  string ReceivedString;

 public:
  TrainerComm();
  void SetReceivedPlayerMove(Move* ReceivedMove);
  void SendReceivedPlayerMoveToGUI();

  void ReceiveMoveFromGUI();
  int ReceiveScoreFromServer(int Score);
  Move* SendPlayerMove();

  void ReceiveString(string str);
  void SendReceivedStringToGUI();
  ~TrainerComm();
};

void sendStringToGUI(string str);