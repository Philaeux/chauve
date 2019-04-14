#ifndef GAME_H
#define GAME_H

#include "parser/parser.h"

class Game {

public:
  Game(uint64_t game_id, std::string dem_path);

  inline uint64_t GetGameId() { return game_id_; };
  inline std::string GetDemPath() { return dem_path_; };
  inline bool HasReplayOnDisk() { return dem_path_ != ""; };
  inline bool IsReplayParsed() { return parse_state_ == SUCCESS; };
  inline ParseResult GetParseResult() { return parse_result_; };

  // Format the end date into a string
  std::string FormatEndDate();
  // Format the game mode into a string
  std::string FormatMode();
  // Start the parse process
  void Parse();
  // Merge the data contained in the game object into this object
  void MergeWith(std::shared_ptr<Game> game);

private:
  // Valve unique game identifier
  uint64_t game_id_;
  // System path to the replay file if it exists, empty otherwise
  std::string dem_path_;
  // Status of the parse process
  ParseState parse_state_;
  // Parse result
  ParseResult parse_result_;
};

#endif // GAME_H
