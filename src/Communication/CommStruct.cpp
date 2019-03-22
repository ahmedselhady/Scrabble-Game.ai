#ifndef COMM_PROTOCOL_CPP
#define COMM_PROTOCOL_CPP

#include <cstdint>
#include <vector>
#include "CommStructs.hpp"

std::vector<uint8_t> NameRequestMessagePadding = {8};

std::vector<uint8_t> ReadyRequestMessagePadding = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 32};

std::vector<uint8_t> InvalidExchangeRequestMessagePadding = {8, 32, 32};

std::vector<uint8_t> OkExchangeRequestMessagePadding = {8, 8, 8, 8, 8, 8, 8, 8};

std::vector<uint8_t> InvalidPlayRequestMessagePadding = {8, 32, 32};

std::vector<uint8_t> ChallengeRejectedRequestMessagePadding = {8, 8, 8, 8,  8,
                                                               8, 8, 8, 32, 32};

std::vector<uint8_t> NoChallengeRequestMessagePadding = {8, 8, 8, 8,
                                                         8, 8, 8, 8};

std::vector<uint8_t> ChallengeAcceptedRequestMessagePadding = {8};

std::vector<uint8_t> PassRequestMessagePadding = {8, 32, 32};

std::vector<uint8_t> ExchangeRequestMessagePadding = {8, 8, 32, 32};

std::vector<uint8_t> PlayRequestMessagePadding = {8, 8, 8, 8,  8,  8,  8, 8,
                                                  8, 8, 8, 32, 32, 32, 32};

std::vector<uint8_t> EndRequestMessagePadding = {8, 8, 32, 32};

/*****************************************************************************/

NameRequestMessage deserializeNameMessage(const std::vector<uint8_t>& binary) {
  NameRequestMessage msg;
  msg.type = binary[0];
  return msg;
};

ReadyRequestMessage deserializeReadyMessage(
    const std::vector<uint8_t>& binary) {
  ReadyRequestMessage msg;
  int index = 0;

  msg.type = binary[index++];
  msg.order = binary[index++];
  // parse the tile, 7
  for (int i = 0; i < 7; i++) {
    msg.tiles[i] = binary[index++];
  }
  // parse the board, 15*15
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      msg.board[i][j] = binary[index++];
    }
  }

  msg.ourScore = binary[index++] << 24 | binary[index++] << 16 |
                 binary[index++] << 8 | binary[index++];
  msg.opponentScore = binary[index++] << 24 | binary[index++] << 16 |
                      binary[index++] << 8 | binary[index++];
  msg.ourRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                         binary[index++] << 8 | binary[index++];
  msg.totalRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                           binary[index++] << 8 | binary[index++];
  return msg;
};

InvalidExchangeRequestMessage deserializeInvalidExchangeMessage(
    const std::vector<uint8_t>& binary) {
  InvalidExchangeRequestMessage msg;
  int index = 0;
  msg.type = binary[index];
  msg.ourRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                         binary[index++] << 8 | binary[index++];
  msg.totalRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                           binary[index++] << 8 | binary[index++];
  return msg;
};

InvalidPlayRequestMessage deserializeInvalidPlayMessage(
    const std::vector<uint8_t>& binary) {
  InvalidPlayRequestMessage msg;
  int index = 0;
  msg.type = binary[index];
  msg.ourRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                         binary[index++] << 8 | binary[index++];
  msg.totalRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                           binary[index++] << 8 | binary[index++];
  return msg;
};

OkExchangeRequestMessage deserializeOkExchangeMessage(
    const std::vector<uint8_t>& binary) {
  OkExchangeRequestMessage msg;
  int index = 0;
  msg.type = binary[index++];
  for (int i = 0; i < 7; i++) {
    msg.newTiles[i] = binary[index++];
  }
  return msg;
};

ChallengeRejectedRequestMessage deserializeChallengeRejectedMessage(
    const std::vector<uint8_t>& binary) {
  ChallengeRejectedRequestMessage msg;
  int index = 0;
  msg.type = binary[index++];
  for (int i = 0; i < 7; i++) {
    msg.tiles[i] = binary[index++];
  }
  msg.ourRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                         binary[index++] << 8 | binary[index++];
  msg.totalRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                           binary[index++] << 8 | binary[index++];
  return msg;
};

NoChallengeRequestMessage deserializeNoChallengeMessage(
    const std::vector<uint8_t>& binary) {
  NoChallengeRequestMessage msg;
  int index = 0;
  msg.type = binary[index++];
  for (int i = 0; i < 7; i++) {
    msg.tiles[i] = binary[index++];
  }
  return msg;
};

ChallengeAcceptedRequestMessage deserializeChallengeAcceptedMessage(
    const std::vector<uint8_t>& binary) {
  ChallengeAcceptedRequestMessage msg;

  msg.type = binary[0];

  return msg;
};

PassRequestMessage deserializePassMessage(const std::vector<uint8_t>& binary) {
  PassRequestMessage msg;
  int index = 0;
  msg.type = binary[index++];
  msg.ourRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                         binary[index++] << 8 | binary[index++];
  msg.totalRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                           binary[index++] << 8 | binary[index++];
  return msg;
};

ExchangeRequestMessage deserializeExchangeMessage(
    const std::vector<uint8_t>& binary) {
  ExchangeRequestMessage msg;
  int index = 0;
  msg.type = binary[index++];
  msg.count = binary[index++];
  msg.ourRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                         binary[index++] << 8 | binary[index++];
  msg.totalRemainingTime = binary[index++] << 24 | binary[index++] << 16 |
                           binary[index++] << 8 | binary[index++];
  return msg;
};

PlayRequestMessage deserializePlayMessage(const std::vector<uint8_t>& binary) {
  PlayRequestMessage msg;
  // TODO: Ahmed Hussein Complete this
  return msg;
};

EndRequestMessage deserializeEndMessage(const std::vector<uint8_t>& binary) {
  EndRequestMessage msg;
  int index = 0;
  msg.type = binary[index++];
  msg.endReason = binary[index++];
  msg.ourScore = binary[index++] << 24 | binary[index++] << 16 |
                 binary[index++] << 8 | binary[index++];
  msg.opponentScore = binary[index++] << 24 | binary[index++] << 16 |
                      binary[index++] << 8 | binary[index++];
  return msg;
};

#endif