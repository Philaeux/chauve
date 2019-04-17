#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

#include "game.h"

// Singleton managing all operations with the database
// Connect to the chauve.db file into the prod folder
// Run migrations on startup to get to the good schema
class DatabaseManager {

public:
  // Singleton instance
  static DatabaseManager& Instance() {
    static DatabaseManager instance;
    return instance;
  };
  DatabaseManager(DatabaseManager const&) = delete;
  void operator=(DatabaseManager const&) = delete;

  // Load application data from database
  void LoadDatabase();
  // Save dirty data to database
  void SaveToDatabase();

private:
  DatabaseManager();

  // Database Methods
  void ApplyMigrationsIfNecessary();

  // Database privates
  QSqlDatabase db_;
  bool db_status_;
};

#endif // DATABASEMANAGER_H
