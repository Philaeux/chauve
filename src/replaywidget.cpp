#include <QDebug>
#include <QDir>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "replaywidget.h"
#include "settingsmanager.h"
#include "replaymanager.h"
#include "replay.h"
#include "protobuf/dota_shared_enums.pb.h"

// Initialize the tool
ReplayWidget::ReplayWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

	HideReplayInfoSection();

    connect(refreshButton, SIGNAL(clicked()),
            this, SLOT(ScanReplayFolder()));
    connect(&SettingsManager::Instance(), SIGNAL(SteamReplayPathUpdated(const QString &)),
            this, SLOT(ScanReplayFolder()));
    connect(replayList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(ChangeSelectedReplay(QListWidgetItem *)));
}

// Scan *.dem files contained in the replay folder
void ReplayWidget::ScanReplayFolder(){
    QDir replay_dir = QDir(SettingsManager::Instance().GetSteamReplayPath());
    replayList->clear();
    QStringList files = replay_dir.entryList(QStringList(QString("*.dem")),
                                             QDir::NoDotAndDotDot | QDir::Files,
                                             QDir::Name);
	files.sort();
    for(int i = 0; i < files.count(); i++) {
        files[i].resize(files[i].length()-4);
    }
	std::reverse(files.begin(), files.end());
    replayList->addItems(files);
}

void ReplayWidget::ChangeSelectedReplay(QListWidgetItem *selected_replay) {
    if (selected_replay == nullptr)
        return;

    Replay* replay = ReplayManager::Instance().GetReplay(selected_replay->text());
    if (replay == nullptr) {
        replay = new Replay(selected_replay->text(),
                            SettingsManager::Instance().GetSteamReplayPath()
                                                       .append("/" + selected_replay->text() + ".dem"));
        ReplayManager::Instance().AddReplay(replay);
    }
    if (!replay->IsReplayParsed()) {
        replay->Parse();
    }

	HideReplayInfoSection();
	DisplayReplayInfoSection(replay);
}

void ReplayWidget::HideReplayInfoSection() {
	radiantWinIcon->hide();
	radiantTeam->setText("");
	direWinIcon->hide();
	direTeam->setText("");
	gameEndDate->setText("");
	gameMode->setText("");
	gameEndDate->setText("");
}


void ReplayWidget::DisplayReplayInfoSection(Replay *replay) {
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

	// Display game mode and time
	switch (replay->GetGameInfo().mode) {
	case DOTA_GAMEMODE_CM: gameMode->setText(QString("CM")); break;
	case DOTA_GAMEMODE_AR: gameMode->setText(QString("AR")); break;
	case DOTA_GAMEMODE_SD: gameMode->setText(QString("SD")); break;
	case DOTA_GAMEMODE_CD: gameMode->setText(QString("CD")); break;
	case DOTA_GAMEMODE_RD: gameMode->setText(QString("RD")); break;
	case DOTA_GAMEMODE_ALL_DRAFT: gameMode->setText(QString("Matchmaking Draft")); break;
	default: gameMode->setText(QString("??")); break;
	}
	
	std::time_t endTime = (std::time_t) replay->GetGameInfo().end_time;
	std::stringstream ss;
	ss << std::put_time(std::gmtime(&endTime), "%e/%m %H:%M GMT");
	gameEndDate->setText(QString::fromStdString(ss.str()));

	// Display Draft
	// TODO
}
