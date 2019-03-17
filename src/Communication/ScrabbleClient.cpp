#ifndef COMM_SCRABBLE_CLIENT_CPP
#define COMM_SCRABBLE_CLIENT_CPP

//#include "easywsclient/easywsclient.hpp"
#include <assert.h>
#include <iostream>
#include <string>
#include "BinaryEnvelope.hpp"
#include "easywsclient/easywsclient.cpp"  // <-- include only if you don't want compile separately

using easywsclient::WebSocket;
static WebSocket::pointer ws = NULL;

void handle_message(std::vector<uint8_t>& message) {
  // the message type always exist in the first
  // byte of the message
  uint8_t msgType = message[0];

  // always send the envelope unless it doesn't matter
  bool sendMessage = true;
  BinaryEnvelope env;

  /**
   * ! This switch case will be very convulted real soon
   * TODO: Should think how to do it in a better way
   */
  switch (msgType) {
    case MessageTypes::NAME:
      // The server is expecting a 0 response to a "Name" request
      env.insertUInt8(0);
      env.insertString("Wermacht 卐");  // Send our name hardcoded :D
      break;
    /*****************************************************************************/
    case MessageTypes::START:
      auto msg = deserializeReadyMessage(message);

      if (msg.order = 1) {
        // well this is our turn
      }

      break;
      /*****************************************************************************/
    case MessageTypes::END:
      std::cout << "An end packet was received... losing the connection";
      auto msg = deserializeEndMessage(message);
      std::cout << "Our score is " << msg.ourScore
                << ", the other player's score is " << msg.opponentScore
                << std::endl;

      ws->close();
      break;
    default:
      std::cerr << "Unknown Message Type" << std::endl;
      break;
  }

  // finished the message, if we need to send then send it
  if (sendMessage) {
    ws->sendBinary(env.serialize());
  }
}

int main(int argc, char** argv) {
  std::string hostname;

  if (argc > 1) {
    hostname = argv[1];
  } else {
    std::cout << "Enter the socket to connect to: ";
    std::cin >> hostname;
  }

  // use the default local machine socket
  if (hostname.empty()) {
    hostname = "ws://localhost:8080/";
  }

  // amount of connection retries to the server
  int retries = 0;

  std::cout << "Will try to connect to " << hostname << std::endl;

  while (true) {
    // try to connect to the host using the library
    ws = WebSocket::from_url(hostname);

    // make sure we got the connection, if not fail and exit
    assert(ws);

    // receive binary message as long as there is connection
    // if the connection dies, loop back to try to connect again
    while (ws->getReadyState() != WebSocket::CLOSED) {
      ws->poll();
      ws->dispatchBinary(handle_message);

      // here we are chillin'
      // do something non-blocking !!!!
    }

    delete ws;

    std::cerr << "The Connection was weirdly closed for the " << ++retries
              << " time, attempting to reconnect..." << std::endl;
  }

  return 0;
}

#endif  // COMM_SCRABBLE_CLIENT_CPP