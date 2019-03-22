#ifndef COMM_PROTOCOL_HPP
#define COMM_PROTOCOL_HPP

#include <cstdint>
#include <vector>

/**
 * The Messages that we receive and send throught the Websocket
 * to the game judge server
 */
enum MessageTypes {
  NAME,
  START,
  PASS,
  EXCHANGE,
  PLAY,
  NO_CHALLENGE,
  CHALLENGE,
  CHALLENGE_ACCEPTED,
  CHALLENGE_REJECTED,
  INVALID,
  END,
};

/**
 * The states that our agent goes through throughout the game
 */
enum States {
  INIT,
  READY,
  IDLE,
  THINKING,
  AWAIT_EXCHANGE_RESPONSE,
  AWAIT_PLAY_RESPONSE,
  AWAIT_AGENT_CHALLENGE,
  AWAIT_CHALLENGE_RESPONSE,
};

/**
 * These are the reasons the server sends us when the game ends
 */
enum EndReasons {
  ALL_TILES_USED,
  TIME_ENDED,
  CONNECTION_ERROR,
  STOP_BUTTON_PRESSED,
};

// Request means client (us) <== server
// Response means client (us) ==> server and
// this is handled by our BinaryEnvelope

// no instanse of BaseSocket is ever parsed
// it just makes for the template
struct BaseSocketMessage {
  uint8_t type;
};

struct NameRequestMessage : BaseSocketMessage {
  // type == 0
};

struct ReadyRequestMessage : BaseSocketMessage {
  // type == 1
  uint8_t order;
  uint8_t tiles[7];
  uint8_t board[15][15];
  int ourScore;
  int opponentScore;
  int ourRemainingTime;
  int totalRemainingTime;
};

struct InvalidExchangeRequestMessage : BaseSocketMessage {
  // type == 9
  int ourRemainingTime;
  int totalRemainingTime;
};

struct OkExchangeRequestMessage : BaseSocketMessage {
  // type == 3
  uint8_t newTiles[7];
};

struct InvalidPlayRequestMessage : BaseSocketMessage {
  // type == 9
  int ourRemainingTime;
  int totalRemainingTime;
};

struct ChallengeRejectedRequestMessage : BaseSocketMessage {
  // type == 8
  uint8_t tiles[7];  // first format
  int ourRemainingTime;
  int totalRemainingTime;
};

struct NoChallengeRequestMessage : BaseSocketMessage {
  // type == 5
  uint8_t tiles[7];  // first format
};

struct ChallengeAcceptedRequestMessage : BaseSocketMessage {
  // type == 7
};

struct PassRequestMessage : BaseSocketMessage {
  // type == 2
  int ourRemainingTime;
  int totalRemainingTime;
};

struct ExchangeRequestMessage : BaseSocketMessage {
  // type == 3
  uint8_t count;
  int ourRemainingTime;
  int totalRemainingTime;
};

struct PlayRequestMessage : BaseSocketMessage {
  // type == 4
  uint8_t column;     // [1-15]
  uint8_t row;        // [1-150]
  uint8_t direction;  // 0 -> right, 1 -> down
  uint8_t tiles[7];   // second format
  int score;
  int allowedChallengeTime;
  int ourRemainingTime;
  int totalRemainingTime;
};

struct EndRequestMessage : BaseSocketMessage {
  // type == 10
  uint8_t endReason;  // enum EndReasons
  int ourScore;
  int opponentScore;
};

enum MessagesStructs {
  NameRequest,
  ReadyRequest,
  InvalidExchangeRequest,
  OkExchangeRequest,
  InvalidPlayRequest,
  ChallengeRejectedRequest,
  NoChallengeRequest,
  ChallengeAcceptedRequest,
  PassRequest,
  ExchangeRequest,
  PlayRequest,
  EndRequest,
};

/**
 * These are the sizes of the messages byte by byte
 * used to parse the binary into the suitable message
 */
extern std::vector<uint8_t> NameRequestMessagePadding;
extern std::vector<uint8_t> ReadyRequestMessagePadding;
extern std::vector<uint8_t> InvalidExchangeRequestMessagePadding;
extern std::vector<uint8_t> OkExchangeRequestMessagePadding;
extern std::vector<uint8_t> InvalidPlayRequestMessagePadding;
extern std::vector<uint8_t> ChallengeRejectedRequestMessagePadding;
extern std::vector<uint8_t> NoChallengeRequestMessagePadding;
extern std::vector<uint8_t> ChallengeAcceptedRequestMessagePadding;
extern std::vector<uint8_t> PassRequestMessagePadding;
extern std::vector<uint8_t> ExchangeRequestMessagePadding;
extern std::vector<uint8_t> PlayRequestMessagePadding;
extern std::vector<uint8_t> EndRequestMessagePadding;

/**
 * These are de-serialization functions implemented in the .cpp.
 * These convert the binary array to the proper message struct
 */
extern NameRequestMessage deserializeNameMessage(const std::vector<uint8_t>&);
extern ReadyRequestMessage deserializeReadyMessage(const std::vector<uint8_t>&);
extern InvalidExchangeRequestMessage deserializeInvalidExchangeMessage(
    const std::vector<uint8_t>&);
extern InvalidPlayRequestMessage deserializeInvalidPlayMessage(
    const std::vector<uint8_t>&);
extern OkExchangeRequestMessage deserializeOkExchangeMessage(
    const std::vector<uint8_t>&);
extern ChallengeRejectedRequestMessage deserializeChallengeRejectedMessage(
    const std::vector<uint8_t>&);
extern NoChallengeRequestMessage deserializeNoChallengeMessage(
    const std::vector<uint8_t>&);
extern ChallengeAcceptedRequestMessage deserializeChallengeAcceptedMessage(
    const std::vector<uint8_t>&);
extern PassRequestMessage deserializePassMessage(const std::vector<uint8_t>&);
extern ExchangeRequestMessage deserializeExchangeMessage(
    const std::vector<uint8_t>&);
extern PlayRequestMessage deserializePlayMessage(const std::vector<uint8_t>&);
extern EndRequestMessage deserializeEndMessage(const std::vector<uint8_t>&);

#endif