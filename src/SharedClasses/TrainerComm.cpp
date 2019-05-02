#include "TrainerComm.hpp"

TrainerComm::TrainerComm() {}

vector<string> TrainerComm::split_string(string input_string)
{
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ')
	{
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = '/';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos)
	{
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}

// void TrainerComm::SetReceivedPlayerMove(Move* ReceivedMove) {
//   ReceivedPlayerMove = ReceivedMove;
// }

// void TrainerComm::SendPlayerMoveToGUI(Move *ReceivedPlayerMove)
// {
// 	string StrVec; //0 row, 1 col, 2 word, 3 ishorizontal
// 	string Row(1, ReceivedPlayerMove->startPosition.ROW);
// 	string Col(1, ReceivedPlayerMove->startPosition.COL);
// 	StrVec += ROW;
// 	StrVec += "/";
// 	StrVec += Col;
// 	StrVec += "/";
// 	StrVec += ReceivedPlayerMove->word;
// 	StrVec += "/";
// 	//StrVec.push_back(Row);
// 	//StrVec.push_back(Col);
// 	//StrVec.push_back(ReceivedPlayerMove->word);
// 	if (ReceivedPlayerMove->horizontal == true)
// 	{
// 		StrVec += "true";
// 	}
// 	else
// 	{
// 		StrVec += "false";
// 	}
// 	SendStringToGUI(StrVec);
// }

int TrainerComm::ReceiveScoreFromServer(int Score) { return Score; }

//Move* TrainerComm::SendPlayerMove() { return PlayerMoveFromServer; }

// void TrainerComm::ReceiveMoveFromGUI() {
//   zmq::context_t context(1);
//   zmq::socket_t socket(context, ZMQ_REP);
//   socket.bind("tcp://*:5551");
//   vector<string> ReceivedMove;  // 0 row, 1 col,2 word, 3 horizontal,4 is
//                                 // bingo,5 calculated score
//   while (1) {
//     zmq_msg_t message;
//     zmq_msg_init(&message);
//     zmq_msg_recv(
//         &message, socket,
//         0);  // int zmq_msg_recv (zmq_msg_t *msg, void *socket, int flags);
//     size_t MsgSize =
//         zmq_msg_size(&message);  // size_t zmq_msg_size (zmq_msg_t *msg);
//     ReceivedMove.push_back(
//         std::string(static_cast<char*>(zmq_msg_data(&message)), MsgSize));
//     //  Process the message frame
//     zmq_msg_close(&message);
//     if (!zmq_msg_more(&message)) break;  //  Last message frame
//   }
//   Position pos;
//   pos.ROW = ReceivedMove[0][0];
//   pos.COL = ReceivedMove[1][0];
//   bool IsHorizontal;
//   if (ReceivedMove[3] == "true")
//     IsHorizontal = true;
//   else
//     IsHorizontal = false;
//   PlayerMoveFromServer =
//       new Move(ReceivedMove[2], IsHorizontal, pos, 0);  // 0 is dummy
//   BoardCommunicator* BoardComm;
//   PlayerMoveFromServer->setScore(BoardComm->calculateScore(
//       ReceivedMove[2], (int)pos.ROW, (int)pos.COL, IsHorizontal));
// }

Move *TrainerComm::ReceiveMoveFromGUI(string str) //may not be used after renewing the protocol
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);
	socket.connect("tcp://192.168.88.208:5555");
	zmq_msg_t message;

	string ReceivedMove; // 0 row, 1 col,2 word, 3 horizontal

	zmq_msg_init_size(&message, str.length());
	memcpy(zmq_msg_data(&message), str.c_str(), str.length());
	zmq_msg_send(&message, socket, !ZMQ_DONTWAIT);
	zmq_msg_recv(&message, socket, !ZMQ_DONTWAIT);

	size_t MsgSize = zmq_msg_size(&message); // size_t zmq_msg_size (zmq_msg_t *msg);
	ReceivedMove = std::string(static_cast<char *>(zmq_msg_data(&message)), MsgSize);
	//  Process the message frame
	zmq_msg_close(&message);
	//if (!zmq_msg_more(&message)) break;  //  Last message frame

	vector<string> ReceivedStrVec = split_string(ReceivedMove);
	Position pos;
	pos.ROW = ReceivedStrVec[0][0];
	pos.COL = ReceivedStrVec[1][0];
	bool IsHorizontal;
	if (ReceivedStrVec[3] == "true")
		IsHorizontal = true;
	else
		IsHorizontal = false;

	Move *PlayerMoveFromServer =
			new Move(ReceivedStrVec[2], IsHorizontal, pos, 0); // 0 is dummy
	//BoardCommunicator* BoardComm;
	//PlayerMoveFromServer->setScore(BoardComm->calculateScore(
	//ReceivedStrVec[2], (int)pos.ROW, (int)pos.COL, IsHorizontal));
	return PlayerMoveFromServer;
}

