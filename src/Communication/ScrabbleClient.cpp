#ifndef COMM_SCRABBLE_CLIENT_CPP
#define COMM_SCRABBLE_CLIENT_CPP


#ifdef _WIN32
	#pragma comment(lib, "ws2_32")
	#include <WinSock2.h>
#endif
#include <assert.h>
#include <cstdlib>
#include <future>
#include <iostream>
#include <string>
#include "BinaryEnvelope.hpp"
#include "../Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "../Brain.hpp"
#include "../SharedClasses/Move.hpp"
#include "../SharedClasses/TrainerComm.hpp"
#include "easywsclient/easywsclient.hpp"
//#include "easywsclient/easywsclient.cpp"  // <-- include only if you don't
// want compile separately

using easywsclient::WebSocket;
static WebSocket::pointer ws_connection = nullptr;

static std::string mode = "";

Board* board = nullptr;
GameBrain* brainiac = nullptr;
bool readySendServer = false;
std::vector<uint8_t> vecToSend;
int our, their, total;

// this is used to hold the current state of our communcation
States state = States::INIT;

void print_vec(const std::vector<uint8_t>& msg) {
  std::cout << std::endl;
  for (auto m : msg) {
    std::cout << std::to_string(m) << ", ";
  }
  std::cout << std::endl;
}

Move* theMove;

void playAIMode() {
  theMove = brainiac->work_computer_vs_computer();


 // print_vec(brainiac->getAITiles());

  BinaryEnvelope env;
  if(theMove == nullptr){
    env.insertUInt8(MessageTypes::PASSMSG);
  } else {
    env.insertUInt8(MessageTypes::PLAYMSG);
    env.insertUInt8(theMove->startPosition.COL + 1);
    env.insertUInt8(theMove->startPosition.ROW + 1);
    env.insertUInt8(theMove->horizontal ? 0 : 1);

    for (int i = 0; i < theMove->word.length(); i++) {
      if (theMove->word[i] >= 0 && theMove->word[i] <= 25) {
        continue;
      } else if (theMove->word[i] >= 'A' && theMove->word[i] <= 'Z') {
        env.insertUInt8((uint8_t)theMove->word[i] -'A'+101);
      } else {
        env.insertUInt8((uint8_t)theMove->word[i] - 'a'+1);
      }
    }

	theMove->word = *Options::moveChar(theMove);
    int len = theMove->word.length();
    while (len < 7) {
      env.insertUInt8(0);
      len++;
    }

    env.insert32BitInt(theMove->moveScore);

	

	
  }
	
  
  auto ser = env.serialize();  
  vecToSend = ser;
  readySendServer = true;
  state = States::AWAIT_PLAY_RESPONSE;
}

