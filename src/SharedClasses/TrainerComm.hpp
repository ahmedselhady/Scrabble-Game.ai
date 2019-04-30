#pragma once

#include <string.h>
#include <zmq.h>
#include <cstdint>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <zmq.hpp>
#include <cstdint>
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
  void SendStringToGUI(string str);

  string ReceiveSTRFromGUI(string str);
  void RecCPPServerSendGUI(uint8_t SRow, uint8_t SCol, uint8_t Dir, vector <uint8_t> LettArr);

  ~TrainerComm();
};

void sendStringToGUI(string str);