Move *TrainerComm::ConstructMoveFromReceivedStr(vector<string> ReceivedStrVec)
{
	//vector<string> ReceivedStrVec = split_string(ReceivedMove);
	Position pos;
	pos.ROW = ReceivedStrVec[1][0];
	pos.COL = ReceivedStrVec[2][0];
	bool IsHorizontal;
	if (ReceivedStrVec[3] == "true")
		IsHorizontal = true;
	else
		IsHorizontal = false;

	Move *PlayerMoveFromServer =
			new Move(ReceivedStrVec[4], IsHorizontal, pos, 0); // 0 is dummy
	return PlayerMoveFromServer;
}

void TrainerComm::SendStringToGUI(string str)
{
	// zmq::context_t context(1);
	// zmq::socket_t socket(context, ZMQ_REQ);
	// socket.connect("tcp://192.168.88.208:5555");
	zmq_msg_t Msg;
	zmq_msg_init_size(&Msg, str.length());
	memcpy(zmq_msg_data(&Msg), str.c_str(), str.length());
	zmq_msg_send(&Msg, socket, !ZMQ_DONTWAIT);
	//zmq_msg_recv(&Msg, socket, !ZMQ_DONTWAIT);
}

string TrainerComm::ReceiveSTRFromGUI(string str) //may not be used after renewing the protocol
{
	// zmq::context_t context(1);
	// zmq::socket_t socket(context, ZMQ_REQ);
	//socket.connect("tcp://192.168.88.208:5555");
	//socket.connect("tcp://192.168.43.169:5555"); //edit it
	zmq_msg_t message;

	string ReceivedMove; // 0 row, 1 col,2 word, 3 horizontal,4 is
											 // bingo,5 calculated score
	zmq_msg_init_size(&message, str.length());
	memcpy(zmq_msg_data(&message), str.c_str(), str.length());
	zmq_msg_send(&message, socket, !ZMQ_DONTWAIT);
	zmq_msg_recv(&message, socket, !ZMQ_DONTWAIT);

	size_t MsgSize = zmq_msg_size(&message); // size_t zmq_msg_size (zmq_msg_t *msg);
	ReceivedMove = std::string(static_cast<char *>(zmq_msg_data(&message)), MsgSize);
	//  Process the message frame
	zmq_msg_close(&message);
	return ReceivedMove;
}

string TrainerComm::RecSTRFromGUI()
{
	// zmq::context_t context(1);
	// zmq::socket_t socket(context, ZMQ_REQ);
	//socket.connect("tcp://192.168.88.208:5555");
	//socket.connect("tcp://192.168.43.169:5555"); //edit it
	zmq_msg_t message;

	//zmq_msg_init_size(&message, str.length());
	//memcpy(zmq_msg_data(&message), str.c_str(), str.length());
	//zmq_msg_send(&message, socket, !ZMQ_DONTWAIT);
	zmq_msg_recv(&message, socket, !ZMQ_DONTWAIT);
	size_t MsgSize = zmq_msg_size(&message); // size_t zmq_msg_size (zmq_msg_t *msg);
	string ReceivedMove = std::string(static_cast<char *>(zmq_msg_data(&message)), MsgSize);
	//  Process the message frame
	zmq_msg_close(&message); //will check this
	return ReceivedMove;
}

