#include "games_manager.h"

#include <map>

// Singleton constructor
GamesManager::GamesManager()
{
}

GamesManager::~GamesManager()
{
}

// Singleton instance
GamesManager GamesManager::instance_{ };

// Return the information about one game or nullptr
std::shared_ptr<Game> GamesManager::GetGame(uint64_t game_id) {
  auto it = games_.find(game_id);
  if (it != games_.end()) {
    return it->second;
  }
  else {
    return std::shared_ptr<Game>(nullptr);
  }
}

// Insert the game inside the container
// Merge information if already present
void GamesManager::InsertGame(std::shared_ptr<Game> game) {
  auto it = games_.find(game->GetGameId());
  if (it == games_.end()) {
    games_.insert({ game->GetGameId(), game });
  }
  else {
    it->second->MergeWith(game);
  }
}
