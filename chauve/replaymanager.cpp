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
    if (replays_.count(game_id) > 0) {
        return replays_[game_id];
    } else {
        return nullptr;
    }
}

void ReplayManager::AddReplay(Replay *replay) {
    replays_[replay->GetGameId()] = replay;
}