PossibleMoves TrainerComm::SendAndReceiveGUI(string str, bool ToSend, bool ToReceive)
{
	//socket.connect("tcp://192.168.88.208:5555"); //edit it
	string ToSendString;
	if (ToSend)
	{
		ToSendString = str;
	}
	else
	{
		ToSendString = "0"; //any dummy
	}
	sendStringToGUI(ToSendString);
	string Received = RecSTRFromGUI();
	if (ToReceive)
	{
		vector<string> StrVec = split_string(Received); //0 move, 1 row, 2 col, 3 ishorizontal, 4 word
		if (StrVec[0] == "####")
			return PASS;
		else if (StrVec[0] == "****")
			return EXCHANGE;
		else if (StrVec[0] == "challenge")
			return CHALLENGE;
		else if (StrVec[0] == "play")
		{
			MovePtr = ConstructMoveFromReceivedStr(StrVec);
			return PLAY;
		}
		else
			return DUMMY;
	}
	else
	{
		return DUMMY;
	}
}

Move *TrainerComm::GetMoveOfGUI()
{
	return MovePtr;
}

void TrainerComm::RecCPPServerSendGUI(uint8_t SRow, uint8_t SCol, uint8_t Dir, vector<uint8_t> LettArr)
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);
	socket.connect("tcp://localhost:5555"); //edit it

	vector<uint8_t> RowColDir;
	RowColDir.push_back(SRow);
	RowColDir.push_back(SCol);
	RowColDir.push_back(Dir);

	for (auto it = RowColDir.begin(); it != RowColDir.end(); it++) //Sending SRow, SCol, Dir
	{
		zmq_msg_t Msg;
		string StringToBeSent = to_string((int)*it);
		int SizeOfSentMsg = StringToBeSent.size();
		zmq_msg_init_size(&Msg, SizeOfSentMsg);
		memcpy(zmq_msg_data(&Msg), StringToBeSent.c_str(), SizeOfSentMsg);
		zmq_msg_send(&Msg, socket, ZMQ_SNDMORE);
	}

	for (auto it = LettArr.begin(); it != LettArr.end(); it++) //sending the vector LettArr
	{
		zmq_msg_t Msg;
		string StringToBeSent = to_string((int)*it);
		int SizeOfSentMsg = StringToBeSent.size();
		zmq_msg_init_size(&Msg, SizeOfSentMsg);
		memcpy(zmq_msg_data(&Msg), StringToBeSent.c_str(), SizeOfSentMsg);
		if (it == LettersArray.end() - 1)
		{
			zmq_msg_send(&Msg, socket, 0);
		}
		else
		{
			zmq_msg_send(&Msg, socket, ZMQ_SNDMORE);
		}
	}
}

// void TrainerComm::SendRackStrToGui(string col, string row, string dir, string tiles,
// 																	 string MyScore, string OppScore, string MyTime, string OppTime, string AllTime, string Rack, string MsgFromTeacher)
// {
// 	string SentStr = "play/tm/" + col + "/" + row + "/" + dir + "/" + tiles + "/" + MyScore + "/" + OppScore + "/" + MyTime;
// 	SentStr += "/" + OppTime + "/" + AllTime + "/" + Rack + "/" + MsgFromTeacher;
// 	SendStringToGUI(SentStr);
// }

TrainerComm::~TrainerComm() {}

// void sendStringToGUI(string str)
// {
// 	TrainerComm tc;
// 	tc.ReceiveString(str);
// 	tc.SendReceivedStringToGUI();
// }
