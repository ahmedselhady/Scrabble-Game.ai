#ifndef COMM_SCRABBLE_CLIENT_CPP
#define COMM_SCRABBLE_CLIENT_CPP

#include <assert.h>
#include <cstdlib>
#include <future>
#include <iostream>
#include <string>
#include "BinaryEnvelope.hpp"
#include "Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "Brain.hpp"
#include "Move.hpp"
#include "SharedClasses/TrainerComm.hpp"
#include "easywsclient/easywsclient.hpp"
//#include "easywsclient/easywsclient.cpp"  // <-- include only if you don't
// want compile separately

using easywsclient::WebSocket;
static WebSocket::pointer ws_connection = nullptr;

static std::string mode = "";

Board* board = nullptr;
GameBrain* brain = nullptr;
bool readyToSend = false;
std::vector<uint8_t> vecToSend;

// this is used to hold the current state of our communcation
States state = States::INIT;

void sendMsgToGUI(std::string str) {
  std::thread t(sendStringToGUI, str);
  t.detach();
}

void print_vec(const std::vector<uint8_t>& msg) {
  std::cout << std::endl;
  for (auto m : msg) {
    std::cout << std::to_string(m) << ", ";
  }
  std::cout << std::endl;
}

void playTeacherMode() {
  auto vec = getMsgFromGUI("MAKE_PASS");
  std::cout << "GOT FROM GUI: ";
  for (auto m : vec) {
    std::cout << m << " ";
  }
  std::cout << std::endl;
}

void playAIMode() {
  auto theMove = brain->work_computer_vs_computer();

  BinaryEnvelope env;
  env.insertUInt8(MessageTypes::PLAY);
  env.insertUInt8(theMove->startPosition.COL + 1);
  env.insertUInt8(theMove->startPosition.ROW + 1);
  env.insertUInt8(theMove->horizontal ? 0 : 1);

  for (int i = 0; i < theMove->word.length(); i++) {
    if (theMove->word[i] >= 0 && theMove->word[i] <= 25) {
      continue;
    } else if (theMove->word[i] >= 65 && theMove->word[i] <= 90) {
      env.insertUInt8((uint8_t)theMove->word[i] + 36);
    } else {
      env.insertUInt8((uint8_t)theMove->word[i] - 96);
    }
  }
  int len = theMove->word.length();
  while (len < 7) {
    env.insertUInt8(0);
    len++;
  }

  env.insert32BitInt(4);
  auto ser = env.serialize();
  print_vec(ser);
  // ws_connection->sendBinary(ser);
  readyToSend = true;
  vecToSend = ser;
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

    board = Board::getBoard();

    GUIMsg += "BOARD / ";
    for (int i = 0; i < 15; i++) {
      for (int j = 0; j < 15; j++) {
        GUIMsg += std::to_string(smsg.board[i][j]) + " ";
      }
    }
    brain->setTiles(smsg.tiles);
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
  } else if (msgType == MessageTypes::PASS) {
    auto passFromOpponent = deserializePassMessage(message);

    // other player passed, we should play
    state = States::THINKING;

    // ? state should be known after the play is known
  } else if (msgType == MessageTypes::PLAY) {
    auto playFromOpponent = deserializePlayMessage(message);
    // TODO: here we can update the gui maybe
    // TODO(Salem): here u can access play data

    state = States::AWAIT_AGENT_CHALLENGE;
  } else if (msgType == MessageTypes::INVALID) {
    if (state == States::AWAIT_PLAY_RESPONSE) {
      auto invalidPlay = deserializeInvalidPlayMessage(message);
      state = States::THINKING;
    } else if (state == States::AWAIT_EXCHANGE_RESPONSE) {
      auto invalidEx = deserializeInvalidExchangeMessage(message);
      state = States::THINKING;
    } else {
      std::cerr << "Undefined state and action Invalid and state: " << state;
    }
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

    // * our extra tiles are given to us at NO_CHALLENGE

    if (state == States::AWAIT_CHALLENGE_RESPONSE) {
      state = States::THINKING;
    } else if (state == States::AWAIT_AGENT_CHALLENGE) {
      state = States::THINKING;
    } else if (state == States::AWAIT_PLAY_RESPONSE) {
      brain->setTiles(nochg.tiles);
      state = States::IDLE;
    }
  } else if (msgType == MessageTypes::EXCHANGE) {
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
  } else if (msgType == MessageTypes::CHALLENGE) {
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
    sendMessage = false;
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
  std::string hostname = "ws://localhost:8080/";

  if (argc == 2) {
    mode = argv[1];
  }

  if (argc == 3) {
    hostname = argv[2];
  }

  brain = new GameBrain();

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
      if (readyToSend) {
        std::cout << "Sending the binary";
        print_vec(vecToSend);
        ws_connection->sendBinary(vecToSend);
        vecToSend.clear();
        readyToSend = false;
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
      // TODO: maybe send a non-blocking message to the GUI, maybe ?
    }

    // * Reset the state to start a new connection
    state = States::INIT;

    delete ws_connection;

    std::cerr << "The Connection was weirdly closed for the " << ++retries
              << " time, attempting to reconnect..." << std::endl;
  }
  // 4, 7, 8, 0, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4,
  // 4, 7, 8, 0, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4,

  return 0;
}

#endif  // COMM_SCRABBLE_CLIENT_CPP