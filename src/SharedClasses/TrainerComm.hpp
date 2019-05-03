#pragma once

#include <string.h>
#include "zmq.h"
#include <cstdint>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include "zmq.hpp"
#include <cstdint>
//#include "BoardCommunicator.hpp"
#include "Move.hpp"

using namespace std;

enum PossibleMoves
{
    PASS,
    PLAY,
    EXCHANGE,
    CHALLENGE,
    DUMMY
};

class TrainerComm
{

    Move *MovePtr;

public:
    TrainerComm();
    vector<string> split_string(string input_string); //finalized

    //void SetReceivedPlayerMove(Move* ReceivedMove);//finalized

    //void SendPlayerMoveToGUI(Move *ReceivedPlayerMove); //finalized isa
    //may not be used after renewing the protocol

    Move *ReceiveMoveFromGUI(string str); //parameter dummy to be able to receive from GUI //finalized
    //may not be used after renewing the protocol

    int ReceiveScoreFromServer(int Score); //finalized

    void SendStringToGUI(string str); //finalized //edited

    string ReceiveSTRFromGUI(string str); //finalized //old protocol
    //may not be used after renewing the protocol

    void RecCPPServerSendGUI(uint8_t SRow, uint8_t SCol, uint8_t Dir, vector<uint8_t> LettArr); //finalized
    //may not be used after renewing the protocol

    // void SendRackStrToGui(string col, string row, string dir, string tiles,
    //                       string MyScore, string OppScore, string MyTime,
    //                       string OppTime, string AllTime, string Rack, string MsgFromTeacher); //finalized
    //may not be used after renewing the protocol

    PossibleMoves SendAndReceiveGUI(string str, bool ToSend, bool ToReceive); //finalized
    Move *ConstructMoveFromReceivedStr(vector<string> ReceivedStrVec);        //finalized
    string RecSTRFromGUI();                                                   //updated protocol                                       //finalized                                                        //finalized
    Move *GetMoveOfGUI();                                                     //finalized

    ~TrainerComm();
};

void sendStringToGUI(string str);