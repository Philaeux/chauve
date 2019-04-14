#include <QDebug>
#include <QDir>
#include <QString>
#include <QLabel>
#include <QPixmap>

#include "replaywidget.h"
#include "settingsmanager.h"
#include "parser/protobuf/dota_shared_enums.pb.h"
#include "parser/hero.h"
#include "game.h"
#include "games_manager.h"

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

  connect(refreshButton, SIGNAL(clicked()),
    this, SLOT(ScanReplayFolder()));
  connect(&SettingsManager::Instance(), SIGNAL(SteamReplayPathUpdated(const QString &)),
    this, SLOT(ScanReplayFolder()));
  connect(gamesTable, SIGNAL(currentCellChanged(int, int, int, int)),
    this, SLOT(ReplayCellChanged(int, int, int, int)));
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
    auto game = std::shared_ptr<Game>(new Game(
      game_id, 
      SettingsManager::Instance().GetSteamReplayPath().append("/" + files[i] + ".dem").toStdString()
    ));
    GamesManager::Instance().InsertGame(game);
  }

  UpdateGameList();
}

void ReplayWidget::UpdateGameList() {
  gamesTable->clearContents();
  gamesTable->setRowCount(static_cast<int>(GamesManager::Instance().GetGames().size()));
  int32_t index = 0;
  for (auto rit = GamesManager::Instance().GetGames().rbegin(); rit != GamesManager::Instance().GetGames().rend(); rit++) {
    QTableWidgetItem *item;

    item = FactoryTableItem(QString::number(rit->first));
    gamesTable->setItem(index, 0, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->FormatMode()));
    gamesTable->setItem(index, 1, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->FormatEndDate()));
    gamesTable->setItem(index, 2, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->GetParseResult().radiant.tag));
    gamesTable->setItem(index, 3, item);

    item = FactoryTableItem(QString::fromStdString(rit->second->GetParseResult().dire.tag));
    gamesTable->setItem(index, 4, item);

    index++;
  }
}

void ReplayWidget::ReplayCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) {
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

void ReplayWidget::UpdateRowAt(int row) {
  auto game_id = std::stoull(gamesTable->item(row, 0)->text().toStdString());
  std::shared_ptr<Game> game = GamesManager::Instance().GetGame(game_id);

  QTableWidgetItem *item = FactoryTableItem(QString::fromStdString(game->FormatMode()));
  gamesTable->setItem(row, 1, item);

  item = FactoryTableItem(QString::fromStdString(game->FormatEndDate()));
  gamesTable->setItem(row, 2, item);

  item = FactoryTableItem(QString::fromStdString(game->GetParseResult().radiant.tag));
  gamesTable->setItem(row, 3, item);

  item = FactoryTableItem(QString::fromStdString(game->GetParseResult().dire.tag));
  gamesTable->setItem(row, 4, item);
}

QTableWidgetItem* ReplayWidget::FactoryTableItem(const QString& text) {
  QTableWidgetItem* item = new QTableWidgetItem(text);
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
  }
  else {
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
