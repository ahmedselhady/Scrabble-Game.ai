#ifndef COMM_BINARY_ENVELOPE_CPP
#define COMM_BINARY_ENVELOPE_CPP

#include "BinaryEnvelope.hpp"

BinaryEnvelope::BinaryEnvelope() { buffer = ""; }

void BinaryEnvelope::clear() {
  if (this->buffer.size() == 0) {
    return;
  }

  this->buffer.clear();
}

std::size_t BinaryEnvelope::size() const { return this->buffer.size(); }

void BinaryEnvelope::insertUInt8(uint8_t x) {
  // this just returns the
  auto result = std::bitset<8>(x).to_string();
  this->buffer.append(result);
}

void BinaryEnvelope::insert32BitInt(int x) {
  // I hope the c++ lords will make this big endian for me <3
  auto result = std::bitset<32>(x).to_string();
  this->buffer.append(result);
}

void BinaryEnvelope::insertEnvelope(const BinaryEnvelope &env) {
  this->buffer.append(env.serialize());
}

const char *BinaryEnvelope::serialize() const { return this->buffer.c_str(); }

#endif  // COMM_BINARY_ENVELOPE_CPP