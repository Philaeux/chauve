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
void GamesManager::InsertGame(std::shared_ptr<Game> game) {
  games_.insert({ game->GetGameId(), game });
}


// Remove a game from the manager
void GamesManager::RemoveGame(uint64_t game_id) {
  games_.erase(game_id);
}
