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
ReplayManager ReplayManager::instance_;

ReplayManager& ReplayManager::Instance()
{
    return instance_;
}

Replay* ReplayManager::GetReplay(uint64_t game_id) {
	auto it = replays_.find(game_id);
    if (it != replays_.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void ReplayManager::AddReplay(Replay *replay) {
    replays_.insert(std::pair<uint64_t, Replay*>(replay->GetGameId(), replay));
}
