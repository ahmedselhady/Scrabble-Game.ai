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

 public:
  TrainerComm();
  vector<string> split_string(string input_string);//finalized

  void SetReceivedPlayerMove(Move* ReceivedMove);//finalized
  void SendPlayerMoveToGUI(Move* ReceivedPlayerMove);//finalized isa

  Move* ReceiveMoveFromGUI(string str);//parameter dummy to be able to receive from GUI //finalized
  int ReceiveScoreFromServer(int Score);//finalized

  void SendStringToGUI(string str);//finalized

  string ReceiveSTRFromGUI(string str);//finalized
  void RecCPPServerSendGUI(uint8_t SRow, uint8_t SCol, uint8_t Dir, vector <uint8_t> LettArr);//finalized

  void SendRackStrToGui(string col,string row,string dir,string tiles,
  string MyScore,string OppScore,string MyTime,string OppTime,string AllTime,string Rack,string MsgFromTeacher);//finalized
  ~TrainerComm();
  
};

void sendStringToGUI(string str);