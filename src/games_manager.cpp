#include "games_manager.h"

#include <map>

// Singleton constructor
GamesManager::GamesManager()
{
}

// Return the information about one game or nullptr
std::shared_ptr<Game> GamesManager::GetGame(uint64_t game_id)
{
  auto it = games_.find(game_id);
  if (it != games_.end()) {
    return it->second;
  }
  else {
    return std::shared_ptr<Game>(nullptr);
  }
}

// Insert the game inside the container
void GamesManager::InsertGame(std::shared_ptr<Game> game)
{
  auto ret = games_.insert({ game->GetGameId(), game });
  bool changed = ret.second;
  if (changed) RecomputeFilteredGames();
}

// Remove a game from the manager
void GamesManager::RemoveGame(uint64_t game_id)
{
  bool changed = games_.erase(game_id);
  if (changed) RecomputeFilteredGames();
}

bool GamesManager::AddFilterTag(std::string tag) 
{
  auto ret = filter_tags_.insert(tag);
  bool changed = ret.second;
  if (changed) RecomputeFilteredGames();
  return changed;
}

bool GamesManager::RemoveFilterTag(std::string tag) {
  bool changed = filter_tags_.erase(tag);
  if (changed) RecomputeFilteredGames();
  return changed;
}

bool GamesManager::ClearFilters() 
{
  if (filter_tags_.empty()) return false;

  filter_tags_.clear();
  RecomputeFilteredGames();

  return true;
}

void GamesManager::RecomputeFilteredGames() 
{
  filtered_games_.clear();

  for (auto rit = games_.rbegin(); rit != games_.rend(); rit++) {
    bool add = true;
    if (filter_tags_.size() != 0) {
      for (auto tag : filter_tags_) {
        std::string compare_tag = tag;
        int expected = 0;
        if (compare_tag[0] == '!') {
          compare_tag = tag.substr(1);
          expected = 1;
        }
        if (rit->second->GetParseResult().generated_tags.count(compare_tag) == expected) {
          add = false;
          break;
        }
      }
    }

    if (add) filtered_games_.insert({ rit->second->GetGameId(), rit->second });
  }
}
