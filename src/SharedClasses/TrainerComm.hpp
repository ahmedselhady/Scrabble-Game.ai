#pragma once

#include <string.h>
#include <zmq.h>
#include <cstdint>
#include <future>
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
  vector<string> split_string(string input_string);
  void SetReceivedPlayerMove(Move* ReceivedMove);
  void SendReceivedPlayerMoveToGUI();

  vector<string> ReceiveMoveFromGUI(string str)
  int ReceiveScoreFromServer(int Score);
  Move* SendPlayerMove();

  void ReceiveString(string str);
  void SendReceivedStringToGUI();

  string ReceiveSTRFromGUI(string str)
  ~TrainerComm();
};

void sendStringToGUI(string str);