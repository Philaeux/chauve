#ifndef GAMESMANAGER_H
#define GAMESMANAGER_H

#include <map>

#include "game.h"

// Singleton class containing game data used inside the whole Application.
class GamesManager {

public:
  inline std::map<uint64_t, std::shared_ptr<Game>>& GetGames() { return games_; };

  // Return the information about one game or nullptr
  std::shared_ptr<Game> GetGame(uint64_t game_id);
  // Insert the game inside the container
  // Merge information if already present
  void InsertGame(std::shared_ptr<Game> game);

  // Singleton instance
  static GamesManager& Instance() { return instance_; };

private:
  // Singleton definition
  GamesManager();
  ~GamesManager();
  static GamesManager instance_;

  // Storing all game informations
  std::map<uint64_t, std::shared_ptr<Game>> games_;
};

#endif // GAMESMANAGER_H