void handle_message(const std::vector<uint8_t>& message) {
  // the message type always exist in the first
  // byte of the message
  uint8_t msgType = message[0];

  // printing the buffer just for debugging
  // TODO: Remove this when finished the game
  std::cout << "Received buffer: ";
  print_vec(message);

  // always send the envelope unless it doesn't matter
  bool sendMessage = true;
  std::string GUIMsg = "";
  // this should be true when we have to make a play then send it
  BinaryEnvelope env;

  // * No switch case because it doesn't accept a variable in the case block
  if (msgType == MessageTypes::NAME) {
    // The server is expecting a 0 response to a "Name" request
    if (state != States::INIT) {
      std::cerr << "Received Name but I have state: " << state << std::endl;
    }
    env.insertUInt8(MessageTypes::NAME);
    env.insertString("Wermacht");  // Send our name hardcoded :D
    state = States::READY;
  } else if (msgType == MessageTypes::START) {
    auto smsg = deserializeReadyMessage(message);
    // TODO: Construct the board and hold it from here
    std::vector<char> vec;
    for (int i = 0; i < 7; i++) {
      uint8_t x = smsg.tiles[i];
      if (x == 0) continue;
      if (x == 100) {
        vec.emplace_back(' '); 
	  } else {
        vec.emplace_back(x + 'a' - 1);
	  }
	}
    brainiac->fillComputerTiles(vec);

    if (smsg.order == 1) {
      // * well this is our turn
      state = States::THINKING;
    } else {
      // ? we are idle, this is the opponent's move
      state = States::IDLE;
    }
  } else if (msgType == MessageTypes::END) {
    std::cout << "An end packet was received... losing the connection ";

    auto emsg = deserializeEndMessage(message);
    std::cout << "Our score is " << emsg.ourScore
              << ", the other player's score is " << emsg.opponentScore
              << std::endl;

    state = States::READY;
  } else if (msgType == MessageTypes::PASSMSG) {
    auto passFromOpponent = deserializePassMessage(message);

    // other player passed, we should play
    state = States::THINKING;

    // ? state should be known after the play is known
  } else if (msgType == MessageTypes::PLAYMSG) {
    auto playFromOpponent = deserializePlayMessage(message);

	Move* oppMove = new Move();
    oppMove->startPosition.COL = playFromOpponent.column - 1;
    oppMove->startPosition.ROW = playFromOpponent.row - 1;
    oppMove->horizontal = playFromOpponent.direction == 0 ? true : false;
    for (int i = 0; i < 7; i++) {
      char chr;
      uint8_t t = playFromOpponent.tiles[i];
      if (t >= 1 && t <= 26) { 
        chr = t + 'a' - 1;
      } else if (t >= 101 && t <= 126) { 
        chr = t + 'A' - 101; 
      } else { 
        continue;
	  }
      oppMove->word.push_back(chr);//aspoor 

	}
	brainiac->updateBoard(oppMove);

	std::vector<char> rack = {};

	brainiac->sendMessage = brainiac->constructString(
            oppMove, 0, playFromOpponent.score, playFromOpponent.ourRemainingTime, playFromOpponent.totalRemainingTime - playFromOpponent.ourRemainingTime, playFromOpponent.totalRemainingTime, rack, "no message no cry");
    brainiac->readyToSend = true;

    state = States::AWAIT_AGENT_CHALLENGE;
  } else if (msgType == MessageTypes::INVALID) {
    if (state == States::AWAIT_PLAY_RESPONSE) {
      auto invalidPlay = deserializeInvalidPlayMessage(message);
      our = invalidPlay.ourRemainingTime;
      total = invalidPlay.totalRemainingTime;
      their = total - our;
      state = States::IDLE;
    } else if (state == States::AWAIT_EXCHANGE_RESPONSE) {
      auto invalidEx = deserializeInvalidExchangeMessage(message);
      our = invalidEx.ourRemainingTime;
      total = invalidEx.totalRemainingTime;
      their = total - our;
	  state = States::THINKING;
    } else {
      std::cerr << "Undefined state and action Invalid and state: " << state;
    }
    sendMessage = true;
    env.insertUInt8(MessageTypes::PASSMSG);
    std::cout << "Received an Invalid message, won't do anything" << std::endl;
  } else if (msgType == MessageTypes::CHALLENGE_ACCEPTED) {
    auto chgmsg = deserializeChallengeAcceptedMessage(message);
    // * we won the challenge we should play as well
    if (state == States::AWAIT_CHALLENGE_RESPONSE) {
      state = States::THINKING;
    } else if (state == States::AWAIT_PLAY_RESPONSE) {
      state = States::IDLE;
    }

    // TODO: maybe update the gui
  } else if (msgType == MessageTypes::CHALLENGE_REJECTED) {
    auto chgrej = deserializeChallengeRejectedMessage(message);

    if (state == States::AWAIT_CHALLENGE_RESPONSE) {
      state = States::IDLE;
    } else if (state == States::AWAIT_PLAY_RESPONSE) {
      state = States::THINKING;
    }

    // TODO: update the gui
  } else if (msgType == MessageTypes::NO_CHALLENGE) {
    auto nochg = deserializeNoChallengeMessage(message, state);
    


    if (state == States::AWAIT_CHALLENGE_RESPONSE) {
      
      state = States::THINKING;
    } else if (state == States::AWAIT_AGENT_CHALLENGE) {
      state = States::THINKING;
    } else if (state == States::AWAIT_PLAY_RESPONSE) {

		std::vector<char> rack = brainiac->getAITiles();

      brainiac->sendMessage = brainiac->constructString(
          theMove, theMove->moveScore, 0, 0, 0, 0, rack, "no message no cry");
      brainiac->readyToSend = true;

	  if (theMove != nullptr) {
        // * check for starting with a tile on board:
        if (theMove->word[0] >= 0 && theMove->word[0] <= 25) {
          if (theMove->horizontal) {
            theMove->startPosition.COL++;
          } else {
            theMove->startPosition.ROW++;
          }
        }
        std::cout << "Updating Board...\n";
        // *update the board with the human's move
        brainiac->updateBoard(theMove);
        brainiac->MyBoard->print();
        brainiac->isFuckinBitchEmpty =
            (brainiac->isFuckinBitchEmpty) ? false : false;
      }

      //* remove the tiles used from the bag:
      std::vector<char>* temporaryRack =
          Options::unusedRackTiles(&brainiac->getAITiles(), theMove);
      brainiac->AI_Tiles.clear();
      for (int i = 0; i < temporaryRack->size(); ++i) {
        brainiac->AI_Tiles.push_back((*temporaryRack)[i]);
      }

      temporaryRack->clear();
      delete temporaryRack;



      std::vector<char> tiles;

      // * our extra tiles are given to us at NO_CHALLENGE
      for(int i = 0;i < 7;i++){
        if(nochg.tiles[i] != 0){
          char t =  nochg.tiles[i];
          if(t == 100){
            t = ' ';
          }else {
            t = t + 'a' - 1;
          }
          tiles.emplace_back(t);
        }
      }

      brainiac->fillComputerTiles(tiles);
      state = States::IDLE;
    }
  } else if (msgType == MessageTypes::EXCHANGEMSG) {
    if (state == States::AWAIT_EXCHANGE_RESPONSE) {
      auto msg = deserializeOkExchangeMessage(message);
      // TODO: now i have new tiles, should update our agent
      state = States::IDLE;
    } else if (state == States::IDLE) {
      // * other player has exchanged, now we play
      state = States::THINKING;
    } else {
      std::cerr
          << "Undefined state and action received Exchange, current state: "
          << state;
    }
  } else if (msgType == MessageTypes::CHALLENGEMSG) {
  } else {
    // ? this is the default if the message is weird
    std::cerr << "Unknown Message Type, ya bashmo7nds zbt acoadk" << std::endl;
  }

  /* if (!GUIMsg.empty()) {
    std::cout << "Sending to GUI NOWWWWWWW";
    sendMsgToGUI(GUIMsg);
  } */

  if (state == States::AWAIT_AGENT_CHALLENGE) {
    // * we are challenging, huh ?
    // if challenging
    // then await_challenge_response
    // else thinking
  }

  if (state == States::THINKING) {
    // clear the envelope anyway because I might have pollute`  ng should modify
    // state, WIP
    // * should investigate doing an async task right here
    env.clear();

    // auto x = std::async(std::launch::async, playAIMode);
    std::thread t(playAIMode);
    t.detach();
    /* env.insertUInt8(MessageTypes::PLAY);

    std::cout << std::endl << "Please enter play: " << std::flush;

    int row, col, dir, score;
    int tiles[7];
    std::cin >> col >> row >> dir;
    for (int i = 0; i < 7; i++) {
      std::cin >> tiles[i];
      // tiles[i] -= '0';
    }
    std::cin >> score;

    env.insertUInt8(col);
    env.insertUInt8(row);
    env.insertUInt8(dir);
    for (int i = 0; i < 7; i++) {
      env.insertUInt8(tiles[i]);
    }
    env.insert32BitInt(score); */
  }

  // finished the message, if we need to send then send it
  if (sendMessage) {
    auto ser = env.serialize();
    std::cout << "Sending: ";
    print_vec(ser);
    ws_connection->sendBinary(ser);
  }
  std::cout << "HERE: ";
}

