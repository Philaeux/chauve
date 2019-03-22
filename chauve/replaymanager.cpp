#include "replaymanager.h"
#include <map>

// Singleton constructor
ReplayManager::ReplayManager():
    QObject()
{

}

ReplayManager::~ReplayManager()
{

}

// Singleton instance
ReplayManager ReplayManager::instance_=ReplayManager();

ReplayManager& ReplayManager::Instance()
{
    return instance_;
}

Replay* ReplayManager::GetReplay(QString game_id) {
    QMap<QString, Replay*>::const_iterator i = replays_.find(game_id);
    if (i != replays_.end()) {
        return i.value();
    } else {
        return nullptr;
    }
}

void ReplayManager::AddReplay(Replay *replay) {
    replays_.insert(replay->GetGameId(), replay);
}
