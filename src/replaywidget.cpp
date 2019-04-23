#include <iostream>
#include <QColor>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <set>

#include "parser/protobuf/dota_shared_enums.pb.h"
#include "parser/hero.h"
#include "database_manager.h"
#include "game.h"
#include "games_manager.h"
#include "replaywidget.h"
#include "settings_manager.h"

// Initialize the tool
ReplayWidget::ReplayWidget(QWidget *parent) :
  QWidget(parent)
{
  setupUi(this);
  gamesTable->setColumnWidth(0, 85);
  gamesTable->setColumnWidth(1, 60);
  gamesTable->setColumnWidth(2, 85);
  gamesTable->setColumnWidth(3, 85);
  gamesTable->setColumnWidth(4, 85);

  ClearGameInfoSection();

  connect(&SettingsManager::Instance(), SIGNAL(SteamReplayPathUpdated(const QString &)),
    this, SLOT(ScanReplayFolder()));
  connect(gamesTable, SIGNAL(currentCellChanged(int, int, int, int)),
    this, SLOT(SelectedCellChanged(int, int, int, int)));
  connect(gamesTable, SIGNAL(cellChanged(int, int)),
    this, SLOT(CellDataChanged(int, int)));
}

// Scan *.dem files contained in the replay folder
void ReplayWidget::ScanReplayFolder() {
  QDir replay_dir = QDir(SettingsManager::Instance().GetSteamReplayPath());
  QStringList files = replay_dir.entryList(QStringList(QString("*.dem")),
    QDir::NoDotAndDotDot | QDir::Files,
    QDir::Name);
  for (int i = 0; i < files.count(); i++) {
    files[i].resize(files[i].length() - 4);
    auto game_id = std::stoull(files[i].toStdString());
    auto game = GamesManager::Instance().GetGame(game_id);
    std::string dem_path = SettingsManager::Instance().GetSteamReplayPath().append("/" + files[i] + ".dem").toStdString();
    if (game == nullptr) {
      game = std::shared_ptr<Game>(new Game(game_id, dem_path));
      GamesManager::Instance().InsertGame(game);
    } else {
      game->SetDemPath(dem_path);
    }
  }

  UpdateGameList();
}

void ReplayWidget::UpdateGameList() {
  gamesTable->clearContents();
  gamesTable->setRowCount(static_cast<int>(GamesManager::Instance().GetGames().size()));
  int32_t index = 0;
  for (auto rit = GamesManager::Instance().GetGames().rbegin(); rit != GamesManager::Instance().GetGames().rend(); rit++) {
    QTableWidgetItem *item;

    QColor id_color;
    if (!rit->second->HasReplayOnDisk()) id_color = QColor(255, 0, 0);
    else id_color = QColor(0, 0, 0);
    item = FactoryTableItem(QString::number(rit->first), id_color);
    gamesTable->setItem(index, 0, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->FormatMode()), QColor(0, 0, 0));
    gamesTable->setItem(index, 1, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->FormatEndDate()), QColor(0, 0, 0));
    gamesTable->setItem(index, 2, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->GetParseResult().radiant.tag), QColor(0, 0, 0));
    gamesTable->setItem(index, 3, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->GetParseResult().dire.tag), QColor(0, 0, 0));
    gamesTable->setItem(index, 4, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->GetNote()), QColor(0, 0, 0), true);
    gamesTable->setItem(index, 5, item);

    index++;
  }
}

void ReplayWidget::SelectedCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) {
  if (currentRow == -1)
    return;

  auto game_id = std::stoull(gamesTable->item(currentRow, 0)->text().toStdString());
  std::shared_ptr<Game> game = GamesManager::Instance().GetGame(game_id);
  if (!game->IsReplayParsed()) {
    game->Parse();
    UpdateRowAt(currentRow);
  }

  ClearGameInfoSection();
  PopulateGameInfoSection(game);
};

void ReplayWidget::CellDataChanged(int row, int column) {
  if (column == 5) {
    auto game_id = std::stoull(gamesTable->item(row, 0)->text().toStdString());
    std::string note = gamesTable->item(row, column)->text().toStdString();

    std::shared_ptr<Game> game = GamesManager::Instance().GetGame(game_id);
    game->SetNote(note);
  }
}