int main(int argc, char** argv) {
  // use the default local machine socket
  // 192.168.43.164  
  std::string hostname = "ws://192.168.43.164:8080/";

  board = Board::getBoard();
  brainiac = new GameBrain(new TrainerComm(), board, false);
  brainiac->initialize_computer_vs_computer();

  if (argc == 2) {
    hostname = argv[1];
  }

  #ifdef _WIN32

  INT rc;

  WSADATA wsaData;

  rc = WSAStartup(MAKEWORD(2, 2), &wsaData);

  if (rc) {
    printf("WSAStartup Failed.\n");
    return 1;
  }

#endif

  // * amount of connection retries to the server
  int retries = 0;

  std::cout << "Will try to connect to " << hostname << std::endl;

  while (true) {
    // * try to connect to the host using the library
    ws_connection = WebSocket::from_url(hostname);

    // ! make sure we got the connection, if not fail and exit
    assert(ws_connection);

    // receive binary message as long as there is connection
    // if the connection dies, loop back to try to connect again

    while (ws_connection->getReadyState() != WebSocket::CLOSED) {
      if (readySendServer) {
        std::cout << "Sending the binary";
        print_vec(vecToSend);
        ws_connection->sendBinary(vecToSend);
        vecToSend.clear();
        readySendServer = false;
      }
      /* if (nMove != nullptr && nMove->valid() &&
          nMove->wait_for(std::chrono::seconds(1)) ==
              std::future_status::ready) {
        std::cout << "no seg fault until here" << std::endl;
        BinaryEnvelope env;
        Move* theMove = nMove->get();

        env.insertUInt8(MessageTypes::PLAY);
        env.insertUInt8(theMove->startPosition.COL);
        env.insertUInt8(theMove->startPosition.ROW);
        env.insertUInt8(theMove->horizontal ? 0 : 1);

        // TODO: add

        env.insert32BitInt(theMove->evaluatedScore);

        ws_connection->sendBinary(env.serialize());
        nMove = nullptr;
      } */
      ws_connection->poll();
      ws_connection->dispatchBinary(handle_message);

      // here we are chillin'
      // do something non-blocking !!!!
    }

    // * Reset the state to start a new connection
    state = States::INIT;

    delete ws_connection;

    std::cerr << "The Connection was weirdly closed for the " << ++retries
              << " time, attempting to reconnect..." << std::endl;
  }
	#ifdef _WIN32

	WSACleanup();

	#endif
  return 0;
}

#endif  // COMM_SCRABBLE_CLIENT_CPP