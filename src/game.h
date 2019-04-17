#ifndef GAME_H
#define GAME_H

#include "parser/parser.h"

// A Dota Game
// Hold multiple informations used in all the application
class Game {

public:
  Game(uint64_t game_id);
  Game(uint64_t game_id, std::string dem_path);

  inline uint64_t GetGameId() { return game_id_; };
  inline std::string GetDemPath() { return dem_path_; };
  inline void SetDemPath(std::string dem_path) { dem_path_ = dem_path; };
  inline bool HasReplayOnDisk() { return dem_path_ != ""; };
  inline std::string GetNote() { return note_; };
  inline void SetNote(std::string note) { note_ = note; };
  inline bool IsReplayParsed() { return parse_state_ == SUCCESS; };
  inline ParseResult GetParseResult() { return parse_result_; };

  // Format the end date into a string
  std::string FormatEndDate();
  // Format the game mode into a string
  std::string FormatMode();
  // Start the parse process
  void Parse();

private:
  // Valve unique game identifier
  uint64_t game_id_;
  // System path to the replay file if it exists, empty otherwise
  std::string dem_path_;
  // User defined note, empty by
  std::string note_;
  // Status of the parse process
  ParseState parse_state_;
  // Parse result
  ParseResult parse_result_;
};

#endif // GAME_H
