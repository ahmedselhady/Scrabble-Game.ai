#include "TrainerComm.hpp"

TrainerComm::TrainerComm()
{
}

void TrainerComm::SetReceivedPlayerMove(Move *ReceivedMove)
{
    ReceivedPlayerMove = ReceivedMove;
}

void TrainerComm::SendReceivedPlayerMoveToGUI()
{
    vector<string> StrVec;
    string Row(1, ReceivedPlayerMove->startPosition.ROW);
    string Col(1, ReceivedPlayerMove->startPosition.COL);
    StrVec.push_back(Row);
    StrVec.push_back(Col);
    StrVec.push_back(ReceivedPlayerMove->word);
    if (ReceivedPlayerMove->horizontal == true)
    {
        StrVec.push_back("true");
    }
    else
    {
        StrVec.push_back("false");
    }

    //zmq::context_t context(1);
    //zmq::socket_t socket(context, ZMQ_REQ);
    //socket.connect("tcp://localhost:5550");
    int Counter = 0;
    for (auto it = StrVec.begin(); it != StrVec.end(); it++) //sending the vector LettArr
    {
        //zmq_msg_t Msg;
        //zmq_msg_init_size(&Msg, StrVec[Counter].length());
        //memcpy(zmq_msg_data(&Msg), StrVec[Counter].c_str(), StrVec[Counter].length());
        if (it == StrVec.end() - 1)
        {
            //zmq_msg_send(&Msg, socket, 0);
        }
        else
        {
            //zmq_msg_send(&Msg, socket, ZMQ_SNDMORE);
        }
        Counter++;
    }
}

int TrainerComm::ReceiveScoreFromServer(int Score)
{
    return Score;
}

Move *TrainerComm::SendPlayerMove()
{
    return PlayerMoveFromServer;
}

void TrainerComm::ReceiveMoveFromGUI()
{
    //zmq::context_t context(1);
    //zmq::socket_t socket(context, ZMQ_REP);
    //socket.bind("tcp://*:5551");
    std::vector<std::string> ReceivedMove; //0 row, 1 col,2 word, 3 horizontal,4 is bingo,5 calculated score
    while (1)
    {
        //zmq_msg_t message;
        //zmq_msg_init(&message);
        //zmq_msg_recv(&message, socket, 0);   //int zmq_msg_recv (zmq_msg_t *msg, void *socket, int flags);
        //size_t MsgSize = zmq_msg_size(&message);//size_t zmq_msg_size (zmq_msg_t *msg);
        //ReceivedMove.push_back(std::string(static_cast<char*>(zmq_msg_data(&message)), MsgSize));
        //  Process the message frame
        //zmq_msg_close(&message);
        //	if (!zmq_msg_more(&message))
        break; //  Last message frame
    }
    Position pos;
    pos.ROW = ReceivedMove[0][0];
    pos.COL = ReceivedMove[1][0];
    bool IsHorizontal;
    if (ReceivedMove[3] == "true")
        IsHorizontal = true;
    else
        IsHorizontal = false;
    PlayerMoveFromServer = new Move(ReceivedMove[2], IsHorizontal, pos, 0); //0 is dummy
    BoardCommunicator *BoardComm;
    PlayerMoveFromServer->setScore(BoardComm->calculateScore(ReceivedMove[2], (int)pos.ROW, (int)pos.COL, IsHorizontal));
}

void TrainerComm::ReceiveString(std::string str)
{
    ReceivedString = str;
}

void TrainerComm::SendReceivedStringToGUI()
{
    //zmq::context_t context(1);
    //zmq::socket_t socket(context, ZMQ_REQ);
    //socket.connect("tcp://localhost:5552");
    //zmq_msg_t Msg;
    //zmq_msg_init_size(&Msg, ReceivedString.length());
    //memcpy(zmq_msg_data(&Msg), ReceivedString.c_str(), ReceivedString.length());
    //zmq_msg_send(&Msg, socket, 0);
}

TrainerComm::~TrainerComm()
{
}