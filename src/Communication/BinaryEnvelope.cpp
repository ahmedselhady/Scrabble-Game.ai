#ifndef COMM_BINARY_ENVELOPE_CPP
#define COMM_BINARY_ENVELOPE_CPP

#include "BinaryEnvelope.hpp"

#include <iostream>

BinaryEnvelope::BinaryEnvelope() { buffer = ""; }

void BinaryEnvelope::clear() {
  if (this->buffer.size() == 0) {
    return;
  }

  this->buffer.clear();
}

std::size_t BinaryEnvelope::size() const { return this->buffer.size(); }

void BinaryEnvelope::insertUInt8(uint8_t x) {
  if (x > 255 || x < 0) {
    throw "Type Error: insertUInt8 expects an 8 bit integer.";
  }

  // get the byte representation of a uint8
  auto result = std::bitset<8>(x).to_string();
  // std::cout << x << " bitset: " << result << std::endl;

  this->buffer.append(result);
}

void BinaryEnvelope::insert32BitInt(int x) {
  // I hope the c++ lords will make this big endian for me <3
  auto result = std::bitset<32>(x).to_string();
  this->buffer.append(result);
}

void BinaryEnvelope::insertEnvelope(const BinaryEnvelope& env) {
  this->buffer.append(env.buffer.data());
}

void BinaryEnvelope::insertString(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    uint8_t d = str[i];
    this->insertUInt8(d);
  }
}

std::vector<uint8_t> BinaryEnvelope::serialize() const {
  std::vector<uint8_t> data;

  std::cout << buffer << std::endl;

  for (int i = 0; i < this->buffer.length(); i += 8) {
    auto st = this->buffer.substr(i, 8);
    auto num = std::stoi(st, nullptr, 2);
    data.emplace_back(num);
  }

  return data;
}

#endif  // COMM_BINARY_ENVELOPE_CPP