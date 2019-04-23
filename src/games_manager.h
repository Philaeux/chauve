#ifndef GAMESMANAGER_H
#define GAMESMANAGER_H

#include <map>

#include "game.h"

// Singleton class containing game data used inside the whole Application.
class GamesManager {

public:
  // Singleton instance
  static GamesManager& Instance() {
    static GamesManager instance;
    return instance;
  };
  GamesManager(GamesManager const&) = delete;
  void operator=(GamesManager const&) = delete;

  // Game collection getter
  inline std::map<uint64_t, std::shared_ptr<Game>>& GetGames() { return games_; };
  // Return the information about one game or nullptr
  std::shared_ptr<Game> GetGame(uint64_t game_id);
  // Insert the game inside the container
  void InsertGame(std::shared_ptr<Game> game);
  // Remove a game from the container
  void RemoveGame(uint64_t game_id);

private:
  GamesManager();

  // Storing all game informations
  std::map<uint64_t, std::shared_ptr<Game>> games_;
};

#endif // GAMESMANAGER_H
