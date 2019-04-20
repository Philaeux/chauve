#include "database_manager.h"

#include <iostream>
#include <QDir>
#include <QtSql>

#include "games_manager.h"

// Singleton constructor
DatabaseManager::DatabaseManager()
{
  db_ = QSqlDatabase::addDatabase("QSQLITE");
  db_.setDatabaseName(QDir::currentPath() + QString("/chauve.db"));

  db_status_ = db_.open();
  if (db_status_) {
    ApplyMigrationsIfNecessary();
  }
}

// Check the database version and apply migrations if necessary
void DatabaseManager::ApplyMigrationsIfNecessary() {
  QSqlQuery query;
  bool queryResult = query.exec("SELECT * FROM settings WHERE key='version'");
  
  if (!queryResult || !query.next()) {
    db_.close();
    db_status_ = false;
    return;
  }

  int version = query.value(1).toInt();
  switch (version) {
  case 0:
    db_.transaction();
    query.exec("UPDATE settings SET value='1' WHERE key='version'");
    query.exec("CREATE TABLE games(id BIGINT PRIMARY KEY, note TEXT NOT NULL DEFAULT '')");
    db_.commit();
  }
}

// Load application data from database
void DatabaseManager::LoadDatabase() {
  QSqlQuery query;
  if (query.exec("SELECT * FROM games")) {
    while (query.next()) {
      uint64_t game_id = std::stoull(query.value(0).toString().toStdString());
      std::string note = query.value(1).toString().toStdString();
      auto game = GamesManager::Instance().GetGame(game_id);
      if (game == nullptr) {
        game = std::shared_ptr<Game>(new Game(game_id));
        GamesManager::Instance().InsertGame(game);
      }
      game->SetNote(note);
    }
  }
}

void DatabaseManager::SaveToDatabase() {
  QSqlQuery query;
  query.prepare("REPLACE INTO games(id, note) values(:id, :note)");

  for (auto rit = GamesManager::Instance().GetGames().rbegin(); rit != GamesManager::Instance().GetGames().rend(); rit++) {
    query.bindValue(":id", rit->second->GetGameId());
    query.bindValue(":note", QString::fromStdString(rit->second->GetNote()));
    query.exec();
  }
}

void DatabaseManager::RemoveFromDatabase(Game& game) {
  QSqlQuery query;
  query.prepare("DELETE FROM games WHERE id = (:id)");
  query.bindValue(":id", game.GetGameId());
  query.exec();
}
