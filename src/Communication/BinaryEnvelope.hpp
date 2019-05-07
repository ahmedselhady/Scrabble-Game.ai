#ifndef COMM_BINARY_ENVELOPE_HPP
#define COMM_BINARY_ENVELOPE_HPP

#include <bitset>
#include <cstdint>
#include <string>
#include <vector>
#include "CommStructs.hpp"

/**
 * class: BinaryEnvelope
 *      This wraps a binary representation for
 *      the message that gets sent through WS.
 */
class BinaryEnvelope {
  std::string buffer;

 public:
  /**
   * function: BinaryEnvelope
   *      This wraps a binary representation for the structs
   * inputs:
   *      void
   * returns:
   *      BinaryEnvelope
   */
  BinaryEnvelope();

  /**
   * function: clear
   *      This function clears the binary inside
   * inputs:
   *      void
   * returns:
   *      void
   */
  void clear(void);

  /**
   * function: size
   *      This function returns how many bits are there in the envelope
   * inputs:
   *      void
   * returns:
   *      size_t
   */
  std::size_t size(void) const;

  /**
   * function: insert32BitInt
   *      This function appends a signed 32 bit integer to the
   *      binary message at the back
   * inputs:
   *      int
   * returns:
   *      void
   */
  void insert32BitInt(int);

  /**
   * function: insertUInt8
   *      This function appends an un-signed 8 bit integer to the
   *      binary message at the back
   * inputs:
   *      uint8_t
   * returns:
   *      void
   */
  void insertUInt8(uint8_t);

  /**
   * function: insertEnvelope
   *      This function appends a signed 32 bit integer to the
   *      binary message at the back
   * inputs:
   *      const BinaryEnvelope &
   * returns:
   *      void
   */
  void insertEnvelope(const BinaryEnvelope&);

  void insertString(std::string);

  /**
   * function: serialize
   *      This main function to get access to the "binary"
   *      array to send across the wire
   * inputs:
   *      void
   * returns:
   *      const char *
   */
  std::vector<uint8_t> serialize() const;

};

#endif  // COMM_BINARY_ENVELOPE_HPP