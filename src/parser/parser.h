#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <tuple>
#include <string>

#include "parser/hero.h"
#include "parser/parse_result.h"

// Single packet present at the start of a dem file
struct DemHeader {
  // Used for verification purposes, needs to equal "PBDEMS2"
  char headerid[8];
  // Points to the location of the game summary
  int32_t offset_summary;
  // Points to another packet
  int32_t offset_2;
};

// A single dem packet
struct DemPacket {
  // Tick this messages was emitted at
  int32_t tick;
  // Message type
  uint32_t type;
  // Size of data
  uint32_t size;
  // Points to start of message
  char* data;
};

// Parser class doing the job
// Contains a buffer for snappy encoded Packets
class Parser {
public:
  // Create the parser with the default snappy buffer size
  Parser();
  // Create the parser with a specific snappy buffer
  Parser(uint32_t snappy_buffer_size);

  // Parse a dem file
  std::pair<ParseState, ParseResult> Parse(std::string dem_path);
private:
  // Buffer to decode packets encoded using snappy
  char* snappy_buffer_;
  // Default size of the snappy buffer
  static const int kSnappyBufferDefaultSize{ 409600 };

  // Read one packet using the snappy buffer if necessary
  char* ReadPacket(DemPacket& msg, char* buffer);
  // Read a variable int
  uint32_t ReadVarint32(const char* data, uint8_t& read);
};

#endif // PARSER_H
