#ifndef GAMESMANAGER_H
#define GAMESMANAGER_H

#include <map>
#include <set>

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

  // Filtered collection getter
  inline std::map<uint64_t, std::shared_ptr<Game>>& GetFilteredGames() { return filtered_games_; };
  // Return all filters activated
  inline std::set<std::string>& GetFilterTags() { return filter_tags_; };
  bool AddFilterTag(std::string tag);
  bool RemoveFilterTag(std::string tag);
  bool ClearFilters();
  void RecomputeFilteredGames();

private:
  GamesManager();

  // Storing all game informations
  std::map<uint64_t, std::shared_ptr<Game>> games_;

  // Storing only filtered games
  std::map<uint64_t, std::shared_ptr<Game>> filtered_games_;
  // Active tag filters
  std::set<std::string> filter_tags_;
};

#endif // GAMESMANAGER_H
