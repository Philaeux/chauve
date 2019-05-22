#include "parser/parser.h"

#include <fstream>

#include "parser/protobuf/demo.pb.h"
#include "parser/protobuf/dota_shared_enums.pb.h"
#include "snappy.h"

// Create the parser with the default snappy buffer size
Parser::Parser()
{
  snappy_buffer_ = new char[Parser::kSnappyBufferDefaultSize];
}

// Create the parser with a specific snappy buffer
Parser::Parser(uint32_t snappy_buffer_size)
{
  snappy_buffer_ = new char[snappy_buffer_size];
}

// Parse a dem file
std::pair<ParseState, ParseResult> Parser::Parse(std::string dem_path) {
  ParseResult parse_result{ 0, { }, 0, 0, NONE, { 0, ""}, { 0, ""}, NO_TEAM, {} };

  // Read dem file into memory
  std::fstream is(dem_path, std::ios::in | std::ios::binary);
  if (!is) {
    return { ERROR_FILE_OPEN, parse_result };
  }

  uint32_t dem_size = 0; // Dem size in bytes

  const auto file_start = is.tellg();
  is.seekg(0, std::ios::end);
  dem_size = is.tellg() - file_start;
  is.seekg(0, std::ios::beg);

  std::unique_ptr<char[]> dem_data{ new char[dem_size] }; // All dem file
  is.read(dem_data.get(), dem_size);

  // Parse Header
  char* head = dem_data.get(); // Pointer to the head of the parsing
  DemHeader* header = (DemHeader*)head;

  if (std::string(header->headerid) != std::string("PBDEMS2")) {
    return { ERROR_INVALID_HEADER, parse_result };
  }

  // First parse summary
  head = dem_data.get() + header->offset_summary;

  DemPacket packet;
  head = ReadPacket(packet, head);

  CDemoFileInfo info;
  info.ParseFromArray(packet.data, packet.size); // Here info has all
  auto game_info = info.game_info().dota();
  if (game_info.has_match_id()) parse_result.game_id = game_info.match_id();
  if (game_info.has_leagueid()) parse_result.league_id = game_info.leagueid();
  if (game_info.has_game_mode()) parse_result.mode = static_cast<GameMode>(game_info.game_mode());
  if (game_info.has_radiant_team_id()) parse_result.radiant.id = game_info.radiant_team_id();
  if (game_info.has_radiant_team_tag()) parse_result.radiant.tag = game_info.radiant_team_tag();
  if (game_info.has_dire_team_id()) parse_result.dire.id = game_info.dire_team_id();
  if (game_info.has_dire_team_tag()) parse_result.dire.tag = game_info.dire_team_tag();
  if (game_info.has_end_time()) parse_result.end_datetime_tick = game_info.end_time(); 
  if (game_info.has_game_winner()) {
    if (game_info.game_winner() == 2)
      parse_result.winner = RADIANT;
    else
      parse_result.winner = DIRE;
  }

  if (game_info.picks_bans_size() > 0) {
    auto first_pickban = game_info.picks_bans(0);
    if (first_pickban.team() == 2)
      parse_result.draft.first_pickban = RADIANT;
    else
      parse_result.draft.first_pickban = DIRE;
  }
  for (auto &select_event : *game_info.mutable_picks_bans()) {
    DraftChoice pb_choice;
    if (select_event.is_pick()) pb_choice = PICK; else pb_choice = BAN;
    Side pb_side;    
    if (select_event.team() == 2) pb_side = RADIANT; else pb_side = DIRE;
    
    Hero pb_hero { select_event.hero_id() };
    parse_result.generated_tags.insert(pb_hero.GetTagName());
    if(pb_choice == PICK) parse_result.generated_tags.insert(pb_hero.GetTagName() + "-pick");
    else parse_result.generated_tags.insert(pb_hero.GetTagName() + "-ban");

    parse_result.draft.draft_sequence.push_back({ pb_side, pb_choice, pb_hero });
  }

  // Tags
  if (parse_result.radiant.tag != "") {
    auto lower = parse_result.radiant.tag;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    parse_result.generated_tags.insert(lower);
    parse_result.generated_tags.insert(lower + "-radiant");
  }
  if (parse_result.dire.tag != "") {
    auto lower = parse_result.dire.tag;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    parse_result.generated_tags.insert(lower);
    parse_result.generated_tags.insert(lower + "-dire");
  }
  if (parse_result.league_id != 0) {
    parse_result.generated_tags.insert("league");
    parse_result.generated_tags.insert("league-" + std::to_string(parse_result.league_id));
  }

  // Get back to first packet
  // TODO PARSE ALL
  head = dem_data.get() + sizeof(DemHeader);

  return { SUCCESS, parse_result };
}

// Read one packet using the snappy buffer if necessary
char* Parser::ReadPacket(DemPacket& msg, char* buffer) {
  uint8_t bytes_read;

  msg.type = ReadVarint32(buffer, bytes_read);
  buffer += bytes_read;

  msg.tick = ReadVarint32(buffer, bytes_read);
  buffer += bytes_read;

  msg.size = ReadVarint32(buffer, bytes_read);
  buffer += bytes_read;

  msg.data = buffer;

  auto new_head = buffer + msg.size;

  if (msg.type & DEM_IsCompressed) {
    size_t uncompressed_size = 0;
    snappy::GetUncompressedLength(msg.data, msg.size, &uncompressed_size);
    snappy::RawUncompress(msg.data, msg.size, snappy_buffer_);

    msg.type = msg.type & ~DEM_IsCompressed;
    msg.data = snappy_buffer_;
    msg.size = (uint32_t)uncompressed_size;
  }

  return new_head;
}

// Read a variable int
uint32_t Parser::ReadVarint32(const char* data, uint8_t& read) {
  uint32_t result = 0;      // result
  char tmp;                 // holds last read value
  read = 0;                 // make sure read is zeroed
  std::size_t position = 0;

  do {
    tmp = data[position++];
    result |= (uint32_t)(tmp & 0x7F) << (7 * read);
    ++read;
  } while (tmp & 0x80);

  return result;
}
