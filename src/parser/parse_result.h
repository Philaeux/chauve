#ifndef PARSE_RESULT_H
#define PARSE_RESULT_H

#include <cstdint>
#include <string>
#include <set>
#include "parser/hero.h"

// A Dota team
struct Team {
  // Valve internal id for the team
  uint32_t id;
  // In-game tag
  std::string tag;
};

// All possible Dota modes
enum GameMode {
  NONE = 0,
  AP = 1,
  CM = 2,
  RD = 3,
  SD = 4,
  AR = 5,
  INTRO = 6,
  HW = 7,
  REVERSE_CM = 8,
  XMAS = 9,
  TUTORIAL = 10,
  MO = 11,
  LP = 12,
  POOL1 = 13,
  FH = 14,
  CUSTOM = 15,
  CD = 16,
  BD = 17,
  ABILITY_DRAFT = 18,
  EVENT = 19,
  ARDM = 20,
  MID_1V1 = 21,
  ALL_DRAFT = 22,
  TURBO = 23,
  MUTATION = 24
};

// During a draft, possible choices
enum DraftChoice {
  PICK = 0,
  BAN = 1
};

// All possible sides in a Dota game
enum Side {
  RADIANT = 0,
  DIRE = 1,
  BROADCASTER = 2,
  SPECTATOR = 3,
  PLAYER_POOL = 4,
  NO_TEAM = 5
};

// A Drafting step
struct DraftSelection {
  // Side doing the choice
  Side side;
  // Choice made
  DraftChoice choice;
  // Hero concerned by this choice
  Hero hero;
};

// A Draft
struct Draft {
  // First side picking or baning a Hero
  Side first_pickban;
  // Draft sequence
  std::vector<DraftSelection> draft_sequence;
};

// States possible for a Parser::Parse call.
enum ParseState {
  NOT_STARTED = 0,         // No replay work as been done on the replay
  SUCCESS = 1,             // Success
  IN_PROGRESS = 2,         // Currently running
  ERROR_GENERIC = 3,       // Generic error return code
  ERROR_FILE_OPEN = 4,     // The input file to decode is not present or invalid
  ERROR_INVALID_HEADER = 5 // Dem header packet is invalid
};

// Possible data to extract during the parsing process
struct ParseResult {
  uint64_t game_id;
  std::set<std::string> generated_tags;
  uint32_t league_id;
  uint32_t end_datetime_tick;
  GameMode mode;
  Team radiant;
  Team dire;
  Side winner;
  Draft draft;
};

#endif // PARSE_RESULT_H
