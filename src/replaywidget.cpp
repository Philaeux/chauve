#include <QDebug>
#include <QDir>
#include <QString>
#include <QLabel>
#include <QPixmap>

#include "replaywidget.h"
#include "settingsmanager.h"
#include "replaymanager.h"
#include "replay.h"
#include "hero.h"
#include "protobuf/dota_shared_enums.pb.h"

// Initialize the tool
ReplayWidget::ReplayWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

	ClearReplayInfoSection();

    connect(refreshButton, SIGNAL(clicked()),
            this, SLOT(ScanReplayFolder()));
    connect(&SettingsManager::Instance(), SIGNAL(SteamReplayPathUpdated(const QString &)),
            this, SLOT(ScanReplayFolder()));
	connect(gamesTable, SIGNAL(currentCellChanged(int, int, int, int)),
			this, SLOT(ReplayCellChanged(int, int, int, int)));
}

// Scan *.dem files contained in the replay folder
void ReplayWidget::ScanReplayFolder(){
    QDir replay_dir = QDir(SettingsManager::Instance().GetSteamReplayPath());
    QStringList files = replay_dir.entryList(QStringList(QString("*.dem")),
                                             QDir::NoDotAndDotDot | QDir::Files,
                                             QDir::Name);
    for(int i = 0; i < files.count(); i++) {
		files[i].resize(files[i].length() - 4);
		auto game_id = std::stoull(files[i].toStdString());
		Replay* replay = ReplayManager::Instance().GetReplay(game_id);
		if (replay == nullptr) {
			replay = new Replay(game_id, SettingsManager::Instance().GetSteamReplayPath().append("/" + files[i] + ".dem"));
			ReplayManager::Instance().AddReplay(replay);
		}
    }
	
	UpdateGameList();
}

void ReplayWidget::UpdateGameList() {
	gamesTable->clearContents();
	gamesTable->setRowCount(ReplayManager::Instance().replays_.size());
	int32_t index = 0;
	for (auto rit = ReplayManager::Instance().replays_.rbegin(); rit != ReplayManager::Instance().replays_.rend(); rit++) {
		QTableWidgetItem *item;

		item = FactoryTableItem(QString::number(rit->first));
		gamesTable->setItem(index, 0, item);

		item = FactoryTableItem(QString::fromStdString(rit->second->GetEndDate()));
		gamesTable->setItem(index, 2, item);
		
		index++;
	}

}

void ReplayWidget::ReplayCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) {
	if (currentRow == -1)
		return;

	auto game_id = std::stoull(gamesTable->item(currentRow, 0)->text().toStdString());
	Replay* replay = ReplayManager::Instance().GetReplay(game_id);
	if (!replay->IsReplayParsed()) {
		replay->Parse();
		UpdateRowAt(currentRow);
	}

	ClearReplayInfoSection();
	PopulateReplayInfoSection(replay);
};

void ReplayWidget::UpdateRowAt(int row) {
	auto game_id = std::stoull(gamesTable->item(row, 0)->text().toStdString());
	Replay* replay = ReplayManager::Instance().GetReplay(game_id);

	QTableWidgetItem *item = FactoryTableItem(QString::fromStdString(replay->GetEndDate()));
	gamesTable->setItem(row, 2, item);
}

QTableWidgetItem* ReplayWidget::FactoryTableItem(const QString& text) {
	QTableWidgetItem* item = new QTableWidgetItem(text);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	item->setTextAlignment(Qt::AlignCenter);
	return item;
}


void ReplayWidget::ClearReplayInfoSection() {
	radiantWinIcon->hide();
	radiantTeam->setText("");
	direWinIcon->hide();
	direTeam->setText("");
	gameMode->setText("");
	draftStackedWidget->setCurrentIndex(0);
}


void ReplayWidget::PopulateReplayInfoSection(Replay *replay) {
	// Display Teams
	radiantTeam->setText(QString::fromStdString(replay->GetRadiantTeam().tag));
	direTeam->setText(QString::fromStdString(replay->GetDireTeam().tag));
	if (replay->GetGameInfo().winner == 2) {
		radiantWinIcon->show();
	}
	else {
		direWinIcon->show();
	}

	// Display Players
	// TODO

	// Display game mode and draft
	switch (replay->GetGameInfo().mode) {
	case DOTA_GAMEMODE_CM: 
		gameMode->setText(QString("CM"));
		if (replay->GetDraft().size() == 22) {
			QString prefix;
			if (replay->GetDraft()[0].team == 2) {
				draftStackedWidget->setCurrentIndex(1);
				prefix = QString("draftCMRadiantPB");
			}
			else if (replay->GetDraft()[0].team == 3) {
				draftStackedWidget->setCurrentIndex(2);
				prefix = QString("draftCMDirePB");
			}
			for (std::size_t i = 0; i < replay->GetDraft().size(); i++) {
				Hero hero = Hero::FindHeroById(replay->GetDraft()[i].hero_id);
				QLabel *heroImage = draftStackedWidget->findChild<QLabel *>(prefix + QString::number(i));
				QImage image = QImage(QString::fromStdString(":/images/dota/heroes/" + hero.GetName() + ".png"));
				if (!replay->GetDraft()[i].is_pick) {
					image = image.convertToFormat(QImage::Format_Grayscale8);
				}
				QPixmap pixmap = QPixmap::fromImage(image);
				pixmap = pixmap.scaledToWidth(100);
				heroImage->setPixmap(pixmap);
			}
		}
		break;
	case DOTA_GAMEMODE_AR: gameMode->setText(QString("AR")); break;
	case DOTA_GAMEMODE_SD: gameMode->setText(QString("SD")); break;
	case DOTA_GAMEMODE_CD: gameMode->setText(QString("CD")); break;
	case DOTA_GAMEMODE_RD: gameMode->setText(QString("RD")); break;
	case DOTA_GAMEMODE_ALL_DRAFT: gameMode->setText(QString("Matchmaking Draft")); break;
	default: gameMode->setText(QString("??")); break;
	}
}
