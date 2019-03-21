#include "replay.h"

// Replay file stuff
Replay::Replay(QString game_id, QString dem_path = nullptr, bool replay_parsed = false)
{
    game_id_ = game_id;
    dem_path_ = dem_path;
    replay_parsed_ = replay_parsed;
}

bool Replay::HasReplayOnDisk() {
    return dem_path_ != nullptr;
}

QString Replay::GetGameId() {
    return game_id_;
}

QString Replay::GetDemPath() {
    return dem_path_;
}

bool Replay::IsReplayParsed() {
    return replay_parsed_;
}

// Load the replay file and parse the necessary information for the application
void Replay::Parse() {
    if (!HasReplayOnDisk()) return;

    // TODO: Decode protobuff

    replay_parsed_ = true;
}

// Replay info getters
