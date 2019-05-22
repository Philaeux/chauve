#include "game.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "parser/parser.h"
#include "parser/parse_result.h"

Game::Game(uint64_t game_id) :
  game_id_{ game_id },
  dem_path_{ "" },
  parse_state_{ NOT_STARTED },
  parse_result_{ game_id, { }, 0, 0, NONE, { 0, ""}, { 0, ""}, NO_TEAM, {} }
{
}

Game::Game(uint64_t game_id, std::string dem_path) :
  game_id_{ game_id },
  dem_path_{ dem_path },
  parse_state_{ NOT_STARTED },
  parse_result_{ game_id, { }, 0, 0, NONE, { 0, ""}, { 0, ""}, NO_TEAM, {} }
{
}

// Format the end date into a string
std::string Game::FormatEndDate() {
  if (!IsReplayParsed())
    return "";

  std::time_t endTime = (std::time_t) parse_result_.end_datetime_tick;
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&endTime), "%d/%m %H:%M");
  return ss.str();
}

// Format the game mode into a string
std::string Game::FormatMode() {
  if (!IsReplayParsed())
    return "";

  switch (parse_result_.mode) {
  case CM:
    return "CM";
  case AR:
    return "AR";
  case SD:
    return "SD";
  case CD:
    return "CD";
  case RD:
    return "RD";
  case ALL_DRAFT:
    return "MM-AP";
  default:
    return std::to_string(parse_result_.mode);
  }
}

// Start the parse process
void Game::Parse() {
  if (!HasReplayOnDisk()) return;

  parse_state_ = IN_PROGRESS;
  
  Parser parser{};
  auto [parse_state, parse_result] = parser.Parse(dem_path_);
  parse_state_ = parse_state;
  parse_result_ = parse_result;
}
