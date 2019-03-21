#include <QDebug>
#include <QDir>

#include "replaywidget.h"
#include "settingsmanager.h"
#include "replaymanager.h"
#include "replay.h"

// Initialize the tool
ReplayWidget::ReplayWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

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
    for(int i = 0; i < files.count(); i++) {
        files[i].resize(files[i].length()-4);
    }
    replayList->addItems(files);
}

void ReplayWidget::ChangeSelectedReplay(QListWidgetItem *selected_replay) {
    if (selected_replay == nullptr) {
        return;

    Replay* replay = ReplayManager::Instance().GetReplay(selected_replay->text());
    if (replay == nullptr) {
        replay = new Replay(selected_replay->text(),
                            SettingsManager::Instance().GetSteamReplayPath()
                                                       .append("/" + selected_replay->text() + ".dem"),
                            false);
        ReplayManager::Instance().AddReplay(replay);
    }
    if (!replay->IsReplayParsed()) {
        replay->Parse();
    }
    qDebug() << replay->GetDemPath();

}