void ReplayWidget::UpdateRowAt(int row) {
  auto game_id = std::stoull(gamesTable->item(row, 0)->text().toStdString());
  std::shared_ptr<Game> game = GamesManager::Instance().GetGame(game_id);

  QColor id_color;
  if (!game->HasReplayOnDisk()) id_color = QColor(255, 0, 0);
  else id_color = QColor(0, 0, 0);
  QTableWidgetItem *item = FactoryTableItem(QString::number(game->GetGameId()), id_color);
  gamesTable->setItem(row, 0, item);

  item = FactoryTableItem(QString::fromStdString(game->FormatMode()), QColor(0, 0, 0));
  gamesTable->setItem(row, 1, item);

  item = FactoryTableItem(QString::fromStdString(game->FormatEndDate()), QColor(0, 0, 0));
  gamesTable->setItem(row, 2, item);

  item = FactoryTableItem(QString::fromStdString(game->GetParseResult().radiant.tag), QColor(0, 0, 0));
  gamesTable->setItem(row, 3, item);

  item = FactoryTableItem(QString::fromStdString(game->GetParseResult().dire.tag), QColor(0, 0, 0));
  gamesTable->setItem(row, 4, item);
}

QTableWidgetItem* ReplayWidget::FactoryTableItem(const QString& text, QColor text_color, bool editable) {
  QTableWidgetItem* item = new QTableWidgetItem(text);
  auto brush = item->foreground();
  brush.setColor(text_color);
  item->setForeground(brush);
  if (!editable) 
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
  item->setTextAlignment(Qt::AlignCenter);
  return item;
}

void ReplayWidget::ClearGameInfoSection() {
  radiantWinIcon->hide();
  radiantTeam->setText("");
  direWinIcon->hide();
  direTeam->setText("");
  draftStackedWidget->setCurrentIndex(0);
}

void ReplayWidget::PopulateGameInfoSection(std::shared_ptr<Game> game) {
  // Display Teams
  radiantTeam->setText(QString::fromStdString(game->GetParseResult().radiant.tag));
  direTeam->setText(QString::fromStdString(game->GetParseResult().dire.tag));
  if (game->GetParseResult().winner == RADIANT) {
    radiantWinIcon->show();
  } else if (game->GetParseResult().winner == DIRE) {
    direWinIcon->show();
  }

  // Display draft
  switch (game->GetParseResult().mode) {
  case CM:
    if (game->GetParseResult().draft.draft_sequence.size() == 22) {
      QString prefix;
      if (game->GetParseResult().draft.first_pickban == RADIANT) {
        draftStackedWidget->setCurrentIndex(1);
        prefix = QString("draftCMRadiantPB");
      }
      else {
        draftStackedWidget->setCurrentIndex(2);
        prefix = QString("draftCMDirePB");
      }
      for (std::size_t i = 0; i < game->GetParseResult().draft.draft_sequence.size(); i++) {
        DraftSelection draftSelection = game->GetParseResult().draft.draft_sequence[i];
        QLabel *heroImage = draftStackedWidget->findChild<QLabel *>(prefix + QString::number(i));
        QImage image = QImage(QString::fromStdString(":/images/dota/heroes/" + draftSelection.hero.GetCodeName() + ".png"));
        if (draftSelection.choice == BAN) {
          image = image.convertToFormat(QImage::Format_Grayscale8);
        }
        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap = pixmap.scaledToWidth(100);
        heroImage->setPixmap(pixmap);
      }
    }
    break;
  default:
    break;
  }
}

std::set<uint64_t> ReplayWidget::GetSelectedGameId() {
  std::set<uint64_t> selected{ };
  for (auto& selectionRange : gamesTable->selectedRanges()) {
    for (int i = selectionRange.topRow(); i < (selectionRange.topRow() + selectionRange.rowCount()); ++i) {
      auto game_id = std::stoull(gamesTable->item(i, 0)->text().toStdString());
      selected.insert(game_id);
    }
  }
  return selected;
}

void ReplayWidget::DeleteSelection() {
  auto selection = GetSelectedGameId();
  for (uint64_t id : selection) {
    auto game = GamesManager::Instance().GetGame(id);
    if (game->HasReplayOnDisk()) {
      QFile::remove(QString::fromStdString(game->GetDemPath()));
      game->SetDemPath("");
    }
  }
  SoftDeleteSelection();
}

void ReplayWidget::SoftDeleteSelection() {
  auto selection = GetSelectedGameId();
  for (uint64_t id : selection) {
    auto game = GamesManager::Instance().GetGame(id);
    game->SetNote("");
    DatabaseManager::Instance().RemoveFromDatabase(*game);
    if (!game->HasReplayOnDisk()) {
      GamesManager::Instance().RemoveGame(id);
    }
  }
  UpdateGameList();
}
